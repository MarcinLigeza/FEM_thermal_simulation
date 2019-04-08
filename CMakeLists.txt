cmake_minimum_required(VERSION 2.8)

project(MES)


find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(MES "main.cpp"
                   "element.h"
                   "element.cpp"
                   "node.h"
                   "node.cpp"
                   "grid.h"
                   "grid.cpp")

target_link_libraries (MES Eigen3::Eigen)
