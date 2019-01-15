cmake_minimum_required(VERSION 2.6)
project(Non-Gravitar)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)


add_library(Observer Observer.cpp)


add_subdirectory(test)
