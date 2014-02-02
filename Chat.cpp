#include "Chat.h"

Chat::Chat(int chatLogSizeIn) : chatLogSize(chatLogSizeIn) 
{
	open = false;
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
		case SDL_KEYDOWN:
		{
			if(ev->key.keysym.sym == SDLK_BACKSPACE)
			{
				if(!currText.empty())
					currText.erase(currText.end() - 1);
			}
			break;
		}
	}
}

void Chat::addMessage(std::string message)
{
	chatLog.push_back(std::make_shared<TimeChat>(message, SDL_GetTicks()));
}

std::string Chat::getCurrText(void)
{
	return currText;
}

std::vector<std::shared_ptr<TimeChat> > Chat::getChatLog(void)
{
	return chatLog;
}

void Chat::setCurrText(std::string currTextIn)
{
	currText = currTextIn;
}

bool Chat::isOpen(void)
{
	return open;
}

void Chat::setOpen(bool openIn)
{
	open = openIn;
}