#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class GameManager;
class TextRenderer
{
public:
	TextRenderer(SDL_Renderer* renderer, GameManager* GameClass, const char* Text);
	void Render();
	void SetText(const char* NewText);
	~TextRenderer();
	

private:
	SDL_Renderer* m_Renderer;
	TTF_Font* m_Font;
	SDL_Color White;
	GameManager* m_GameClass;
	SDL_Surface* Surface;
	const char* m_Text;
	SDL_Texture* Message;
	const SDL_Rect Rect;

};

