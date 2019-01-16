# TO-DO Make executable output name end in `.out'
add_executable(
	test-all
	$<TARGET_OBJECTS:test-main>
	$<TARGET_OBJECTS:test-observer>
	$<TARGET_OBJECTS:test-entities>
)
target_link_libraries(test-all Observer Entities)

add_library(test-main OBJECT test-main.cpp)
add_library(test-observer OBJECT test-observer.cpp)
add_library(test-entities OBJECT test-entities.cpp)
