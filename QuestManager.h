//
// Created by sibirsky on 15.08.16.
//

#ifndef DREAMER_GIT_QUESTMANAGER_H
#define DREAMER_GIT_QUESTMANAGER_H


#include <stdint-gcc.h>
#include <string>
#include <vector>
#include "tinyxml2/tinyxml2.h"
#include "QuestPage.h"

class QuestManager {
public:
    void set_work_dir(const std::string& dir);
    std::string get_work_dir();
    void create_page(std::string page_name);

private:
    std::string work_dir_;
    std::string manifest_file_;
    std::vector<QuestPage> pages_;
};


#endif //DREAMER_GIT_QUESTMANAGER_H
