#include "Dot.h"
#include <string>
Dot::Dot(bool chaser)
{
	isChaser = chaser;
	//Initialize the offsets
	m_pos.set(0.0f, 0.0f);

	//Initialize the velocity
	m_velocity.set(0.0f, 0.0f);

	if (isChaser)
	{
		gDotTexture.setColor(244, 66, 66);
	}
	else
	{
		gDotTexture.setColor(66, 69, 244);
	}

	width = 10;
	height = 10;
	m_centre.set((m_pos.x + (width / 2)), (m_pos.y + (height / 2)));
}

Dot::~Dot()
{
	gDotTexture.free();
}

void Dot::SetPosition(float x, float y)
{
	m_pos.set(x, y);

	m_centre.set((m_pos.x + (width / 2)), (m_pos.y + (height / 2)) );
}

float Dot::length(float t_x, float t_y)
{
	return sqrt((t_x * t_x) + (t_y * t_y));
}

//"dot.bmp"
void Dot::Init(SDL_Renderer *gRenderer)
{
	if (isChaser)
	{
		if (!gDotTexture.loadFromFile("Assets/reddot.bmp", gRenderer))
		{
			printf("Failed to load dot texture!\n");
		}
	}
	else {
		if (!gDotTexture.loadFromFile("Assets/bluedot.bmp", gRenderer))
		{
			printf("Failed to load dot texture!\n");
		}
	}
}

void Dot::handleEvent(SDL_Event& e)
{
	if (isChaser)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: m_movingUp = true; break;
			case SDLK_s: m_movingDown = true; break;
			case SDLK_a: m_movingLeft = true; break;
			case SDLK_d: m_movingRight = true; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: m_movingUp = false; break;
			case SDLK_s: m_movingDown = false; break;
			case SDLK_a: m_movingLeft = false; break;
			case SDLK_d: m_movingRight = false; break;
			}
		}
	}
	else if (!isChaser)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: m_movingUp = true; break;
			case SDLK_DOWN: m_movingDown = true; break;
			case SDLK_LEFT: m_movingLeft = true; break;
			case SDLK_RIGHT: m_movingRight = true; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: m_movingUp = false; break;
			case SDLK_DOWN: m_movingDown = false; break;
			case SDLK_LEFT: m_movingLeft = false; break;
			case SDLK_RIGHT: m_movingRight = false; break;
			}
		}
		
	}
}

void Dot::update(int SCREEN_HEIGHT, int SCREEN_WIDTH)
{
	m_velocity.x = m_velocity.x * 0.99f;
	m_velocity.y = m_velocity.y * 0.99f;
	handleInput();
	//Move the dot left or right
	m_pos.x += m_velocity.x;

	//If the dot went too far to the left or right
	if ((m_pos.x < 0) || (m_pos.x + DOT_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		m_pos.x -= m_velocity.x;
		m_velocity.x = -m_velocity.x;
	}

	//Move the dot up or down
	m_pos.y += m_velocity.y;

	//If the dot went too far up or down
	if ((m_pos.y < 0) || (m_pos.y + DOT_HEIGHT > SCREEN_HEIGHT))
	{
		//Move back
		m_pos.y -= m_velocity.y;
		m_velocity.y = -m_velocity.y;
	}

	m_centre.x = m_pos.x + (width / 2);
	m_centre.y = m_pos.y + (height / 2);
}

void Dot::handleInput()
{
	if (m_movingDown)
	{
		m_velocity.y = (DOT_VEL / 90.0f);
	}
	else if (m_movingUp)
	{
		m_velocity.y = -(DOT_VEL / 90.0f);
	}

	if (m_movingRight)
	{
		m_velocity.x = (DOT_VEL / 90.0f);
	}
	else if (m_movingLeft)
	{
		m_velocity.x = -(DOT_VEL / 90.0f);
	}
	

}

void Dot::constrainSpeeds()
{

}

void Dot::render(SDL_Renderer *gRenderer)
{
	//Show the dot
	gDotTexture.render(m_pos.x, m_pos.y, gRenderer);
}

std::string Dot::GetPosAsString()
{
	return std::string("X: "+ std::to_string(m_pos.x) + ", " + "Y: " + std::to_string(m_pos.y));
}

int Dot::GetCenterX()
{
	return m_centre.x;
}

int Dot::GetCenterY()
{
	return m_centre.y;
}

bool Dot::Checkcollision(int centerX, int centerY)
{
	float distance = sqrt(((m_centre.x - centerX) * (m_centre.x - centerX)) + ((m_centre.y - centerY) * (m_centre.y - centerY)));
	
	if (distance <= width)
	{
		return true;
	}
	else
	{
		return false;
	}
}