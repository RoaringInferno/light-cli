cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(light-cli)

add_library(light-cli STATIC)
file(GLOB_RECURSE LIGHT_CLI_SOURCES src/*.cpp)
target_sources(light-cli PRIVATE ${LIGHT_CLI_SOURCES} include/light-cli)
target_include_directories(light-cli PUBLIC include)
target_include_directories(light-cli PRIVATE include/light-cli-bits/)

add_executable(light-cli-test test/main.cpp)
target_link_libraries(light-cli-test light-cli)