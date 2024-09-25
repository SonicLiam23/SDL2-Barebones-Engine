#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
class GameManager;
class SoundPlayer
{
public:
	SoundPlayer(int MaxSounds, GameManager* GameManager);
	void PlaySound(const char* Path);
	void Uninit();

private:
	int m_MaxSounds;
	const char** LoadedPaths;
	SDL_AudioSpec wavSpec;
	Mix_Music** Sounds;
};

