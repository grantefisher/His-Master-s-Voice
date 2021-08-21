
#pragma once

#include <SDL.h>

enum grid_square_type
{
	lava,
	rock,
	door
};

struct grid_square
{
	bool walkable = true;
	bool deadly = false;
	SDL_Texture* texture = NULL;
	SDL_Rect rect = { 0, 0, 0, 0, 0 };
	int animation_state = 0;
	int alpha = 255;
	grid_square_type square_type = grid_square_type::rock;
};
