#ifndef LOADIMAGE_H_
#define LOADIMAGE_H_


#include "CommonFunc.h"

class LoadImage
{
public:

	LoadImage();


	~LoadImage();


	bool loadFromFile(string path, SDL_Renderer* gRenderer);


	void free();

	void render(int x, int y, SDL_Renderer* gRenderer);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;

	
	int mWidth;
	int mHeight;
};

#endif