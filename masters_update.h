// ====================================
//  Grant Fisher 2021
// ==================================== 

#pragma once

#include "masters_globals.h"
#include "masters_entity.h"
#include "masters_grid.h"

// called upon movement
extern void movement_update(Player*, grid_square** , vec_two, int size, direction_input);

extern void game_update(Player*, grid_square**, Bastard*, Long_Bastard*);

extern void animation_update();

//extern  void update_relative_to_camera();
