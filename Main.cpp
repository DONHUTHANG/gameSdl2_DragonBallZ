#include "CommonFunc.h"
#include "LoadImage.h"
#include "MainObject.h"
#include "AmoObject.h"
#include "ThreatObject.h"
#include "Text.h"
#include "Life.h"

bool initSDL(SDL_Window*& gWindow, SDL_Renderer*& gRender);

int main(int argc, char* argv[])
{
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRender = NULL;
    SDL_Event gEvents;

    if (!initSDL(gWindow, gRender)) return 0;
    else
    {
        bool quit = false;

        LoadImage background;

        LoadImage menu[3];

        MainObject mainObject;

        AmoObject amo;

        ThreatObject threat;

        Explosion explosion;

        Explosion expMain;

        ThreatObject* initEnemy = new ThreatObject[NUMBER_ENEMIES];

        Life life;

        Mix_Chunk* laserSound = Mix_LoadWAV("laser_gun.wav");

        Mix_Chunk* explosionSound = Mix_LoadWAV("explosion_sound.wav");

        Mix_Music* galaxySound = Mix_LoadMUS("MenuSound.wav");

        TTF_Font* font = TTF_OpenFont("font_text.ttf", 35);

        Text time;
        time.setColorWithType(Text::WHITE);

        Text mark;
        mark.setColorWithType(Text::WHITE);
        int markValue = 0;

        int scrolling = 0;

        int numberLife = 3;

        Mix_PlayMusic(galaxySound, -1);

        if (!background.loadFromFile("images/BackGround.png", gRender))
        {
            cout << "Unable to load image background";
            return 0;
        }
        //mainObject.SwapImage(gEvents, gRender, 150, 250);
        if (!mainObject.loadMainObject("images/songoku.png", gRender))
        {
            cout << "Unable to load image main object";
            return 0;
        }
        if (!explosion.loadExplosionImg("images/explosion_(1).png", gRender))
        {
            cout << "Unable to load image explosion";
            return 0;
        }

        menu[0].loadFromFile("images/Menu.png", gRender);
        menu[1].loadFromFile("images/win.png", gRender);
        menu[2].loadFromFile("images/failed.png", gRender);

        expMain.loadExplosionImg("images/bum1.png", gRender);

        expMain.setClip();

        explosion.setClip();

        threat.createThreatObject(gRender, initEnemy, NUMBER_ENEMIES);

        life.initLife(gRender);

        bool is_quit = true;

        while (!quit)
        {
            menu[0].render(0, 0, gRender);
            SDL_RenderPresent(gRender);
            while (SDL_PollEvent(&gEvents) != 0 && is_quit == true)
            {
                if (gEvents.type == SDL_KEYDOWN)
                {
                    switch (gEvents.key.keysym.sym)
                    {
                    case SDLK_2:
                    {
                        close(gWindow, gRender);
                        return 0;
                    }
                    break;
                    case SDLK_1:
                        quit = true;
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        quit = false;

        while (!quit)
        {
            while (SDL_PollEvent(&gEvents) != 0)
            {
                if (gEvents.type == SDL_QUIT)
                {
                    quit = true;
                }

                mainObject.handleInput(gEvents, gRender);
                amo.handleInputAmoObject(gEvents, gRender, laserSound,
                    mainObject.getPosX() + mainObject.getMainObjectWidth() - 110, mainObject.getPosY() + mainObject.getMainObjectHeight() / 2 - 28);
            }

            mainObject.handleMove();

            scrolling -= 2;
            if (scrolling < -background.getWidth())
            {
                scrolling = 0;
            }
            background.render(scrolling, 0, gRender);
            background.render(scrolling + background.getWidth(), 0, gRender);

            amo.handleAmoObject(gRender);

            mainObject.RenderMainObject(gRender);

            life.showLife(gRender);

            string texTime = "Time Survive: ";
            Uint32 timeValue = SDL_GetTicks() / 1000;
            string currentTime = to_string(timeValue);
            texTime += currentTime;
            time.setText(texTime);
            time.loadFromRenderTex(font, gRender);
            time.setTexPos(SCREEN_WIDTH - 250, 15);
            time.texRender(gRender);

            string texMark = "Score: ";
            string currentMark = to_string(markValue);
            texMark += currentMark;
            mark.setText(texMark);
            mark.loadFromRenderTex(font, gRender);
            mark.setTexPos(SCREEN_WIDTH / 2 - 75, 15);
            mark.texRender(gRender);

            if (markValue >= 50 && timeValue >= 60)
            {
                menu[1].render(0, 0, gRender);
                SDL_RenderPresent(gRender);
                SDL_Delay(10000);
                close(gWindow, gRender);
                return 0;
            }

            if (threat.ThreatAttack(gRender, gWindow, initEnemy, NUMBER_ENEMIES, mainObject.getMainObjectRect(),
                amo.getAmoObjectList(), explosionSound, explosion, markValue, expMain))
            {
                Mix_PlayChannel(-1, explosionSound, 0);
                numberLife--;
                if (numberLife > 0)
                {
                    mainObject.setMainObjectPos(150, 250);
                    threat.resetAllThreat(initEnemy, NUMBER_ENEMIES);
                    life.decreaseLife();
                    life.lifeRender(gRender);
                    SDL_Delay(500);
                    amo.getAmoObjectList().clear();
                }
                else
                {
                    menu[2].render(0, 0, gRender);
                    SDL_RenderPresent(gRender);
                    SDL_Delay(10000);
                    close(gWindow, gRender);
                    return 0;
                }
            }

            SDL_RenderPresent(gRender);

        }

        delete[] initEnemy;
    }

    close(gWindow, gRender);

    return 0;
}

bool initSDL(SDL_Window*& gWindow, SDL_Renderer*& gRender)
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "SDL could not initialize!" << SDL_GetError();
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            cout << "Warning: Linear texture filtering not enabled!";
        }
        gWindow = SDL_CreateWindow("Dragon Ball Z", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
            , SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            cout << "Window could not be created!" << SDL_GetError();
            success = false;
        }
        else
        {
            gRender = SDL_CreateRenderer(gWindow, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRender == NULL)
            {
                cout << "Renderer could not be created!" << SDL_GetError();
                success = false;
            }
            else
            {
                int Img = IMG_INIT_PNG;
                if (!(IMG_Init(Img) & Img))
                {
                    cout << "SDL_image could not initialize!" << IMG_GetError();
                    success = false;
                }
                if (TTF_Init() < 0)
                {
                    cout << "SDL_ttf could not initialize!" << TTF_GetError();
                    success = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    cout << "SDL_mixer could not initialize!" << Mix_GetError();
                    success = false;
                }
            }
        }
    }
    return success;
}
