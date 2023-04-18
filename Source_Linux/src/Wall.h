#ifndef WALL_H
#define WALL_H

#include "Object.h"
#include "Game.h"

/**
 * @brief									The class that represents one of the varieties of the parent class Object - the Wall
 */
class Wall : public Object {
public:

	/**
	 * @brief Standard constructor initializing baricade class object
	 *
	 * @param[in] SDL_Texture * img		object texture pointer
	 * @param[in] const int & y			coordinate for drawing the texture along the Y axis
	 * @param[in] const int & x			coordinate for drawing the texture along the X axis
	 */
	Wall(SDL_Texture *img, const int &y, const int &x);

	~Wall();

};

#endif
