#pragma once
#include "SDL.h"
class StarScape
{
public:
	StarScape(SDL_Renderer* renderer);
	~StarScape();
	void Update();
	void Render();

private:
	void m_MoveStarsRight();
	void m_MoveStarsUp();
	SDL_Texture* m_Texture;
	SDL_Renderer* m_Renderer;
	Uint32* m_Pixels;
	int m_NumOfStars;
	int NumOfBits;
	int* m_stars;
	int m_NumOfPixels;
	int m_FramesPerMove;
	int m_CurrentFrame;
	// 921600
};

