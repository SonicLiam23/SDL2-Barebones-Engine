#pragma once
#include "SDL.h"

enum KeyState
{
	NONE,
	HELD,
	UP,
	DOWN
};

class InputManager
{
public:
	static void Update();
	static bool GetKeyUp(SDL_Keycode Key);
	static bool GetKeyDown(SDL_Keycode Key);
	static bool GetKeyHeld(SDL_Keycode Key);
	static void init();
	

private:
	static KeyState m_PressedKeys[SDL_NUM_SCANCODES];


};

