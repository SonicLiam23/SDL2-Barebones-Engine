#include "Menu.h"
#include "Globals.h"
#include "GameManager.h"
#include "Object.h"

Menu::Menu() : MenuActive(true)
{
}

void Menu::RunMenu(GameManager* GameClass, const char* ImgPath)
{
	G = GameClass;
	MenuScreen = new Object("Menu", 0, 0, Globals::SCREEN_SIZE_X, Globals::SCREEN_SIZE_Y, ImgPath, GameClass);
}

bool Menu::IsMenuActive()
{
	return MenuActive;
}

void Menu::StopMenu()
{
	G->DeleteObject(MenuScreen);
	MenuActive = false;
}


