#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<Graphic> graphicIn) : BaseWindow(graphicIn)
{
	buttons.push_back(GuiButton(font, fontColor, graphic->getRenderer(), "Singleplayer", 600, 200, 110, 24, STATE::GAME));
	buttons.push_back(GuiButton(font, fontColor, graphic->getRenderer(), "Multiplayer", 600, 230, 110, 24, STATE::SERVERLIST));
}