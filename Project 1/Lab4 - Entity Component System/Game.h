#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Dot.h"
#include "Client.h"


//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.


class Game
{
public:

	Game();
	~Game();

	void run(Client& t_client);

private:
	void processEvents();
	void update();
	void render();
	void cleanup();
	void endGame();


	std::string userinput; //holds the user's chat message



	// window used in the program
	SDL_Window* m_window;

	// used for drawing things onto the screen
	SDL_Renderer* m_renderer;

	// texture
	SDL_Texture* m_texture;


	// if game loop is happening
	bool isRunning;
	bool m_anyInput{ false };

	SDL_Keycode m_currentKey;//The Current Key Pressed for input


	std::string getErrorString(std::string t_errorMsg);
	Dot m_player;
	Dot m_player2;

	int m_gameState = 1; //0 Is Server Set up, 1 is Playing, 2 is Victory.


};

