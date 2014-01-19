#include "Network.h"

Network::Network(const char* ipChar)
{
	success = true;
	SDLNet_Init();
	IPaddress ip;
	if(SDLNet_ResolveHost(&ip, ipChar, 1234) == -1)
	{
		std::cout << "Could not connect to server (SDLNet_ResolveHost)" << std::endl;
		success = false;
	}
	connection = SDLNet_TCP_Open(&ip);
	if(connection == NULL)
	{
		std::cout << "Could not connect to server (SDLNet_TCP_Open)" << std::endl;
		success = false;
	}
	server = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(server, connection);
}

Network::~Network(void)
{
	if(success)
	{
		sprintf(tmp, "2 %d \n", pId);
		SDLNet_TCP_Send(connection, tmp, strlen(tmp)+1);
		SDLNet_FreeSocketSet(server);
	}
	SDLNet_TCP_Close(connection);
	SDLNet_Quit();
}

void Network::send(EntityPlayer player, int ticks)
{
	if(player.isOnline())
	{
		glm::vec2 pos = player.getPosition();
		//1 id posX posY
		sprintf(tmp, "1 %d %f %f %d \n", player.getId(), pos.x, pos.y, ticks);

		int size = 0;
		int len = strlen(tmp)+1;
		while(size<len)
		{
			size += SDLNet_TCP_Send(connection, tmp+size, len-size);
		}
	}
}

void Network::sendMessage(EntityPlayer player, std::string message)
{
	//3 id message
	sprintf(tmp, "3 %d %s \n", player.getId(), message.c_str());

	int size = 0;
	int len = strlen(tmp)+1;

	while(size<len)
	{
		size += SDLNet_TCP_Send(connection, tmp+size, len-size);
	}
}

void Network::recv(std::vector<std::shared_ptr<PlayerMP> >& players, std::shared_ptr<EntityPlayer> player, int ticks, std::shared_ptr<Chat> chat)
{
	while(SDLNet_CheckSockets(server, 0)>0 && SDLNet_SocketReady(connection))
	{
		int offset = 0;
		do
		{
			offset += SDLNet_TCP_Recv(connection, tmp+offset, 1400);
			if(offset <= 0)
				return;
		}while(tmp[strlen(tmp) - 1] != '\n');
		int type, id;
		sscanf(tmp, "%d %d", &type, &id);
		//std::cout << "Packet of type: " << type << " got sent" << std::endl;

		switch (type)
		{
			case 0:
			{
				std::cout << "You are id: " << id << std::endl;
				player->setId(id);
				pId = id;
				break;
			}
			case 1:
			{
				int i;
				for(i = 0; i < players.size(); i++)
				{
					if(players[i]->getId() == id)
					{
						int tmp2;
						float x, y;
						int tick;
						sscanf(tmp, "1 %d %f %f %d \n", &tmp2, &x, &y, &tick);
						players[i]->setLatestSnapShot(x, y, tick);
						break;
					}	
				}
				if(i >= players.size())
				{
					if(id != pId)
					{
						std::cout << "Adding new player: " << id << std::endl;
						players.push_back(std::make_shared<PlayerMP>(PlayerMP(id)));
					}
				}
				break;
			}
			case 2:
			{
				std::cout << "remove onlinePlayer with id: " << id << std::endl;
				for(int i = 0; i < players.size(); i++)
				{
					if(players[i]->getId() == id)
					{
						std::cout << "removed onlinePlayer with id: " << id << std::endl;
						players.erase(players.begin()+i);
					}
				}
				break;
			}
			case 3:
			{
				int tmp2;
				char* tmpMessage = (char*)malloc(strlen(tmp)+1);
				sscanf(tmp, "3 %d %[0-9a-�A-� ]s \n", &tmp2, tmpMessage);
				
				std::stringstream ss;

				ss << "Player " << id << ": " << tmpMessage;

				chat->addMessage(ss.str());
				//std::cout << "Player " << id << ": " << tmpMessage << std::endl;
				break;
			}
		}
	}
}

bool Network::getSuccess(void)
{
	return success;
}