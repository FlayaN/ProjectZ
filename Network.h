#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>

#include <enet/enet.h>

#include "EntityPlayer.h"
#include "PlayerMP.h"
#include "Chat.h"
#include "ChunkUtility.h"

class Network
{
public:
	Network(const char* ip);
	~Network(void);
	void send(EntityPlayer, int);
	void sendMessage(EntityPlayer, TimeChat);
	void placeItem(std::shared_ptr<GroundItemStack>);
	void pickupItem(std::shared_ptr<GroundItemStack>);

	void recv(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >&, std::vector<std::shared_ptr<PlayerMP> >&, std::shared_ptr<EntityPlayer>, int, std::shared_ptr<Chat>);
	bool getSuccess(void);

private:
	ENetHost* client;
	ENetPeer* server;
	char tmp[1400];
	bool success;
	int pId;
};


#endif