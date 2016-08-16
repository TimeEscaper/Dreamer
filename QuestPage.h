//
// Created by sibirsky on 15.08.16.
//

#ifndef DREAMER_GIT_QUESTPAGE_H
#define DREAMER_GIT_QUESTPAGE_H

#include <string>

class QuestPage {
public:
    QuestPage();
    void set_page_file(const std::string& file_name);
    std::string get_page_file();
    void set_text(const std::string& text);
    std::string get_text();
    void set_image(const std::string& image_file_name);
    std::string get_image();
private:
    std::string page_file_;

};


#endif //DREAMER_GIT_QUESTPAGE_H
