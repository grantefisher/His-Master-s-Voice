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
	right
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

	void move_player(direction_input input);
	void grid_to_position(int size);
};

struct Bastard
{
	vec_two grid_position = { 0, 0 };
	SDL_Texture* texture;
	SDL_Rect* rect;

	void move_bastard(direction_input input);
	void grid_to_position(int size);
};

struct Long_Bastard
{
	vec_two grid_position = { 0, 0 };
	SDL_Texture* texture;
	SDL_Rect* rect;

	void move_long_bastard(direction_input input);
	void grid_to_position(int size);
};