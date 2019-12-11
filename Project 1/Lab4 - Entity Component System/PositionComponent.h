#pragma once
#include "Component.h"
#include "Vector2.h"
//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.

class PositionComponent :
	public Component
{
public:
	PositionComponent() : m_position(50,50) { m_id = "POSITION"; }
	~PositionComponent() { std::cout << "Bye Position Component"; };
	/* Data Only */
	Vector2 getPosition() { return m_position; }
	void setPosition(Vector2 t_position) { this->m_position = t_position; }
	void setPosition(float t_x, float t_y) {Vector2 temp(t_x, t_y);m_position = temp;};
private:
	Vector2 m_position;
};

