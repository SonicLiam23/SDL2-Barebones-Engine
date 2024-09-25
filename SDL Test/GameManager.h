#pragma once
#include "SDL.h"
class TextRenderer;
class BMPRenderer;
class Object;
class Player;
class SoundPlayer;
class GameManager
{
	friend class Object;
	friend class Player;
public:
	void Init();
	void Update();
	void Render();
	bool IsGameRunning();
	void StopGame(bool PlayAgain);
	void SetBgColour(int Pr, int Pg, int Pb);
	void SetPlayer(Player* p);
	Player* GetPlayer();
	int DeleteObject(Object* obj);
	/** Returns name of object you are colliding with
	* obj - The object that you are checking collisions on*/
	const char* CollidingWith(Object* obj);
	bool CollidingWithAnything(Object* obj);
	double DT();
	// void SetTextRenderer(TextRenderer* P_TextRenderer);
	int GetDistance(Object* Obj1, Object* Obj2);
	int GetDistance(Object* Obj1, int EndX, int EndY);
	Object* GetClosestTargetTo(Object* Centre);
	void SetTextRenderer(TextRenderer* TextRenderClass);
	SDL_Renderer* GetRenderer();
	void PlaySound(const char* Path);
	void SetSoundPlayer(SoundPlayer* Class);
private:
	bool m_PlayAgain;
	void UnInit();
	bool TestCollision(Object* ObjWeAreChecking, Object* OtherObj);
	int AddObjectToArray(Object* obj);
	//All objects (no object is nullptr)
	Object** m_Objects;
	SDL_Window* Window;
	// Pointer to a SDL_Renderer
	SDL_Renderer* Renderer;
	SDL_Event Event;
	// Pointer to BMPrenderer CLASS
	BMPRenderer* m_BMPRenderer;
	TextRenderer* m_TextRenderer;
	int m_ImageID;
	SDL_Rect* m_Rect;
	bool GameRunning;
	int r = 0, b = 72, g = 100;
	Player* m_PlayerClass;
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;
	SoundPlayer* m_SoundPlayerClass;
};

