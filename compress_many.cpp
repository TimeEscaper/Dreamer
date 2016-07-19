#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <cassert>

#include <zlib.h>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384
#define NAME_SIZE 160
#define NAME_LENGTH 20

int compress_single_file(const char* source_path, const char* dest_path)
{
    FILE *source = fopen(source_path, "rb");
    FILE *dest = fopen(dest_path, "wb");

    if ((source == NULL) || (dest == NULL))
        return -1;

    int res_code;
    int flush;
    int compression_level = 9;
    unsigned have;
    z_stream stream;
    unsigned char input[CHUNK];
    unsigned char output[CHUNK];

    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    res_code = deflateInit(&stream, compression_level);
    if (res_code != Z_OK)
        return res_code;

    do
    {
        stream.avail_in = fread(input, 1, CHUNK, source);
        if (ferror(source))
        {
            (void)deflateEnd(&stream);
            fclose(source);
            fclose(dest);

            return Z_ERRNO;
        }

        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        stream.next_in = input;

        do{
            stream.avail_out = CHUNK;
            stream.next_out = output;

            res_code = deflate(&stream, flush);
            assert(res_code != Z_STREAM_ERROR);

            have = CHUNK - stream.avail_out;
            if ((fwrite(output, 1, have, dest) != have) || (ferror(dest)))
            {
                (void)deflateEnd(&stream);
                fclose(source);
                fclose(dest);

                return Z_ERRNO;
            }
        } while (stream.avail_out == 0);
        assert(stream.avail_in == 0);

    } while (flush != Z_FINISH);
    assert(res_code == Z_STREAM_END);

    (void)deflateEnd(&stream);
    fclose(source);
    fclose(dest);

    return Z_OK;
}

bool compress()
{
    int res_code;

    res_code = compress_single_file("./data/manifest.xml", "./data/manifest.cxml");
    if (res_code != Z_OK)
        return false;
    res_code - compress_single_file("./data/page_example.xml", "./data/page_example.cxml");
    if (res_code != Z_OK)
        return false;

    FILE *dest = fopen("./data/quest.dqf", "wb");
    if (dest == NULL)
        return false;
    FILE *file_1 = fopen("./data/manifest.cxml", "rb");
    if (file_1 == NULL)
        return false;

    const char file_name[NAME_LENGTH] = "manifest.cxml";

    size_t written = fwrite(file_name, 1, NAME_SIZE, dest);
    std::cout << written << std::endl;

    fclose(dest);

    return true;
}

void decompress()
{
    FILE *source = fopen("./data/quest.dqf", "rb");
    char file_name[NAME_LENGTH];

    fread(file_name, 1, NAME_SIZE, source);
    fclose(source);

    std::cout << file_name << std::endl;
}

int main()
{
    decompress();
    //bool result = compress();
    //std::cout << result << std::endl;

    return 0;
}
