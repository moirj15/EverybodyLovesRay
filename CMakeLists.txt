project(ray)
add_executable(
	ray
	main.cpp
	math.h
	common.h
)
set(CMAKE_C_FLAGS "-std=c++17 -Wall -Wextra -pedantic")
set(CMAKE_EXE_LINKER_FLAGS "-lSDL2 -lm")
target_link_libraries(
	ray
	SDL2
)
