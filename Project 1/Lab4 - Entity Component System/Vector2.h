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

	float x() { return m_x; };
	float y() { return m_y; };
	void set(Vector2 t_vec) { m_x = t_vec.x(); m_y = t_vec.y(); };
	void set(float t_x, float t_y) { m_x = t_x; m_y = t_y; };
	static Vector2 sub(Vector2 leftVector, Vector2 rightVector);
	static Vector2 add(Vector2 leftVector, Vector2 rightVector);


private:
	float m_x;
	float m_y;
};

