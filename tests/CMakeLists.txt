cmake_minimum_required(VERSION 4.3.2)
project(DatabaseTest VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
    ../src/pager.cpp
    test_main.cpp
    test_pager.cpp
)

include_directories("../include")
