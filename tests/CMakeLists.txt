cmake_minimum_required(VERSION 4.3.2)
project(DatabaseTest VERSION 0.2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} 
    ../src/pager.cpp
    ../src/records.cpp
    test_main.cpp
    test_pager.cpp
    test_records.cpp
    test.h
)

include_directories("../include")
