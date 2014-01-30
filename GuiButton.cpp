#include "GuiButton.h"

GuiButton::GuiButton(TTF_Font* font, SDL_Color fontColor, SDL_Renderer* renderer, std::string textIn, int x, int y, int width, int height, STATE onClickIn)
{
	texture = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/button.png").c_str());
	textureHover = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/buttonHover.png").c_str());
	textureClick = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/buttonClick.png").c_str());
	text = new GuiText(font, fontColor, renderer, textIn, x, y);
	dest.x = x;
	dest.y = y;
	dest.h = height;
	dest.w = width;
	state = NORMAL;
	onClick = onClickIn;
	clicked = false;
}

SDL_Texture* GuiButton::getTexture(void)
{
	return texture;
}

SDL_Texture* GuiButton::getTextureHover(void)
{
	return textureHover;
}

SDL_Texture* GuiButton::getTextureClick(void)
{
	return textureClick;
}

void GuiButton::setState(int stateIn)
{
	state = stateIn;
}

int GuiButton::getState(void)
{
	return state;
}

GuiText* GuiButton::getGuiText(void)
{
	return text;
}

SDL_Rect GuiButton::getRect(void)
{
	return dest;
}

STATE GuiButton::getOnClick(void)
{
	return onClick;
}

void GuiButton::render(void)
{
	switch (state)
	{
	case BUTTONSTATE::NORMAL:
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), texture, NULL, &dest);
		break;
	case BUTTONSTATE::HOVER:
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), textureHover, NULL, &dest);
		break;
	case BUTTONSTATE::CLICK:
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), textureClick, NULL, &dest);
		break;
	default:
		break;
	}

	text->render();
}

void GuiButton::onEvent(SDL_Event* ev, const Uint8*)
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
			
			if(state != GuiButton::BUTTONSTATE::CLICK)
			{
				if(SDL_HasIntersection(&mouse, &dest))
					state = GuiButton::BUTTONSTATE::HOVER;
				else
					state = GuiButton::BUTTONSTATE::NORMAL;
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
					state = GuiButton::BUTTONSTATE::CLICK;
				else
					state = GuiButton::BUTTONSTATE::NORMAL;
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
				if(state == GuiButton::BUTTONSTATE::CLICK)
				{
					if(SDL_HasIntersection(&mouse, &dest))
					{
						clicked = true;
					}
					else
						state = GuiButton::BUTTONSTATE::NORMAL;
				}
			}
			break;
		}
	}
}

bool GuiButton::hasClicked(void)
{
	return clicked;
}