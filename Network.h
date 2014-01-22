#ifndef NETWORK_H2
#define NETWORK_H2

#include <string>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>

#include <enet/enet.h>

#include "EntityPlayer.h"
#include "PlayerMP.h"
#include "Chat.h"

class Network
{
public:
	Network(const char* ip);
	~Network(void);
	void send(EntityPlayer, int);
	void sendMessage(EntityPlayer, std::string);

	void recv(std::vector<std::shared_ptr<PlayerMP> >&, std::shared_ptr<EntityPlayer>, int, std::shared_ptr<Chat>);
	bool getSuccess(void);

private:
	ENetHost* client;
	ENetPeer* server;
	char tmp[1400];
	bool success;
	int pId;
};


#endif