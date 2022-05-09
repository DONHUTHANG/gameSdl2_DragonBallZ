#include "LoadImage.h"

LoadImage::LoadImage()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LoadImage::~LoadImage()
{

	free();
}

bool LoadImage::loadFromFile(string path, SDL_Renderer* gRenderer)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{

		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}


		SDL_FreeSurface(loadedSurface);
	}

	
	mTexture = newTexture;
	return mTexture != NULL;
}

void LoadImage::free()
{

	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LoadImage::render(int x, int y, SDL_Renderer* gRenderer)
{

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LoadImage::getWidth()
{
	return mWidth;
}

int LoadImage::getHeight()
{
	return mHeight;
}
