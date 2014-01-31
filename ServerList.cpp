#include "ServerList.h"

ServerList::ServerList(void) : BaseWindow()
{
	texts.push_back(GuiText(font, fontColor, renderer, "IP", 100, 20));
	texts.push_back(GuiText(font, fontColor, renderer, "Name", 300, 20));
	texts.push_back(GuiText(font, fontColor, renderer, "Description", 500, 20));
	texts.push_back(GuiText(font, fontColor, renderer, "PlayerCount", 900, 20));
	texts.push_back(GuiText(font, fontColor, renderer, "Ping", 1100, 20));
	buttons.push_back(GuiButton(font, fontColor, renderer, "BACK", 100, 600, 55, 24, STATE::MAINMENU));
	buttons.push_back(GuiButton(font, fontColor, renderer, "Refresh", 600, 600, 70, 24, STATE::SERVERLIST));
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
	std::string jsonString = Utility::doWebRequest("http://hannesf.com/ProjectZ/get.php");
	rapidjson::Document doc;

	if(!doc.Parse<0>(jsonString.c_str()).HasParseError());
	{
		const rapidjson::Value& a = doc;
		for (rapidjson::SizeType i = 0; i < a.Size(); i++)
		{
			serverList.push_back(GuiServerList(font, fontColor, renderer, a[i]["ip"].GetString(), a[i]["name"].GetString(), a[i]["description"].GetString(), 50+50*(i+1)));
		}
	}

	if(enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
    }
	ENetHost* client = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);

	if(client == NULL)
	{
		fprintf (stderr, "An error occurred while trying to create an ENet client host.\n");
	}

	for(int i = 0; i < serverList.size(); i++)
	{
		ENetAddress address;
		enet_address_set_host(&address, serverList[i].getIp().c_str());
		address.port = 1234;

		ENetPeer* server = enet_host_connect(client, &address, 2, 0);

		if(server == NULL)
		{
			fprintf (stderr, "No available peers for initiating an ENet connection.\n");
		}

		ENetEvent event;

		if(enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
		{
			std::cout << "Pinging server..." << std::endl;
			char tmp[1400];

			sprintf(tmp, "2 %d", SDL_GetTicks());
			ENetPacket* packet = enet_packet_create(tmp, strlen(tmp)+1, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(server, 0, packet);
			enet_host_flush(client);

			if(enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_RECEIVE)
			{
				int time;
				sscanf((char*)event.packet->data, "2 %d", &time);
				serverList[i].setPing(SDL_GetTicks()-time);
			}

			std::cout << "Getting playercount..." << std::endl;

			packet = enet_packet_create("3", 2, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(server, 0, packet);
			enet_host_flush(client);

			if(enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_RECEIVE)
			{
				int playerCount, maxPlayers;
				sscanf((char*)event.packet->data, "3 %d %d", &playerCount, &maxPlayers);
				serverList[i].setPlayerCount(playerCount, maxPlayers);
			}
		}
		else
		{
			std::cout << "Failed to connect to server" << std::endl;
		}
		enet_host_flush(client);
		enet_peer_disconnect(server, 0);
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