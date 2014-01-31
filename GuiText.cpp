#include "GuiText.h"

GuiText::GuiText(TTF_Font* fontIn, SDL_Color fontColorIn, SDL_Renderer* rendererIn, std::string text, int x, int y)
{
	font = fontIn;
	fontColor = fontColorIn;
	renderer = rendererIn;
	dest.x = x;
	dest.y = y;
	setText(text);
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

void GuiText::setText(std::string text)
{
	SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), fontColor);
	dest.w = textImage->w;
	dest.h = textImage->h;
	texture = SDL_CreateTextureFromSurface(renderer, textImage);
	SDL_FreeSurface(textImage);
}