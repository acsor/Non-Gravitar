cmake_minimum_required(VERSION 2.6)
project(Non-Gravitar)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -Wall)

set(DIR_SRC "src")
set(DIR_SHAPE "${DIR_SRC}/shape")
set(DIR_SHAPE_BUNDLE "${DIR_SRC}/shape-bundle")
set(DIR_VIEWS "${DIR_SRC}/view")
set(DIR_UTILS "${DIR_SRC}/utils")
set(DIR_BOUND "${DIR_SRC}/bounding-polygon")
set(DIR_SAMPLES "samples/")

# The project versionig scheme is Semver: https://semver.org/
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# TO-DO Add find_package directive for adding a dependency to the SFML library


include_directories("${DIR_SRC}")

add_library(Observer "${DIR_UTILS}/Observer.cpp")
add_library(Event "${DIR_UTILS}/Event.cpp")


add_library(BoundingPolygon "${DIR_BOUND}/BoundingPolygon.cpp")

add_library(BoundingTriangle "${DIR_BOUND}/BoundingTriangle.cpp")
target_link_libraries(BoundingTriangle BoundingPolygon)

add_library(BoundingRectangle "${DIR_BOUND}/BoundingRectangle.cpp")
target_link_libraries(BoundingRectangle BoundingPolygon)
add_library(Shape "${DIR_SHAPE}/Shape.cpp")


add_library(ShapeBundle "${DIR_SHAPE_BUNDLE}/ShapeBundle.cpp")
target_link_libraries(ShapeBundle Event Shape)

add_library(CollisionBundle "${DIR_SHAPE_BUNDLE}/CollisionBundle.cpp")
target_link_libraries(CollisionBundle ShapeBundle)



add_library(Point "${DIR_SHAPE}/Point.cpp")
target_link_libraries(Point Shape)

add_library(Line "${DIR_SHAPE}/Line.cpp")
target_link_libraries(Line Shape Point Rectangle)

add_library(Circle "${DIR_SHAPE}/Circle.cpp")
target_link_libraries(Circle Shape Rectangle)

add_library(Rectangle "${DIR_SHAPE}/Rectangle.cpp")
target_link_libraries(Rectangle Shape)


add_library(Spaceship "${DIR_SHAPE}/Spaceship.cpp")
target_link_libraries(Spaceship Shape Point Rectangle Fuel)

add_library(Fuel "${DIR_SHAPE}/Fuel.cpp")
target_link_libraries(Fuel Spaceship)

add_library(RoundMissile "${DIR_SHAPE}/RoundMissile.cpp")
target_link_libraries(RoundMissile Shape Circle)

add_library(Bunker "${DIR_SHAPE}/Bunker.cpp")
target_link_libraries(Bunker Shape RoundMissile)

add_library(Mountain "${DIR_SHAPE}/Mountain.cpp")
target_link_libraries(Mountain Shape)


add_library(Utils "${DIR_UTILS}/Utils.cpp")


add_library(ShapeView "${DIR_VIEWS}/ShapeView.cpp")
target_link_libraries(ShapeView Shape)

add_library(ShapeBundleView "${DIR_VIEWS}/ShapeBundleView.cpp")
target_link_libraries(
	ShapeBundleView Event Shape ShapeBundle BunkerView SpaceshipView
)

add_library(SpaceshipView "${DIR_VIEWS}/SpaceshipView.cpp")
target_link_libraries(SpaceshipView Spaceship ShapeView Utils)

add_library(BunkerView "${DIR_VIEWS}/BunkerView.cpp")
target_link_libraries(BunkerView Bunker ShapeView Utils)


add_executable(SFMLCollision "${DIR_SAMPLES}/SFMLCollision.cpp")
target_link_libraries(SFMLCollision sfml-window sfml-graphics sfml-system)

add_executable(SFMLOrigin "${DIR_SAMPLES}/SFMLOrigin.cpp")
target_link_libraries(SFMLOrigin sfml-window sfml-graphics sfml-system)

add_executable(NonGravitar "${DIR_SRC}/NonGravitar.cpp")
target_link_libraries(
	NonGravitar
	sfml-window sfml-graphics sfml-system
	ShapeBundle ShapeBundleView
)

add_subdirectory(test)
