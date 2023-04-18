#ifndef Game_H
#define Game_H

#include "Map.h"
#include <memory>
#include <fstream>

using namespace std;

/**
 * @brief									The central class that represents Game, also stores and processes information about each object.
 */
class Game {
public:

	/**
	 * @brief								Standard default constructor initializing object - Game
	 */
	Game();

	/**
	 * @brief								Method that reads the map and initializes the variables before the game starts
	 */
	void start();

	/**
	 * @brief								Method that creates the window and loads all the necessary textures
	 *
	 * @param[in] const char * title		Window name
	 * @param[in] const int & ypos			coordinate for creating the texture along the Y axis
	 * @param[in] const int & xpos			coordinate for creating the texture along the X axis
	 * @param[in] const int & height		height of the window being created
	 * @param[in] const int & width			width of the window being created
	 * @param[in] const int & flags			some sdl flags for creating window
	 */
	void loadMenu(const char* title, const int &xpos, const int &ypos, const int &width, const int &height, const int &flags);

	/**
	 * @brief								Method that handles user presses
	 */
	void handleEvents();

	/**
	 * @brief								Method that updates object container and release switching between menu and game
	 */
	void update();

	/**
	 * @brief								Method that rengering all objects from container
	 */
	void render() const;

	/**
	 * @brief								Method that implements cleaning up memory before closing the program
	 */
	void clean() const;

	/**
	 * @brief								Method returning game state
	 *
	 * @return								true if game or manu are active and false overwise
	 */
	bool running() const;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	/**
	 * @brief								Method that pull new Bomb into list of Objects
	 *
	 * @param[in] const int & y				coordinate of position Bomb along the Y axis
	 * @param[in] const int & x				coordinate of position Bomb along the X axis
	 * @param[in] const int & range			range of bomb explosion
	 * @param[in] const int & num			the number of the player who put the bomb
	 */
	void plant(const int &x, const int &y, const int &range, const int &num);

	/**
	 * @brief								Method that pull new Bonus into list of Objects
	 *
	 * @param[in] const int & y				coordinate of position Bonus along the Y axis
	 * @param[in] const int & x				coordinate of position Bonus along the X axis
	 */
	void drop_Bonus(const int &x, const int &y);

	/**
	 * @brief								Method that pull new Flame into list of Objects
	 *
	 * @param[in] const int & y				coordinate of position Bonus along the Y axis
	 * @param[in] const int & x				coordinate of position Bonus along the X axis
	 * @param[in] const int & range			range of bomb explosion
	 * @param[in] const int & num			the number of the player who put the bomb
	 */
	void boom(const int &x, const int &y, const int &range, const int &num);

	/**
	 * @brief								Method that pull new animation of DesBar into list of Objects
	 *
	 * @param[in] const int & y				coordinate of position DesBar along the Y axis
	 * @param[in] const int & x				coordinate of position DesBar along the X axis
	 */
	void destroy_bar(const int &x, const int &y);

	/**
	 * @brief								Method that pull new animation of DesPlayer into list of Objects
	 *
	 * @param[in] const int & y				coordinate of position DesPlayer along the Y axis
	 * @param[in] const int & x				coordinate of position DesPlayer along the X axis
	 */
	void death(const int &x, const int &y);

	/**
	 * @brief								Method that check collision between flame and other objects
	 *
	 * @details								Delete object which intersect with Flame and add score to unit which place the bomb
	 *
	 * @param[in] const SDL_Rect & A		ñollision rectangle of flame
	 * @param[in] const int & num			the number of the player who put the bomb
	 */
	bool check_collision_flame(const SDL_Rect &A, const int &num);

	/**
	 * @brief								Method that check collision between Unit and other objects
	 *
	 * @details								Delete object which intersect with Unit
	 *
	 * @param[in] const SDL_Rect & A		ñollision rectangle of Unit
	 * @param[in] const int & fix			the number of layer
	 */
	bool check_collision_player(const SDL_Rect &A, const int &fix) const;

	/**
	 * @brief								Method that check collision between Unit and Bonus
	 *
	 * @details								Delete Bonus which intersect with Unit and return number of buff
	 *
	 * @param[in] const SDL_Rect & A		ñollision rectangle of Unit
	 */
	int  look_drop(const SDL_Rect &A);

	/**
	 * @brief								Method that create way for AI to the nearest Unit, Bonus or Bar
	 *
	 * @param[in] const SDL_Rect & A		ñollision rectangle of Unit
	 * @param[in] const int & mode			type of searching
	 */
	int  search_object(const SDL_Rect &A, const int &mode) const;

	/**
	 * @brief								Method that create way for AI to the nearest safe zone
	 *
	 * @param[in] const SDL_Rect & A		ñollision rectangle of Unit
	 * @param[in] const int & fix			the number of layer
	 */
	int  try_escape(const SDL_Rect &A, const int &fix) const;

	~Game();

	bool act[322];

private:

	SDL_Window *win;
	SDL_Renderer *ren;

	SDL_AudioSpec wavSpec;
	SDL_AudioSpec wavSpec1;
	SDL_AudioSpec wavSpec2;
	Uint32 wavLength;
	Uint32 wavLength1;
	Uint32 wavLength2;
	Uint8 *wavPowerup;
	Uint8 *wavDeath;
	Uint8 *wavExplosion;
	SDL_AudioDeviceID Channel1;
	SDL_AudioDeviceID Channel2;
	SDL_AudioDeviceID Channel3;

	SDL_Surface *icon;
	SDL_Texture *bomb;
	SDL_Texture *menu;
	SDL_Texture *backg;
	SDL_Texture *tileset;
	SDL_Texture *tilesetplayer;
	SDL_Texture *tilesetdeath;

	list <shared_ptr<Object>> obj;

	Map* map;

	SDL_Event event;

	ifstream fin;
	ofstream fout;

	int score1 = 0;
	int score2 = 0;
	int point_state = 0;

	char vec[17][23];
	char vec2[17][23];

	bool menuRun = false;
	bool gameRun = false;
	bool presed = false;

	int delta_time = 0;
	int frame_count = 0;

	Uint32 old_ticks = 0;
	Uint32 ticks;
	Uint32 time;
	Uint32 sprite;
};

#endif
