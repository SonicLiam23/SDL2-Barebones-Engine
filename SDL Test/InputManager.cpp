#include "InputManager.h"
#include "SDL.h"
#include "GameManager.h"

KeyState InputManager::m_PressedKeys[SDL_NUM_SCANCODES];

void InputManager::Update()
{
	SDL_Event Event;
	for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
	{
		if (m_PressedKeys[i] == DOWN)
		{
			m_PressedKeys[i] = HELD;
		}
		else if (m_PressedKeys[i] == UP)
		{
			m_PressedKeys[i] = NONE;
		}
	}

	while (SDL_PollEvent(&Event))
	{
		SDL_Scancode NewScanCode = SDL_GetScancodeFromKey(Event.key.keysym.sym);


		if (Event.type == SDL_KEYDOWN)
		{
			if (m_PressedKeys[NewScanCode] == NONE)
			{
				m_PressedKeys[NewScanCode] = DOWN;
			}
		}
		else if (Event.type == SDL_KEYUP)
		{
			m_PressedKeys[NewScanCode] = UP;
		}
	}
}

bool InputManager::GetKeyUp(SDL_Keycode Key)
{
	SDL_Scancode Scan = SDL_GetScancodeFromKey(Key);
	if (m_PressedKeys[Scan] == UP)
	{
		return true;
	}
	return false;
}

bool InputManager::GetKeyDown(SDL_Keycode Key)
{
	SDL_Scancode Scan = SDL_GetScancodeFromKey(Key);
	if (m_PressedKeys[Scan] == DOWN)
	{
		return true;
	}

	return false;
}

bool InputManager::GetKeyHeld(SDL_Keycode Key)
{
	SDL_Scancode Scan = SDL_GetScancodeFromKey(Key);
	if (m_PressedKeys[Scan] == HELD)
	{
		return true;
	}

	return false;
}

void InputManager::init()
{
	for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
	{
		m_PressedKeys[i] = NONE;
	}
}
