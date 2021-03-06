// ====================================
//  Grant Fisher 2021
// ==================================== 


#include "masters_level_loader.h"
#include "masters_startup.h"
#include "masters_camera.h"
#include "masters_render.h"
#include "masters_update.h"
#include "masters_particle.h"
#include "audio.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>

// TODO: delete this later	
// NOTE: only using for std::cin input and debugging
#include <iostream>

// FIXES PROBLEM WITH EXTERNAL MAIN FUNCTION IN SDL
#undef main 



#define MUS_PATH "./resources/lava.wav"



int main()
{
    // INIT EXTERNALS
    ///////////////////////////
    
    // INITIALIZE SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}
    
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "couldn't initialize SDL AUDIO: %s", SDL_GetError());
		return 3;
	}
    
	initAudio();
    
    // INITIALIZE SDL IMAGE
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("SDL IMAGE could not initizalize\n");
    }
    
    
    ///////////////////////////
    // EO INIT EXTERNALS
    ///////////////////////////
    
    
    
    
    
    
    // CREATE AND SETUP WINDOW AND RENDERER
    ///////////////////////////
    
	SDL_Window* window;
	SDL_Renderer* renderer;
    
	if (SDL_CreateWindowAndRenderer(900, 700, SDL_WINDOW_SHOWN, &window, &renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "couldn't create window and renderer: %s", SDL_GetError());
		return 3;
	}
    
    
#ifdef _DEBUG
	// WINDOWED
	// NOTE: window is 900 BY 700
	printf("\nrunning debug mode\n");
#endif
    
#ifdef NDEBUG
	// FULLSCREEN
	// NOTE: window is 900 BY 700
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    
	printf("\nrunning release mode\n");
	
#endif
    
    
	SDL_ShowCursor(SDL_FALSE);
    
	SDL_RenderSetLogicalSize(renderer, 900, 700);
	
    
	SDL_SetWindowTitle(window, "His Master's Voice");
	
    
	SDL_DisplayMode current;
	int refresh_rate = 0;
	get_monitor_data(&refresh_rate, &current);
    
	///////////////////////////
    // EO CREATE AND SETUP WINDOW AND RENDERER
    ///////////////////////////
    
    
	
	
	// ALLOCATE ON STACK
	///////////////////////////
	// TODO: allocate on HEAP rather than STACK
	const char* level_list[13] = {
        "resources/level complete/level_one.txt",
        "resources/level complete/level_two.txt",
        "resources/level complete/level_three.txt",
        "resources/level complete/level_four.txt",
        "resources/level complete/level_five.txt",
        "resources/level complete/level_six.txt",
		"resources/level complete/level_seven.txt",
		"resources/level complete/level_eight.txt",
		"resources/level complete/level_nine.txt",
        "resources/level complete/level_ten.txt",
        "resources/level complete/level_fourteen.txt",
		"resources/level complete/level_fifteen.txt",
		"resources/level complete/game_over.txt" // 12
    };
	/////////////////////////////////
	// EO ALLOCATE LEVEL LIST ON STACK
	/////////////////////////////////
    
	
    
    
    
	// ALLOCATE SURFACES AND TEXTURES
	/////////////////////////////////
	SDL_Surface* surface = IMG_Load("resources/smoke.png");
	SDL_Texture* smoke_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/fireman.png");
	
    
	// NOTE: THIS SETS THE WINDOW ICON
	/////////////////////////////////
	SDL_SetWindowIcon(window, surface);
	/////////////////////////////////
    
    
	SDL_Texture* player_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/death_undo.png");
	SDL_Texture* death_undo_txt = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/conor_stand.png");
	SDL_Texture* p_frame_stand = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/conor_walk_one.png");
	SDL_Texture* p_frame_w_one = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/conor_walk_two.png");
	SDL_Texture* p_frame_w_two = SDL_CreateTextureFromSurface(renderer, surface);
	
	surface = IMG_Load("resources/conor_walk_three.png");
	SDL_Texture* p_frame_w_three = SDL_CreateTextureFromSurface(renderer, surface);
	
	surface = IMG_Load("resources/conor_walk_four.png");
	SDL_Texture* p_frame_w_four = SDL_CreateTextureFromSurface(renderer, surface);
	
	// PLAYER FRAMES (right) ALLOCATED ON HEAP BY SDL
	SDL_Texture* player_frames_right[5] = {p_frame_stand, p_frame_w_one, p_frame_w_two, p_frame_w_three, p_frame_w_four};
    
	surface = IMG_Load("resources/conor_stand_left.png");
	SDL_Texture* p_frame_stand_left = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/conor_walk_one_left.png");
	SDL_Texture* p_frame_w_one_left = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/conor_walk_two_left.png");
	SDL_Texture* p_frame_w_two_left = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/conor_walk_three_left.png");
	SDL_Texture* p_frame_w_three_left = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/conor_walk_four_left.png");
	SDL_Texture* p_frame_w_four_left = SDL_CreateTextureFromSurface(renderer, surface);
    
	// PLAYER FRAMES (left) ALLOCATED ON HEAP BY SDL
	SDL_Texture* player_frames_left[5] = { p_frame_stand_left, p_frame_w_one_left, p_frame_w_two_left, p_frame_w_three_left, p_frame_w_four_left };
    
	// LOAD GRID SQUARE TEXTURES
	surface = IMG_Load("resources/bastard.png");
	SDL_Texture* bastard_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/long_bastard.png");
	SDL_Texture* long_bastard_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/broken_long_bastard.png");
	SDL_Texture* broken_long_bastard_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/door.png");
	SDL_Texture* door_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/walkable_square.png");
	SDL_Texture* walkable = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/two_walkable_square.png");
	SDL_Texture* walkable_two = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/three_walkable_square.png");
	SDL_Texture* walkable_three = SDL_CreateTextureFromSurface(renderer, surface);
    
    
	surface = IMG_Load("resources/deadly_square.png");
	SDL_Texture* lava_one_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/deadly_square_two.png");
	SDL_Texture* lava_two_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/deadly_square_three.png");
	SDL_Texture* lava_three_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
	// CREATE LAVA TEXTURE ARRAY
	SDL_Texture* lava_txt_arr[] = { lava_one_texture, lava_two_texture, lava_three_texture };
	
    
    
    surface = IMG_Load("resources/pause_resume.png");
    SDL_Texture* pause_resume = SDL_CreateTextureFromSurface(renderer, surface);
    
    surface = IMG_Load("resources/pause_settings.png");
    SDL_Texture* pause_settings = SDL_CreateTextureFromSurface(renderer, surface);
    
    surface = IMG_Load("resources/pause_save.png");
    SDL_Texture* pause_save = SDL_CreateTextureFromSurface(renderer, surface);
    
    surface = IMG_Load("resources/pause_exit.png");
    SDL_Texture* pause_exit = SDL_CreateTextureFromSurface(renderer, surface);
    
	surface = IMG_Load("resources/hmv_title_card.png");
	SDL_Texture* title_card = SDL_CreateTextureFromSurface(renderer, surface);

	surface = IMG_Load("resources/demo_completed.png");
	SDL_Texture* game_complete_texture = SDL_CreateTextureFromSurface(renderer, surface);

	surface = IMG_Load("resources/conor_head.png");
	SDL_Texture* conor_head = SDL_CreateTextureFromSurface(renderer, surface);
    ///////////////////////////
	// EO LOAD TEXTURES
	///////////////////////////
    
    
    
    // SPECIAL CASE STRUCTURE FOR RENDERING
	struct spec_render_obj
	{
		SDL_Texture* texture;
		SDL_Rect rect = { 0, 0, 0, 0, 0, 0 };
		int alpha = 255;
	};

	std::vector<spec_render_obj*> special_render;
	spec_render_obj title_card_obj = { title_card, {90, 90, 720, 258, 0, 0} };
	special_render.push_back(&title_card_obj);
    
	// CREATE PLAYER ON HEAP
	///////////////////////////
	Player conor;
	conor.texture = player_texture;
	SDL_Rect conor_rect = { 0, 0, 40, 60, 0, 0 };
	conor.rect = &conor_rect;
	conor.grid_position = { 14, 9 };
	conor.move_state = player_move_state::standing;
	///////////////////////////
    
    
    
	// CREATE CAMERA ON HEAP
	///////////////////////////
	camera* default_camera = new camera;
	default_camera->center = { 800, 600 };
	default_camera->dimensions = { 800, 600 };
    
	camera previous_camera = *default_camera;
	///////////////////////////
	
    
    
	
    
    
	// CREATE GRID
	///////////////////////////
	// TODO: unless rows and columns will not be constant, NEED to #define these variables for preprocessing
	const int rows = 12;  
	const int columns = 16;
    
	vec_two grid_dimensions = { rows, columns };
	const int total_squares = rows * columns;
	int size = 50;
	printf("total squares: %d\n", total_squares);
    
	grid_square* gGrid = (grid_square*) calloc(total_squares, sizeof(grid_square));
	if (gGrid == NULL)
	{
		printf("ERROR allocating gGrid\n");
		return 0;
	}
	//////////////////////////////////
	// EO CREATE GRID
	//////////////////////////////////
    
    
    
    
    
    
    
	// CREATE ARRAYS ON HEAP
	///////////////////////////
	// PARTRICLE SYSTEM STACK VARIABLES
	int particle_sys_count;
	// PARTICLE SYSTEM HEAP POINTER
	Smoke_Particle_System* particle_sys_arr = (Smoke_Particle_System*) calloc(192, sizeof(Smoke_Particle_System));
    
	// B/LB COUNT VARS ON STACK
	int lb_count = 0;
	int b_count = 0;
    
	// B/LB HEAP ARRAY POINTERS
	Long_Bastard* long_bastard_arr = (Long_Bastard*) calloc(50, sizeof(Long_Bastard));
	Bastard* bastard_arr = (Bastard*) calloc(50, sizeof(Bastard));
	///////////////////////////
    
    
    
    
    
    
	// GAME STATE, FRAME, and ANIMATION VARS ON STACK
	///////////////////////////
	game_state GAME_STATE = game_state::in_game;;
    
	int level_count = 13;
	int current_level = 0;
	bool restart_level = true;
	bool next_level = false;
    
	bool running = true;
    
	int p_time = 16;
	int last_time = SDL_GetTicks();
	int current_diff;
	int bastard_frame_iterator = 0;
	int lava_animation_iterator = 0;
	int temp_door_change = -1;

	bool first_run = true;
	///////////////////////////
	// EO GAME STATE, FRAME, and ANIMATION VARS ON STACK
	///////////////////////////
    
    
    
    
    
    // CREATE AUDIO STREAM
    /////////////////////////////
	Audio* lava_audio = createAudio("resources/lava.wav", 1, SDL_MIX_MAXVOLUME/10);
	playMusicFromMemory(lava_audio, SDL_MIX_MAXVOLUME/100);
	///playSound("resources/highlands.wav", SDL_MIX_MAXVOLUME / 3);
    
    
	/////////////////////////////
    
    
    
	std::vector<direction_input> input_arr;
	bool w_pressed = false;
	bool a_pressed = false;
	bool s_pressed = false;
	bool d_pressed = false;
    
    pause_menu_state pause_state = pause_menu_state::resume;
    
    
	// GAME LOOP
	//////////////////////////////////
	while (running)
	{
		// CHECK GAME STATE
		///////////////////////////
        
		// GAME STATE is IN_GAME
		//////////////////////////////////
		if (GAME_STATE == game_state::in_game)
		{
			current_diff = SDL_GetTicks() - last_time;
			if (current_diff > 16)
			{
				// CHECK TO RESTART LEVEL
				//////////////////////////////////
				if (restart_level || conor.lives == 0)
				{
					if (current_level > level_count - 1)
					{
						return 0;
					}
					load_level(level_list[current_level], &gGrid, bastard_arr,
                               long_bastard_arr, &conor, particle_sys_arr,
                               walkable, walkable_two, walkable_three,
                               lava_one_texture, smoke_texture,
                               bastard_texture, lava_two_texture, lava_three_texture,
                               long_bastard_texture, door_texture,
                               &b_count, &lb_count, &particle_sys_count);
					for (int i = 0; i < b_count; i++)
					{
						bastard_arr[i].grid_to_position(size);
					}
					for (int i = 0; i < lb_count; i++)
					{
						long_bastard_arr[i].grid_to_position(size);
					}
					conor.grid_to_position(size);
                    conor.prev_grid_position = conor.grid_position;
					conor.lives = 3;
					conor.alive = true;
					conor.slope = { 0, 0 };
					restart_level = false;
				}
				//////////////////////////////////
				// EO CHECK TO RESTART LEVEL
				//////////////////////////////////
                
                
                
				// CHECK GO TO NEXT LEVEL
				//////////////////////////////////
				else if (next_level)
				{
					current_level++;
					printf("level: %d\n", current_level);
					if (current_level >= level_count-1)
					{
						printf("\nhere\n");
						GAME_STATE = game_state::complete;

						load_level(level_list[current_level], &gGrid, bastard_arr,
							long_bastard_arr, &conor, particle_sys_arr,
							walkable, walkable_two, walkable_three,
							lava_one_texture, smoke_texture,
							bastard_texture, lava_two_texture, lava_three_texture,
							long_bastard_texture, door_texture,
							&b_count, &lb_count, &particle_sys_count);

					}
					else
					{ 
						load_level(level_list[current_level], &gGrid, bastard_arr,
								   long_bastard_arr, &conor, particle_sys_arr,
								   walkable, walkable_two, walkable_three,
								   lava_one_texture, smoke_texture,
								   bastard_texture, lava_two_texture, lava_three_texture,
								   long_bastard_texture, door_texture,
								   &b_count, &lb_count, &particle_sys_count);
                    
						for (int i = 0; i < b_count; i++)
						{
							bastard_arr[i].grid_to_position(size);
						}
						for (int i = 0; i < lb_count; i++)
						{
							long_bastard_arr[i].grid_to_position(size);
						}
						conor.grid_to_position(size);
						conor.prev_grid_position = conor.grid_position;
						conor.slope = { 0, 0 };
						conor.lives = 3;
						restart_level = false;
						next_level = false;
					}
				}
				//////////////////////////////////
				// EO CHECK NEXT LEVEL
				//////////////////////////////////
                
                
                
                
				// UPDATE FPS TIMER
				//////////////////////////////////
				last_time = SDL_GetTicks();
				//////////////////////////////////
                
                
                
                
                
				// CHECK ENTITY FLAGS
				//////////////////////////////////
				for (int i = b_count - 1; i >= 0; i--)
				{
					if (bastard_arr[i].delete_flag)
					{
						for (int curs = i; curs <= b_count; curs++)
						{
							bastard_arr[curs] = bastard_arr[curs + 1];
						}
						b_count--;
					}
				}
				for (int i = lb_count - 1; i >= 0; i--)
				{
					if (long_bastard_arr[i].delete_flag)
					{
						for (int curs = i; curs <= lb_count; curs++)
						{
							long_bastard_arr[curs] = long_bastard_arr[curs + 1];
						}
						lb_count--;
					}
				}
				//////////////////////////////////
				// EO CHECK ENTITY FLAGS
				//////////////////////////////////
                
                
                
                
                
                
                
				// INPUT LOOP
				//////////////////////////////////
				SDL_Event Event;
                
				while (SDL_PollEvent(&Event) != 0)
				{
					if (input_arr.size() < 1)
					{
						
                        
						//User requests quit 
						if (Event.type == SDL_QUIT)
						{
							running = false;
						}
                        
						//User releases a qwkey
						else if (Event.type == SDL_KEYUP)
						{
							switch (Event.key.keysym.sym)
							{
                                case SDLK_w:
								w_pressed = false;
								break;
                                case SDLK_a:
								a_pressed = false;
								break;
                                case SDLK_s:
								s_pressed = false;
								break;
                                case SDLK_d:
								d_pressed = false;
								break;
                                default:
								break;
							}
                            
						}
                        
                        
						//User presses a key
						else if (Event.type == SDL_KEYDOWN)
						{
							switch (Event.key.keysym.sym)
							{
								case SDLK_w:
                                if (!w_pressed)
                                {
                                    input_arr.push_back(direction_input::up);
                                    w_pressed = true;
                                }
                                break;
								case SDLK_a:
                                if (!a_pressed)
                                {
                                    input_arr.push_back(direction_input::left);
                                    a_pressed = true;
                                }
                                break;
								case SDLK_s:
                                if (!s_pressed)
                                {
                                    input_arr.push_back(direction_input::down);
                                    s_pressed = true;
                                }
                                break;
								case SDLK_d:
                                if (!d_pressed)
                                {
                                    input_arr.push_back(direction_input::right);
                                    d_pressed = true;
                                }
                                break;
								case SDLK_LSHIFT:
                                input_arr.push_back(direction_input::undo);
                                break;
								case SDLK_r:
                                restart_level = true;
                                break;
								case SDLK_n: // NOTE: THIS IS ONLY FOR DEBUGGING/TESTING
                                next_level = true;
                                break;
								case SDLK_UP:
                                default_camera->center.y -= 5;
                                break;
								case SDLK_DOWN:
                                default_camera->center.y += 5;
                                break;
								case SDLK_LEFT:
                                default_camera->center.x -= 5;
                                break;
								case SDLK_RIGHT:
                                default_camera->center.x += 5;
                                break;
								case SDLK_BACKQUOTE:
                                break;
								case SDLK_ESCAPE:
                                GAME_STATE = game_state::paused;
                                break;
								default:
                                break;
							}
                            
						}
						
					}
				}
				
				//////////////////////////////////
				// EO INPUT LOOP
				//////////////////////////////////
                
                
                
                
                
                
				// PLAYER/LB MOVEMENT UPDATE
				//////////////////////////////////
				bool input_per_frame = false;
                
				direction_input input;
                
				for (int i = input_arr.size()-1; i > -1; i--) {
					
                    
					input = input_arr[i];
                    
					// PLAYER MOVEMENT UPDATE
					//////////////////////////////////
					vec_two player_new_grid_position = conor.grid_position;
                    
					if (conor.slope.x == 0 && conor.slope.y == 0)
					{
						if (input == up)
						{
							player_new_grid_position.y += 1;
							input_per_frame = true;
							input_arr.pop_back();
						}
						else if (input == down)
						{
							player_new_grid_position.y -= 1;
							input_per_frame = true;
							input_arr.pop_back();
						}
						else if (input == left)
						{
							player_new_grid_position.x += 1;
							input_per_frame = true;
							input_arr.pop_back();
						}
						else if (input == right)
						{
							player_new_grid_position.x -= 1;
							input_per_frame = true;
							input_arr.pop_back();
						}
						else if (input == undo)
						{
							if (!conor.alive)
							{
								conor.alive = true;
								conor.grid_position = conor.prev_grid_position;
								conor.grid_to_position(size);
							}
                            
							input_arr.pop_back();
							break;
						}
						else
						{
							continue;
						}
					}
                    
					if (input_per_frame && conor.alive)
					{
						int row = player_new_grid_position.y * grid_dimensions.y;
						int column = player_new_grid_position.x;
						int index = row + column;
						if (player_new_grid_position.y < grid_dimensions.x
							&& player_new_grid_position.x < grid_dimensions.y
							&& player_new_grid_position.y >= 0
							&& player_new_grid_position.x >= 0) {
							if (gGrid[index].walkable == true)
							{
								if (gGrid[index].texture == door_texture)
								{
									next_level = true;
								}
								if (gGrid[index].deadly == true)
								{
									conor.alive = false;
									conor.lives--;
								}
								conor.prev_grid_position = conor.grid_position;
								conor.grid_position = player_new_grid_position;
								if ((conor.grid_position.x - conor.prev_grid_position.x) < 0)
								{
									conor.slope.x += -1;
									conor.facing_right = true;
								}
								else if ((conor.grid_position.x - conor.prev_grid_position.x) > 0)
								{
									conor.slope.x += 1;
									conor.facing_right = false;
								}
								if ((conor.grid_position.y - conor.prev_grid_position.y) < 0)
								{
									conor.slope.y += -1;
								}
								else if ((conor.grid_position.y - conor.prev_grid_position.y) > 0)
								{
									conor.slope.y += 1;
								}
                                
                                //					conor.slope.x = (conor.grid_position.x - conor.start_grid_position.x);
                                //				conor.slope.y = (conor.grid_position.y - conor.start_grid_position.y);
                                
                                
								// CHECK IF COLLIDE WITH BASTARD
								for (int i = 0; i < b_count; i++)
								{
									if (bastard_arr[i].grid_position.x == conor.grid_position.x
										&& bastard_arr[i].grid_position.y == conor.grid_position.y)
									{
										conor.alive = false;
										conor.lives--;
										break;
									}
								}
								//////////////////////////////////
                                
                                
                                
                                
								//////////////////////////////////
								// EO PLAYER UPDATE
								//////////////////////////////////
                                
                                
                                
                                
                                
                                
								// TODO: refactor
								// LONG BASTARD MOVEMENT UPDATE
								//////////////////////////////////
								for (int lb_i = 0; lb_i < lb_count; lb_i++)
								{
									Long_Bastard* temp_long_bastard = &long_bastard_arr[lb_i];
									if (!temp_long_bastard->stuck) {
										vec_two lb_new_grid_position = temp_long_bastard->grid_position;
                                        
										if (input == up)
										{
											lb_new_grid_position.y -= 1;
										}
										else if (input == down)
										{
											lb_new_grid_position.y += 1;
										}
										else if (input == left)
										{
											lb_new_grid_position.x -= 1;
										}
										else if (input == right)
										{
											lb_new_grid_position.x += 1;
										}
                                        
										row = lb_new_grid_position.y * grid_dimensions.y;
										column = lb_new_grid_position.x;
										index = row + column;
										if (lb_new_grid_position.y < grid_dimensions.x
											&& lb_new_grid_position.x < grid_dimensions.y
											&& lb_new_grid_position.y >= 0
											&& lb_new_grid_position.x >= 0)
										{
											bool update_lb_pos = false;
											if (gGrid[index].walkable == true)
											{
												bool update_lb_pos = true;
												if (gGrid[index].deadly == true)
												{
													temp_long_bastard->stuck = true;
													printf("LB STUCK\n");
													gGrid[index].deadly = false;
													temp_long_bastard->texture = broken_long_bastard_texture;
												}
                                                
												// CHECK IF CURRENT LONG-BASTARD COLLIDES WITH ANY OF THE OTHER LONG BASTARDS
												for (int lb_j = 0; lb_j < lb_count; lb_j++)
												{
													if (lb_j != lb_i)
													{
														if (lb_new_grid_position.x == long_bastard_arr[lb_j].grid_position.x
															&& lb_new_grid_position.y == long_bastard_arr[lb_j].grid_position.y)
														{
															// CHECK IF OTHER LB is in LAVA
															int lava_grid_index = long_bastard_arr[lb_j].grid_position.x + (long_bastard_arr[lb_j].grid_position.y * grid_dimensions.y);
															if (gGrid[lava_grid_index].square_type != grid_square_type::lava)
															{
																update_lb_pos = false;
																break;
															}
														}
													}
												}
                                                
                                                
												// CHECK IF CURRENT LONG-BASTARD COLLIDES WITH ANY OF THE OTHER LONG BASTARDS
												for (int b_i = 0; b_i < b_count; b_i++)
												{
													if (lb_new_grid_position.x == bastard_arr[b_i].grid_position.x
														&& lb_new_grid_position.y == bastard_arr[b_i].grid_position.y)
													{
														update_lb_pos = false;
														break;
													}
												}
                                                
                                                
												// UPDATE THE POSITION OF THE CURRENT LONG BASTARD
												if (update_lb_pos)
												{
													temp_long_bastard->grid_position = lb_new_grid_position;
													temp_long_bastard->grid_to_position(size);
												}
											}
											else
											{
												printf("LONG BASTARD couldn't move in this direction\n");
											}
										}
									}
								}
								//////////////////////////////////
								// EO LONG BASTARD UPDATE
								//////////////////////////////////
                                
                                
                                
                                
							}
						}
						else
						{
							printf("Player couldn't move in this direction\n");
						}
					}
					//////////////////////////////////
					// EO PLAYER WALKABLE MOVEMENT UPDATE
					//////////////////////////////////
				}
                
                
                
				// PLAYER SMOOTH MOVEMENT
				//////////////////////////////////
                
				
				
                
                
				
				for (int i = 0; i < 6; i++)
				{
                    
					conor.position.x += conor.slope.x;
					conor.position.y += conor.slope.y;
                    
					conor.rect->orig_x += conor.slope.x;
					conor.rect->orig_y += conor.slope.y;
                    
					if (conor.rect->orig_x == ((conor.grid_position.x) * size) &&
						conor.rect->orig_y == ((conor.grid_position.y + .5) * size))
					{
                        
						conor.slope = { 0, 0 };
					}
				}
                
				
                
				//////////////////////////////////
				// EO PLAYER SMOOTH MOVEMENT
				//////////////////////////////////
                
				//////////////////////////////////
				// EO PLAYER/LB SMOOTH MOVEMENT
				//////////////////////////////////
                
                
                
                
                
				// B MOVEMENT UPDATE
				//////////////////////////////////
				bastard_frame_iterator++;
				if (bastard_frame_iterator >= 35)
				{
					bastard_frame_iterator = 0;
                    
					vec_two bastard_new_grid_position;
					for (int b_i = 0; b_i < b_count; b_i++)
					{
						Bastard* temp_bastard = &bastard_arr[b_i];
						bastard_new_grid_position = bastard_arr[b_i].grid_position;
						if (bastard_arr[b_i].movement.x > 0)
						{
							bastard_new_grid_position.x -= bastard_arr[b_i].direction;
						}
						if (bastard_arr[b_i].movement.y > 0)
						{
							bastard_new_grid_position.y -= bastard_arr[b_i].direction;
						}
                        
						int row = bastard_new_grid_position.y * grid_dimensions.y;
						int column = bastard_new_grid_position.x;
						if (bastard_new_grid_position.y < grid_dimensions.x
							&& bastard_new_grid_position.x < grid_dimensions.y
							&& bastard_new_grid_position.y >= 0
							&& bastard_new_grid_position.x >= 0) {
							int index = row + column;
							bool update_bastard_pos = false;
							if (gGrid[index].walkable == true)
							{
								if (!gGrid[index].deadly)
								{
									update_bastard_pos = true;
                                    
								}
								// check if colliding with LONG BASTARD
								for (int i = 0; i < lb_count; i++)
								{
									if (bastard_new_grid_position.x == long_bastard_arr[i].grid_position.x
										&& bastard_new_grid_position.y == long_bastard_arr[i].grid_position.y)
									{
										update_bastard_pos = false;
										break;
									}
								}
                                
								// CHECK IF CURRENT LONG-BASTARD COLLIDES WITH ANY OF THE OTHER LONG BASTARDS
								for (int b_j = 0; b_j < b_count; b_j++)
								{
									if (b_j != b_i)
									{
										if (bastard_new_grid_position.x == bastard_arr[b_j].grid_position.x
											&& bastard_new_grid_position.y == bastard_arr[b_j].grid_position.y)
										{
											update_bastard_pos = false;
											break;
										}
									}
								}
                                
                                
								
								if (update_bastard_pos)
								{
									bastard_arr[b_i].grid_position = bastard_new_grid_position;
									bastard_arr[b_i].grid_to_position(size);
								}
								// check if colliding with PLAYER
								if (bastard_arr[b_i].grid_position.x == conor.grid_position.x
									&& bastard_arr[b_i].grid_position.y == conor.grid_position.y)
								{
									conor.alive = false;
									conor.lives--;
								}
							}
                            
                            
						}
						bastard_arr[b_i].iteration++;
						if (bastard_arr[b_i].iteration >= bastard_arr[b_i].movement.x)
						{
							bastard_arr[b_i].iteration = 0;
							bastard_arr[b_i].direction *= -1;
						}
					}
                    
				}
				//////////////////////////////////
				// EO B UPDATE
				//////////////////////////////////
                
                
                
                
                
                
				// LAVA_SQUARE ANIMATION UPDATE
				//////////////////////////////////
				lava_animation_iterator++;
				if (lava_animation_iterator >= 55)
				{
					lava_animation_iterator = 0;
					for (int i = 0; i < total_squares; i++)
					{
						if (gGrid[i].deadly)
						{
							if (gGrid[i].alpha > 240)
							{
								gGrid[i].alpha = 200 + (rand() % (240 - 200 + 1));
							}
							gGrid[i].alpha++;
						}
					}
				}
                
                
                
                
				// LAVA_SQUARE ANIMATION UPDATE
				//////////////////////////////////
                
				for (int i = 0; i < total_squares; i++)
				{
					if (gGrid[i].deadly)
					{
						gGrid[i].animation_state++;
						int check = rand() % 500 + 200;
						if (gGrid[i].animation_state >= check)
						{
							gGrid[i].animation_state = 0;
							int texture_choice = (rand() % 99) + 1;
                            
							if (texture_choice == 1)
							{
								gGrid[i].texture = lava_two_texture;
								gGrid[i].animation_state = 100;
							}
							else if (texture_choice > 50)
							{
								gGrid[i].texture = lava_one_texture;
								gGrid[i].animation_state = 0;
							}
							else if (texture_choice <= 50)
							{
								gGrid[i].texture = lava_three_texture;
								gGrid[i].animation_state = 50;
							}
						}
					}
				}
                
				//////////////////////////////////
				// EO UPDATE LAVA SQUARE ANIMATION
				//////////////////////////////////
                
                
                
                
                
                
				// PLAYER ANIMATION
				//////////////////////////////////
				if (conor.move_state == player_move_state::walking)
				{
					if (conor.current_frame == player_anim_frame::stand)
					{
						conor.current_frame = walking_one;
					}
					else if (conor.frame_iterator % 1 == 0)
					{
						conor.current_frame = iterate_player_frame(conor.current_frame);
						if (conor.current_frame == player_anim_frame::stand)
						{
							conor.current_frame = iterate_player_frame(conor.current_frame);
						}
					}
					conor.frame_iterator++;
				}
				if (conor.slope.x == 0 && conor.slope.y == 0)
				{
					conor.move_state = player_move_state::standing;
					conor.current_frame = player_anim_frame::stand;
					conor.frame_iterator = 0;
				}
				else
				{
					conor.move_state = player_move_state::walking;
				}
                
				if (conor.facing_right)
				{
					conor.texture = player_frames_right[int(conor.current_frame)];
				}
				else
				{
					conor.texture = player_frames_left[int(conor.current_frame)];
				}
                
				//////////////////////////////////
				// EO PLAYER ANIMATION UPDATE
				//////////////////////////////////
                
                
                
                
                
                
				// UPDATE ENTITIES RELATIVE TO THE CAMERA
				//////////////////////////////////
                
				// update grid relativce to camera
				for (int i = 0; i < total_squares; i++)
				{
					update_rect_relative_camera(default_camera, &gGrid[i].rect);
				}
                
				// UPDATE PLAYER RELATIVE TO CAMERA
				update_rect_relative_camera(default_camera, conor.rect);
				// UPDATE CAMERA previous_camera
				previous_camera.center.x = default_camera->center.x;
				previous_camera.center.y = default_camera->center.y;
                
				//////////////////////////////////
				// EO CAMERA UPDATE AND ENTITY MOVEMENT RELATIVE TO CAMERA
				//////////////////////////////////
                
                
                
                
				// UPDATE PARTICLE SYSTEM 
				//////////////////////////////////
				for (int i = 0; i < particle_sys_count; i++)
				{
					particle_sys_arr[i].update();
				}
				//////////////////////////////////
                
                
				// TODO: FRAME-INDEPENDENT PROCESSING
                
                
				// RENDERING
				//////////////////////////////////////////////////////
                
				// CLEAR SCREEN
				//////////////////////////////////
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
				SDL_RenderClear(renderer);
				//////////////////////////////////
                
                
                
                
                
				// RENDER GRID
				/////////////////////////////
				GRID_RENDER(renderer, &gGrid, rows, columns);
				/////////////////////////////
                
                
                
                
                
				// RENDER BASTARDS
				/////////////////////////////
				for (int i = 0; i < b_count; i++)
				{
					update_rect_relative_camera(default_camera, &bastard_arr[i].rect);
					BASE_RENDER(renderer, bastard_arr[i].texture, &bastard_arr[i].rect);
				}
				/////////////////////////////
                
                
                
                
                
				// RENDER LONG BASTARDS
				/////////////////////////////
				for (int i = 0; i < lb_count; i++)
				{
					update_rect_relative_camera(default_camera, &long_bastard_arr[i].rect);
					BASE_RENDER(renderer, long_bastard_arr[i].texture, &long_bastard_arr[i].rect);
				}
				/////////////////////////////
                
                
                
              
                
                
				/*SDL_SetRenderDrawColor(renderer, 0, 200, 0, 100);
				SDL_Rect player_grid_pos = {  0, 0, 50, 50, conor.grid_position.x * size, conor.grid_position.y * size };
				update_rect_relative_camera(default_camera, &player_grid_pos);
				SDL_RenderDrawRect(renderer, &player_grid_pos);
                */

				// RENDER LIVES INDICATION
				/////////////////////////////
				for (int i = 0; i < conor.lives; i++)
				{
					SDL_Rect temp_rect = { (i*50) + 50, 5, 40, 40, 0, 0 };
					BASE_RENDER(renderer, conor_head, &temp_rect);
				}
				/////////////////////////////




				// RENDER PLAYER
				/////////////////////////////
				BASE_RENDER(renderer, conor.texture, conor.rect);
				/////////////////////////////
                
                
                
                
                
				// if dead
				////////////////////////////
				if (!conor.alive)
				{
					SDL_Rect render_rect;
					render_rect.orig_x = 700;
					render_rect.orig_y = 400;
					render_rect.w = 700;
					render_rect.h = 200;
                    
					update_rect_relative_camera(default_camera, &render_rect);
                    
					BASE_RENDER(renderer, death_undo_txt, &render_rect);
				}
				////////////////////////////
                
                
                
                
                
                
				// if dead and out of undo
				// TODO: RENDER DEATH TEXT
				// TODO: RESTART LEVEL PROMPT
				////////////////////////////
				/////////////////////////////
                
                
                
                
                
                
                
				// RENDER SMOKE PARTICLE SYSTEMS
				/////////////////////////////
				for (int i = 0; i < particle_sys_count; i++)
				{
					particle_sys_arr[i].render(renderer, smoke_texture);
				}
				/////////////////////////////
                
				for (int i = 0; i < special_render.size(); i++)
				{
					spec_render_obj* render_ob = special_render[i];
					if (render_ob->alpha <= 2)
					{
						SDL_DestroyTexture(render_ob->texture);
						special_render.erase(special_render.begin() + i);
						break;
					}
					render_ob->alpha -= 2;
					BASE_RENDER_ALPHA(renderer, render_ob->texture, &render_ob->rect, render_ob->alpha);
				}



				SDL_RenderPresent(renderer);
                
				if (first_run)
				{
					SDL_Delay(3100);
					first_run = false;
				}

				//////////////////////////////////////////////////////
				// EO RENDERING
				//////////////////////////////////////////////////////
			}
            
		}
		
		///////////////////////////
		// EO GAME STATE is IN_GAME
		///////////////////////////
        
        
        
        
        
        
        
        
		// GAME STATE is PAUSED
		///////////////////////////
		else if (GAME_STATE == game_state::paused)
		{
			// paused INPUT LOOP
			///////////////////////////
			SDL_Event Event;
			std::vector<direction_input> input_arr;
            
			while (SDL_PollEvent(&Event) != 0)
			{
				//User requests quit 
				if (Event.type == SDL_QUIT)
				{
					GAME_STATE = game_state::close_game;
					break;
				}
                
				//User presses a key
				else if (Event.type == SDL_KEYDOWN)
				{
					switch (Event.key.keysym.sym)
					{
                        case SDLK_w:
						input_arr.push_back(direction_input::up);
						break;
                        
                        case SDLK_a:
						input_arr.push_back(direction_input::left);
						break;
                        
                        case SDLK_s:
						input_arr.push_back(direction_input::down);
						break;
                        
                        case SDLK_d:
						input_arr.push_back(direction_input::right);
						break;
                        
                        // NOTE: ENTER READ AS UNDO DIRECTION INPUT
						case SDLK_RETURN:
                        input_arr.push_back(direction_input::undo);
						break;
                        
                        case SDLK_ESCAPE:
						GAME_STATE = game_state::in_game;
						break;
                        
                        default:
						break;
					}
                    
				}
			}
			//////////////////////////////////
			// EO INPUT LOOP
			//////////////////////////////////
            
            
            
            // INPUT PROCESSESING
			//////////////////////////////////
            for (auto input : input_arr)
            {
                if (input == direction_input::up)
                {
                    if (pause_state == pause_menu_state::resume)
                    {
                        pause_state = pause_menu_state::exit_pause;
                    }
                    else if (pause_state == pause_menu_state::exit_pause)
                    {
                        pause_state = pause_menu_state::save;
                    }
                    else if (pause_state == pause_menu_state::save)
                    {
                        pause_state = pause_menu_state::settings;
                    }
                    else if (pause_state == pause_menu_state::settings)
                    {
                        pause_state = pause_menu_state::resume;
                    }
                }
                else if (input == direction_input::down)
                {
                    if (pause_state == pause_menu_state::resume)
                    {
                        pause_state = pause_menu_state::settings;
                    }
                    else if (pause_state == pause_menu_state::settings)
                    {
                        pause_state = pause_menu_state::save;
                    }
                    else if (pause_state == pause_menu_state::save)
                    {
                        pause_state = pause_menu_state::exit_pause;
                    }
                    else if (pause_state == pause_menu_state::exit_pause)
                    {
                        pause_state = pause_menu_state::resume;
                    }
                }
                else if (input == direction_input::undo)
                {
                    if (pause_state == pause_menu_state::resume)
                    {
                        // CHANGE GAME STATE
                        GAME_STATE = game_state::in_game;
                    }
                    else if (pause_state == pause_menu_state::settings)
                    {
                        
                    }
                    else if (pause_state == pause_menu_state::save)
                    {
                        
                    }
                    else if (pause_state == pause_menu_state::exit_pause)
                    {
                        GAME_STATE = game_state::close_game;
                    }
                }
            }
            
            //////////////////////////////////
			// EO INPUT PROCESSESING
			//////////////////////////////////
            
            
            // UPDATE SMOKE PARTICLE SYSTEMS
            /////////////////////////////
            for (int i = 0; i < particle_sys_count; i++)
            {
                particle_sys_arr[i].update();
            }
            /////////////////////////////
            
            
            
            
            
			// PAUSE RENDER LOOP
			//////////////////////////////////
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
			SDL_RenderClear(renderer);
            
            // RENDER SMOKE PARTICLE SYSTEMS
            /////////////////////////////
            for (int i = 0; i < particle_sys_count; i++)
            {
                particle_sys_arr[i].render(renderer, smoke_texture);
            }
            /////////////////////////////
            
			BASE_RENDER(renderer, conor.texture, conor.rect);
            
            
            if (pause_state == pause_menu_state::resume)
            {
                SDL_Rect temp = { 400, 100, 130, 45, 0, 0 };
				SDL_SetTextureColorMod(pause_resume, 255, 255, 255);
                BASE_RENDER(renderer, pause_resume, &temp);
                
                temp.y = 250;
				SDL_SetTextureColorMod(pause_settings, 64, 64, 64);
                BASE_RENDER(renderer, pause_settings, &temp);
                
                temp.y = 400;
				SDL_SetTextureColorMod(pause_save, 64, 64, 64);
                BASE_RENDER(renderer, pause_save, &temp);
                
                temp.y = 550;
				SDL_SetTextureColorMod(pause_exit, 64, 64, 64);
                BASE_RENDER(renderer, pause_exit, &temp);
            }
            else if (pause_state == pause_menu_state::settings)
            {
                SDL_Rect temp = { 400, 100, 130, 45, 0, 0 };
				SDL_SetTextureColorMod(pause_resume, 64, 64, 64);
                BASE_RENDER(renderer, pause_resume, &temp);
                
                temp.y = 250;
				SDL_SetTextureColorMod(pause_settings, 255, 255, 255);
                BASE_RENDER(renderer, pause_settings, &temp);
                
                temp.y = 400;
				SDL_SetTextureColorMod(pause_save, 64, 64, 64);
                BASE_RENDER(renderer, pause_save, &temp);
                
                temp.y = 550;
				SDL_SetTextureColorMod(pause_exit, 64, 64, 64);
                BASE_RENDER(renderer, pause_exit, &temp);
            }
            else if (pause_state == pause_menu_state::save)
            {
                SDL_Rect temp = { 400, 100, 130, 45, 0, 0 };
				SDL_SetTextureColorMod(pause_resume, 64, 64, 64);
                BASE_RENDER(renderer, pause_resume, &temp);
                
                temp.y = 250;
				SDL_SetTextureColorMod(pause_settings, 64, 64, 64);
                BASE_RENDER(renderer, pause_settings, &temp);
                
                temp.y = 400;
				SDL_SetTextureColorMod(pause_save, 255, 255, 255);
                BASE_RENDER(renderer, pause_save, &temp);
                
                temp.y = 550;
				SDL_SetTextureColorMod(pause_exit, 64, 64, 64);
                BASE_RENDER(renderer, pause_exit, &temp);
            }
            else if (pause_state == pause_menu_state::exit_pause)
            {
                SDL_Rect temp = { 400, 100, 130, 45, 0, 0 };
				SDL_SetTextureColorMod(pause_resume, 64, 64, 64);
                BASE_RENDER(renderer, pause_resume, &temp);
                
                temp.y = 250;
				SDL_SetTextureColorMod(pause_settings, 64, 64, 64);
                BASE_RENDER(renderer, pause_settings, &temp);
                
                temp.y = 400;
				SDL_SetTextureColorMod(pause_save, 64, 64, 64);
                BASE_RENDER(renderer, pause_save, &temp);
                
                temp.y = 550;
				SDL_SetTextureColorMod(pause_exit, 255, 255, 255);
                BASE_RENDER(renderer, pause_exit, &temp);
            }
            
            
            
			SDL_RenderPresent(renderer);
			//////////////////////////////////
			// EO PAUSE RENDER LOOP
			//////////////////////////////////
            
            
		}
		///////////////////////////
		// EO GAME STATE is PAUSED
		///////////////////////////
        
		
        
        
        
        
		// GAME STATE is CLOSE_GAME
		///////////////////////////
		else if (GAME_STATE == game_state::close_game)
		{
			running = false;
		}
		///////////////////////////
		// EO GAME STATE is CLOSE_GAME
		///////////////////////////
        
		else if (GAME_STATE == game_state::complete)
		{
			// paused INPUT LOOP
			///////////////////////////
			SDL_Event Event;
			std::vector<direction_input> input_arr;

			while (SDL_PollEvent(&Event) != 0)
			{
				//User requests quit 
				if (Event.type == SDL_QUIT)
				{
					GAME_STATE = game_state::close_game;
					break;
				}

				//User presses a key
				else if (Event.type == SDL_KEYDOWN)
				{
					switch (Event.key.keysym.sym)
					{
					// NOTE: ENTER READ AS UNDO DIRECTION INPUT
					case SDLK_RETURN:
						GAME_STATE = game_state::close_game;
						break;
					default:
						break;
					}

				}
			}
			//////////////////////////////////
			// EO INPUT LOOP
			//////////////////////////////////










			// update grid relativce to camera
			for (int i = 0; i < total_squares; i++)
			{
				update_rect_relative_camera(default_camera, &gGrid[i].rect);
			}


			// LAVA_SQUARE ANIMATION UPDATE
			//////////////////////////////////
			lava_animation_iterator++;
			if (lava_animation_iterator >= 55)
			{
				lava_animation_iterator = 0;
				for (int i = 0; i < total_squares; i++)
				{
					if (gGrid[i].deadly)
					{
						if (gGrid[i].alpha > 240)
						{
							gGrid[i].alpha = 200 + (rand() % (240 - 200 + 1));
						}
						gGrid[i].alpha++;
					}
				}
			}



			// LAVA_SQUARE ANIMATION UPDATE
			//////////////////////////////////

			for (int i = 0; i < total_squares; i++)
			{
				if (gGrid[i].deadly)
				{
					gGrid[i].animation_state++;
					int check = rand() % 500 + 200;
					if (gGrid[i].animation_state >= check)
					{
						gGrid[i].animation_state = 0;
						int texture_choice = (rand() % 99) + 1;

						if (texture_choice == 1)
						{
							gGrid[i].texture = lava_two_texture;
							gGrid[i].animation_state = 100;
						}
						else if (texture_choice > 50)
						{
							gGrid[i].texture = lava_one_texture;
							gGrid[i].animation_state = 0;
						}
						else if (texture_choice <= 50)
						{
							gGrid[i].texture = lava_three_texture;
							gGrid[i].animation_state = 50;
						}
					}
				}
			}

			//////////////////////////////////
			// EO UPDATE LAVA SQUARE ANIMATION
			//////////////////////////////////

			// UPDATE SMOKE PARTICLE SYSTEMS
			/////////////////////////////
			for (int i = 0; i < particle_sys_count; i++)
			{
				particle_sys_arr[i].update();
			}
			/////////////////////////////





			// GAME COMPLETE RENDER LOOP
			//////////////////////////////////
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
			SDL_RenderClear(renderer);
			
			// RENDER GRID
			/////////////////////////////
			GRID_RENDER(renderer, &gGrid, rows, columns);
			/////////////////////////////

			BASE_RENDER(renderer, conor.texture, conor.rect);


			// RENDER SMOKE PARTICLE SYSTEMS
			/////////////////////////////
			for (int i = 0; i < particle_sys_count; i++)
			{
				particle_sys_arr[i].render(renderer, smoke_texture);
			}
			/////////////////////////////

			SDL_Rect temp_rect = { 0, 100, 900, 524, 0, 0 };

			BASE_RENDER(renderer, game_complete_texture, &temp_rect);




			SDL_RenderPresent(renderer);
		}
		///////////////////////////
		// EO GAME STATE is COMPLETE
		///////////////////////////
        
        
        
        
		//////////////////////////
		// EO CHECK GAME STATE
		//////////////////////////
	}
    
	///////////////////////////
	// EO GAME LOOP
	///////////////////////////
    
    
    
    // CLOSE EVERYTHING
	endAudio();
	freeAudio(lava_audio);
    
    
	// CLOSE PROGRAM, DEALLOCATE MEMORY
	///////////////////////////
	// TODO: properly deallocate memory
    
	SDL_Quit();
    
	///////////////////////////
	// EO CLOSE PROGRAM, DEALLOCATE MEMORY
	///////////////////////////
    
    
    
    
    
    
	return 0;
}