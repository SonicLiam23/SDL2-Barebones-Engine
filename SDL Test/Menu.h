#pragma once
class Object;
class GameManager;
class Menu
{
	public:
		Menu();
		void RunMenu(GameManager* GameClass, const char* ImgPath);
		bool IsMenuActive();
		void StopMenu();

private:
	GameManager* G;
	Object* MenuScreen;
	bool MenuActive;
};

