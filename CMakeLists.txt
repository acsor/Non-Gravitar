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
add_library(Plane "${DIR_SRC}/Plane.cpp")
add_library(PlaneTraits "${DIR_SRC}/PlaneTraits.cpp")
add_library(Trajectory "${DIR_SRC}/Trajectory.cpp")

add_library(PlaneObject "${DIR_SRC}/PlaneObject.cpp")
target_link_libraries(PlaneObject Plane)

add_library(Line "${DIR_SRC}/Line.cpp")
target_link_libraries(Line PlaneObject PlaneTraits)

add_library(Rectangle "${DIR_SRC}/Rectangle.cpp")
target_link_libraries(Rectangle PlaneObject PlaneTraits)

add_library(Spaceship "${DIR_SRC}/Spaceship.cpp")
target_link_libraries(Spaceship PlaneObject PlaneTraits)

add_library(Fuel "${DIR_SRC}/Fuel.cpp")
target_link_libraries(Fuel Spaceship)

add_library(Bunker "${DIR_SRC}/Bunker.cpp")
target_link_libraries(Bunker PlaneObject PlaneTraits Trajectory)

add_library(Utils "${DIR_SRC}/Utils.cpp")


add_subdirectory(test)
