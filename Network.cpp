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
	SDLNet_TCP_Send(connection, "2 \n", 4);
	SDLNet_TCP_Close(connection);
	SDLNet_FreeSocketSet(server);
	SDLNet_Quit();
}
void Network::send(EntityPlayer* player)
{
	if(player->isReady())
	{
		glm::vec2 pos = *player->getPosition();
		//1 id posX posY
		sprintf(tmp, "1 %d %f %f \n", player->getId(), pos.x, pos.y);

		int size = 0;
		int len = strlen(tmp)+1;
		while(size<len)
		{
			size += SDLNet_TCP_Send(connection, tmp+size, len-size);
		}
	}
}
void Network::recv(std::vector<PlayerMP*>& players, EntityPlayer* player)
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
		if(type == 0)
		{
			player->setId(id);
		}else if(type == 1)
		{
			//std::cout << "Got an update from " << id << std::endl;
			int i;
			for(i = 0; i < players.size(); i++)
			{
				if(players[i]->getId() == id)
				{
					int tmp2;
					float x, y;
					sscanf(tmp, "1 %d %f %f \n", &tmp2, &x, &y);
					players[i]->setPosition(new glm::vec2(x, y));
					break;
				}	
			}
			if(i >= players.size())
			{
				std::cout << "Adding new player: " << id << std::endl;
				players.push_back(new PlayerMP(id));
			}
		}else if(type == 2)
		{
			for(int i = 0; i < players.size(); i++)
			{
				if(players[i]->getId() == id)
					players.erase(players.begin()+i);
			}
		}
	}
}

bool Network::getSuccess(void)
{
	return success;
}