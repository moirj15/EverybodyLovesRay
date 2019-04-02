cmake_minimum_required(VERSION 3.14)
project(ray)
add_executable(
	ray
	main.cpp
	math.h
	common.h
)

if (WIN32)
	set(CMAKE_CXX_FLAGS "/std:c++17 /MP /GS /TP /W3 -D_CRT_SECURE_NO_WARNINGS")
	include_directories(
		D:/libraries/SDL2-2.0.9/include
		D:/libraries/glm
	)
	target_link_libraries(
		ray
		D:/libraries/SDL2-2.0.9/lib/x64/SDL2.lib
		D:/libraries/SDL2-2.0.9/lib/x64/SDL2main.lib
	)
else()
	set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -pedantic -Wno-missing-braces")
	set(CMAKE_EXE_LINKER_FLAGS "-lSDL2")
	target_link_libraries(
		ray
		SDL2
	)
endif()
