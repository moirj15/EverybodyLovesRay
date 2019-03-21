project(ray)
add_executable(
	ray
	main.cpp
	math.h
	common.h
)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -pedantic -Wno-missing-braces")
set(CMAKE_EXE_LINKER_FLAGS "-lSDL2")
target_link_libraries(
	ray
	SDL2
)
