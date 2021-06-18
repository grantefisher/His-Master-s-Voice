// ====================================
//  Grant Fisher 2021
// ==================================== 


#include "masters_camera.h"
#include "masters_render.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

// TODO: delete this later
// NOTE: only using for std::cin input
#include <iostream>

// FIXES PROBLEM WITH EXTERNAL MAIN FUNCTION IN SDL
#undef main 

// TODO: write function to update all entity vectors relative to camera
inline void update_vectors_relative_camera(camera* default_cam_ref, camera* prev_cam_ref);

int main()
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("SDL IMAGE did not initialize\n");
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}


	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event Event;

	bool running = true;

	if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "couldn't create window and renderer: %s", SDL_GetError());
		return 3;
	}

	// look at all displays
	SDL_DisplayMode current;
	int refresh_rate = 0;
	float time_between_frames;
	for (int i = 0; i < SDL_GetNumVideoDisplays(); i++)
	{
		int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

		if (should_be_zero != 0)
		{
			SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
		}
		else
		{
			if (i == 0)
			{
				refresh_rate = current.refresh_rate;
				time_between_frames = 1000 / refresh_rate;
			}
			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz", i, current.w, current.h, current.refresh_rate);
		}

	}

	//                         x  y    w    h   rx   ry
	SDL_Rect rectangle =     { 0, 0, 200, 200, 200, 200 };
	SDL_Rect rectangle_two = { 0, 0, 200, 200, 300, 400 };

	SDL_Surface* surface = SDL_LoadBMP("resources/frog.bmp");
	if (surface == NULL)
	{
		SDL_Log("error loading bmp: %s\n", SDL_GetError());
	} 

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);


	camera default_camera;
	default_camera.center = { 200, 200 };
	default_camera.dimensions = { 800, 600 };
	
	camera previous_camera = default_camera;

	refresh_rate = 60;
	double ms_per_frame = (1000 / refresh_rate);
	float ms_per_frame_sixty = 1000 / 60;

	int process_units;
	int p_time;
	process_units = 1;
	p_time = 16.6;


	int last_time;
	int current_diff;
	while (running)
	{
		last_time = SDL_GetTicks();
		while (SDL_PollEvent(&Event) != 0)
		{
			//User requests quit
			if (Event.type == SDL_QUIT)
			{
				running = false;
			}
			//User presses a key
			else if (Event.type == SDL_KEYDOWN)
			{
				switch (Event.key.keysym.sym)
				{
				case SDLK_w:
					break;
				case SDLK_a:
					break;
				case SDLK_s:
					break;
				case SDLK_d:
					break;
				case SDLK_UP:
					default_camera.center.y -= 5;
					break;

				case SDLK_DOWN:
					default_camera.center.y += 5;
					break;

				case SDLK_LEFT:
					default_camera.center.x -= 5;
					break;

				case SDLK_RIGHT:
					default_camera.center.x += 5;
					break;
				case SDLK_BACKQUOTE:
					break;
				default:
					break;
				}
			}

		}

		if (previous_camera.center.x != default_camera.center.x || default_camera.center.y != previous_camera.center.y)
		{
			update_rect_relative_camera(&default_camera, &rectangle);
			update_rect_relative_camera(&default_camera, &rectangle_two);
			previous_camera.center.x = default_camera.center.x;
			previous_camera.center.y = default_camera.center.y;
		}
		current_diff = SDL_GetTicks() - last_time;
		while (current_diff < 16) {
			current_diff = SDL_GetTicks() - last_time;
		}


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
		SDL_RenderClear(renderer);

		BASE_RENDER(renderer, texture, &rectangle);
		BASE_RENDER(renderer, texture, &rectangle_two);

		SDL_RenderPresent(renderer);
	}
	SDL_Quit();

	return 0;
}