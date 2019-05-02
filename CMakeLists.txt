cmake_minimum_required(VERSION 2.8)

project(MES)

add_executable(MES "main.cpp"
                   "element.h"
                   "element.cpp"
                   "node.h"
                   "node.cpp"
                   "grid.h"
                   "grid.cpp")
