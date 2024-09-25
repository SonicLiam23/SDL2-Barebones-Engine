#include "SoundPlayer.h"
#include <iostream>
#include "GameManager.h"

SoundPlayer::SoundPlayer(int MaxSounds, GameManager* p_GameManager) : m_MaxSounds(MaxSounds)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) == -1)
	{
		std::cout << "Could not init mixer";
		system("Pause");
	}
	
	LoadedPaths = new const char* [MaxSounds];
	for (int i = 0; i < m_MaxSounds; ++i)
	{
		LoadedPaths[i] = nullptr;
	}


	Sounds = new Mix_Music*[MaxSounds];
	for (int i = 0; i < m_MaxSounds; ++i)
	{
		Sounds[i] = nullptr;
	}

	p_GameManager->SetSoundPlayer(this);
}

void SoundPlayer::PlaySound(const char* Path)
{
	bool IsAlreadyLoaded = false;
	int ID = -1;
	for (int i = 0; i < m_MaxSounds; ++i)
	{
		if (Path == LoadedPaths[i])
		{
			IsAlreadyLoaded = true;
			ID = i;
		}
	}

	if (!IsAlreadyLoaded)
	{
		for (int i = 0; i < m_MaxSounds; ++i)
		{
			if (LoadedPaths[i] == nullptr)
			{
				LoadedPaths[i] = Path;
				ID = i;
				Sounds[i] = Mix_LoadMUS(Path);
				if (Sounds[i] == nullptr)
				{
					std::cout << "Invalid mp3 path";
					return;
				}

				break;
			}
		}
	}

	if (ID == -1)
	{
		std::cout << "Max audio files loaded";
		return;
	}

	Mix_PlayMusic(Sounds[ID], 1);
}

void SoundPlayer::Uninit()
{
	for (int i = 0; i < m_MaxSounds; ++i)
	{
		if (Sounds[i] != nullptr)
		{
			Mix_FreeMusic(Sounds[i]);
		}
	}
	Mix_CloseAudio();
}
