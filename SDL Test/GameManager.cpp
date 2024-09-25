#include "GameManager.h"
#include "RenderModes.h"
#include "InputManager.h"
//#include "StarScape.h"
#include "Globals.h"
#include "BMPRenderer.h"
#include "Object.h"
#include "TextRenderer.h"
#include "SoundPlayer.h"
#include <iostream>
using std::cout;

void GameManager::Init()
{
	// This can only run as false the first time we are playing
	if (!m_PlayAgain)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			// Log error
			cout << "Error bc ur bad (skill issue)";
			system("Pause");
		}

		Window = SDL_CreateWindow("window", 100, 100, Globals::SCREEN_SIZE_X, Globals::SCREEN_SIZE_Y, SDL_WINDOW_BORDERLESS);
		Renderer = SDL_CreateRenderer(Window, 0, 0);
	}

	m_BMPRenderer = new BMPRenderer(Renderer);
	m_SoundPlayerClass = new SoundPlayer(4, this);
	GameRunning = true;
	m_TextRenderer = nullptr;
	SDL_SetRenderDrawColor(Renderer, r, g, b, 255);

	// init the objects array
	m_Objects = new Object*[Globals::MAX_OBJECTS];
	// Set all objects to be nullptr
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		m_Objects[i] = nullptr;
	}
	m_PlayerClass = nullptr;

}

void GameManager::Update()
{
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (m_Objects[i] != nullptr)
		{
			m_Objects[i]->Update();
		}
	}


	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

	SDL_Delay(1000 / 60);
}

void GameManager::Render()
{
	SDL_RenderClear(Renderer);
	// Render textures/objects and whatnot
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (m_Objects[i] != nullptr)
		{
			m_Objects[i]->Render();
		}
	}

	if (m_TextRenderer != nullptr)
	{
		m_TextRenderer->Render();
	}
	SDL_RenderPresent(Renderer);
	SDL_SetRenderDrawColor(Renderer, r, g, b, 255);
}

bool GameManager::IsGameRunning()
{
	return GameRunning;
}

void GameManager::StopGame(bool PlayAgain)
{
	m_PlayAgain = PlayAgain;
	GameRunning = false;
	UnInit();
}

void GameManager::UnInit()
{
	delete m_BMPRenderer;
	delete m_Rect;
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (m_Objects[i] != nullptr)
		{
			if (m_Objects[i]->m_RenderMode == ANIMATION)
			{
				for (int j = 0; i < m_Objects[i]->m_ImgCount; ++i)
				{
					delete m_Objects[i]->m_ImgSections[j];
				}
				delete[] m_Objects[i]->m_ImgSections;
			}
			delete m_Objects[i]->m_Rect;
		}
	}
	delete[] m_Objects;
	m_SoundPlayerClass->Uninit();
	delete m_SoundPlayerClass;
	if (!m_PlayAgain)
	{
		SDL_DestroyWindow(Window);
		SDL_DestroyRenderer(Renderer);
		SDL_Quit();
	}

}

void GameManager::SetBgColour(int Pr, int Pg, int Pb)
{
	r = Pr;
	g = Pg;
	b = Pb;
}

void GameManager::SetPlayer(Player* p)
{
	m_PlayerClass = p;
}

Player* GameManager::GetPlayer()
{
	//will return nullptr if no player is set
	return m_PlayerClass;
}

/*
* Adds the object to the array and sets the renderer
*/
int GameManager::AddObjectToArray(Object* obj)
{
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (m_Objects[i] == nullptr)
		{
			m_Objects[i] = obj;
			m_Objects[i]->SetRenderer(m_BMPRenderer);
			return i;
		}
	}
	return -2;
}

/* Deletes an object.
* obj - Reference to the object to delete
* Returns 0 if successful.
* Returns -1 if unsuccessful (Probably incorrect name).
* 
* This also uses the "delete" operator, so no memory leaks! (You're welcome Matt)
*/
int GameManager::DeleteObject(Object* obj)
{
	m_Objects[obj->m_ID] = nullptr;
	// m_BMPRenderer->RemoveImage(obj->m_ID);
	delete obj->m_Rect;
	delete obj;
	
	return 0;
}

const char* GameManager::CollidingWith(Object* obj)
{
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (m_Objects[i] != nullptr && obj != m_Objects[i])
		{
			if (TestCollision(obj, m_Objects[i]))
			{
				return m_Objects[i]->m_Name;
			}
		}
	}
	return "";
}
bool GameManager::CollidingWithAnything(Object* obj)
{
	bool colliding;
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (m_Objects[i] != nullptr && obj != m_Objects[i])
		{
			colliding = TestCollision(obj, m_Objects[i]);
			if (colliding)
			{
				return true;
			}
		}
	}
	return false;
}

double GameManager::DT()
{
	return deltaTime;
}

int GameManager::GetDistance(Object* Obj1, Object* Obj2)
{
	int DiffX = Obj2->x - Obj1->x;
	int DiffY = Obj2->y - Obj1->y;
	int DiffX2 = DiffX * DiffX;
	int DiffY2 = DiffY * DiffY;
	int FinalDistance = std::sqrt(DiffX2 + DiffY2);

	return FinalDistance;
}
int GameManager::GetDistance(Object* Obj1, int EndX, int EndY)
{
	int DiffX = EndX - Obj1->x;
	int DiffY = EndY - Obj1->y;
	int DiffX2 = DiffX * DiffX;
	int DiffY2 = DiffY * DiffY;
	int FinalDistance = std::sqrt(DiffX2 + DiffY2);

	return FinalDistance;
}

Object* GameManager::GetClosestTargetTo(Object* Centre)
{
	// set it to the max, any number will be below this
	int ShortestDist = INT_MAX;
	Object* CurrentClosestObj = nullptr;
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (m_Objects[i] != nullptr)
		{
			if (m_Objects[i]->m_ID != Centre->m_ID && m_Objects[i]->GetShowInClosestTargetTest())
			{
				int Dist = GetDistance(Centre, m_Objects[i]);
				if (Dist < ShortestDist)
				{
					ShortestDist = Dist;
					CurrentClosestObj = m_Objects[i];
				}
			}
		}
	}
	return CurrentClosestObj;
}

void GameManager::SetTextRenderer(TextRenderer* TextRenderClass)
{
	m_TextRenderer = TextRenderClass;
}

SDL_Renderer* GameManager::GetRenderer()
{
	return Renderer;
}

void GameManager::PlaySound(const char* Path)
{
	m_SoundPlayerClass->PlaySound(Path);
}

void GameManager::SetSoundPlayer(SoundPlayer* Class)
{
	m_SoundPlayerClass = Class;
}


bool GameManager::TestCollision(Object* ObjWeAreChecking, Object* OtherObj)
{
	if (ObjWeAreChecking->y > OtherObj->MaxY)
	{
		return false;
	}
	else if (ObjWeAreChecking->MaxY < OtherObj->y)
	{
		return false;
	}
	else if (ObjWeAreChecking->x > OtherObj->MaxX)
	{
		return false;
	}
	else if (ObjWeAreChecking->MaxX < OtherObj->x)
	{
		return false;
	}

	return true;
}