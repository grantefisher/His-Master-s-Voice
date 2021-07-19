#pragma once

#include "masters_render.h"

#include <SDL.h>


struct Smoke_Particle
{
	int x, y;
	int size;
	int y_change;
	int frame_life_time = 0;
};

struct Smoke_Particle_System
{
	vec_twoi x_range;
	vec_twoi y_range;
	vec_twoi size_range;

	vec_twoi speed_range;

	vec_twoi frame_life_range;

	Smoke_Particle pool[10];

	void update();
	void render(SDL_Renderer* renderer, SDL_Texture* texture);
};