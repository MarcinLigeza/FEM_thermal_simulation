cmake_minimum_required(VERSION 2.8)

project(MES)

add_executable(MES "main.cpp"
                   "element.h"
                   "element.cpp"
                   "node.h"
                   "node.cpp"
                   "grid.h"
                   "grid.cpp"
                   "controller.h"
                   "controller.cpp"
                   "view.h"
                   "view.cpp")


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED COMPONENTS
                                   network
                                   audio
                                   graphics
                                   window
                                   system)
target_link_libraries(MES ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
if(SFML_FOUND)
 include_directories(${SFML_INCLUDE_DIR})
 target_link_libraries(MES ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
