// ====================================
//  Grant Fisher 2021
// ==================================== 

#include "masters_render.h"

#include <stdio.h>

extern  void BASE_RENDER(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* rectangle)
{
	if (SDL_RenderCopy(renderer, texture, NULL, rectangle))
	{
		printf("ERROR RENDERING: %s\n", SDL_GetError());
	}
}

extern  void GRID_RENDER(SDL_Renderer* renderer, grid_square** GRID, int rows, int columns)
{
	int square_count = rows * columns;
	for (int i = 0; i < square_count; i++)
	{
			BASE_RENDER(renderer, GRID[i]->texture, &GRID[i]->rect);
	}
}