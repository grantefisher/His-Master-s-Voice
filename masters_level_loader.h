#pragma once

#include "masters_entity.h"
#include "masters_grid.h"
#include "masters_particle.h"


#include <SDL.h>

void load_level(const char* file, grid_square** grid, Bastard* bastard_arr,
				Long_Bastard* long_bastard_arr, Player* player, Smoke_Particle_System* particle_sys_arr,
				SDL_Texture* walkable, SDL_Texture* deadly, SDL_Texture* smoke_texture,
				SDL_Texture* bastard_texture, SDL_Texture* long_bastard_texture, SDL_Texture* door_texture,
				int* bastard_count, int* long_bastard_count, int* particle_sys_count);