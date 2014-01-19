#ifndef CHAT_H
#define CHAT_H

#include <vector>
#include <memory>

#include "SDL.h"

#include "EntityPlayer.h"

class Chat
{
public:
	Chat(int);
	void handleKeyInput(SDL_Event*, const Uint8*);
	//void sendMessage(EntityPlayer, std::shared_ptr<Network>);
	void setCurrText(std::string);
	std::string getCurrText(void);
	std::vector<std::string> getChatLog(void);
	void addMessage(std::string);
private:

	int chatLogSize;

	std::vector<std::string> chatLog;
	std::string currText;
};

#endif