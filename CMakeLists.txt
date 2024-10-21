cmake_minimum_required(VERSION 3.29)
project(3semestr_1laboratory)

set(CMAKE_CXX_STANDARD 23)

add_executable(3semestr_1laboratory main.cpp
        shared_pointer.h
        unique_pointer.h
        pointer_tests.h
        pointer_tests.cpp
        test_structure.h
        progress_bar.h
        progress_bar.cpp
)
