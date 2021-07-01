#include "masters_startup.h"

 void get_monitor_data(int* refresh_rate, SDL_DisplayMode* current)
{
	if (SDL_GetCurrentDisplayMode(0, current) != 0)
	{
		SDL_Log("Could not get display mode for video display #%d: %s", 0, SDL_GetError());
	}
	else
	{
		*refresh_rate = current->refresh_rate;
	}
	SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz", 0, current->w, current->h, *refresh_rate);

}

