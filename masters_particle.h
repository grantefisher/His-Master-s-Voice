#pragma once

#include "masters_render.h"

#include <SDL.h>

#define PARTICLE_SIZE sizeof(particle_struct)

struct particle_struct
{
	SDL_Rect rect;
	bool shown = true;
	vec_two slope;
	int life_time;
};



struct particle_system
{
	particle_struct* ptr;
	int count;
	int min_x, max_x;
	int min_y, max_y;
	int min_size, max_size;
	float min_speed, max_speed;
	int min_time, max_time;
	int rotation;
	SDL_Texture* default_texture;
};

// NOTE: default 15 degree variance in angle
extern particle_system init_particle_system(particle_struct* particle_ptr, int num_particles,
	SDL_Texture* default_texture, int angle,
	int min_x, int max_x, int min_y,
	int max_y, int min_speed, int max_speed,
	int min_time, int max_time,	int min_size, int max_size);

extern void render_particle_system(SDL_Renderer* renderer, particle_system* system);

extern void update_particle_system(particle_system* system);