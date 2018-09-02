#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "common.h"
#include "math.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	mat4 m1 = {{{5.0f, 0.0f, 2.0f, 5.0f},
				{0.0f, 1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 1.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, 7.0f}}}; 
	mat4 m2 = {{{5.0f, 0.0f, 0.0f, 1.0f},
				{0.0f, 1.0f, 1.0f, 0.0f},
				{0.0f, 1.0f, 1.0f, 0.0f},
				{1.0f, 0.0f, 0.0f, 1.0f}}};
	print_mat4(m1);
	printf("\n");
	print_mat4(m2);

	printf("\n");
	mat4 m3 = m1 * m2;
	print_mat4(m3);

	printf("\n");
	vec4 v1 = {1.0f, 1.0f, 1.0f, 1.0f};
	print_vec4(v1);

	vec4 v2 = m1 * v1;
	print_vec4(v2);
	
	return EXIT_SUCCESS;
}
