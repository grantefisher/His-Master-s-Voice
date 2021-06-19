// ====================================
//  Grant Fisher 2021
// ==================================== 


#pragma once

#include "masters_grid.h"
#include "masters_entity.h"
#include "masters_math.h"
#include "masters_camera.h"

#include <SDL.h>


extern inline void BASE_RENDER(SDL_Renderer*, SDL_Texture*, SDL_Rect*);

extern inline void GRID_RENDER(SDL_Renderer* renderer, grid_square** GRID, int rows, int columns);

extern inline void GRID_COORD_RENDER(SDL_Renderer* renderer, vec_two position, SDL_Texture* texture, SDL_Rect* rect);

extern inline void PLAYER_RENDER(SDL_Renderer* renderer, camera* cam_ptr, Player* player);

extern inline void BASE_RENDER_ALPHA(SDL_Renderer*, SDL_Texture*, SDL_Rect*, Uint8 alpha);

// TODO: ROTATE default center will be calculated to the real center of the object?
extern inline void BASE_RENDER_ROTATE(SDL_Renderer*, SDL_Texture*, SDL_Rect*, const double angle);

extern inline void BASE_RENDER_ALPHA_ROTATE(SDL_Renderer*, SDL_Texture*, SDL_Rect*, Uint8 alpha, const double angle);

extern inline void BASE_RENDER_FLIP(SDL_Renderer*, SDL_Texture*, SDL_Rect*, SDL_RendererFlip);

extern inline void BASE_RENDER_ALPHA_FLIP(SDL_Renderer*, SDL_Texture*, SDL_Rect*, Uint8 alpha, SDL_RendererFlip);