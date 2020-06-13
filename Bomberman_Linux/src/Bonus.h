#ifndef BONUS_H
#define BONUS_H

#include "Object.h"
#include "Game.h"

/**
 * @brief									The class that represents one of the varieties of the parent class Object - the Bonus
 */
class Bonus : public Object {
public:

	/**
	 * @brief								Standard constructor initializing bonus class object
	 *
	 * @param[in] SDL_Texture * img			object texture pointer
	 * @param[in] const int & y				coordinate for drawing the texture along the Y axis
	 * @param[in] const int & x				coordinate for drawing the texture along the X axis
	 */
	Bonus(SDL_Texture *img, const int &y, const int &x);

	/**
	 * @brief								Method that responds to an attempt to destroy an object with a flame
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is possible to destroy and false otherwise
	 */
	bool tryDestroy(Game &game);

	/**
	 * @brief								Method that responds to an attempt to collect an object by player or AI
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true number of bonus type
	 */
	int tryCollect(Game &game);

	~Bonus();

};

#endif
