
#include "masters_level_loader.h"

#include <SDL.h>
#include <fstream>
#include <string>
#include <random>

extern const int grid_rows = 12;
extern const int grid_columns = 16;


// 32 = START
// 7 = WALKABLE
// 58 = DEADLY
void load_level(const char* file, grid_square** grid, Bastard* bastard_arr, 
				Long_Bastard* long_bastard_arr, Player* player, Smoke_Particle_System* smoke_system_arr,
				SDL_Texture* walkable, SDL_Texture* deadly, SDL_Texture* smoke_texture,
				SDL_Texture* bastard_texture,  SDL_Texture* lava_two_texture, SDL_Texture* lava_three_texture, 
				SDL_Texture* long_bastard_texture, SDL_Texture* door_texture,
				int* bastard_count, int* long_bastard_count, int* particle_sys_count)
{
	int input;
	std::ifstream level_file;
	level_file.open(file);

	int temp_b_count = 0;
	int temp_lb_count = 0;
	int temp_particle_sys_count = 0;

	int size = 50;
	int square_count = -1;
	for (int row = 0; row < grid_rows; row++)
	{
		for (int column = 0; column < grid_columns; column++)
		{
			level_file >> input;

			square_count++;
			grid_square empty = {};
			(*grid)[square_count] = empty;
			(*grid)[square_count].rect = { column * size, row * size,
										  size, size,
										  column * size, row * size
			};

			// WALKABLE = 0
			if (input == 0)
			{
				(*grid)[square_count].walkable = true;
				(*grid)[square_count].deadly = false;
				(*grid)[square_count].texture = walkable;
			}
			// DEADLY = 1
			else if (input == 1)
			{
				(*grid)[square_count].walkable = true;
				(*grid)[square_count].deadly = true;

				int texture_choice = (rand() % 99) + 1;
				
				if (texture_choice == 1)
				{
					(*grid)[square_count].texture = lava_two_texture;
					(*grid)[square_count].animation_state = 100;
				}
				else if (texture_choice > 50)
				{
					(*grid)[square_count].texture = deadly;
					(*grid)[square_count].animation_state =  0;
				}
				else if (texture_choice <= 50)
				{
					(*grid)[square_count].texture = lava_three_texture;
					(*grid)[square_count].animation_state = 50;
				}

				//MAKE SMOKE PARTICLE SYSTEM
				Smoke_Particle_System smoke_system = 
				{
					{  ((grid_columns - column) * 50) + 1, ((grid_columns - column)*50) + 50}, // { min_x, max_x }
					{ ((grid_rows - row) * size) + 10, ((grid_rows - row) * size) + 46} , // { min_y, max_y },
					{ 1, 3 }, // { min_size, max_size }
 					{ -1, -.5 }, // { min_speed, max_speed }
					{ 10, 15} // { min_frame_life, max_frame_life }
				};

				smoke_system_arr[temp_particle_sys_count] = smoke_system;

				temp_particle_sys_count++;
				*particle_sys_count = temp_particle_sys_count;
			}

			// START = 4
			else if (input == 4)
			{
				(*grid)[square_count].walkable = true;
				(*grid)[square_count].deadly = false;
				(*grid)[square_count].texture = walkable;
				player->grid_position = { (float)column, (float)row };
				(*player).grid_to_position(size);
			}

			

			// BASTARD = 2
			else if (input == 2)
			{
				(*grid)[square_count].walkable = true;
				(*grid)[square_count].deadly = false;
				(*grid)[square_count].texture = walkable;

				bastard_arr[temp_b_count].grid_position = { (float)column, (float)row };
				bastard_arr[temp_b_count].texture = bastard_texture;
				SDL_Rect bastard_rect = { 0, 0, 60, 60, 0, 0 };
				bastard_arr[temp_b_count].movement = { 4, 0 };
				bastard_arr[temp_b_count].iteration = 0;
				bastard_arr[temp_b_count].direction = 1;
				bastard_arr[temp_b_count].rect = bastard_rect;
				bastard_arr[temp_b_count].grid_to_position(size);

				temp_b_count++;
				*bastard_count = temp_b_count;
			}	

			// LONG BASTARD = 3
			else if (input == 3)
			{
				(*grid)[square_count].walkable = true;
				(*grid)[square_count].deadly = false;
				(*grid)[square_count].texture = walkable;

				long_bastard_arr[temp_lb_count].grid_position = { (float)column, (float)row };
				long_bastard_arr[temp_lb_count].texture = long_bastard_texture;
				SDL_Rect long_bastard_rect = { 0, 0, 60, 40, 0, 0 };
				long_bastard_arr[temp_lb_count].rect = long_bastard_rect;
				long_bastard_arr[temp_lb_count].grid_to_position(size);
				
				temp_lb_count++;
				*long_bastard_count = temp_lb_count;
			}

			// DOOR / END = 5
			else if (input == 5)
			{
				(*grid)[square_count].walkable = true;
				(*grid)[square_count].deadly = false;
				(*grid)[square_count].texture = door_texture;
			}

			
		}
	}
}