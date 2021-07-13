// ====================================
//  Grant Fisher 2021
// ==================================== 

#pragma once
#include "masters_math.h"

#include <SDL.h>

// ANIMATION DATA STRUCTURES
enum player_anim_frame
{
	standing,
	walking,
	running,
	jumping
};

enum direction_input
{
	up,
	down,
	left,
	right,
	undo
};

// ENTITY DATA STRUCTURES
struct Player
{
	bool alive = true;
	vec_two position;
	vec_two grid_position = { 0, 0 };
	vec_two	velocity = { 0, 0 };
	// TODO: complex vector point collision structure
	SDL_Texture* texture;
	SDL_Rect* rect;
	// enum player_anim_frame anim_frame;
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