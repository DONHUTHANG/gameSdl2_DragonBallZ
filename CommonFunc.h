#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <fstream>
#include <algorithm>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int NUMBER_ENEMIES = 9;


using namespace std;

void close(SDL_Window*& gWindow, SDL_Renderer*& gRender);

#endif
