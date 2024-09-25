#pragma once
#include "SDL.h"
#include "Globals.h"
class BMPRenderer
{
public:
	BMPRenderer(SDL_Renderer* PASSED_renderer);
	~BMPRenderer();
	int AddImage(const char* Path);
	int RemoveImage(int ID);
	void DrawImage(int index, SDL_Rect* rect);
	void DrawImage(int index, SDL_Rect* rect, SDL_Rect* ImgSection);
private:
	SDL_Renderer* m_Renderer;
	SDL_Texture** m_Textures;
	const char* StoredTextures[Globals::MAX_OBJECTS];
};

