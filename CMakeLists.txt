cmake_minimum_required(VERSION 3.24)
project(CPP)

set(CMAKE_CXX_STANDARD 20)

#add_executable(CPP main.cpp)
add_executable(CPP main.c main.c AdptArray.c book.c)
