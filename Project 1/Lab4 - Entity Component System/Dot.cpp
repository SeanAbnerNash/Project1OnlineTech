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

	width = 50;
	height = 50;
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

Vector2 Dot::getPos()
{
	return m_pos;
}

Vector2 Dot::getCentre()
{
	return m_centre;
}

void Dot::reset()
{
	m_velocity.set(0.0f, 0.0f);
	m_centre.set((m_pos.x + (width / 2)), (m_pos.y + (height / 2)));
	m_movingDown = false;
	m_movingLeft = false;
	m_movingRight = false;
	m_movingUp = false;
	m_sprinting = false;
	m_tickTimer = 0;
	m_sprintOnCD = false;
	m_sprintBonus = 0;

}


void Dot::setLocal(bool t_local)
{
	isLocalplayer = t_local;
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
			case SDLK_LSHIFT:
				if (!m_sprintOnCD)
				{
					m_sprinting = true;
				} break;
			
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
			case SDLK_LSHIFT: 
				if (!m_sprintOnCD)
				{
					m_sprinting = true;
				} break;
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

void Dot::update(int SCREEN_HEIGHT, int SCREEN_WIDTH, Vector2 t_otherPos)
{
	m_velocity.x = m_velocity.x * 0.95f;
	m_velocity.y = m_velocity.y * 0.95f;
	handleInput();
	//Move the dot left or right
	m_pos.x += m_velocity.x;
	Checkcollision(t_otherPos);

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
	if (m_sprintOnCD)
	{
		m_tickTimer--;
		if (m_sprintBonus > 0)
		{
			m_sprintBonus -= 2;
		}
		if (m_sprintBonus < 0)
		{
			m_sprintBonus = 0;
		}
	}
	if (m_tickTimer <= 0 && m_sprintOnCD)
	{
		m_tickTimer = 0;
		m_sprintOnCD = false;
	}
}

void Dot::handleInput()
{
	if (m_sprinting)
	{
		m_sprinting = false;
		m_sprintOnCD = true;
		m_tickTimer = m_maxCoolDown;
		m_sprintBonus = m_maxSprint;
	}

	if (m_movingDown)
	{
		m_velocity.y = (DOT_VEL / 120.0f);
		m_velocity.y += m_sprintBonus;
		

	}
	else if (m_movingUp)
	{
		m_velocity.y = -(DOT_VEL / 120.0);
		m_velocity.y += -m_sprintBonus;
	}

	if (m_movingRight)
	{
		m_velocity.x = (DOT_VEL / 120.0f);
		m_velocity.x += m_sprintBonus;
	}
	else if (m_movingLeft)
	{
		m_velocity.x = -(DOT_VEL / 120.0f);
		m_velocity.x += -m_sprintBonus;
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

bool Dot::Checkcollision(Vector2 t_otherPos)
{
	float distance = sqrt(((m_centre.x - t_otherPos.x) * (m_centre.x - t_otherPos.x)) + ((m_centre.y - t_otherPos.y) * (m_centre.y - t_otherPos.y)));
	
	//std::cout << " Distance: " << distance << std::endl;

	if (distance <= width)
	{
		return true;	
	}
	else
	{
		return false;
	}
}