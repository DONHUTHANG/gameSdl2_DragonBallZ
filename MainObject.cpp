#include "MainObject.h"

MainObject::MainObject()
{
    MainObjectImg = NULL;
    MainObjectTexWidth = 0;
    MainObjectTexHeight = 0;
    PosX = 150;
    PosY = 250;
    x_val = 0;
    y_val = 0;
}

MainObject::~MainObject()
{
    freeMainObject();
}

bool MainObject::loadMainObject(string mainObjectPath, SDL_Renderer* gRender)
{
    freeMainObject();

    SDL_Texture* newMainObjectTexture = NULL;

    SDL_Surface* newMainObjectSurface = IMG_Load(mainObjectPath.c_str());
    if (newMainObjectSurface == NULL)
    {
        cout << "Unable to load image MainObject:" << IMG_GetError();
    }
    else
    {
        newMainObjectTexture = SDL_CreateTextureFromSurface(gRender, newMainObjectSurface);
        if (newMainObjectTexture == NULL)
        {
            cout << "Unable to MainObject Texture: " << SDL_GetError();
        }
        else
        {
            MainObjectTexWidth = newMainObjectSurface->w;
            MainObjectTexHeight = newMainObjectSurface->h;
        }
        SDL_FreeSurface(newMainObjectSurface);
    }
    MainObjectImg = newMainObjectTexture;

    return MainObjectImg != NULL;
}

void MainObject::freeMainObject()
{
    if (MainObjectImg != NULL)
    {
        SDL_DestroyTexture(MainObjectImg);
        MainObjectImg = NULL;
        MainObjectTexWidth = 0;
        MainObjectTexHeight = 0;
        PosX = 0;
        PosY = 0;
        x_val = 0;
        y_val = 0;
    }
}

void MainObject::setMainObjectPos(int posx, int posy)
{
    PosX = posx;
    PosY = posy;
}

void MainObject::RenderMainObject(SDL_Renderer* gRender)
{
    SDL_Rect MainObjectRect = { PosX, PosY, MainObjectTexWidth, MainObjectTexHeight };
    SDL_RenderCopy(gRender, MainObjectImg, NULL, &MainObjectRect);
}

void MainObject::handleInput(SDL_Event& gEvent, SDL_Renderer* gRender)
{
    if (gEvent.type == SDL_KEYDOWN && gEvent.key.repeat == 0)
    {
        switch (gEvent.key.keysym.sym)
        {
        case SDLK_UP:
            y_val -= MainObjectTexHeight / 10;
            break;
        case SDLK_DOWN:
            y_val += MainObjectTexHeight / 10;
            break;
        case SDLK_LEFT:
            x_val -= MainObjectTexWidth / 10;
            break;
        case SDLK_RIGHT:
            x_val += MainObjectTexWidth / 10;
            break;
        default:
            break;
        }
    }
    else if (gEvent.type == SDL_KEYUP && gEvent.key.repeat == 0)
    {
        switch (gEvent.key.keysym.sym)
        {
        case SDLK_UP:
            y_val += MainObjectTexHeight / 10;
            break;
        case SDLK_DOWN:
             y_val -= MainObjectTexHeight / 10;
            break;
        case SDLK_LEFT:
            x_val += MainObjectTexWidth / 10;
            break;
        case SDLK_RIGHT:
            x_val -= MainObjectTexWidth / 10;
            break;
        default:
            break;
        }
    }
}

void MainObject::handleMove()
{
    PosX += x_val;
    if (PosX < 0 || PosX + MainObjectTexWidth > SCREEN_WIDTH)
    {
        PosX -= x_val;
    }

    PosY += y_val;
    if (PosY < 0 || PosY + MainObjectTexHeight > SCREEN_HEIGHT)
    {
        PosY -= y_val;
    }
}

SDL_Rect MainObject::getMainObjectRect()
{
    SDL_Rect newMainObjectRect = { PosX, PosY, MainObjectTexWidth, MainObjectTexHeight };
    return newMainObjectRect;
}

/*
void MainObject::SwapImage(SDL_Event& gEvent, SDL_Renderer* gRender, int posX, int posY)
{
    if (gEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        if (gEvent.button.button == SDL_BUTTON_LEFT)
        {
            freeMainObject();
            loadMainObject("images/bum.png", gRender);
        }
    }
}
*/

int MainObject::getPosX()
{
    return PosX;
}

int MainObject::getPosY()
{
    return PosY;
}

int MainObject::getMainObjectWidth()
{
    return MainObjectTexWidth;
}

int MainObject::getMainObjectHeight()
{
    return MainObjectTexHeight;
}

