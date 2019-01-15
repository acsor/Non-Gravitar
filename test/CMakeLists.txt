# TO-DO Make executable output name end in `.out'
add_executable(
	test-all
	$<TARGET_OBJECTS:test-main> $<TARGET_OBJECTS:test-observer>
)
target_link_libraries(test-all Observer)

add_library(test-main OBJECT test-main.cpp)
add_library(test-observer OBJECT test-observer.cpp)
