#include "Explosion.h"

Explosion::Explosion()
{
	explosionTexWidth = 0;
	explosionTexHeight = 0;
	explosionPosX = 0;
	explosionPosY = 0;
	explosionFrame = 0;
}

Explosion::~Explosion()
{

}

bool Explosion::loadExplosionImg(string explosionPath, SDL_Renderer* gRender)
{
	SDL_Surface* newExplosionSurface = IMG_Load(explosionPath.c_str());

	SDL_Texture* newExplosionTexture = NULL;

	if (newExplosionSurface != NULL)
	{
		newExplosionTexture = SDL_CreateTextureFromSurface(gRender, newExplosionSurface);
		if (newExplosionTexture == NULL)
		{
			cout << "Unable to load image ExplosionImg: " << SDL_GetError();
		}
		else
		{
			explosionTexWidth = newExplosionSurface->w / NUMBER_FRAME;
			explosionTexHeight = newExplosionSurface->h;
		}
		SDL_FreeSurface(newExplosionSurface);
	}
	explosionImg = newExplosionTexture;

	return explosionImg != NULL;
}

void Explosion::RenderExplosion(SDL_Renderer* gRender)
{
	SDL_Rect* currenClip = &clip[explosionFrame];
	SDL_Rect clipQuad = { explosionPosX, explosionPosY, explosionTexWidth, explosionTexHeight };
	if (currenClip != NULL)
	{
		clipQuad.w = currenClip->w;
		clipQuad.h = currenClip->h;
	}
	SDL_RenderCopy(gRender, explosionImg, currenClip, &clipQuad);
}

void Explosion::setExplosionPos(int pos_x, int pox_y)
{
	explosionPosX = pos_x + 10;
	explosionPosY = pox_y - 10;
}

void Explosion::setClip()
{
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = explosionTexWidth;
	clip[0].h = explosionTexHeight;

	clip[1].x = explosionTexWidth;
	clip[1].y = 0;
	clip[1].w = explosionTexWidth;
	clip[1].h = explosionTexHeight;

	clip[2].x = explosionTexWidth * 2;
	clip[2].y = 0;
	clip[2].w = explosionTexWidth;
	clip[2].h = explosionTexHeight;

	clip[3].x = explosionTexWidth * 3;
	clip[3].y = 0;
	clip[3].w = explosionTexWidth;
	clip[3].h = explosionTexHeight;
}

int Explosion::getExplosionWidth()
{
	return explosionTexWidth;
}

int Explosion::getExplosionHeight()
{
	return explosionTexHeight;
}