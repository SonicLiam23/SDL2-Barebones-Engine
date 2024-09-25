//Maybe add an "autoupdate/autorender" thing, as updates happen automatically (through Game::Update() and Game::Render()), let the programmer set if they want to control that?

#include "Object.h"
#include "BMPRenderer.h"
#include "GameManager.h"
#include <iostream>
using std::cout;
/*
* x - Starting x position
* y - Starting y position
* w - Width
* h - Height
* Path - Image Path
* 
*/
Object::Object(const char* name, int P_x, int P_y, int P_w, int P_h, const char* Path, GameManager* GameClass) : m_ID(GameClass->AddObjectToArray(this)), x(P_x), y(P_y), w(P_w), h(P_h), m_Name(name), m_ImgPath(Path), MaxX(P_x + P_w), MaxY(P_y + P_h), m_ImgID(-1), m_GameClass(GameClass), m_ShowInClosestTargetTest(true)
{	
	if (m_ImgPath == "")
	{
		m_RenderMode = DO_NOT_RENDER;
	}
	else
	{
		m_RenderMode = SINGLE_IMG;
		m_ImgID = m_Renderer->AddImage(m_ImgPath);
	}
	
	m_Rect = new SDL_Rect{ x, y, w, h };
}

// FOR ANIMATIONS
// PixelWidth and PixelHeight is image pixel the width and height of a single frame 
Object::Object(const char* name, int P_x, int P_y, int P_w, int P_h, const char* Path, GameManager* GameClass, int ImgCount, int PixelWidth, int PixelHeight) : m_ID(GameClass->AddObjectToArray(this)), x(P_x), y(P_y), w(P_w), h(P_h), m_Name(name), m_ImgPath(Path), MaxX(P_x + P_w), MaxY(P_y + P_h), m_ImgID(-1), m_ImgIndex(0), m_ImgCount(ImgCount), m_GameClass(GameClass), m_ShowInClosestTargetTest(true)
{
	m_RenderMode = ANIMATION;
	m_ImgSections = new SDL_Rect * [m_ImgCount];
	for (int i = 0; i < m_ImgCount; ++i)
	{
		m_ImgSections[i] = new SDL_Rect{ i * PixelWidth, 0, PixelWidth, PixelHeight };
	}
	m_ImgID = m_Renderer->AddImage(m_ImgPath);
	m_Rect = new SDL_Rect{ x, y, w, h };
	m_AnimTimer = new double(0);
}

void Object::SetRenderer(BMPRenderer* renderer)
{
	m_Renderer = renderer;
}

void Object::Render()
{
	if (m_RenderMode == SINGLE_IMG)
	{
		m_Renderer->DrawImage(m_ImgID, m_Rect);
	}
	else if (m_RenderMode == ANIMATION)
	{
		m_Renderer->DrawImage(m_ImgID, m_Rect, m_ImgSections[m_ImgIndex]);
	}
}

void Object::Update()
{
	if (m_RenderMode == ANIMATION)
	{
		if (*m_AnimTimer >= m_AnimDelay)
		{
			m_ImgIndex = (m_ImgIndex + 1) % m_ImgCount;
			*m_AnimTimer = 0;
		}
		else
		{
			*m_AnimTimer += m_GameClass->DT();
		}
	}
	MaxX = x + w;
	MaxY = y + h;
	m_Rect->x = x; m_Rect->y = y; m_Rect->w = w; m_Rect->h = h;
}


void Object::SetDest(Object* Destination)
{
	DestX = Destination->x;
	DestY = Destination->y;
}

void Object::SetDest(int x, int y)
{
	DestX = x;
	DestY = y;
}

// Moves towards the destination set
void Object::Move()
{
	int DiffX = DestX - x;
	int DiffY = DestY - y;

	float hyp = std::sqrt((DiffX * DiffX) + (DiffY * DiffY));

	float XYRatio, YXRatio;
	XYRatio = (float)DiffX / hyp;
	YXRatio = (float)DiffY / hyp;

	x += (m_Speed * XYRatio);
	y += (m_Speed * YXRatio);
}

bool Object::AtDest()
{
	if (x == DestX && y == DestY)
	{
		return true;
	}
	return false;
}

int Object::GetSpeed()
{
	return m_Speed;
}

void Object::SetSpeed(int NewSpeed)
{
	m_Speed = NewSpeed;
}

bool Object::IsOfScreen()
{
	if (MaxX < 0)
	{
		return true;
	}
	else if (MaxY < 0)
	{
		return true;
	}
	else if (x > Globals::SCREEN_SIZE_X)
	{
		return true;
	}
	else if (y > Globals::SCREEN_SIZE_Y)
	{
		return true;
	}

	return false;
}

int Object::GetMiddleOfObjectX()
{
	return x + (w/2);
}

int Object::GetMiddleOfObjectY()
{
	return y + (h/2);
}

void Object::SetAnimDelay(float Delay)
{
	m_AnimDelay = Delay;
}

bool Object::GetShowInClosestTargetTest()
{
	return m_ShowInClosestTargetTest;
}


void Object::SetShowInClosestTargetTest(bool n)
{
	m_ShowInClosestTargetTest = n;
}
