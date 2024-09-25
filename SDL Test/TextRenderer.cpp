#include "TextRenderer.h"
#include "GameManager.h"

TextRenderer::TextRenderer(SDL_Renderer* renderer, GameManager* GameClass, const char* Text) : m_Renderer(renderer), m_GameClass(GameClass), m_Text(Text), Rect({0, 0, 150, 50})
{
	TTF_Init();
	White = { 255, 255, 255 };
	m_Font = TTF_OpenFont("KenneyFuture.ttf", 24);
	m_GameClass->SetTextRenderer(this);
	Surface = TTF_RenderText_Solid(m_Font, Text, White);
	Message = SDL_CreateTextureFromSurface(renderer, Surface);
}

void TextRenderer::Render()
{
	SDL_RenderCopy(m_Renderer, Message, NULL, &Rect);
}

void TextRenderer::SetText(const char* NewText)
{
	SDL_FreeSurface(Surface);
	SDL_DestroyTexture(Message);

	Surface = TTF_RenderText_Solid(m_Font, NewText, White);
	Message = SDL_CreateTextureFromSurface(m_Renderer, Surface);
}

TextRenderer::~TextRenderer()
{
	TTF_CloseFont(m_Font);
	SDL_FreeSurface(Surface);
	SDL_DestroyTexture(Message);
}