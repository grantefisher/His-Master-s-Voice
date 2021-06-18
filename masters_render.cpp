#include "masters_render.h"

#include <stdio.h>


inline void BASE_RENDER(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* rectangle)
{
	if (SDL_RenderCopy(renderer, texture, NULL, rectangle))
	{
		printf("ERROR RENDERING: %s\n", SDL_GetError());
	}
}