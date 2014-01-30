#include "GuiServerList.h"

GuiServerList::GuiServerList(TTF_Font* font, SDL_Color fontColor, SDL_Renderer* renderer, std::string ipIn, std::string nameIn, std::string descriptionIn, std::string pingIn, int yIn)
{
	dest.x = 20;
	dest.y = yIn;
	dest.h = 30;
	dest.w = Settings::Graphics::screenWidth-40;
	SDL_Surface* surface = SDL_CreateRGBSurface(0,dest.w,dest.h,32,0,0,0,0);
	SDL_FillRect(surface, &dest, SDL_MapRGB(surface->format, 0x0, 0xff, 0xff));
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	ipGuiText = new GuiText(font, fontColor, renderer, ipIn, 100, yIn);
	nameGuiText = new GuiText(font, fontColor, renderer, nameIn, 300, yIn);
	descGuiText = new GuiText(font, fontColor, renderer, descriptionIn, 500, yIn);
	pingGuiText = new GuiText(font, fontColor, renderer, pingIn, 1100, yIn);

	state = NORMAL;
	onClick = STATE::GAME;
	clicked = false;
	ip = ipIn;
}

SDL_Texture* GuiServerList::getTexture(void)
{
	return texture;
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

SDL_Rect GuiServerList::getRect(void)
{
	return dest;
}

STATE GuiServerList::getOnClick(void)
{
	return onClick;
}

void GuiServerList::render(void)
{
	SDL_RenderCopy(Graphics::getInstance().getRenderer(), texture, NULL, &dest);

	ipGuiText->render();
	nameGuiText->render();
	descGuiText->render();
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
				if(SDL_HasIntersection(&mouse, &dest))
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
				
				if(SDL_HasIntersection(&mouse, &dest))
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
					if(SDL_HasIntersection(&mouse, &dest))
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