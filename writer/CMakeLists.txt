cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(writer)

set(SOURCES writer.cpp sharedbuf.cpp sharedbuf.h)
add_executable("${PROJECT_NAME}" "${SOURCES}")
target_include_directories(${PROJECT_NAME} PUBLIC ..)
target_link_libraries("${PROJECT_NAME}" pthread)
