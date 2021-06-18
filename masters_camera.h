// ====================================
//  Grant Fisher 2021
// ==================================== 

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

extern inline void update_rect_relative_camera(camera* deafult_cam_ref, SDL_Rect* rectangle);

// use when generating camera
extern inline camera scaled_camera(vec_two window_dimesions, vec_two desired_dimensions);

extern inline void mod_camera_center_x(camera* cam_ref, float change_x);
extern inline void mod_camera_center_y(camera* cam_ref, float change_y);

extern inline void update_camera_center_x(camera* cam_ref, float new_x);
extern inline void update_camera_center_y(camera* cam_ref, float new_y);

extern inline void mod_camera_zoom(camera* cam_ref, float change_zoom);
extern inline void update_camera_zoom(camera* cam_ref, float new_zoom);