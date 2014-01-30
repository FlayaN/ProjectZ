#include "MainMenu.h"

MainMenu::MainMenu(void) : BaseWindow()
{
	buttons.push_back(GuiButton(font, fontColor, renderer, "Singleplayer", 600, 200, 256, 64, STATE::GAME));
	buttons.push_back(GuiButton(font, fontColor, renderer, "Multiplayer", 600, 300, 256, 64, STATE::SERVERLIST));
}