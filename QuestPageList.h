//
// Created by sibirsky on 15.08.16.
//

#ifndef DREAMER_GIT_QUESTPAGELIST_H
#define DREAMER_GIT_QUESTPAGELIST_H

#include <vector>
#include "QuestPage.h"

class QuestPageList {
public:
    void create_page(std::string page_name);
    //[] operator
private:
    std::vector<QuestPage> page_list_;
};


#endif //DREAMER_GIT_QUESTPAGELIST_H
