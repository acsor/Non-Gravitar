cmake_minimum_required(VERSION 2.6)
project(Non-Gravitar)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -Wall)
set(DIR_SRC "src/")

# The project versionig scheme is Semver: https://semver.org/
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# TO-DO Add find_package directive for adding a dependency to the SFML library


include_directories("${DIR_SRC}")
add_library(Observer "${DIR_SRC}/Observer.cpp")


add_subdirectory(test)
