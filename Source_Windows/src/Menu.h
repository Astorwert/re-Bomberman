#ifndef MENU_H
#define MENU_H

class Menu {
public:
	void create(const char* title, int xpos, int ypos, int width, int height, int flags);

private:
	SDL_Window *win;
	SDL_Renderer *ren;
};

#endif