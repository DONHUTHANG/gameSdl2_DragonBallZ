

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "CommonFunc.h"

const int NUMBER_FRAME = 4;

class Explosion
{
public:

	Explosion();
	~Explosion();

	bool loadExplosionImg(string explosionPath, SDL_Renderer* gRender);

	void RenderExplosion(SDL_Renderer* gRender);

	void setExplosion(int frame_) { explosionFrame = frame_; }

	void setExplosionPos(int pos_x, int pox_y);

	void setClip();

	int getExplosionWidth();
	int getExplosionHeight();

private:

	SDL_Texture* explosionImg;

	SDL_Rect clip[4];

	int explosionTexWidth;
	int explosionTexHeight;
	int explosionPosX;
	int explosionPosY;
	int explosionFrame;

};


#endif