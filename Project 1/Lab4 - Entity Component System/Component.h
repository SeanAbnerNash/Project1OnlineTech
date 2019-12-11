#pragma once
#include <iostream>
//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.
class Component
{
public:
	Component() {}
	virtual ~Component() {};
	std::string m_id{""};//THE ID IS USED TO IDENTIFY COMPONENTS
	void setID(std::string t_id) { m_id = t_id; };
	std::string getID() { return m_id; };
};

