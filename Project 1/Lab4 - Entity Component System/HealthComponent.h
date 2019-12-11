#pragma once
#include "Component.h"
//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.
class HealthComponent :
	public Component
{
public:
	HealthComponent() : m_health(100) { m_id = "HEALTH"; }
	~HealthComponent() { std::cout << "Bye Health Component"; };
	/* Data Only */
	int getHealth() { return m_health; }
	void setHealth(int t_health) { this->m_health = t_health; }
private:
	int m_health;

};

