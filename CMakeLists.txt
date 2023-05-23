cmake_minimum_required(VERSION 3.24)
project(lab5_dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab5_dsa
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h
        SortedIndexedList.cpp
        SortedIndexedList.h)
