#include "GuiButton.h"

GuiButton::GuiButton(TTF_Font* font, SDL_Color fontColor, SDL_Renderer* rendererIn, std::string textIn, int x, int y, int width, int height, STATE onClickIn)
{
    renderer = rendererIn;
	edgeTexture = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/edge.png").c_str());
	texture = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/border.png").c_str());
	textureHover = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/borderHover.png").c_str());
	textureClick = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/borderClick.png").c_str());
	text = new GuiText(font, fontColor, renderer, textIn, x, y);

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
	onClick = onClickIn;
	clicked = false;
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

STATE GuiButton::getOnClick(void)
{
	return onClick;
}

void GuiButton::render(void)
{
	SDL_RenderCopy(renderer, edgeTexture, NULL, &leftEdge);
	SDL_RenderCopyEx(renderer, edgeTexture, NULL, &rightEdge, 0.0, NULL, SDL_FLIP_HORIZONTAL);
	switch (state)
	{
	case BUTTONSTATE::NORMAL:
		SDL_RenderCopy(renderer, texture, NULL, &middle);
		break;
	case BUTTONSTATE::HOVER:
		SDL_RenderCopy(renderer, textureHover, NULL, &middle);
		break;
	case BUTTONSTATE::CLICK:
		SDL_RenderCopy(renderer, textureClick, NULL, &middle);
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
				if(SDL_HasIntersection(&mouse, &rect))
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
				
				if(SDL_HasIntersection(&mouse, &rect))
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
					if(SDL_HasIntersection(&mouse, &rect))
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