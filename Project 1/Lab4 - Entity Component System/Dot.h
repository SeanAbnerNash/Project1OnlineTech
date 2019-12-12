#pragma once

#include "LTexture.h"
#include "Vector2.h"


class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;
	static const int MAX_VEL = 15;


	//Initializes the variables
	Dot(bool chaser);
	~Dot();

	void Init(SDL_Renderer* gRenderer);
	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void update(int SCREEN_HEIGHT, int SCREEN_WIDTH, Vector2 t_otherPos);
	void handleInput();
	void constrainSpeeds();

	//Shows the dot on the screen
	void render(SDL_Renderer *gRenderer);

	std::string GetPosAsString();

	bool Checkcollision(Vector2 t_otherPos);

	bool GetLocal() { return isLocalplayer; };

	int GetCenterX();
	int GetCenterY();

	void SetPosition(float x, float y);
	float length(float t_x, float t_y);
	Vector2 getPos();
	Vector2 getCentre();
	void reset();
	void setLocal(bool t_local);

private:
	bool isLocalplayer;
	bool isChaser;

	//The X and Y offsets of the dot
	Vector2 m_pos{ 0.0f,0.0f };

	int width, height;

	Vector2 m_centre{ 0.0f,0.0f };
	//The velocity of the dot
	Vector2 m_velocity{ 0.0f,0.0f };
	bool m_movingUp{ false };
	bool m_movingDown{ false };
	bool m_movingLeft{ false };
	bool m_movingRight{ false };



	LTexture gDotTexture;
};