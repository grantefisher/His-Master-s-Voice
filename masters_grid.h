#include <SDL.h>

struct grid_square
{
	bool walkable = true;
	bool deadly = false;
	SDL_Texture* texture = NULL;
	SDL_Rect rect = { 0, 0, 0, 0, 0 };
};

//extern inline struct grid_square* create_grid(int rows, int columns);

