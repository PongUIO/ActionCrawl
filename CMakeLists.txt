CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(ActionCrawl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_SOURCE_DIR}/cmake/Utils/")

find_package(OGRE REQUIRED)

add_definitions(-std=gnu++0x -Wall)
include_directories(${OGRE_INCLUDE_DIRS})
include_directories(src/)
