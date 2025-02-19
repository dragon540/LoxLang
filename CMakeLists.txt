cmake_minimum_required(VERSION 3.30)
project(LoxLang)

set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(lib)

add_executable(LoxLang main.cpp)

target_link_libraries(LoxLang PUBLIC LoxLangLib)
