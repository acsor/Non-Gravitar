cmake_minimum_required(VERSION 2.6)
project(Non-Gravitar)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -Wall)

set(DIR_SRC "src")
set(DIR_MODELS "${DIR_SRC}/model")
set(DIR_VIEWS "${DIR_SRC}/view")
set(DIR_BOUND "${DIR_SRC}/BoundingPolygon")
set(DIR_SAMPLES "samples/")

# The project versionig scheme is Semver: https://semver.org/
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# TO-DO Add find_package directive for adding a dependency to the SFML library


include_directories("${DIR_SRC}")

add_library(Observer "${DIR_SRC}/Observer.cpp")
add_library(Event "${DIR_SRC}/Event.cpp")


add_library(BoundingPolygon "${DIR_BOUND}/BoundingPolygon.cpp")

add_library(BoundingTriangle "${DIR_BOUND}/BoundingTriangle.cpp")
target_link_libraries(BoundingTriangle BoundingPolygon)
add_library(Shape "${DIR_MODELS}/Shape.cpp")


add_library(ShapeBundle "${DIR_MODELS}/ShapeBundle.cpp")
target_link_libraries(ShapeBundle Event Shape)

add_library(DummyBundle "${DIR_MODELS}/DummyBundle.cpp")
target_link_libraries(DummyBundle ShapeBundle)


add_library(Point "${DIR_MODELS}/Point.cpp")
target_link_libraries(Point Shape)

add_library(Line "${DIR_MODELS}/Line.cpp")
target_link_libraries(Line Shape Point Rectangle)

add_library(Circle "${DIR_MODELS}/Circle.cpp")
target_link_libraries(Circle Shape Rectangle)

add_library(Rectangle "${DIR_MODELS}/Rectangle.cpp")
target_link_libraries(Rectangle Shape)


add_library(Spaceship "${DIR_MODELS}/Spaceship.cpp")
target_link_libraries(Spaceship Shape Point Rectangle Fuel)

add_library(Fuel "${DIR_MODELS}/Fuel.cpp")
target_link_libraries(Fuel Spaceship)

add_library(RoundMissile "${DIR_MODELS}/RoundMissile.cpp")
target_link_libraries(RoundMissile Shape Circle)

add_library(Bunker "${DIR_MODELS}/Bunker.cpp")
target_link_libraries(Bunker Shape RoundMissile)


add_library(Utils "${DIR_SRC}/Utils.cpp")


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
	ShapeBundle DummyBundle ShapeBundleView
)

add_subdirectory(test)
