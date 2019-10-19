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

add_library(ClosedShape "${DIR_SHAPE}/ClosedShape.cpp")
target_link_libraries(ClosedShape Shape)

add_library(Polyline "${DIR_SHAPE}/Polyline.cpp")
target_link_libraries(Polyline Shape)

add_library(MountainChain "${DIR_SHAPE}/MountainChain.cpp")
target_link_libraries(MountainChain Polyline)

add_library(Circle "${DIR_SHAPE}/Circle.cpp")
target_link_libraries(Circle ClosedShape Rectangle)

add_library(CRPolygon "${DIR_SHAPE}/CRPolygon.cpp")
target_link_libraries(CRPolygon ClosedShape BoundingPolygon)

add_library(Planet "${DIR_SHAPE}/Planet.cpp")
target_link_libraries(Planet CRPolygon)

add_library(Rectangle "${DIR_SHAPE}/Rectangle.cpp")
target_link_libraries(Rectangle ClosedShape BoundingPolygon)

add_library(Spaceship "${DIR_SHAPE}/Spaceship.cpp")
target_link_libraries(Spaceship Fuel BoundingPolygon)

add_library(SpawnArea "${DIR_SHAPE}/SpawnArea.cpp")
target_link_libraries(SpawnArea CRPolygon)

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

add_library(GridShapeLayout "${DIR_SHAPE_GROUP}/GridShapeLayout.cpp")
target_link_libraries(GridShapeLayout Shape)

add_library(RoundShapeLayout "${DIR_SHAPE_GROUP}/RoundShapeLayout.cpp")
target_link_libraries(RoundShapeLayout Shape)

add_library(CollisionGroup "${DIR_SHAPE_GROUP}/CollisionGroup.cpp")
target_link_libraries(CollisionGroup ShapeGroup)

add_library(PlanetBuilder "${DIR_SHAPE_GROUP}/PlanetBuilder.cpp")
target_link_libraries(PlanetBuilder Planet PlanetSurface MountainChain)

add_library(SolarSystem "${DIR_SHAPE_GROUP}/SolarSystem.cpp")
target_link_libraries(SolarSystem PlanetSurface SpawnArea)

add_library(PlanetSurface "${DIR_SHAPE_GROUP}/PlanetSurface.cpp")
target_link_libraries(PlanetSurface Planet CollisionGroup)


# Shape views section
add_library(GraphicAssets "${DIR_VIEWS}/GraphicAssets.cpp")
target_link_libraries(GraphicAssets Utils)

add_library(DebuggableView "${DIR_VIEWS}/DebuggableView.cpp")

add_library(ShapeView "${DIR_VIEWS}/ShapeView.cpp")
target_link_libraries(ShapeView Shape DebuggableView GraphicAssets)

add_library(ClosedShapeView "${DIR_VIEWS}/ClosedShapeView.cpp")
target_link_libraries(ClosedShapeView ClosedShape ShapeView)

add_library(PlanetView "${DIR_VIEWS}/PlanetView.cpp")
target_link_libraries(PlanetView Planet ClosedShapeView)

add_library(PolylineView "${DIR_VIEWS}/PolylineView.cpp")
target_link_libraries(PolylineView Polyline ShapeView)

add_library(RoundMissileView "${DIR_VIEWS}/RoundMissileView.cpp")
target_link_libraries(RoundMissileView RoundMissile ClosedShapeView)

add_library(FuelView "${DIR_VIEWS}/FuelView.cpp")
target_link_libraries(FuelView Fuel ClosedShapeView)

add_library(BunkerView "${DIR_VIEWS}/BunkerView.cpp")
target_link_libraries(BunkerView Bunker ClosedShapeView Utils)

add_library(ShapeGroupView "${DIR_VIEWS}/ShapeGroupView.cpp")
target_link_libraries(ShapeGroupView ShapeGroup ShapeViewFactory)

add_library(TractorBeamView "${DIR_VIEWS}/TractorBeamView.cpp")
target_link_libraries(TractorBeamView TractorBeam ClosedShapeView)

add_library(ShapeViewFactory "${DIR_VIEWS}/ShapeViewFactory.cpp")
target_link_libraries(
		ShapeViewFactory BunkerView FuelView PolylineView
		PlanetView RoundMissileView SpaceshipView SpawnAreaView TractorBeamView
)

add_library(SpaceshipView "${DIR_VIEWS}/SpaceshipView.cpp")
target_link_libraries(SpaceshipView Spaceship ClosedShapeView Utils)

add_library(SpawnAreaView "${DIR_VIEWS}/SpawnAreaView.cpp")
target_link_libraries(SpawnAreaView SpawnArea ClosedShapeView)

add_library(GameInfoView "${DIR_VIEWS}/GameInfoView.cpp")
target_link_libraries(GameInfoView GameInfo SpaceshipView)


# Game and scenes section
add_library(Game "${DIR_CONTROL}/Game.cpp")
target_link_libraries(
		Game SceneFrame MoveShipCallback GameInfoView SolarSystemScene
		SolarSystemSceneBuilder
)

add_library(MoveShipCallback "${DIR_CONTROL}/MoveShipCallback.cpp")
target_link_libraries(MoveShipCallback Game)

add_library(SceneFrame "${DIR_CONTROL}/SceneFrame.cpp")
target_link_libraries(SceneFrame Game Spaceship)

add_library(GameInfo "${DIR_CONTROL}/GameInfo.cpp")
target_link_libraries(GameInfo SpaceshipView)

add_library(Scene "${DIR_CONTROL}/Scene.cpp")
target_link_libraries(Scene ShapeGroup ShapeGroupView)

add_library(SolarSystemScene "${DIR_CONTROL}/SolarSystemScene.cpp")
target_link_libraries(
	SolarSystemScene SolarSystem SolarSystemSceneBuilder PlanetSurfaceScene
)

add_library(PlanetSurfaceScene "${DIR_CONTROL}/PlanetSurfaceScene.cpp")
target_link_libraries(PlanetSurfaceScene Scene PlanetSurface MountainChain)

add_library(SolarSystemSceneBuilder "${DIR_CONTROL}/SolarSystemSceneBuilder.cpp")
target_link_libraries(
		SolarSystemSceneBuilder SolarSystem PlanetBuilder RoundShapeLayout
)


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
