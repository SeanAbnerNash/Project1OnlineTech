#pragma once
//@Author Sean Nash
//@Login C00217019
//Lab 4 - Engineering  - Entity Component System
//Time Taken 8 Hours.


class Vector2
{
public:
	Vector2(float x, float y);
	~Vector2() {};

	float X() { return x; };
	float Y() { return y; };
	void set(Vector2 t_vec) { x = t_vec.x; y = t_vec.y; };
	void set(float t_x, float t_y) { x = t_x; y = t_y; };
	static Vector2 sub(Vector2 leftVector, Vector2 rightVector);
	static Vector2 add(Vector2 leftVector, Vector2 rightVector);

	float x{ 0 };
	float y{ 0 };


private:

};

