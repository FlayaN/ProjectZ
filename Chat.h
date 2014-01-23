#ifndef CHAT_H
#define CHAT_H

#include <vector>
#include <memory>

#include "SDL.h"

#include "EntityPlayer.h"

struct TimeChat
{
	TimeChat(std::string chatIn, float timeIn) : chat(chatIn), time(timeIn) {}
	std::string chat;
	float time;
};

class Chat
{
public:
	Chat(int);
	void handleKeyInput(SDL_Event*, const Uint8*);
	//void sendMessage(EntityPlayer, std::shared_ptr<Network>);
	void setCurrText(std::string);
	std::string getCurrText(void);
	std::vector<std::shared_ptr<TimeChat> > getChatLog(void);
	void addMessage(std::string);
	void addMessage(std::string, float);
	bool isOpen(void);
	void setOpen(bool);
private:

	int chatLogSize;

	std::vector<std::shared_ptr<TimeChat> > chatLog;
	std::string currText;
	bool open;
};

#endif