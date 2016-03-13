cmake_minimum_required(VERSION 3.3)
project(swpattern_hw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -liconv")

set(SOURCE_FILES
     Main.cpp)

add_executable(search ${SOURCE_FILES})

add_library(ReadFileLibrary STATIC ReadingFileLib.cpp)
target_link_libraries(search ReadFileLibrary)