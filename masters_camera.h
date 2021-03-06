// ====================================
//  Grant Fisher 2021
// ==================================== 

#pragma once

#include "masters_math.h"

#include <SDL.h>

struct camera
{
    // top-left
    vec_two center;

    // W and H
    // will be defaulted to window dimensions, then scaled
    vec_two dimensions; 
};


extern void update_rect_relative_camera(camera* deafult_cam_ref, SDL_Rect* rectangle);

extern void update_point_relative_camera(camera* default_cam_ref, int x, int y);

// TODO: update particle array relative to camera
extern  void update_particles_relative_camera();

// use when generating camera
extern  camera scaled_camera(vec_two window_dimesions, vec_two desired_dimensions);

extern  void mod_camera_center_x(camera* cam_ref, float change_x);
extern  void mod_camera_center_y(camera* cam_ref, float change_y);

extern  void update_camera_center_x(camera* cam_ref, float new_x);
extern  void update_camera_center_y(camera* cam_ref, float new_y);

extern  void mod_camera_zoom(camera* cam_ref, float change_zoom);
extern  void update_camera_zoom(camera* cam_ref, float new_zoom);