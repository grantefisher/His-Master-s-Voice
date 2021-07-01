#include "masters_update.h"
#include <stdio.h>


extern void movement_update(Player* player,  grid_square** grid, vec_two dimensions, int size, direction_input input) 
{
	vec_two new_grid_position = player->grid_position;

	if (input == up)
	{
		new_grid_position.y += 1;
	}
	else if (input == down)
	{
		new_grid_position.y -= 1;
	}
	else if (input == left)
	{
		new_grid_position.x += 1;
	}
	else if (input == right)
	{
		new_grid_position.x -= 1;
	}

	int row = new_grid_position.y * dimensions.y;
	int column = new_grid_position.x;
	printf("grid x: %f\n", new_grid_position.x);
	printf("grid y: %f\n", new_grid_position.y);
	int index = row + column;
	printf("index: %d\n", index);
	if (grid[index]->walkable == true)
	{
		if (grid[index]->deadly == true)
		{
			player->alive = false;
			printf("Player has died\n");
		}
		player->grid_position = new_grid_position;
		player->grid_to_position(size);
	}
	else
	{
		printf("Player couldn't move in this direction\n");
	}
}

extern void game_update(Player* player, grid_square** grid, Bastard* bastard, Long_Bastard* long_bastard)
{

}