#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H

#include "CommonFunc.h"

class MainObject
{
public:

    MainObject();
    ~MainObject();

    bool loadMainObject(string mainObjectPath, SDL_Renderer* gRender);

    void freeMainObject();

    void setMainObjectPos(int posX, int posY);

    void RenderMainObject(SDL_Renderer* gRender);

    void handleInput(SDL_Event& gEvent, SDL_Renderer* gRender);

    void handleMove();

    void SwapImage(SDL_Event& gEvent, SDL_Renderer* gRender, int posX, int posY);

    SDL_Rect getMainObjectRect();
    int getPosX();
    int getPosY();
    int getMainObjectWidth();
    int getMainObjectHeight();

private:

    SDL_Texture* MainObjectImg;

    int MainObjectTexWidth;
    int MainObjectTexHeight;
    int PosX;
    int PosY;
    int x_val;
    int y_val;

};

#endif
