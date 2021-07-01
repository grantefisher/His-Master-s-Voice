// ====================================
//  Grant Fisher 2021
// ==================================== 


#include "masters_startup.h"
#include "masters_camera.h"
#include "masters_render.h"
#include "masters_update.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

// TODO: delete this later
// NOTE: only using for std::cin input
#include <iostream>

// FIXES PROBLEM WITH EXTERNAL MAIN FUNCTION IN SDL
#undef main 

// TODO: write function to update all entity vectors relative to camera
void update_vectors_relative_camera(camera* default_cam_ref, camera* prev_cam_ref);



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

	if (SDL_CreateWindowAndRenderer(900, 700, SDL_WINDOW_SHOWN, &window, &renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "couldn't create window and renderer: %s", SDL_GetError());
		return 3;
	}
	
	SDL_SetWindowTitle(window, "His Master's Voice");
	

	SDL_DisplayMode current;
	int refresh_rate = 0;
	get_monitor_data(&refresh_rate, &current);

	/////////////////////////////////////////////////////////////////
	// 	   TEST OBJECT SECTION
	//                         x  y    w    h   rx   ry
	SDL_Rect rectangle =     { 0, 0, 200, 200, 200, 200 };
	SDL_Rect rectangle_two = { 0, 0, 200, 200, 300, 400 };

	

	SDL_Surface* surface = IMG_Load("resources/fireman.png");
	SDL_SetWindowIcon(window, surface);
	SDL_Texture* player_texture = SDL_CreateTextureFromSurface(renderer, surface);

	Player conor;
	conor.texture = player_texture;
	SDL_Rect conor_rect = { 0, 0, 50, 80, 0, 0 };
	conor.rect = &conor_rect;
	conor.grid_position = { 14, 9 };

	surface = IMG_Load("resources/bastard.png");
	SDL_Texture* bastard_texture = SDL_CreateTextureFromSurface(renderer, surface);

	Bastard bastard;
	bastard.grid_position = { 10, 10 };
	bastard.texture = bastard_texture;
	SDL_Rect bastard_rect = { 0, 0, 60, 60, 0, 0 };
	bastard.rect = &bastard_rect;

	surface = IMG_Load("resources/long_bastard.png");
	SDL_Texture* long_bastard_texture = SDL_CreateTextureFromSurface(renderer, surface);

	Long_Bastard long_bastard;
	long_bastard.grid_position = { 5, 0 };
	long_bastard.texture = long_bastard_texture;
	SDL_Rect long_bastard_rect = { 0, 0, 60, 40, 0, 0 };
	long_bastard.rect = &long_bastard_rect;


	camera default_camera;
	default_camera.center = { 800, 600 };
	default_camera.dimensions = { 800, 600 };

	camera previous_camera = default_camera;

	surface = IMG_Load("resources/walkable_square.png");
	if (surface == NULL)
	{
		SDL_Log("error loading bmp: %s\n", SDL_GetError());
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	
	const int rows = 12;
	const int columns = 16;
	vec_two grid_dimensions = { rows, columns };
	const int total_squares = rows * columns;
	printf("Total squares: %d", total_squares);
	int size = 50;
	grid_square* gGrid[total_squares];
	int square_count = -1;

	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++) 
		{
			square_count++;
			gGrid[square_count] = new grid_square();
			gGrid[square_count]->rect = { column * size, row * size,
										  size, size,
									      column * size, row * size
										};
			gGrid[square_count]->walkable = true;
			gGrid[square_count]->deadly = false;
			gGrid[square_count]->texture = texture;
		}
	}

	/////////////////////////////////////////////////////////////////
	surface = IMG_Load("resources/deadly_square.png");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	gGrid[100]->texture = texture;
	gGrid[100]->deadly = true;

	// player one-time setup
	conor.grid_to_position(size);

	int p_time = 16;
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
					movement_update(&conor, gGrid, grid_dimensions, size, direction_input::up);
					//conor.move_player(direction_input::up);
					long_bastard.move_long_bastard(direction_input::up);
					break;
				case SDLK_a:
					movement_update(&conor, gGrid, grid_dimensions, size, direction_input::left);
					//conor.move_player(direction_input::left);
					long_bastard.move_long_bastard(direction_input::left);
					break;
				case SDLK_s:
					movement_update(&conor, gGrid, grid_dimensions, size, direction_input::down);
					//conor.move_player(direction_input::down);
					long_bastard.move_long_bastard(direction_input::down);
					break;
				case SDLK_d:
					movement_update(&conor, gGrid, grid_dimensions, size, direction_input::right);
					//conor.move_player(direction_input::right);
					long_bastard.move_long_bastard(direction_input::right);
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

		bastard.grid_to_position(size);
		long_bastard.grid_to_position(size);

		//if (previous_camera.center.x != default_camera.center.x || default_camera.center.y != previous_camera.center.y)
		//{
		for (int i = 0; i < total_squares; i++)
		{
				update_rect_relative_camera(&default_camera, &gGrid[i]->rect);
		}
		update_rect_relative_camera(&default_camera, conor.rect);
		update_rect_relative_camera(&default_camera, bastard.rect);
		update_rect_relative_camera(&default_camera, long_bastard.rect);
		previous_camera.center.x = default_camera.center.x;
		previous_camera.center.y = default_camera.center.y;
		//}

		// PAUSE AND WAIT TO RENDER
		current_diff = SDL_GetTicks() - last_time;
		while (current_diff < 16) {
			current_diff = SDL_GetTicks() - last_time;
		}


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
		SDL_RenderClear(renderer);

		//BASE_RENDER(renderer, texture, &rectangle);
		//BASE_RENDER(renderer, texture, &rectangle_two);

		GRID_RENDER(renderer, gGrid, rows, columns);
		BASE_RENDER(renderer, bastard.texture, bastard.rect);
		BASE_RENDER(renderer, long_bastard.texture, long_bastard.rect);
		BASE_RENDER(renderer, conor.texture, conor.rect);


		SDL_RenderPresent(renderer);
	}
	SDL_Quit();

	return 0;
}