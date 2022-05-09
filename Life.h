#ifndef LIFE__H_
#define LIFE__H_

#include "CommonFunc.h"

class Life
{
public:

	Life();
	~Life();

	bool loadLifeImg(string lifePath, SDL_Renderer* gRender);

	void setLifePos(const int& pos);

	void initLife(SDL_Renderer* render);

	void showLife(SDL_Renderer* render);

	void lifeRender(SDL_Renderer* render);

	void decreaseLife();

private:

	SDL_Texture* lifeImg;

	vector<int> lifeList;

	int numberLife;
	int lifePosX;
	int lifePosY;
	int lifeTexWidth;
	int lifeTexHeight;

};

#endif
