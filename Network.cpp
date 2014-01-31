#include "Network.h"

Network::Network(const char* ipChar)
{
	if(enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
    }

	client = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);

	if(client == NULL)
	{
		fprintf (stderr, "An error occurred while trying to create an ENet client host.\n");
	}

	ENetAddress address;

	enet_address_set_host(&address, ipChar);
	address.port = 1234;

	server = enet_host_connect(client, &address, 2, 0);

	if(server == NULL)
	{
		fprintf (stderr, "No available peers for initiating an ENet connection.\n");
	}

	ENetEvent event;

	if(enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Successfully connected to server" << std::endl;
		success = true;
		ENetPacket* packet = enet_packet_create("0", 2, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(server, 0, packet);
		enet_host_flush(client);
	}
	else
	{
		std::cout << "Failed to connect to server" << std::endl;
		success = false;
	}
	enet_host_flush(client);
}

Network::~Network(void)
{
	ENetPacket* packet = enet_packet_create("1", 2, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(server, 0, packet);
	enet_host_flush(client);
}

bool Network::getSuccess(void)
{
	return success;
}

void Network::sendMessage(EntityPlayer player, TimeChat timeChat)
{
	sprintf(tmp, "5 %d %f %s", player.getId(), timeChat.time, timeChat.chat.c_str());

	ENetPacket* packet = enet_packet_create(tmp, strlen(tmp)+1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(server, 0, packet);
	enet_host_flush(client);
}

void Network::send(EntityPlayer player, int ticks)
{
	if(player.isOnline())
	{
		glm::vec2 pos = player.getPosition();
		//3 id posX posY
		sprintf(tmp, "4 %d %f %f %d", player.getId(), pos.x, pos.y, ticks);

		ENetPacket* packet = enet_packet_create(tmp, strlen(tmp)+1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(server, 0, packet);
		enet_host_flush(client);
	}
}

void Network::recv(std::vector<std::shared_ptr<PlayerMP> >& players, std::shared_ptr<EntityPlayer> player, int ticks, std::shared_ptr<Chat> chat)
{
	ENetEvent event;
	while(enet_host_service(client, &event, 0) && event.type == ENET_EVENT_TYPE_RECEIVE)
	{

		int type, id;
		sscanf((char*)event.packet->data, "%d %d", &type, &id);

		if(type != 4)
			std::cout << "Packet of type: " << type << " was recieved from id: " << id << std::endl;

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
			case 4:
			{
				int i;
				for(i = 0; i < players.size(); i++)
				{
					if(players[i]->getId() == id)
					{
						int tmp2;
						float x, y;
						int tick;
						sscanf((char*)event.packet->data, "4 %d %f %f %d", &tmp2, &x, &y, &tick);
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
			case 5:
			{
				int tmp2;
				char* tmpMessage = (char*)malloc(strlen(tmp)+1);
				float time;
				sscanf((char*)event.packet->data, "5 %d %f %[0-9a-öA-Ö?*/ ]s", &tmp2, &time, tmpMessage);
				
				std::stringstream ss;
				ss << "Player " << id << ": " << tmpMessage;

				chat->addMessage(ss.str());
				break;
			}
		}
	}
}