#include "MainMenu.h"

MainMenu::MainMenu(void)
{
	TTF_Init();
	font = TTF_OpenFont(std::string(Utility::getBasePath() + "assets/fonts/arial.ttf").c_str(), 36);

	fontColor.r = 0;
	fontColor.g = 0xff;
	fontColor.b = 0;

	renderer = Graphics::getInstance().getRenderer();

	buttons.push_back(Button(font, fontColor, renderer, "Singleplayer", 600, 200, 256, 64, STATE::GAME));
	buttons.push_back(Button(font, fontColor, renderer, "Multiplayer", 600, 300, 256, 64, STATE::MAINMENU));
	running = true;
	newState = false;
	state = STATE::MAINMENU;
}

MainMenu::~MainMenu(void)
{

}

void renderButton(Button button)
{
	switch (button.state)
	{
	case button.BUTTONSTATE::NORMAL:
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), button.texture, NULL, &button.dest);
		break;
	case button.BUTTONSTATE::HOVER:
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), button.textureHover, NULL, &button.dest);
		break;
	case button.BUTTONSTATE::CLICK:
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), button.textureClick, NULL, &button.dest);
		break;
	default:
		break;
	}
	
	SDL_RenderCopy(Graphics::getInstance().getRenderer(), button.text->texture, NULL, &button.text->dest);
}

void MainMenu::render(void)
{
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(renderer);

	for(int i = 0; i < texts.size(); i++)
	{
		SDL_RenderCopy(Graphics::getInstance().getRenderer(), texts[i].texture, NULL, &texts[i].dest);
	}

	for(int i = 0; i < buttons.size(); i++)
	{
		renderButton(buttons[i]);
	}

	SDL_RenderPresent(renderer);
}

void MainMenu::onEvent(SDL_Event* ev, const Uint8*)
{
	switch (ev->type)
	{
		case SDL_QUIT:
			running = false;
			break;
			
		case SDL_KEYDOWN:
		{
			if(ev->key.keysym.sym == SDLK_ESCAPE)
			{
				running = false;
			}
			break;
		}
		case SDL_MOUSEMOTION:
		{
			SDL_Rect mouse;
			mouse.x = ev->button.x;
			mouse.y = ev->button.y;
			mouse.w = 1;
			mouse.h = 1;
			for(int i = 0; i < buttons.size(); i++)
			{
				if(buttons[i].state != Button::BUTTONSTATE::CLICK)
				{
					if(SDL_HasIntersection(&mouse, &buttons[i].dest))
						buttons[i].state = Button::BUTTONSTATE::HOVER;
					else
						buttons[i].state = Button::BUTTONSTATE::NORMAL;
				}
				
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
				for(int i = 0; i < buttons.size(); i++)
				{
					if(SDL_HasIntersection(&mouse, &buttons[i].dest))
						buttons[i].state = Button::BUTTONSTATE::CLICK;
					else
						buttons[i].state = Button::BUTTONSTATE::NORMAL;
				}
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
				for(int i = 0; i < buttons.size(); i++)
				{
					if(buttons[i].state == Button::BUTTONSTATE::CLICK)
					{
						if(SDL_HasIntersection(&mouse, &buttons[i].dest))
						{
							newState = true;
							state = buttons[i].onClick;
						}
						else
							buttons[i].state = Button::BUTTONSTATE::NORMAL;
					}
				}
			}
			break;
		}
	}
}

void MainMenu::update(float, const Uint8*)
{

}

bool MainMenu::hasNewState(void)
{
	return newState;
}
STATE MainMenu::requestStateChange(void)
{
	return state;
}

bool MainMenu::isRunning(void)
{
	return running;
}