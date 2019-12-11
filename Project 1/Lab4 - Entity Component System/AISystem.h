#pragma once
#include <vector>
#include <iostream>
#include "Vector2.h"

#include "Entity.h"
#include "PositionComponent.h"
#include "HealthComponent.h"

//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.


class AISystem
{
	std::vector<Entity*> m_entities;


public:
	AISystem() { };
	void addEntity(Entity* e) { m_entities.push_back(e); };
	void update() {
		for (auto& ownedEntity : m_entities)//For Each Enitity in the vector
		{
		
			std::vector<Component*> components = ownedEntity->getComponents();
			HealthComponent* compHealth = NULL;
			PositionComponent* compPos = NULL;//These are only replaced if the entity has valid components.

			for (auto& ownedComponent : components)//For Each Component of said entity
			{
				if (ownedComponent->getID() == std::string("POSITION")) {//If the current Componets match the required then it casts them.
					compPos = static_cast<PositionComponent*>(ownedComponent);
					
				}

				if (ownedComponent->getID() == std::string("HEALTH")) {
					compHealth = static_cast<HealthComponent*>(ownedComponent);

				}

			}
			if (compHealth != NULL && compPos != NULL)//Both Components are valid
			{
				Vector2 tempPos = compPos->getPosition();
				
				if (compHealth->getHealth() < 50)//Moves one way above 50 HP another below it.
				{
					tempPos = Vector2::add(tempPos, Vector2(0, 0.27));

				}
				else
				{
					tempPos = Vector2::add(tempPos, Vector2(0, -0.25));
				}
				compPos->setPosition(tempPos);

			}
		}

	}
};

