cmake_minimum_required(VERSION 2.6)
project(Non-Gravitar)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -Wall)

set(DIR_SRC "src")
set(DIR_SHAPE "${DIR_SRC}/shape")
set(DIR_SHAPE_GROUP "${DIR_SRC}/shape-group")
set(DIR_VIEWS "${DIR_SRC}/view")
set(DIR_UTILS "${DIR_SRC}/utils")
set(DIR_BOUND "${DIR_SRC}/bounding-polygon")
set(DIR_SAMPLES "samples/")

# The project versionig scheme is Semver: https://semver.org/
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# TODO Add find_package directive for adding a dependency to the SFML library


include_directories("${DIR_SRC}")


add_library(Observer "${DIR_UTILS}/Observer.cpp")
add_library(Utils "${DIR_UTILS}/Utils.cpp")


# Bounding polygon section
add_library(BoundingPolygon "${DIR_BOUND}/BoundingPolygon.cpp")

add_library(BoundingTriangle "${DIR_BOUND}/BoundingTriangle.cpp")
target_link_libraries(BoundingTriangle BoundingPolygon)

add_library(BoundingRectangle "${DIR_BOUND}/BoundingRectangle.cpp")
target_link_libraries(BoundingRectangle BoundingPolygon)


# Shapes section
add_library(Shape "${DIR_SHAPE}/Shape.cpp")

add_library(Polyline "${DIR_SHAPE}/Polyline.cpp")
target_link_libraries(Polyline Shape)

add_library(ShapeGroup "${DIR_SHAPE_GROUP}/ShapeGroup.cpp")
target_link_libraries(ShapeGroup Shape)

add_library(CollisionGroup "${DIR_SHAPE_GROUP}/CollisionGroup.cpp")
target_link_libraries(CollisionGroup ShapeGroup)

add_library(Circle "${DIR_SHAPE}/Circle.cpp")
target_link_libraries(Circle Shape Rectangle)

add_library(Rectangle "${DIR_SHAPE}/Rectangle.cpp")
target_link_libraries(Rectangle Shape BoundingRectangle)

add_library(Spaceship "${DIR_SHAPE}/Spaceship.cpp")
target_link_libraries(Spaceship Fuel BoundingTriangle)

add_library(Fuel "${DIR_SHAPE}/Fuel.cpp")
target_link_libraries(Fuel Spaceship BoundingRectangle)

add_library(RoundMissile "${DIR_SHAPE}/RoundMissile.cpp")
target_link_libraries(RoundMissile Circle)

add_library(Bunker "${DIR_SHAPE}/Bunker.cpp")
target_link_libraries(Bunker RoundMissile)

add_library(Mountain "${DIR_SHAPE}/Mountain.cpp")
target_link_libraries(Mountain Shape)


# Shape views section
add_library(ShapeView "${DIR_VIEWS}/ShapeView.cpp")
target_link_libraries(ShapeView Shape)

add_library(Shape2DView "${DIR_VIEWS}/Shape2DView.cpp")
target_link_libraries(Shape2DView ShapeView)

add_library(BunkerView "${DIR_VIEWS}/BunkerView.cpp")
target_link_libraries(BunkerView Bunker Shape2DView Utils)

add_library(MountainView "${DIR_VIEWS}/MountainView.cpp")
target_link_libraries(MountainView Mountain Shape2DView Utils)

add_library(ShapeGroupView "${DIR_VIEWS}/ShapeGroupView.cpp")
target_link_libraries(ShapeGroupView ShapeGroup ShapeViewFactory)

add_library(ShapeViewFactory "${DIR_VIEWS}/ShapeViewFactory.cpp")
target_link_libraries(ShapeViewFactory SpaceshipView BunkerView MountainView)

add_library(SpaceshipView "${DIR_VIEWS}/SpaceshipView.cpp")
target_link_libraries(SpaceshipView Spaceship Shape2DView Utils)


# Samples section
add_executable(SFMLCollision "${DIR_SAMPLES}/SFMLCollision.cpp")
target_link_libraries(SFMLCollision sfml-window sfml-graphics sfml-system)

add_executable(SFMLOrigin "${DIR_SAMPLES}/SFMLOrigin.cpp")
target_link_libraries(SFMLOrigin sfml-window sfml-graphics sfml-system)


# Final executable section
add_executable(NonGravitar "${DIR_SRC}/NonGravitar.cpp")
target_link_libraries(
	NonGravitar
	sfml-window sfml-graphics sfml-system
	ShapeGroup ShapeGroupView
)


add_subdirectory(test)
