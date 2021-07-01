#pragma once

#include "masters_render.h"
#include "masters_consts.h"

#include <SDL.h>

#define PARTICLE_SIZE sizeof(particle_struct)

struct particle_struct
{
	SDL_Rect rect;
	SDL_Texture* texture; /* not sure if this is necessary */
	bool shown = true;
	vec_two slope;
	int life_time;
};



struct particle_system
{
	particle_struct* ptr;
	int count;
	float speed;
	int rotation;
	
};

// NOTE: default 15 degree variance in angle
extern particle_struct** init_particle_system(int num_particles, SDL_Texture* default_texture, int angle,
													float min_speed, float max_speed, int min_time, int max_time
													);

extern void render_particle_system(SDL_Renderer* renderer, particle_struct** arr, int count);

extern void update_particle_system(SDL_Renderer* renderer, particle_struct** arr, int count);