#include "Game.h"

//@Author Sean Nash & Oisin Wilson
//@Login C00217019 & C00213826
//Project 1
//Time Taken 8 Hours.	

#define WIDTH 700
#define HEIGHT 500

Game::Game():
m_player(false),
m_player2(true)

{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)//Initializes all SDL's modules
	{
		throw getErrorString("Error Loading SDL");
		isRunning = false;
	}
	else
	{
		
		// create window
		m_window = SDL_CreateWindow("Project One", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL);
		if (!m_window)
		{
			std::cout << getErrorString("Error Loading Window") << std::endl;
		}
		// create renderer
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (!m_renderer)
		{
			std::cout << getErrorString("Error Loading Renderer") << std::endl;
		}
		SDL_SetRenderDrawColor(m_renderer, 125, 0, 0, 255);//Sets background colour
		isRunning = true;

		//load texture
		m_texture = IMG_LoadTexture(m_renderer, "Assets/grid.png");
		if (!m_texture)
		{
			std::cout << getErrorString("Error Loading Texture") << std::endl;
		}
		m_player.Init(m_renderer);
		m_player2.Init(m_renderer);
		m_player.setLocal(true);
		m_player.SetPosition(200, 250);
		m_player2.SetPosition(400, 250);
		m_currentKey = NULL;
	}

}

Game::~Game()
{
	cleanup();
}

void Game::run(Client& t_client)
{
	double frameTime = 0.0;
	double dt = 0.0;
	double currentTime = SDL_GetTicks();
	start = SDL_GetTicks();


	while (isRunning)
	{
		dt = SDL_GetTicks() - currentTime;
		currentTime = SDL_GetTicks();
		frameTime += dt;

		while (frameTime > 1.0f / 60.0f)
		{
			//std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
			//t_client.SendString(userinput); //Send string to server

			processEvents();
			update();
			frameTime -= 1.0 / 60.0;
		}
		render();
	}
}

void Game::processEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (m_gameState)
	{
	case 0:
		break;
	case 1:
		m_player.handleEvent(event);
		m_player2.handleEvent(event);
		break;
	case 2:
		if (event.type == SDL_KEYDOWN) {
			m_anyInput = true;
		}
		break;
	}


	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		m_currentKey = event.key.keysym.sym;
		break;
	case SDL_KEYUP:
		m_currentKey = NULL;
		break;
	default:
		break;
	}



}

#include <vector>
void Game::update()
{
	switch (m_gameState) {
	case 0 :

	case 1 :
		m_player.update(HEIGHT, WIDTH, m_player2.getCentre());
		m_player2.update(HEIGHT, WIDTH, m_player.getCentre());
		if (m_player.GetLocal())
		{
			if (m_player.Checkcollision(m_player2.getCentre()))
			{
				m_gameState = 2;
				m_showEnd = true;
			}
		}

	case 2 :
		endGame();
	}


}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	switch (m_gameState) {
	case 0:

	case 1:
		m_player.render(m_renderer);
		m_player2.render(m_renderer);

	case 2:
		m_player.render(m_renderer);
		m_player2.render(m_renderer);
	}

	SDL_RenderPresent(m_renderer);
}

void Game::cleanup()
{
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_QUIT;
}

void Game::endGame()
{
	if (m_showEnd == true)
	{
		std::cout << "GAME OVER" << std::endl;
		float survivalTime = SDL_GetTicks() - start;
		survivalTime = survivalTime / 1000;
		std::cout << "It Took  " << survivalTime << " for the Chaser to catch up. " << std::endl;
		m_showEnd = false;
	}
	if (m_anyInput)
	{
		reset();
	}
}

void Game::reset()
{
	m_gameState = 1;
	m_anyInput = false ;
	m_showEnd =  false ;
	start = SDL_GetTicks();
	m_player.SetPosition(200, 250);
	m_player2.SetPosition(400, 250);
	m_player.reset();
	m_player2.reset();
}


std::string Game::getErrorString(std::string t_errorMsg)
{
	std::string sdlError = SDL_GetError();
	return t_errorMsg += " " + sdlError;
}
