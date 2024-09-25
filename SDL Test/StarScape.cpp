#include "StarScape.h"
#include "Globals.h"
#include <cstring>
#include <random>

StarScape::StarScape(SDL_Renderer* renderer) : m_Renderer(renderer), m_NumOfPixels(Globals::SCREEN_SIZE_X* Globals::SCREEN_SIZE_Y), m_FramesPerMove(5), m_CurrentFrame(0)
{
	srand(time(NULL));

	NumOfBits = m_NumOfPixels * sizeof(Uint32);
	m_NumOfStars = m_NumOfPixels * 0.005;
	m_Texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, Globals::SCREEN_SIZE_X, Globals::SCREEN_SIZE_Y);
	m_Pixels = new Uint32[m_NumOfPixels];
	m_stars = new int[m_NumOfStars];
	// Set all pixels to 0
	memset(m_Pixels, 0, NumOfBits);

	int x, y, index;
	for (int i = 0; i < m_NumOfStars; ++i)
	{
		x = rand() % Globals::SCREEN_SIZE_X;
		y = Globals::SCREEN_SIZE_X * (rand() % Globals::SCREEN_SIZE_Y);
		index = x + y;
		m_Pixels[index] = 0xFFFFFFFF;
		m_stars[i] = index;
	}
	// SDL_SetTextureBlendMode(m_Texture, SDL_BLENDMODE_BLEND);
	SDL_UpdateTexture(m_Texture, NULL, m_Pixels, Globals::SCREEN_SIZE_X * sizeof(Uint32));
}

StarScape::~StarScape()
{
	delete m_Pixels;
}

void StarScape::Update()
{
	SDL_UpdateTexture(m_Texture, NULL, m_Pixels, Globals::SCREEN_SIZE_X * sizeof(Uint32));
}

void StarScape::Render()
{
	SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
}

void StarScape::m_MoveStarsRight()
{
	for (int i = 0; i < m_NumOfPixels; ++i)
	{
		if (m_Pixels[i] == 0xFFFFFFFF)
		{
			m_Pixels[i] = 0;
			if ((i % Globals::SCREEN_SIZE_X) == 0)
			{
				int LoopCoordinate = i;
				// LoopCoordinate = Globals::SCREEN_SIZE_X * (rand() % Globals::SCREEN_SIZE_Y);
				LoopCoordinate = i - Globals::SCREEN_SIZE_X + 1;
				m_Pixels[LoopCoordinate] = 0xFFFFFFFF;
			}
			else
			{
				m_Pixels[i + 1] = 0xFFFFFFFF;
				++i;
			}
		}
	}
}

void StarScape::m_MoveStarsUp()
{
	for (int i = 0; i < m_NumOfStars; ++i)
	{
		m_Pixels[m_stars[i]] = 0;
		m_stars[i] += Globals::SCREEN_SIZE_X;
		if (m_stars[i] > m_NumOfPixels - Globals::SCREEN_SIZE_X)
		{
			// m_stars[i] -= m_NumOfPixels + (m_stars[i] % Globals::SCREEN_SIZE_X);
			m_stars[i] = rand() % Globals::SCREEN_SIZE_X;
		}
		m_Pixels[m_stars[i]] = 0xFFFFFFFF;
	}
}
