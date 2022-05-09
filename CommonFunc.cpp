#include "CommonFunc.h"

void close(SDL_Window*& gWindow, SDL_Renderer*& gRender)
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRender);
	gWindow = NULL;
	gRender = NULL;

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();

}