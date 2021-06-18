#include <SDL.h>

// ANIMATION DATA STRUCTURES
enum player_anim_frame
{
	standing,
	walking,
	running,
	jumping
};

// ENTITY DATA STRUCTURES
struct Player
{
	int x_vel = 0, y_vel = 0;
	int x, y;
	int w, h;
	// TODO: complex vector point collision structure
	SDL_Texture* texture;
	// enum player_anim_frame anim_frame;
};

struct ground
{
	int x, y;
	int w, h;
	SDL_Texture* texture;
};
