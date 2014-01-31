#include "MainMenu.h"

MainMenu::MainMenu(void) : BaseWindow()
{
	buttons.push_back(GuiButton(font, fontColor, renderer, "Singleplayer", 600, 200, 110, 24, STATE::GAME));
	buttons.push_back(GuiButton(font, fontColor, renderer, "Multiplayer", 600, 230, 110, 24, STATE::SERVERLIST));
}