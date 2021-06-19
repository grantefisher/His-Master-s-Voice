// ====================================
//  Grant Fisher 2021
// ==================================== 

#include "masters_entity.h"

void Player::move_player(direction_input input)
{
	if (input == up)
	{
		grid_position.y += 1;
	}
	else if (input == down)
	{
		grid_position.y -= 1;
	}
	else if (input == left)
	{
		grid_position.x += 1;
	}
	else if (input == right)
	{
		grid_position.x -= 1;
	}
}

void Player::grid_to_position(int size)
{
	rect->orig_x = grid_position.x * size;
	rect->orig_y = grid_position.y * size;
}