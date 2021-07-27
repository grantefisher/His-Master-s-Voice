// ====================================
//  Grant Fisher 2021
// ==================================== 

#include "masters_particle.h"
#include <random>
#include <math.h>


void Smoke_Particle_System::update()
{
	for (int i = 0; i < 10; i++)
	{
		Smoke_Particle* particle = &pool[i];

		// GENERATE NEW PARTICLE IF NECESSARY
		if (particle->frame_life_time <= 0)
		{
			particle->x = x_range.x + (rand() % (x_range.y - x_range.x + 1));
			particle->y = y_range.x + (rand() % (y_range.y - y_range.x + 1));

			particle->size = size_range.x + (rand() % (size_range.y - size_range.x + 1));

			particle->y_change = speed_range.x + (rand() % (speed_range.y - speed_range.x + 1));

			particle->frame_life_time = frame_life_range.x + (rand() % (frame_life_range.y - frame_life_range.x + 1));
		}

		// UPDATE PARTICLE
		else
		{
			particle->y += particle->y_change;
			particle->frame_life_time--;
		}

	}
}

void Smoke_Particle_System::render(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_Rect temp;
	for (int i = 0; i < 10; i++)
	{
		temp = { pool[i].x, pool[i].y, pool[i].size, pool[i].size , 0, 0 };
		BASE_RENDER(renderer, texture, &temp);
	}
}
