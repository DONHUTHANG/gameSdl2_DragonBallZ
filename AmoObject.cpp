#include "AmoObject.h"

AmoObject::AmoObject()
{
    AmoObjectImg = NULL;
    posX = 0;
    posY = 0;
    AmoObjectTexWidth = 0;
    AmoObjectTexHeight = 0;
    AmoObject_val = 15;
    isShot = false;
}

AmoObject::~AmoObject()
{
    freeAmoObject();
}

bool AmoObject::loadAmoObjectImg(string amoObjectPath, SDL_Renderer* gRender)
{
    freeAmoObject();

    SDL_Texture* newAmoObjectTexture = NULL;

    SDL_Surface* newAmoObjectSurface = IMG_Load(amoObjectPath.c_str());

    if (newAmoObjectSurface == NULL)
    {
        cout << "Unable to load image AmoObject : " << IMG_GetError();
    }
    else
    {
        newAmoObjectTexture = SDL_CreateTextureFromSurface(gRender, newAmoObjectSurface);
        if (newAmoObjectTexture == NULL)
        {
            cout << "Unable to AmoObjectTexture: " << SDL_GetError();
        }
        else
        {
            AmoObjectTexWidth = newAmoObjectSurface->w;
            AmoObjectTexHeight = newAmoObjectSurface->h;
        }
        SDL_FreeSurface(newAmoObjectSurface);
    }

    AmoObjectImg = newAmoObjectTexture;

    return AmoObjectImg != NULL;
}

void AmoObject::freeAmoObject()
{
    if (AmoObjectImg != NULL)
    {
        SDL_DestroyTexture(AmoObjectImg);
        AmoObjectImg = 0;
        posX = 0;
        posY = 0;
        AmoObjectTexWidth = 0;
        AmoObjectTexHeight = 0;
        isShot = false;
    }
}

void AmoObject::AmoObjectMove(int rectx, int recty)
{
    posX += AmoObject_val;
    if (posX + AmoObjectTexWidth > rectx)
    {
        isShot = false;
    }
}

void AmoObject::HandleMoveRightToLeft()
{
    posX -= AmoObject_val;
    if (posX < 0)
    {
        isShot = false;
    }
}

void AmoObject::RenderAmoObject(SDL_Renderer* gRender)
{
    SDL_Rect AmoObjectQuad = { posX, posY, AmoObjectTexWidth, AmoObjectTexHeight };
    SDL_RenderCopy(gRender, AmoObjectImg, NULL, &AmoObjectQuad);
}

void AmoObject::setAmoObjectPos(int PosX, int PosY)
{
    posX = PosX;
    posY = PosY;
}

void AmoObject::handleInputAmoObject(SDL_Event gEvent, SDL_Renderer* gRender, Mix_Chunk* laserSound,  int PosX, int PosY)
{

    if (gEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        AmoObject* newAmoObject = new AmoObject();
        if (gEvent.button.button == SDL_BUTTON_LEFT)
        {
            Mix_PlayChannel(-1, laserSound, 0);
            newAmoObject->loadAmoObjectImg("images/kamejoko.png", gRender);
            newAmoObject->setAmoObjectPos(PosX, PosY);
            newAmoObject->setIsShot(true);
        }
        else if (gEvent.button.button == SDL_BUTTON_RIGHT)
        {
            Mix_PlayChannel(-1, laserSound, 0);
            newAmoObject->loadAmoObjectImg("images/kamekame.png", gRender);
            newAmoObject->setAmoObjectPos(PosX + 10, PosY - 18);
            newAmoObject->setIsShot(true);
        }
        AmoObjectList.push_back(newAmoObject);
    }
}

void AmoObject::handleAmoObject(SDL_Renderer* gRender)
{
    for (int i = 0; i < AmoObjectList.size(); i++)
    {
        AmoObject* temp = AmoObjectList.at(i);
        if (temp != NULL)
        {
            if (temp->getIsShot() == true)
            {
                temp->AmoObjectMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                temp->RenderAmoObject(gRender);
            }
            else
            {
                AmoObjectList.erase(AmoObjectList.begin() + i);
                if (temp != NULL)
                {
                    delete temp;
                    temp = NULL;
                }
            }
        }
    }
}

bool AmoObject::checkCol(const SDL_Rect& amoObjectRect, const SDL_Rect& threatObjectRect)
{
    int left_1 = amoObjectRect.x;
    int right_1 = amoObjectRect.x + amoObjectRect.w;
    int top_1 = amoObjectRect.y;
    int bot_1 = amoObjectRect.y + amoObjectRect.h;

    int left_2 = threatObjectRect.x;
    int right_2 = threatObjectRect.x + threatObjectRect.w;
    int top_2 = threatObjectRect.y;
    int bot_2 = threatObjectRect.y + threatObjectRect.h;

    if (left_2 > left_1 && left_2 < right_1 - 10)
    {
        if (top_2 >= top_1 + amoObjectRect.h * 0.45 && top_2 <= top_1 + amoObjectRect.h * 0.65)
        {
            return true;
        }
        else if ((top_2 > top_1 && top_2 < top_1 + amoObjectRect.h * 0.45) || (top_2 > top_1 + amoObjectRect.h * 0.7 && top_2 < bot_1 - 20))
        {
            if (left_2 > left_1 && left_2 < left_1 + amoObjectRect.w * 0.5)
            {
                return true;
            }
        }
        else if ((top_2 < top_1 + amoObjectRect.h * 0.1 && top_2 > top_1) || (bot_2 > top_1 + amoObjectRect.h * 0.9 && bot_2 < bot_1 - 20))
        {
            if (left_2 > left_1 && left_2 < left_1 + amoObjectRect.w * 0.08)
            {
                return true;
            }
        }
    }

    return false;
}

void AmoObject::removeAmoObject(const int pos)
{
    if (AmoObjectList.size() > 0 && pos < AmoObjectList.size())
    {
        AmoObject* nowAmoObject = AmoObjectList.at(pos);
        AmoObjectList.erase(AmoObjectList.begin() + pos);
        if (nowAmoObject)
        {
            delete nowAmoObject;
            nowAmoObject = NULL;
        }
    }
  
}

SDL_Rect AmoObject::getAmoObjectRect()
{
    SDL_Rect newAmoObjectRect = { posX, posY, AmoObjectTexWidth, AmoObjectTexHeight };
    return newAmoObjectRect;
}

int AmoObject::getPosX()
{
    return posX;
}

int AmoObject::getPosY()
{
    return posY;
}

int AmoObject::getAmoObjectWidth()
{
    return AmoObjectTexWidth;
}

int AmoObject::getAmoObjectHeight()
{
    return AmoObjectTexHeight;
}





