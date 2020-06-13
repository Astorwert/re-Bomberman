#ifndef TEXTURE_H
#define TEXTURE_H

using namespace std;

//basic sdl function which load texture from image
SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren);

//function which render texture from without animation
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, const int &x, const int &y, const int &h, const int &w);

//function which render texture from with animation
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, const int &x, const int &y, const int &h, const int &w, const int &frame);

//function which render animation of Unit
void renderPlayer(SDL_Texture *tex, SDL_Renderer *ren, const int &x, const int &y, const int &sprite, const int &direct, const int &move);

#endif 