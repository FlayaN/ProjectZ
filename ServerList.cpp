#include "ServerList.h"

ServerList::ServerList(void) : BaseWindow()
{
	texts.push_back(GuiText(font, fontColor, renderer, "IP", 100, 20));
	texts.push_back(GuiText(font, fontColor, renderer, "Name", 300, 20));
	texts.push_back(GuiText(font, fontColor, renderer, "Description", 500, 20));
	texts.push_back(GuiText(font, fontColor, renderer, "Ping", 1100, 20));
	buttons.push_back(GuiButton(font, fontColor, renderer, "BACK", 100, 600, 256, 64, STATE::MAINMENU));
	buttons.push_back(GuiButton(font, fontColor, renderer, "Refresh", 600, 600, 256, 64, STATE::SERVERLIST));
	loadServerList();
	yourIp = Utility::doWebRequest("http://icanhazip.com");
	yourIp = std::regex_replace(yourIp,std::regex("\\s+"), "");
}

void ServerList::renderBody(void)
{
	BaseWindow::renderBody();

	for(int i = 0; i < serverList.size(); i++)
	{
		serverList[i].render();
	}
}

void ServerList::loadServerList(void)
{
	std::cout << "Loading serverlist..." << std::endl;
	std::string jsonString = Utility::doWebRequest("http://hannesf.com/ProjectZ/get.php");

	std::cout << "JsonString: " << jsonString << std::endl;

	rapidjson::Document doc;

	if(!doc.Parse<0>(jsonString.c_str()).HasParseError());
	{
		const rapidjson::Value& a = doc;
		for (rapidjson::SizeType i = 0; i < a.Size(); i++)
		{
			serverList.push_back(GuiServerList(font, fontColor, renderer, a[i]["ip"].GetString(), a[i]["name"].GetString(), a[i]["description"].GetString(), "30", 50+50*(i+1)));
		}
	}
}

void ServerList::onEvent(SDL_Event* ev, const Uint8* keyStates)
{
	BaseWindow::onEvent(ev, keyStates);
	for(int i = 0; i < serverList.size(); i++)
	{
		serverList[i].onEvent(ev, keyStates);
	}
}

void ServerList::update(float delta, const Uint8* keyStates)
{
	BaseWindow::update(delta, keyStates);
	for(int i = 0; i < serverList.size(); i++)
	{
		if(serverList[i].hasClicked())
		{
			newState = true;
			state = serverList[i].getOnClick();
			std::string tmpIp = serverList[i].getIp();
			if(yourIp == tmpIp)
				ip = "localhost";
			else
				ip = tmpIp;
		}
	}
}

std::string ServerList::getIp(void)
{
	return ip;
}