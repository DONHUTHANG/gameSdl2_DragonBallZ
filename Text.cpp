#include "Text.h"

Text::Text()
{
	texImg = NULL;
	texColor.r = 255;
	texColor.g = 255;
	texColor.b = 255;
	texWidth = 0;
	texHeight = 0;
	texPosX = 0;
	texPosY = 0;
}

Text::~Text()
{
	freeTex();
}

bool Text::loadFromRenderTex(TTF_Font* texFont, SDL_Renderer* render)
{
	SDL_Surface* texSurface = TTF_RenderText_Solid(texFont, texString.c_str(), texColor);

	if (texSurface)
	{
		texImg = SDL_CreateTextureFromSurface(render, texSurface);
		texWidth = texSurface->w;
		texHeight = texSurface->h;

		SDL_FreeSurface(texSurface);
	}

	return texImg != NULL;
}

void Text::freeTex()
{
	if (texImg != NULL)
	{
		SDL_DestroyTexture(texImg);
		texImg = NULL;
		texWidth = 0;
		texHeight = 0;
		texPosX = 0;
		texPosY = 0;
	}
}

void Text::setTexColor(Uint8 red, Uint8 green, Uint8 blue)
{
	texColor.r = red;
	texColor.g = green;
	texColor.b = blue;
}

void Text::setColorWithType(int type)
{
	if (type == WHITE)
	{
		SDL_Color color = { 255,255,255 };
		texColor = color;
	}
	if (type == RED)
	{
		SDL_Color color = { 255,0,0 };
		texColor = color;
	}
	if (type == YELLOW)
	{
		SDL_Color color = { 255,255,0 };
		texColor = color;
	}
}

void Text::setTexPos(int tex_x, int tex_y)
{
	texPosX = tex_x;
	texPosY = tex_y;
}

void Text::texRender(SDL_Renderer* render)
{
	SDL_Rect texQuad = { texPosX, texPosY, texWidth, texHeight };
	SDL_RenderCopy(render, texImg, NULL, &texQuad);
}

string Text::getText()
{
	return texString;
}

int Text::getTexWidth()
{
	return texWidth;
}

int Text::getTexHeight()
{
	return texHeight;
}
