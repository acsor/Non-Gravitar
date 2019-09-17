cmake_minimum_required(VERSION 2.6)
project(Non-Gravitar)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -Wall)

set(DIR_SRC "src")
set(DIR_SHAPE "${DIR_SRC}/shape")
set(DIR_SHAPE_GROUP "${DIR_SRC}/shape-group")
set(DIR_VIEWS "${DIR_SRC}/view")
set(DIR_CONTROL "${DIR_SRC}/control")
set(DIR_UTILS "${DIR_SRC}/utils")
set(DIR_SAMPLES "samples/")

# The project versionig scheme is Semver: https://semver.org/
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# TODO Add find_package directive for adding a dependency to the SFML library


include_directories("${DIR_SRC}")


# Utils section
add_library(Observer "${DIR_UTILS}/Observer.cpp")
add_library(Utils "${DIR_UTILS}/Utils.cpp")


# Bounding polygon section
add_library(BoundingPolygon "${DIR_UTILS}/BoundingPolygon.cpp")


# Shapes section
add_library(Shape "${DIR_SHAPE}/Shape.cpp")

add_library(Polyline "${DIR_SHAPE}/Polyline.cpp")
target_link_libraries(Polyline Shape)

add_library(MountainChain "${DIR_SHAPE}/MountainChain.cpp")
target_link_libraries(MountainChain Polyline)

add_library(Circle "${DIR_SHAPE}/Circle.cpp")
target_link_libraries(Circle Shape Rectangle)

add_library(Planet "${DIR_SHAPE}/Planet.cpp")
target_link_libraries(Planet Circle)

add_library(Rectangle "${DIR_SHAPE}/Rectangle.cpp")
target_link_libraries(Rectangle Shape BoundingPolygon)

add_library(Spaceship "${DIR_SHAPE}/Spaceship.cpp")
target_link_libraries(Spaceship Fuel BoundingPolygon)

add_library(Fuel "${DIR_SHAPE}/Fuel.cpp")
target_link_libraries(Fuel Spaceship BoundingPolygon)

add_library(RoundMissile "${DIR_SHAPE}/RoundMissile.cpp")
target_link_libraries(RoundMissile Circle)

add_library(Bunker "${DIR_SHAPE}/Bunker.cpp")
target_link_libraries(Bunker RoundMissile)

add_library(TractorBeam "${DIR_SHAPE}/TractorBeam.cpp")
target_link_libraries(TractorBeam Spaceship)


# Shape group section
add_library(ShapeGroup "${DIR_SHAPE_GROUP}/ShapeGroup.cpp")
target_link_libraries(ShapeGroup Shape)

add_library(CollisionGroup "${DIR_SHAPE_GROUP}/CollisionGroup.cpp")
target_link_libraries(CollisionGroup ShapeGroup)

add_library(SolarSystem "${DIR_SHAPE_GROUP}/SolarSystem.cpp")
target_link_libraries(SolarSystem PlanetSurface)

add_library(PlanetSurface "${DIR_SHAPE_GROUP}/PlanetSurface.cpp")
target_link_libraries(PlanetSurface Planet CollisionGroup)


# Shape views section
add_library(DebuggableView "${DIR_VIEWS}/DebuggableView.cpp")

add_library(ShapeView "${DIR_VIEWS}/ShapeView.cpp")
target_link_libraries(ShapeView Shape DebuggableView)

add_library(Shape2DView "${DIR_VIEWS}/Shape2DView.cpp")
target_link_libraries(Shape2DView ShapeView)

add_library(PlanetView "${DIR_VIEWS}/PlanetView.cpp")
target_link_libraries(PlanetView Planet Shape2DView)

add_library(PolylineView "${DIR_VIEWS}/PolylineView.cpp")
target_link_libraries(PolylineView Polyline ShapeView)

add_library(RoundMissileView "${DIR_VIEWS}/RoundMissileView.cpp")
target_link_libraries(RoundMissileView RoundMissile Shape2DView)

add_library(FuelView "${DIR_VIEWS}/FuelView.cpp")
target_link_libraries(FuelView Fuel Shape2DView)

add_library(BunkerView "${DIR_VIEWS}/BunkerView.cpp")
target_link_libraries(BunkerView Bunker Shape2DView Utils)

add_library(ShapeGroupView "${DIR_VIEWS}/ShapeGroupView.cpp")
target_link_libraries(ShapeGroupView ShapeGroup ShapeViewFactory)

add_library(ShapeViewFactory "${DIR_VIEWS}/ShapeViewFactory.cpp")
target_link_libraries(
		ShapeViewFactory SpaceshipView BunkerView FuelView PolylineView
		PlanetView RoundMissileView
)

add_library(SpaceshipView "${DIR_VIEWS}/SpaceshipView.cpp")
target_link_libraries(SpaceshipView Spaceship Shape2DView Utils)

add_library(GameInfoView "${DIR_VIEWS}/GameInfoView.cpp")
target_link_libraries(GameInfoView GameInfo SpaceshipView)


# Game and scenes section
add_library(Game "${DIR_CONTROL}/Game.cpp")
target_link_libraries(Game Spaceship GameInfoView SolarSystemScene)

add_library(GameInfo "${DIR_CONTROL}/GameInfo.cpp")
target_link_libraries(GameInfo SpaceshipView)

add_library(Scene "${DIR_CONTROL}/Scene.cpp")
target_link_libraries(Scene ShapeGroup ShapeGroupView)

add_library(SolarSystemScene "${DIR_CONTROL}/SolarSystemScene.cpp")
target_link_libraries(SolarSystemScene SolarSystem PlanetSurfaceScene)

add_library(PlanetSurfaceScene "${DIR_CONTROL}/PlanetSurfaceScene.cpp")
target_link_libraries(PlanetSurfaceScene Scene PlanetSurface MountainChain)


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
	Game
)


add_subdirectory(test)
