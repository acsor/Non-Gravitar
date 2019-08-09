# TODO Make executable output name end in `.out'
# TODO Find a shorter way of specifying `test-all' dependencies
add_executable(
	test-all
	$<TARGET_OBJECTS:test-main>
	$<TARGET_OBJECTS:test-bounding-polygon>
	$<TARGET_OBJECTS:test-circle>
	$<TARGET_OBJECTS:test-rectangle>
	$<TARGET_OBJECTS:test-vector>

	$<TARGET_OBJECTS:test-bunker>

	$<TARGET_OBJECTS:test-observer>
	$<TARGET_OBJECTS:test-event>
	$<TARGET_OBJECTS:test-utils>
)
target_link_libraries(
	test-all
	Rectangle Circle Bunker RoundMissile
	BoundingPolygon BoundingTriangle BoundingRectangle
	Observer Utils
)

add_library(test-main OBJECT test-main.cpp)

add_library(test-bounding-polygon OBJECT test-bounding-polygon.cpp)
add_library(test-circle OBJECT test-circle.cpp)
add_library(test-rectangle OBJECT test-rectangle.cpp)
add_library(test-vector OBJECT test-vector.cpp)

add_library(test-bunker OBJECT test-bunker.cpp)

add_library(test-observer OBJECT test-observer.cpp)
add_library(test-event OBJECT test-event.cpp)
add_library(test-utils OBJECT test-utils.cpp)
