#pragma once

#include "masters_render.h"

#include <SDL.h>

#define PARTICLE_SIZE sizeof(particle_struct)

struct Smoke_Particle
{
	int x, y;
	int y_change;
	int frame_life_time = 0;
};

struct Smoke_Particle_System
{
	vec_twoi x_range;
	vec_twoi y_range;

	vec_twoi speed_range;

	vec_twoi frame_life_range;

	Smoke_Particle pool[500];

	void update();
	void render(SDL_Renderer* renderer, camera* cam);
};