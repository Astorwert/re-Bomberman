#ifndef BAR_H
#define BAR_H

#include "Bar.h"
#include "Object.h"
#include "Game.h"

/**	
 * @brief									The class that represents one of the varieties of the parent class Object - the Barricade
 */
class Bar : public Object {
public:

	 /**
	  * @brief								Standard constructor initializing baricade class object
	  *
	  * @param[in] SDL_Texture * img		object texture pointer
	  * @param[in] const int & y			coordinate for drawing the texture along the Y axis
	  * @param[in] const int & x			coordinate for drawing the texture along the X axis
	  */
	Bar(SDL_Texture *img, const int &y, const int &x);

	/**
	 * @brief								Method that responds to an attempt to destroy an object with a flame
	 * 
	 * @details								Calls a method to draw an object destruction animation 
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is possible to destroy and false otherwise
	 */
	bool tryDestroy(Game &game);

	~Bar();

};

#endif