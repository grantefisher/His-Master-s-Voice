// ====================================
//  Grant Fisher 2021
// ==================================== 

#pragma once

#include "masters_globals.h"
#include "masters_entity.h"
#include "masters_grid.h"

// called upon movement
extern inline void movement_update(Player*, grid_square** , vec_two, int size, direction_input);

extern inline void game_update(Player*, grid_square**, Bastard*, Long_Bastard*);

extern inline void animation_update();

//extern inline void update_relative_to_camera();
