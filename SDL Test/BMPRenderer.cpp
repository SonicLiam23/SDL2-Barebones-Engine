#include "BMPRenderer.h"
#include "RenderModes.h"
#include <iostream>
using std::cout;

BMPRenderer::BMPRenderer(SDL_Renderer* PASSED_renderer) : m_Renderer(PASSED_renderer)
{
	m_Textures = new SDL_Texture*[Globals::MAX_OBJECTS];
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		m_Textures[i] = nullptr;
		StoredTextures[i] = NULL;
	}

}

BMPRenderer::~BMPRenderer()
{
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (m_Textures[i] != nullptr)
		{
			SDL_DestroyTexture(m_Textures[i]);
		}
	}
	delete[] m_Textures;
}

// Returns the ID the image is stored at
int BMPRenderer::AddImage(const char* Path)
{
for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (StoredTextures[i] == Path)
		{
			return i;
		}
	}
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (StoredTextures[i] == NULL)
		{
			StoredTextures[i] = Path;
			break;
		}
	}
	SDL_Texture* Texture;
	SDL_Surface* Surface = SDL_LoadBMP(Path);

	if (Surface == nullptr)
	{
		cout << "Surface is nullptr. Incorrect path?\n";
		system("Pause");
		return -1;
	}

	SDL_SetColorKey(Surface, SDL_TRUE, 0xFF00FF);
	Texture = SDL_CreateTextureFromSurface(m_Renderer, Surface);
	for (int i = 0; i < Globals::MAX_OBJECTS; ++i)
	{
		if (m_Textures[i] == nullptr)
		{
			m_Textures[i] = Texture;
			SDL_FreeSurface(Surface);
			return i;
		}
	}
	return -1;
}

int BMPRenderer::RemoveImage(int ID)
{
	if (m_Textures[ID] != nullptr)
	{
		SDL_DestroyTexture(m_Textures[ID]);
		m_Textures[ID] = nullptr;
		return 0;
	}
	return -1;
}

// Render single image
void BMPRenderer::DrawImage(int index, SDL_Rect* Position)
{
	SDL_RenderCopy(m_Renderer, m_Textures[index], NULL, Position);
}

void BMPRenderer::DrawImage(int index, SDL_Rect* ScreenPosition, SDL_Rect* ImgSection)
{
	SDL_RenderCopy(m_Renderer, m_Textures[index], ImgSection, ScreenPosition);
}
