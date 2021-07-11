// ====================================
//  Grant Fisher 2021
// ==================================== 

#include "masters_entity.h"



void Player::grid_to_position(int size) // size of each grid square
{
	rect->orig_x = (grid_position.x) * size;
	rect->orig_y = (grid_position.y + 1) * size;
}



void Bastard::grid_to_position(int size)
{
	rect.orig_x = grid_position.x * size;
	rect.orig_y = grid_position.y * size;
}

void Long_Bastard::grid_to_position(int size)
{
	rect.orig_x = grid_position.x * size;
	rect.orig_y = grid_position.y * size;
}