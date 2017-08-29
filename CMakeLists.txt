cmake_minimum_required(VERSION 3.8)
project(metaquotes)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/main.cpp
        src/ILogReader.h
        src/CLogReader.cpp
        src/CLogReader.h)

add_executable(metaquotes ${SOURCE_FILES})