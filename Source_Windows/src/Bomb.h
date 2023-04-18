#ifndef BOMB_H
#define BOMB_H

#include "Object.h"
#include "Game.h"

/**
 * @brief The class that represents one of the varieties of the parent class Object - the Bomb
 */
class Bomb : public Object {
public:

	/**
	 * @brief								Standard constructor initializing baricade class object
	 *
	 * @param[in] SDL_Texture * img			object texture pointer
	 * @param[in] const int & y				coordinate for drawing the texture along the Y axis
	 * @param[in] const int & x				coordinate for drawing the texture along the X axis
	 * @param[in] const int & e				time before the boom explose
	 * @param[in] const int & r				bomb blast radius
	 * @param[in] const int & num			the number of the player who put the bomb
	 */
	Bomb(SDL_Texture *img, const int &y, const int &x, const int &e, const int &r, const int &num);

	/**
	 * @brief								Method that responds to an attempt to destroy an object with a flame
	 *
	 * @details								Calls a method to release bomb explosion
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is possible to destroy and false otherwise
	 */
	bool tryDestroy(const Game &game);

	/**
	 * @brief								Method that responds to draw animation of bomb
	 *
	 * @param[in] SDL_Texture * ren			pointer to render surface
	 * @param[in] const int & frame			frame number from sprite animation
	 */
	void Draw(SDL_Renderer *ren, const int &frame) const;

	/**
	 * @brief								Method that emits object activity
	 *
	 * @details								Calls a method to release bomb explosion if timer expired
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is still active and false otherwise
	 */
	bool Action(Game &game);

	~Bomb();

protected:

	int lifetime, range, n;

};

#endif
