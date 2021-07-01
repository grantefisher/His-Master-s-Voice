// ====================================
//  Grant Fisher 2021
// ==================================== 

#include "masters_particle.h"
#include <random>


extern particle_struct** init_particle_system(int num_particles, SDL_Texture* default_texture, int angle,
													float min_speed, float max_speed, int min_time, int max_time)
{
	particle_struct* res[grid_rows * grid_columns];

	return res;

}

// TODO: take into account camera for scaling
extern void render_particle_system(SDL_Renderer* renderer, particle_struct** arr, int count)
{
	for (int i = 0; i < count; i++)
	{

		BASE_RENDER(renderer, arr[i]->texture, &arr[i]->rect);
	}
}

extern void update_particle_system(SDL_Renderer* renderer, particle_struct** arr, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (arr[i]->life_time <= 0)
		{
			// RESET PARTICLE
			
		}

		arr[i]->rect.x += arr[i]->slope.x;
		arr[i]->rect.y += arr[i]->slope.y;
		arr[i]->life_time -= 1;
	}

	// RENDER
	render_particle_system(renderer, arr, count);
}