project(rayTracer)

add_executable(
	rayTracer
	main.cpp
	bmpIO.h
	bmpIO.cpp
	camera.h
	camera.cpp
	object.h
	object.cpp
#	world.h
#	world.cpp
	utils.h
	utils.cpp
	illumination.cpp
	illumination.h
	intersectData.cpp
	intersectData.h
	ray.h
	ray.cpp
)
if (WIN32)
    set(CMAKE_CXX_FLAGS "/std:c++17 /MP /GS /TP /W3 -D_CRT_SECURE_NO_WARNINGS")
    include_directories(
        D:/libraries/SDL2-2.0.9/include
        D:/libraries/glm
    )
    target_link_libraries(
        rayTracer
        D:/libraries/SDL2-2.0.9/lib/x64/SDL2.lib
        D:/libraries/SDL2-2.0.9/lib/x64/SDL2main.lib
    )
else()
    set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -pedantic -Wno-missing-braces")
    set(CMAKE_EXE_LINKER_FLAGS "-lSDL2")
    target_link_libraries(
        rayTracer
        SDL2
    )
endif()
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic")
#set(CMAKE_EXE_LINKER_FLAGES "-lSDL2 -lm")
#target_link_libraries(
#	rayTracer
#	SDL2
#    m
#)
