#ifndef FLAME_H
#define FLAME_H

#include "Bomb.h"

/**
 * @brief									The class that represents objects, which creates by bomb explosion - the Flame
 */
class Flame : public Bomb {
public:

	/**
	 * @brief								Standard constructor initializing object - Flame
	 *
	 * @param[in] SDL_Texture * img			object texture pointer
	 * @param[in] const int & y				coordinate for drawing the texture along the Y axis
	 * @param[in] const int & x				coordinate for drawing the texture along the X axis
	 * @param[in] const int & time			time allotted for playing animation
	 * @param[in] const int & direct		flame direction number
	 * @param[in] const int & num			the number of the player who put the bomb
	 */
	Flame(SDL_Texture *img, const int &y, const int &x, const int &time, const int &direct, const int &num);

	/**
	 * @brief								Method that responds to draw animation of flame
	 *
	 * @param[in] SDL_Texture * ren			pointer to render surface
	 * @param[in] const int & frame			frame number from sprite animation
	 */
	void Draw(SDL_Renderer *ren, const int &frame) const;

	/**
	 * @brief								Method that emits activity animation
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the animation is still active and false otherwise
	 */
	bool Action(Game &game);

	~Flame();

private:

	int maxlifetime;

};

#endif
