
#include "masters_level_loader.h"

#include <SDL.h>
#include <fstream>
#include <string>

extern const int grid_rows = 12;
extern const int grid_columns = 16;


// 32 = START
// 7 = WALKABLE
// 58 = DEADLY
void load_level(const char* file, grid_square** grid, Bastard* bastard_arr, 
				Long_Bastard* long_bastard_arr, Player* player, Smoke_Particle_System* smoke_system_arr,
				SDL_Texture* walkable, SDL_Texture* deadly, SDL_Texture* smoke_texture,
				SDL_Texture* bastard_texture, SDL_Texture* long_bastard_texture, SDL_Texture* door_texture,
				int* bastard_count, int* long_bastard_count, int* particle_sys_count)
{
	int input;
	std::ifstream level_file;
	level_file.open(file);

	int temp_b_count = 0;
	int temp_lb_count = 0;
	int temp_particle_sys_count = 0;

	int size = 50;
	int square_count = grid_rows*grid_columns;
	for (int row = grid_rows-1; row >= 0; row--)
	{
		printf("row = %d\n", row);
		for (int column = grid_columns-1; column >= 0; column--)
		{
			level_file >> input;

			square_count--;
			grid[square_count] = new grid_square();
			grid[square_count]->rect = { column * size, row * size,
										  size, size,
										  column * size, row * size
			};

			

			// DEADLY
			if (input == 79)
			{
				grid[square_count]->walkable = true;
				grid[square_count]->deadly = true;
				grid[square_count]->texture = deadly;

				// MAKE SMOKE PARTICLE SYSTEM
				//Smoke_Particle_System smoke_system = 
				//{
				//	{ 600 - (column * 50), (650 - (column * 50)) +1 }, // { min_x, max_x }
				//	{ 500 -  (row * size) + 1,  500 - (row * size) + 2} , // { min_y, max_y }
 			//		{ 1, 1 }, // { min_speed, max_speed }
				//	{ 1, 3} // { min_frame_life, max_frame_life }
				//};

				//smoke_system_arr[temp_particle_sys_count] = smoke_system;

				temp_particle_sys_count++;
				*particle_sys_count = temp_particle_sys_count;
			}

			// START = 32
			else if (input == 83)
			{
				grid[square_count]->walkable = true;
				grid[square_count]->deadly = false;
				grid[square_count]->texture = walkable;
				player->grid_position = { (float)column, (float)row};
			}

			// WALKABLE = 7
			else if (input == 81)
			{
				grid[square_count]->walkable = true;
				grid[square_count]->deadly = false;
				grid[square_count]->texture = walkable;
			}

			// BASTARD = 76
			else if (input == 76)
			{
				grid[square_count]->walkable = true;
				grid[square_count]->deadly = false;
				grid[square_count]->texture = walkable;

				Bastard bastard;
				bastard.grid_position = { (float)column, (float)row };
				bastard.texture = bastard_texture;
				SDL_Rect bastard_rect = { 0, 0, 60, 60, 0, 0 };
				bastard.rect = bastard_rect;
				bastard.grid_to_position(size);
				bastard_arr[temp_b_count] = bastard;

				temp_b_count++;
				*bastard_count = temp_b_count;
			}	

			// LONG BASTARD = 77
			else if (input == 77)
			{
				grid[square_count]->walkable = true;
				grid[square_count]->deadly = false;
				grid[square_count]->texture = walkable;

				Long_Bastard long_bastard;
				long_bastard.grid_position = { (float)column, (float)row };
				long_bastard.texture = long_bastard_texture;
				SDL_Rect long_bastard_rect = { 0, 0, 60, 40, 0, 0 };
				long_bastard.rect = long_bastard_rect;
				long_bastard.grid_to_position(size);
				long_bastard_arr[temp_lb_count] = long_bastard;

				
				temp_lb_count++;
				*long_bastard_count = temp_lb_count;
			}

			// END = 6
			else if (input == 80)
			{
				grid[square_count]->walkable = true;
				grid[square_count]->deadly = false;
				grid[square_count]->texture = door_texture;
				printf("END FOUND\n");
			}

			
		}
	}
}