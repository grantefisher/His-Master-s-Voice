#include <SDL.h>


extern inline void BASE_RENDER(SDL_Renderer*, SDL_Texture*, SDL_Rect*);

inline void BASE_RENDER_ALPHA(SDL_Renderer*, SDL_Texture*, SDL_Rect*, Uint8 alpha);

// TODO: ROTATE default center will be calculated to the real center of the object?
inline void BASE_RENDER_ROTATE(SDL_Renderer*, SDL_Texture*, SDL_Rect*, const double angle);

inline void BASE_RENDER_ALPHA_ROTATE(SDL_Renderer*, SDL_Texture*, SDL_Rect*, Uint8 alpha, const double angle);

inline void BASE_RENDER_FLIP(SDL_Renderer*, SDL_Texture*, SDL_Rect*, SDL_RendererFlip);

inline void BASE_RENDER_ALPHA_FLIP(SDL_Renderer*, SDL_Texture*, SDL_Rect*, Uint8 alpha, SDL_RendererFlip);