cmake_minimum_required(VERSION 3.13...3.16 FATAL_ERROR)
project(usageExample VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(usageExample Src/main.cpp)
target_compile_features(usageExample PRIVATE cxx_auto_type)

find_package(LittleArgsParser 1.0 REQUIRED)
target_link_libraries(usageExample LittleArgsParser::LittleArgsParser)
