cmake_minimum_required(VERSION 3.16)
project(CS380C C)

set(CMAKE_C_STANDARD 11)

add_executable(CS380C main.c heapqueue.c)
add_executable(CS380C2 primefinder.c)