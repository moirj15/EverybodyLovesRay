#include "bmpIO.h"
#include <SDL2/SDL.h>


/**
 * Converts a vec4 containing color data to a u32 with the same color data.
 *
 * @param color: The vector with the color data.
 * @return: The color data as a u32.
 */
u32 vec4_to_u32(const glm::vec4 color) {
	u8 red = (u8) (255.0 * color.r);
	u8 green = (u8) (255.0 * color.g);
	u8 blue = (u8) (255.0 * color.b);

	return (0xff << 24) | (blue << 16) | (green << 8) | red;
}

/**
 * Writes a bmp file out to the given file name.
 *
 * @param file: The file that will be written out.
 * @param data: The color data that will be stored in the file.
 * @param size: The size of data.
 */
void writeBMP(const char *file, ScreenBuffer *screenBuffer)  {
	u32 rmask = 0x000000ff;
	u32 gmask = 0x0000ff00;
	u32 bmask = 0x00ff0000;
	u32 amask = 0xff000000;
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void *)screenBuffer->buffer, screenBuffer->width,
                            screenBuffer->height, 32, screenBuffer->width * 4, rmask, gmask, bmask, amask);

	SDL_SaveBMP(surface, file);
	SDL_FreeSurface(surface);
}
