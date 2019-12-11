#include "Vector2.h"
//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.


Vector2::Vector2(float x, float y)
{
	x = x;
	y = y;
}

Vector2 Vector2::add(Vector2 leftVector, Vector2 rightVector)
{
	return Vector2(leftVector.x + rightVector.x, leftVector.y + rightVector.y);
}

Vector2 Vector2::sub(Vector2 leftVector, Vector2 rightVector)
{
	return Vector2(leftVector.x - rightVector.x, leftVector.x - rightVector.x);
}
