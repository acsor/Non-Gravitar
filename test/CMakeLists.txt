add_executable(
	test-all
	$<TARGET_OBJECTS:test-main>

	$<TARGET_OBJECTS:test-bounding-polygon>

    $<TARGET_OBJECTS:test-bunker>
	$<TARGET_OBJECTS:test-circle>
	$<TARGET_OBJECTS:test-rectangle>

    $<TARGET_OBJECTS:test-algraph>
	$<TARGET_OBJECTS:test-event>
    $<TARGET_OBJECTS:test-observer>
	$<TARGET_OBJECTS:test-random>
	$<TARGET_OBJECTS:test-utils>
    $<TARGET_OBJECTS:test-vector>
)
target_link_libraries(
	test-all
	Rectangle Circle Bunker RoundMissile
	BoundingPolygon
	Observer Utils
)

add_library(test-main OBJECT test-main.cpp)

add_library(test-bounding-polygon OBJECT test-bounding-polygon.cpp)

# Shapes tests
add_library(test-bunker OBJECT test-bunker.cpp)
add_library(test-circle OBJECT test-circle.cpp)
add_library(test-rectangle OBJECT test-rectangle.cpp)

# Utils tests
add_library(test-algraph OBJECT test-algraph.cpp)
add_library(test-event OBJECT test-event.cpp)
add_library(test-observer OBJECT test-observer.cpp)
add_library(test-random OBJECT test-random.cpp)
add_library(test-utils OBJECT test-utils.cpp)
add_library(test-vector OBJECT test-vector.cpp)
