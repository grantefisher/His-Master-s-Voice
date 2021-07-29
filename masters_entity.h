// ====================================
//  Grant Fisher 2021
// ==================================== 

#pragma once
#include "masters_math.h"

#include <SDL.h>

// ANIMATION DATA STRUCTURES
enum player_move_state
{
	standing,
	walking,
	dead
};

enum player_anim_frame
{
	stand,
	walking_one,
	walking_two,
	walking_three,
	walking_four
};

inline player_anim_frame iterate_player_frame(player_anim_frame frame)
{
	if (frame == player_anim_frame::stand)
	{
		return player_anim_frame::walking_one;
	}
	else if (frame == player_anim_frame::walking_one)
	{
		return player_anim_frame::walking_two;
	}
	else if (frame == player_anim_frame::walking_two)
	{
		return player_anim_frame::walking_three;
	}
	else if (frame == player_anim_frame::walking_three)
	{
		return player_anim_frame::walking_four;
	}
	else
	{
		return player_anim_frame::stand;
	}
}

enum direction_input
{
	up,
	down,
	left,
	right,
	undo
};


//void grid_to_position(auto& pointer);

// ENTITY DATA STRUCTURES
struct Player
{
	bool alive = true;
	vec_two position;
	vec_two grid_position = { 0, 0 };
	vec_two	slope = { 0, 0 };
	// TODO: complex vector point collision structure
	SDL_Texture* texture;
	SDL_Rect* rect;
	int frame_iterator = 0;
	enum player_move_state move_state = player_move_state::standing;
	enum player_anim_frame current_frame;

	bool facing_right = true;

	vec_two prev_grid_position = { 0, 0 };
	int undo_count = 3;
	int lives = 3;

	void grid_to_position(int size);
};

struct Bastard
{
	vec_two grid_position = { 0, 0 };
	SDL_Texture* texture;
	SDL_Rect rect;
	vec_two movement = { 4, 0 };
	int iteration = 0;
	int direction = 1;
	bool delete_flag = false;
	void grid_to_position(int size);
};

struct Long_Bastard
{
	vec_two grid_position = { 0, 0 };
	SDL_Texture* texture;
	SDL_Rect rect;

	bool stuck = false;
	bool delete_flag = false;
	void grid_to_position(int size);
};
