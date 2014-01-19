#include "Chat.h"

Chat::Chat(int chatLogSizeIn) : chatLogSize(chatLogSizeIn) 
{
	for(int i = 0; i < chatLogSize; i++)
	{
		//chatLog.push_back("HEJ");
	}
}
void Chat::handleKeyInput(SDL_Event* ev, const Uint8* keyStates)
{
	int temp = SDL_GetModState(); 
	temp = temp & KMOD_CAPS;
	bool ifVersals = temp == KMOD_CAPS || keyStates[SDL_SCANCODE_LSHIFT] || keyStates[SDL_SCANCODE_RSHIFT];

	switch (ev->type)
	{
		case SDL_TEXTINPUT:
		{
			currText += ev->text.text;
			break;
		}
	}
}

void Chat::addMessage(std::string message)
{
	chatLog.push_back(message);
}

std::string Chat::getCurrText(void)
{
	return currText;
}

std::vector<std::string> Chat::getChatLog(void)
{
	return chatLog;
}

void Chat::setCurrText(std::string currTextIn)
{
	currText = currTextIn;
}