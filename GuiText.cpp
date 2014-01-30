#include "GuiText.h"

GuiText::GuiText(TTF_Font* font, SDL_Color fontColor, SDL_Renderer* renderer, std::string text, int x, int y)
{
	SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), fontColor);
	dest.x = x;
	dest.y = y;
	dest.w = textImage->w;
	dest.h = textImage->h;
	texture = SDL_CreateTextureFromSurface(renderer, textImage);
	SDL_FreeSurface(textImage);
}

SDL_Texture* GuiText::getTexture(void)
{
	return texture;
}

SDL_Rect GuiText::getRect(void)
{
	return dest;
}

void GuiText::render(void)
{
	SDL_RenderCopy(Graphics::getInstance().getRenderer(), texture, NULL, &dest);
}