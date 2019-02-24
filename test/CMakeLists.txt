# TO-DO Make executable output name end in `.out'
# TO-DO Find a shorter way of specifying `test-all' dependencies
add_executable(
	test-all
	$<TARGET_OBJECTS:test-main>
	$<TARGET_OBJECTS:test-observer>
	$<TARGET_OBJECTS:test-rectangle>
	$<TARGET_OBJECTS:test-line>
	$<TARGET_OBJECTS:test-point>
)
target_link_libraries(test-all Rectangle Line Observer)

add_library(test-main OBJECT test-main.cpp)
add_library(test-line OBJECT test-line.cpp)
add_library(test-point OBJECT test-point.cpp)
add_library(test-rectangle OBJECT test-rectangle.cpp)
add_library(test-observer OBJECT test-observer.cpp)
