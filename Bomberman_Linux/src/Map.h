#ifndef MAP_H
#define MAP_H

using namespace std;

/**
 * @brief									The class that represents rendering background and part of Map
 */
class Map {
public:

	Map();

	/**
	 * @brief								Method that responds to draw Map
	 *
	 * @param[in] SDL_Texture * ren			pointer to render surface
	 * @param[in] SDL_Texture *tileset		pointer to tilesat of textures
	 * @param[in] SDL_Texture *tileset		pointer to background image
	 */
	void drawMap(SDL_Texture *tileset, SDL_Texture *backg, SDL_Renderer *ren) const;
	
	~Map();
};

#endif