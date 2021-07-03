// ====================================
//  Grant Fisher 2021
// ==================================== 

#include "masters_particle.h"
#include <random>
#include <math.h>


long gcd(long a, long b)
{
	if (a == 0)
		return b;
	else if (b == 0)
		return a;

	if (a < b)
		return gcd(a, b % a);
	else
		return gcd(b, a % b);
}

void dec_to_frac(double input, float *slope_x, float *slope_y)
{
	double integral = std::floor(input);
	double frac = input - integral;

	const long precision = 1000000000; // This is the accuracy.

	long gcd_ = gcd(round(frac * precision), precision);

	*slope_x = precision / gcd_;
	*slope_y = round(frac * precision) / gcd_;

}

extern particle_system init_particle_system(particle_struct* particle_ptr, int num_particles, 
											SDL_Texture* default_texture, int angle,
											int min_x, int max_x, int min_y, int max_y,
											int min_speed, int max_speed, int min_time, 
											int max_time, int min_size, int max_size)
{
	int min = angle - 1;
	int max = angle + 1;
	for (int i = 0; i < num_particles; i++)
	{
		int size = rand() % max_size + min_speed;
		int theta = angle;
		int slope = 90;
		int start_x = (rand() % max_x) + min_x;
		int start_y = (rand() % max_y) + min_y;
		float slope_x, slope_y;
		int speed = rand() % max_speed + min_speed;
		int life = rand() % max_time + min_time;
		if (theta == 90) {
			slope_x = 0;
			slope_y = 1 * speed;
		}
		else if ((slope % 2) == 0)
		{
			slope_x = slope / 2;
			slope_y = slope / 2;
		}
		else {
			dec_to_frac(slope, &slope_x, &slope_y);
		}
		particle_struct particle = {
			{0, 0, size, size, start_x, start_y},
			true,
			{slope_x, slope_y},
			life
		};
		particle_ptr[i] = particle;
	}


	particle_system res = {particle_ptr, num_particles, min_x, max_x, min_y, max_y, min_size, max_size, min_speed, max_speed, min_time, max_time , angle, default_texture };
	
	return res;

}

// TODO: take into account camera for scaling
extern void render_particle_system(SDL_Renderer* renderer, particle_system* system)
{
	for (int i = 0; i < system->count; i++)
	{

		BASE_RENDER(renderer, system->default_texture, &system->ptr[i].rect);
	}
}

extern void update_particle_system(particle_system* system)
{
	int min = system->rotation - 1;
	int max = system->rotation + 1;
	int max_speed = system->max_speed;
	int min_speed = system->min_speed;
	int min_size = system->min_size;
	int max_size = system->max_size;
	int min_time = system->min_time;
	int max_time = system->max_time;
	for (int i = 0; i < system->count; i++)
	{
		if (system->ptr[i].life_time <= 0)
		{
			// RESET PARTICLE
			int size = rand() % max_size + min_size;
			int theta = system->rotation;
			int slope = 90;
			int start_x = (rand() % system->max_x) + system->min_x;
			int start_y = (rand() % system->max_y) + system->min_y;
			float slope_x, slope_y;
			int speed = rand() % max_speed + min_speed;
			int life = rand() % max_time + min_time;
			if (theta == 90) {
				slope_x = 0;
				slope_y = 1 * speed;
			}
			else if (slope % 2 == 0)
			{
				slope_x = slope / 2;
				slope_y = slope / 2;
			}
			else {
				dec_to_frac(slope, &slope_x, &slope_y);
			}
			system->ptr[i].life_time = life;
			system->ptr[i].rect = { 0, 0, size, size, start_x, start_y };
			system->ptr[i].shown = true;
			system->ptr[i].slope = { slope_x, slope_y };
		}

		system->ptr[i].rect.orig_x += system->ptr[i].slope.x;
		system->ptr[i].rect.orig_y += system->ptr[i].slope.y;
		system->ptr[i].life_time -= 1;
	}
}