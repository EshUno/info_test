cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(reader)

set(SOURCES main.cpp)

add_executable("${PROJECT_NAME}" "${SOURCES}")

target_include_directories(${PROJECT_NAME} PUBLIC ..)

