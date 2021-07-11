// ====================================
//  Grant Fisher 2021
// ==================================== 


#include "masters_level_loader.h"
#include "masters_startup.h"
#include "masters_camera.h"
#include "masters_render.h"
#include "masters_update.h"
#include "masters_particle.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>

// TODO: delete this later
// NOTE: only using for std::cin input and debugging
#include <iostream>

// FIXES PROBLEM WITH EXTERNAL MAIN FUNCTION IN SDL
#undef main 



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
	// 900 BY 700
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
	SDL_Rect rectangle = { 0, 0, 200, 200, 200, 200 };
	SDL_Rect rectangle_two = { 0, 0, 200, 200, 300, 400 };

	SDL_Surface* surface = IMG_Load("resources/smoke.png");
	SDL_Texture* smoke_texture = SDL_CreateTextureFromSurface(renderer, surface);


	surface = IMG_Load("resources/fireman.png");
	SDL_SetWindowIcon(window, surface);
	SDL_Texture* player_texture = SDL_CreateTextureFromSurface(renderer, surface);

	surface = IMG_Load("resources/death_undo.png");
	SDL_Texture* death_undo_txt = SDL_CreateTextureFromSurface(renderer, surface);

	Player conor;
	conor.texture = player_texture;
	SDL_Rect conor_rect = { 0, 0, 50, 80, 0, 0 };
	conor.rect = &conor_rect;
	conor.grid_position = { 14, 9 }; 

	surface = IMG_Load("resources/bastard.png");
	SDL_Texture* bastard_texture = SDL_CreateTextureFromSurface(renderer, surface);



	

	surface = IMG_Load("resources/long_bastard.png");
	SDL_Texture* long_bastard_texture = SDL_CreateTextureFromSurface(renderer, surface);


	camera default_camera;
	default_camera.center = { 800, 600 };
	default_camera.dimensions = { 800, 600 };

	camera previous_camera = default_camera;

	
	SDL_Texture* texture;

	const int rows = 12;
	const int columns = 16;


	vec_two grid_dimensions = { rows, columns };
	const int total_squares = rows * columns;
	printf("Total squares: %d", total_squares);
	int size = 50;


	grid_square* gGrid[total_squares]; 


	

	surface = IMG_Load("resources/walkable_square.png");
	if (surface == NULL)
	{
		SDL_Log("error loading bmp: %s\n", SDL_GetError());
	}

	SDL_Texture* walkable = SDL_CreateTextureFromSurface(renderer, surface);


	surface = IMG_Load("resources/deadly_square.png");
	SDL_Texture* deadly = SDL_CreateTextureFromSurface(renderer, surface);


	int particle_sys_count;
	Smoke_Particle_System* particle_sys_arr = new Smoke_Particle_System[100];

	Long_Bastard long_bastard_arr[10];
	int lb_count;
	Bastard bastard_arr[10];
	int b_count;

	surface = IMG_Load("resources/door.png");
	SDL_Texture* door_texture = SDL_CreateTextureFromSurface(renderer, surface);

	load_level("resources/level_two.json", gGrid, bastard_arr,
			    long_bastard_arr, &conor, particle_sys_arr, 
			    walkable, deadly, smoke_texture, 
				bastard_texture, long_bastard_texture, door_texture,
			    &b_count, &lb_count, &particle_sys_count);



	for (int i = 0; i < b_count; i++)
	{
		bastard_arr[i].grid_to_position(size);
	}
	for (int i = 0; i < lb_count; i++)
	{
		long_bastard_arr[i].grid_to_position(size);
	}


	// GENERATE GRID
	/*
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
	*/
		


	
	//gGrid[100]->texture = texture;
	//gGrid[100]->deadly = true;
	/////////////////////////////////////////////////////////////////
	


	// TODO: perform one time grid-position setup on every single entity
	// player one-time setup
	conor.grid_to_position(size);

	int p_time = 16;
	int last_time;
	int current_diff;
	int bastard_frame_iterator = 0;

	while (running)
	{
		
		last_time = SDL_GetTicks();

		// CHECK ENTITY FLAGS
		//////////////////////////////////
		for (int i = b_count-1; i >= 0; i--)
		{
			if (bastard_arr[i].delete_flag)
			{
				for (int curs = i; curs <= b_count; curs++)
				{
					bastard_arr[curs] = bastard_arr[curs + 1];
				}
				b_count--;
			}
		}
		for (int i = lb_count-1; i >= 0; i--)
		{
			if (long_bastard_arr[i].delete_flag)
			{
				for (int curs = i; curs <= lb_count; curs++)
				{
					long_bastard_arr[curs] = long_bastard_arr[curs + 1];
				}
				lb_count--;
			}
		}
		//////////////////////////////////
		// EO CHECK ENTITY FLAGS
		//////////////////////////////////




		//////////////////////////////////
		// INPUT LOOP
		//////////////////////////////////
		SDL_Event Event;
		std::vector<direction_input> input_arr;
		
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
					input_arr.push_back(direction_input::up);
					break;
				case SDLK_a:
					input_arr.push_back(direction_input::left);
					break;
				case SDLK_s:
					input_arr.push_back(direction_input::down);
					break;
				case SDLK_ d:
					input_arr.push_back(direction_input::right);
					break;
				case SDLK_LSHIFT:
					input_arr.push_back(direction_input::undo);
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
		//////////////////////////////////
		// EO INPUT LOOP
		//////////////////////////////////


		// PLAYER/LONG BASTARD MOVEMENT UPDATE
		bool input_per_frame = false;

		for (direction_input input : input_arr) {
			if (input_per_frame)
			{
				break;
			}
			
			// PLAYER MOVEMENT UPDATE
			//////////////////////////////////
			vec_two player_new_grid_position = conor.grid_position;


			if (input == up)
			{
				player_new_grid_position.y += 1;
				input_per_frame = true;
			}
			else if (input == down)
			{
				player_new_grid_position.y -= 1;
				input_per_frame = true;
			}
			else if (input == left)
			{
				player_new_grid_position.x += 1;
				input_per_frame = true;
			}
			else if (input == right)
			{
				player_new_grid_position.x -= 1;
				input_per_frame = true;
			}
			else if (input == undo)
			{
				if (!conor.alive)
				{
					conor.alive = true;
				}
				conor.grid_position = conor.prev_grid_position;
				conor.grid_to_position(size);

				break;
			}
			else
			{
				continue;
			}


			// TODO: check if there was a movement input at all
			if (conor.alive)
			{
				int row = player_new_grid_position.y * grid_dimensions.y;
				int column = player_new_grid_position.x;
				int index = row + column;
				if (player_new_grid_position.y < grid_dimensions.x
					&& player_new_grid_position.x < grid_dimensions.y
					&& player_new_grid_position.y >= 0
					&& player_new_grid_position.x >= 0) {
					if (gGrid[index]->walkable == true)
					{
						if (gGrid[index]->deadly == true)
						{
							conor.alive = false;
							printf("Player has died\n");
						}
						conor.prev_grid_position = conor.grid_position;
						conor.grid_position = player_new_grid_position;
						conor.grid_to_position(size);

						// CHECK IF COLLIDE WITH BASTARD
						for (int i = 0; i < b_count; i++)
						{
							if (bastard_arr[i].grid_position.x == conor.grid_position.x
								&& bastard_arr[i].grid_position.y == conor.grid_position.y)
							{
								conor.alive = false;
								break;
							}
						}
						//////////////////////////////////




						//////////////////////////////////
						// EO PLAYER UPDATE
						//////////////////////////////////






						// LONG BASTARD MOVEMENT UPDATE
						//////////////////////////////////
						for (int lb_i = 0; lb_i < lb_count; lb_i++)
						{
							Long_Bastard* temp_long_bastard = &long_bastard_arr[lb_i];
							if (!temp_long_bastard->stuck) {
								vec_two lb_new_grid_position = temp_long_bastard->grid_position;

								if (input == up)
								{
									lb_new_grid_position.y -= 1;
								}
								else if (input == down)
								{
									lb_new_grid_position.y += 1;
								}
								else if (input == left)
								{
									lb_new_grid_position.x -= 1;
								}
								else if (input == right)
								{
									lb_new_grid_position.x += 1;
								}

								row = lb_new_grid_position.y * grid_dimensions.y;
								column = lb_new_grid_position.x;
								index = row + column;
								if (lb_new_grid_position.y < grid_dimensions.x
									&& lb_new_grid_position.x < grid_dimensions.y
									&& lb_new_grid_position.y >= 0
									&& lb_new_grid_position.x >= 0)
								{
									bool update_lb_pos = false;
									if (gGrid[index]->walkable == true)
									{
										bool update_lb_pos = true;
										if (gGrid[index]->deadly == true)
										{
											temp_long_bastard->stuck = true;
											printf("LB STUCK\n");
											gGrid[index]->deadly = false;
										}

										// CHECK IF CURRENT LONG-BASTARD COLLIDES WITH ANY OF THE OTHER LONG BASTARDS
										for (int lb_j = 0; lb_j < lb_count; lb_j++)
										{
											if (lb_j != lb_i)
											{
												if (lb_new_grid_position.x == long_bastard_arr[lb_j].grid_position.x
													&& lb_new_grid_position.y == long_bastard_arr[lb_j].grid_position.y)
												{
													update_lb_pos = false;
													break;
												}
											}
										}


										// CHECK IF CURRENT LONG-BASTARD COLLIDES WITH ANY OF THE OTHER LONG BASTARDS
										for (int b_i = 0; b_i < b_count; b_i++)
										{
											if (lb_new_grid_position.x == bastard_arr[b_i].grid_position.x
												&& lb_new_grid_position.y == bastard_arr[b_i].grid_position.y)
											{
												update_lb_pos = false;
												break;
											}
										}


										// UPDATE THE POSITION OF THE CURRENT LONG BASTARD
										if (update_lb_pos)
										{
											temp_long_bastard->grid_position = lb_new_grid_position;
											temp_long_bastard->grid_to_position(size);
										}
									}
									else
									{
										printf("LONG BASTARD couldn't move in this direction\n");
									}
								}
							}
						}
						//////////////////////////////////
						// EO LONG BASTARD UPDATE
						//////////////////////////////////




					}
				}
				else
				{
					printf("Player couldn't move in this direction\n");
				}
			}
			//////////////////////////////////
			// EO PLAYER WALKABLE MOVEMENT UPDATE
			//////////////////////////////////
		}

		

		// BASTARD MOVEMENT UPDATE
		//////////////////////////////////
		bastard_frame_iterator++;
		if (bastard_frame_iterator >= 35)
		{
			bastard_frame_iterator = 0;

			vec_two bastard_new_grid_position;
			for (int b_i = 0; b_i < b_count; b_i++)
			{
				Bastard* temp_bastard = &bastard_arr[b_i];
				bastard_new_grid_position = temp_bastard->grid_position;
				if (temp_bastard->movement.x > 0)
				{
					bastard_new_grid_position.x -= temp_bastard->direction;
				}
				if (temp_bastard->movement.y > 0)
				{
					bastard_new_grid_position.y -= temp_bastard->direction;
				}

				int row = bastard_new_grid_position.y * grid_dimensions.y;
				int column = bastard_new_grid_position.x;
				if (bastard_new_grid_position.y < grid_dimensions.x
					&& bastard_new_grid_position.x < grid_dimensions.y
					&& bastard_new_grid_position.y >= 0
					&& bastard_new_grid_position.x >= 0) {
					int index = row + column;
					bool update_bastard_pos = false;
					if (gGrid[index]->walkable == true)
					{
						if (!gGrid[index]->deadly)
						{
							update_bastard_pos = true;
							
						}
						// check if colliding with LONG BASTARD
						for (int i = 0; i < lb_count; i++)
						{
							if (bastard_new_grid_position.x == long_bastard_arr[i].grid_position.x
								&& bastard_new_grid_position.y == long_bastard_arr[i].grid_position.y)
							{
								update_bastard_pos = false;
								break;
							}
						}

						// CHECK IF CURRENT LONG-BASTARD COLLIDES WITH ANY OF THE OTHER LONG BASTARDS
						for (int b_j = 0; b_j < b_count; b_j++)
						{
							if (b_j != b_i)
							{
								if (bastard_new_grid_position.x == bastard_arr[b_j].grid_position.x
									&& bastard_new_grid_position.y == bastard_arr[b_j].grid_position.y)
								{
									update_bastard_pos = false;
									break;
								}
							}
						}


						// check if colliding with PLAYER
						if (bastard_new_grid_position.x == conor.grid_position.x
							&& bastard_new_grid_position.y == conor.grid_position.y)
						{
							conor.alive = false;
						}
						if (update_bastard_pos)
						{ 
							temp_bastard->grid_position = bastard_new_grid_position;
							temp_bastard->grid_to_position(size);
						}
					}
					

				}

				temp_bastard->iteration++;

				if (temp_bastard->iteration >= temp_bastard->movement.x)
				{
					temp_bastard->iteration = 0;
					temp_bastard->direction *= -1;
				}
			}
			//////////////////////////////////
			// EO BASTARD UPDATE
			//////////////////////////////////
		}
		




		// UPDATE ENTITIES RELATIVE TO THE CAMERA
		//////////////////////////////////
		// UPDATE GRID relativce to camera
		//////////////////////////////////
		for (int i = 0; i < total_squares; i++)
		{
			update_rect_relative_camera(&default_camera, &gGrid[i]->rect);
		}
		//////////////////////////////////



		// UPDATE PARTICLE SYSTEM 
		//////////////////////////////////
		/*for (int i = 0; i < particle_sys_count; i++)
		{
			particle_sys_arr[i].update();
		}*/
	
		
		//////////////////////////////////



		// UPDATE PLAYER RELATIVE TO CAMERA
		update_rect_relative_camera(&default_camera, conor.rect);

		previous_camera.center.x = default_camera.center.x;
		previous_camera.center.y = default_camera.center.y;
		//////////////////////////////////
		// EO CAMERA UPDATE AND ENTITY MOVEMENT RELATIVE TO CAMERA
		//////////////////////////////////



		// PAUSE AND WAIT TO RENDER
		/////////////////////////////
		current_diff = SDL_GetTicks() - last_time;
		while (current_diff < 16) {
			current_diff = SDL_GetTicks() - last_time;
		}
		/////////////////////////////


		// CLEAR SCREEN
		//////////////////////////////////
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
		SDL_RenderClear(renderer);
		//////////////////////////////////
		


		// RENDER GRID
		/////////////////////////////
		GRID_RENDER(renderer, gGrid, rows, columns);
		/////////////////////////////


		// RENDER BASTARDS
		/////////////////////////////
		for (int i = 0; i < b_count; i++)
		{
			update_rect_relative_camera(&default_camera, &bastard_arr[i].rect);
			BASE_RENDER(renderer, bastard_arr[i].texture, &bastard_arr[i].rect);
		}
		
		/////////////////////////////


		// RENDER LONG BASTARDS
		/////////////////////////////
		for (int i = 0; i < lb_count; i++)
		{ 
			update_rect_relative_camera(&default_camera, &long_bastard_arr[i].rect);
			BASE_RENDER(renderer, long_bastard_arr[i].texture, &long_bastard_arr[i].rect);
		}
		/////////////////////////////


		// RENDER PLAYER
		/////////////////////////////
		BASE_RENDER(renderer, conor.texture, conor.rect);
		/////////////////////////////

		// RENDER DEATH TEXT
		/////////////////////////////

		// if dead
		if (!conor.alive)
		{
			SDL_Rect render_rect;
			render_rect.orig_x = 700;
			render_rect.orig_y = 400;
			render_rect.w = 700;
			render_rect.h = 200;

			update_rect_relative_camera(&default_camera, &render_rect);

			BASE_RENDER(renderer, death_undo_txt, &render_rect);
		}

		// if dead and out of undo


		/////////////////////////////


		// TODO: write particle system for loop renderer
		// RENDER PARTICLE SYSTEMS
		/////////////////////////////
		/*for (int i = 0; i < particle_sys_count; i++)
		{
			particle_sys_arr[i].render(renderer, &default_camera);
		}*/
		/////////////////////////////

		SDL_RenderPresent(renderer);

		
	}
	SDL_Quit();

	return 0;
}