cmake_minimum_required(VERSION 3.5)
project(Dreamer_git)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lz")

set(SOURCE_FILES main.cpp QuestManager.cpp QuestManager.h QuestPage.cpp QuestPage.h QuestPageList.cpp QuestPageList.h)
add_executable(Dreamer_git ${SOURCE_FILES})
target_link_libraries(Dreamer_git "${CMAKE_SOURCE_DIR}//tinyxml2/libtinyxml2.a")