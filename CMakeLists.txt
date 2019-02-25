cmake_minimum_required(VERSION 2.6)
project(Non-Gravitar)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -Wall)
set(DIR_SRC "src/")
set(DIR_SAMPLES "samples/")

# The project versionig scheme is Semver: https://semver.org/
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# TO-DO Add find_package directive for adding a dependency to the SFML library


include_directories("${DIR_SRC}")

add_library(Observer "${DIR_SRC}/Observer.cpp")
add_library(Plane "${DIR_SRC}/Plane.cpp")

add_library(PlaneObject "${DIR_SRC}/PlaneObject.cpp")
target_link_libraries(PlaneObject Plane)

add_library(Point "${DIR_SRC}/Point.cpp")
target_link_libraries(Point PlaneObject)

add_library(Line "${DIR_SRC}/Line.cpp")
target_link_libraries(Line PlaneObject Point Rectangle)

add_library(Circle "${DIR_SRC}/Circle.cpp")
target_link_libraries(Circle PlaneObject Rectangle)

add_library(Vector "${DIR_SRC}/Vector.cpp")

add_library(Rectangle "${DIR_SRC}/Rectangle.cpp")
target_link_libraries(Rectangle PlaneObject)

add_library(Spaceship "${DIR_SRC}/Spaceship.cpp")
target_link_libraries(Spaceship PlaneObject)

add_library(Fuel "${DIR_SRC}/Fuel.cpp")
target_link_libraries(Fuel Spaceship)

add_library(Bunker "${DIR_SRC}/Bunker.cpp")
target_link_libraries(Bunker PlaneObject Vector)

add_library(Utils "${DIR_SRC}/Utils.cpp")


add_executable(SFMLCollision "${DIR_SAMPLES}/SFMLCollision.cpp")
target_link_libraries(SFMLCollision sfml-window sfml-graphics sfml-system)

add_subdirectory(test)
