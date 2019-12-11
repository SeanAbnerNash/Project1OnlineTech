#pragma once
#include <vector>
#include <iostream>
#include "Vector2.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "PositionComponent.h"

//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.


class RenderSystem
{
	std::vector<Entity*> m_entities;
	SDL_Texture* m_texture;
	SDL_Rect m_grid;

public:
	void initializePicture(SDL_Texture* t_texture) {//Sets up the Display rect and the pointer to the texture.
		m_texture = t_texture;
		int w, h;
		SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
		m_grid.x = 0; m_grid.y = 0; m_grid.w = w/8 ; m_grid.h = h/8 ;

	};
	void addEntity(Entity* e) { m_entities.push_back(e); };
	void update(SDL_Renderer* m_renderer) {
		for (auto& ownedEntity : m_entities)
		{
			std::vector<Component*> components = ownedEntity->getComponents();
			for (auto& ownedComponent : components)
			{
				if (ownedComponent->getID() == std::string("POSITION")) {
					PositionComponent* pc = static_cast<PositionComponent*>(ownedComponent);
					Vector2 temp = pc->getPosition();
					m_grid.x = temp.x();
					m_grid.y = temp.y();
					SDL_RenderCopy(m_renderer, m_texture, NULL, &m_grid);//Draws the grid at the Entities Position.
				}

			}
		}

	}
};

