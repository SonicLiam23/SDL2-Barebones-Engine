#pragma once
#include "SDL.h"
#include "RenderModes.h"
class BMPRenderer;
class GameManager;

// Code in Object.cpp
class Object
{
	friend class GameManager;
public:
	Object(const char* name, int P_x, int P_y, int P_w, int P_h, const char* Path, GameManager* GameClass);
	Object(const char* name, int P_x, int P_y, int P_w, int P_h, const char* Path, GameManager* GameClass, int ImgCount, int PixelWidth, int PixelHeight);
	int x, y, w, h;
	const char* m_Name;
	void SetDest(Object* Destination);
	void SetDest(int x, int y);
	void Move();
	bool AtDest();
	int GetSpeed();
	void SetSpeed(int NewSpeed);
	bool IsOfScreen();
	int GetMiddleOfObjectX();
	int GetMiddleOfObjectY();
	void SetAnimDelay(float Delay);
	bool GetShowInClosestTargetTest();
	void SetShowInClosestTargetTest(bool n);

private:
	bool m_ShowInClosestTargetTest;
	double* m_AnimTimer;
	double m_AnimDelay;
	int m_Speed;
	int MaxX, MaxY;
	void SetRenderer(BMPRenderer* renderer);
	int m_ImgCount;
	// Pointer, as I do not want this to exist unless we're in animation 
	int m_ImgIndex;
	SDL_Rect** m_ImgSections;

protected:
	GameManager* m_GameClass;
	int DestY, DestX;
	virtual void Update();
	virtual void Render();
	int m_ID;
	int m_ImgID;
	BMPRenderer* m_Renderer;
	const char* m_ImgPath;
	SDL_Rect* m_Rect;
	RenderMode m_RenderMode;
};

/** Code in Player.cpp
* Only one player class allowed, creating another will render the previous player classes as regular objects
*/



