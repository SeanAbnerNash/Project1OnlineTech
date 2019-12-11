#pragma once
#include <vector>
#include <iostream>
#include "Vector2.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "InputComponent.h"

//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.


class ControlSystem
{
	std::vector<Entity*> m_entities;


public:
	ControlSystem() { };
	void addEntity(Entity* e) { m_entities.push_back(e); };
	void update(SDL_Keycode t_input) {
		for (auto& ownedEntity : m_entities)//For Each Entity
		{
			std::vector<Component*> components = ownedEntity->getComponents();
			InputComponent* compInput = NULL;
			PositionComponent* compPos = NULL;//Sets the base to be null

			for (auto& ownedComponent : components)//For Each Component of said entity
			{
				if (ownedComponent->getID() == std::string("POSITION")) {//If the Enitity possess both components
					compPos = static_cast<PositionComponent*>(ownedComponent);
				}

				if (ownedComponent->getID() == std::string("INPUT")) {
					compInput = static_cast<InputComponent*>(ownedComponent);
				}

			}
			if (compInput != NULL && compPos != NULL)//Only if both entities contain both valid components
			{
				Vector2 tempPos = compPos->getPosition();
				compInput->setInput(t_input);
				
				if (compInput->getInput() == SDLK_LEFT)//Control Keypresses
				{
					tempPos = Vector2::add(tempPos, Vector2(-0.5, 0));
				}

				if (compInput->getInput() == SDLK_DOWN)
				{
					tempPos = Vector2::add(tempPos, Vector2(0, 0.5));
				}
				if (compInput->getInput() == SDLK_RIGHT)
				{
					tempPos = Vector2::add(tempPos, Vector2(0.5, 0));
				}

				if (compInput->getInput() == SDLK_UP)
				{
					tempPos = Vector2::add(tempPos, Vector2(0, -0.5));
				}
				compPos->setPosition(tempPos);

			}
		}

	}
};

