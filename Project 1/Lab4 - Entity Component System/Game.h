#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Dot.h"

//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.


class Game
{
public:

	Game();
	~Game();

	void run();

private:
	void processEvents();
	void update();
	void render();
	void cleanup();

	// window used in the program
	SDL_Window* m_window;

	// used for drawing things onto the screen
	SDL_Renderer* m_renderer;

	// texture
	SDL_Texture* m_texture;


	// if game loop is happening
	bool isRunning;

	SDL_Keycode m_currentKey;//The Current Key Pressed for input


	std::string getErrorString(std::string t_errorMsg);
	Dot m_player;
	Dot m_player2;


};

