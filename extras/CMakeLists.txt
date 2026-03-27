cmake_minimum_required(VERSION 3.25)

project(main)

add_executable(${PROJECT_NAME} main.cpp)

add_library(my_lib STATIC include/my_proj/utils.hpp)

target_link_libraries(${} PRIVATE plog::plog)


