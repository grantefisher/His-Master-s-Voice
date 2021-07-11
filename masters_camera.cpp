// ====================================
//  Grant Fisher 2021
// ==================================== 

#include "masters_camera.h"

 void update_rect_relative_camera(camera* cam_ref, SDL_Rect* rectangle)
{
	rectangle->x = cam_ref->center.x - rectangle->orig_x;
	rectangle->y = cam_ref->center.y - rectangle->orig_y;
}


 void mod_camera_center_x(camera* cam_ref, float change_x)
{
	cam_ref->center.x += change_x;
}

 void mod_camera_center_y(camera* cam_ref, float change_y)
{
	cam_ref->center.y += change_y;
}

 void update_camera_center_x(camera* cam_ref, float new_x)
{
	cam_ref->center.x = new_x;
}

 void update_camera_center_y(camera* cam_ref, float new_y)
{
	cam_ref->center.y = new_y;
}


// TODO: write camera zoom functions
 void mod_camera_zoom(camera* cam_ref, float change_zoom)
{

}

 void update_camera_zoom(camera* cam_Ref, float new_zoom)
{

}
