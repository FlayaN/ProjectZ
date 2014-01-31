#include "GuiServerList.h"

GuiServerList::GuiServerList(TTF_Font* font, SDL_Color fontColor, SDL_Renderer* renderer, std::string ipIn, std::string nameIn, std::string descriptionIn, int yIn)
{
	edgeTexture = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/edge.png").c_str());
	texture = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/border.png").c_str());
	textureHover = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/borderHover.png").c_str());
	textureClick = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/borderClick.png").c_str());

	ipGuiText = new GuiText(font, fontColor, renderer, ipIn, 100, yIn);
	nameGuiText = new GuiText(font, fontColor, renderer, nameIn, 300, yIn);
	descGuiText = new GuiText(font, fontColor, renderer, descriptionIn, 500, yIn);
	playerCountGuiText = new GuiText(font, fontColor, renderer, "NaN", 900, yIn);
	pingGuiText = new GuiText(font, fontColor, renderer, "NaN", 1100, yIn);

	int x = 20;
	int y = yIn;
	int height = 24;
	int width = Settings::Graphics::screenWidth-40;

	leftEdge.x = x;
	leftEdge.y = y;
	leftEdge.h = height;
	leftEdge.w = 2;

	rightEdge.x = x+width-2;
	rightEdge.y = y;
	rightEdge.h = height;
	rightEdge.w = 2;

	middle.x = x+2;
	middle.y = y;
	middle.h = height;
	middle.w = width-4;

	rect.x = x;
	rect.y = y;
	rect.h = height;
	rect.w = width;

	state = NORMAL;
	onClick = STATE::GAME;
	clicked = false;
	ip = ipIn;
}

void GuiServerList::setState(int stateIn)
{
	state = stateIn;
}

int GuiServerList::getState(void)
{
	return state;
}

std::string GuiServerList::getIp(void)
{
	return ip;
}

STATE GuiServerList::getOnClick(void)
{
	return onClick;
}

void GuiServerList::render(void)
{
	SDL_RenderCopy(Graphics::getInstance().getRenderer(), edgeTexture, NULL, &leftEdge);
	SDL_RenderCopyEx(Graphics::getInstance().getRenderer(), edgeTexture, NULL, &rightEdge, 0.0, NULL, SDL_FLIP_HORIZONTAL);
	switch (state)
	{
	case BUTTONSTATE::NORMAL:
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), texture, NULL, &middle);
		break;
	case BUTTONSTATE::HOVER:
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), textureHover, NULL, &middle);
		break;
	case BUTTONSTATE::CLICK:
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), textureClick, NULL, &middle);
		break;
	default:
		break;
	}

	ipGuiText->render();
	nameGuiText->render();
	descGuiText->render();
	playerCountGuiText->render();
	pingGuiText->render();
}

void GuiServerList::onEvent(SDL_Event* ev, const Uint8*)
{
	switch (ev->type)
	{
		case SDL_MOUSEMOTION:
		{
			SDL_Rect mouse;
			mouse.x = ev->button.x;
			mouse.y = ev->button.y;
			mouse.w = 1;
			mouse.h = 1;
			
			if(state != GuiServerList::BUTTONSTATE::CLICK)
			{
				if(SDL_HasIntersection(&mouse, &rect))
					state = GuiServerList::BUTTONSTATE::HOVER;
				else
					state = GuiServerList::BUTTONSTATE::NORMAL;
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if(ev->button.button == SDL_BUTTON_LEFT)
			{
				SDL_Rect mouse;
				mouse.x = ev->button.x;
				mouse.y = ev->button.y;
				mouse.w = 1;
				mouse.h = 1;
				
				if(SDL_HasIntersection(&mouse, &rect))
					state = GuiServerList::BUTTONSTATE::CLICK;
				else
					state = GuiServerList::BUTTONSTATE::NORMAL;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			if(ev->button.button == SDL_BUTTON_LEFT)
			{
				SDL_Rect mouse;
				mouse.x = ev->button.x;
				mouse.y = ev->button.y;
				mouse.w = 1;
				mouse.h = 1;
				if(state == GuiServerList::BUTTONSTATE::CLICK)
				{
					if(SDL_HasIntersection(&mouse, &rect))
					{
						clicked = true;
					}
					else
						state = GuiServerList::BUTTONSTATE::NORMAL;
				}
			}
			break;
		}
	}
}

bool GuiServerList::hasClicked(void)
{
	return clicked;
}

void GuiServerList::setPing(int pingIn)
{
	pingGuiText->setText(std::to_string(pingIn));
}

void GuiServerList::setPlayerCount(int curr, int max)
{
	playerCountGuiText->setText(std::to_string(curr) + "/" + std::to_string(max));
}