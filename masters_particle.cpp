// ====================================
//  Grant Fisher 2021
// ==================================== 

#include "masters_particle.h"
#include <random>
#include <math.h>


void Smoke_Particle_System::update()
{
	for (int i = 0; i < 500; i++)
	{
		Smoke_Particle* particle = &pool[i];

		// GENERATE NEW PARTICLE IF NECESSARY
		if (particle->frame_life_time <= 0)
		{
			particle->x = x_range.y;
			particle->y = y_range.y;

			particle->y_change = (rand() % speed_range.y) + speed_range.x;

			particle->frame_life_time = (rand() % frame_life_range.x) + frame_life_range.y;
		}

		// UPDATE PARTICLE
		else
		{
			particle->y += particle->y_change;
			particle->frame_life_time--;
		}

	}
}

void Smoke_Particle_System::render(SDL_Renderer* renderer, camera* cam)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	for (int i = 0; i < 500; i++)
	{
		SDL_RenderDrawPoint(renderer, cam->center.x - pool[i].x, cam->center.y - pool[i].y);
	}
}