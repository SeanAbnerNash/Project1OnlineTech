#pragma once
#include "Component.h"
#include <SDL.h>
//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.
class InputComponent :
	public Component
{
public:
	InputComponent() : m_input(false) { m_id = "INPUT"; }
	~InputComponent() { std::cout << "Bye Input Component"; };
	/* Data Only */
	SDL_Keycode getInput() { return m_input; };
	void setInput(SDL_Keycode t_input) { this->m_input = t_input; };
private:
	SDL_Keycode m_input;
};

