#pragma once
#include <vector>
#include <iostream>
#include "Entity.h"
#include "HealthComponent.h"


//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.




class HealthSystem
{
	std::vector<Entity*> m_entities;

public:
	void addEntity(Entity* e) { m_entities.push_back(e); };
	void update() {
		for (auto& ownedEntity : m_entities)//For Each Entitiy
		{
			std::vector<Component*> components = ownedEntity->getComponents();
			for (auto & ownedComponent : components)//For Each component
			{
				if (ownedComponent->getID() == std::string("HEALTH")) {//If it has a component. Casts then decrements it. Resets if below zero to 100
					HealthComponent* hc = static_cast<HealthComponent*>(ownedComponent);
					hc->setHealth(hc->getHealth() - 1);
					if (hc->getHealth() < 1)
					{
						hc->setHealth(100);
					}
				}

			}
		}

	}
};


