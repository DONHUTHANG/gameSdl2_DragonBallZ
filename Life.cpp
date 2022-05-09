#include "Life.h"

Life::Life()
{
	lifeImg = NULL;
	numberLife = 0;
	lifePosX = 0;
	lifePosY = 0;
	lifeTexWidth = 0;
	lifeTexHeight = 0;
}

Life::~Life()
{

}

bool Life::loadLifeImg(string lifePath, SDL_Renderer* render)
{
	SDL_Texture* newLifeTexture = NULL;

	SDL_Surface* newLifeSurface = IMG_Load(lifePath.c_str());

	if (newLifeSurface != NULL)
	{
		newLifeTexture = SDL_CreateTextureFromSurface(render, newLifeSurface);
		if (newLifeTexture)
		{
			lifeTexWidth = newLifeSurface->w;
			lifeTexHeight = newLifeSurface->h;
		}

		SDL_FreeSurface(newLifeSurface);
	}

	lifeImg = newLifeTexture;

	return lifeImg != NULL;
}

void Life::setLifePos(const int& pos)
{
	lifeList.push_back(pos);
}

void Life::initLife(SDL_Renderer* render)
{
	loadLifeImg("images/heart.png", render);
	numberLife = 3;
	if (lifeList.size() > 0)
	{
		lifeList.clear();
	}

	setLifePos(0);
	setLifePos(50);
	setLifePos(100);
}

void Life::showLife(SDL_Renderer* render)
{
	for (int i = 0; i < lifeList.size(); i++)
	{
		lifePosX = lifeList.at(i);
		lifePosY = 0;
		lifeRender(render);
	}
}

void Life::lifeRender(SDL_Renderer* render)
{
	SDL_Rect lifeQuad = { lifePosX, lifePosY, lifeTexWidth, lifeTexHeight };
	SDL_RenderCopy(render, lifeImg, NULL, &lifeQuad);
}

void Life::decreaseLife()
{
	numberLife--;
	lifeList.pop_back();
}