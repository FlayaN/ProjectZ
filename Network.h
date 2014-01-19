#ifndef NETWORK_H
#define NETWORK_H

#ifdef __APPLE__
	#include <SDL\SDL_net.h>
#else
	#include "SDL_net.h"
#endif

#include <string>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>

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
	SDLNet_SocketSet server;
	TCPsocket connection;
	char tmp[1400];
	bool success;
	int pId;
};


#endif