#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	threatObjectImg = NULL;
	posX = 0;
	posY = 0;
	ThreatObjectTexWidth = 0;
	ThreatObjectTexHeight = 0;
	ThreatVal = 5;
}

ThreatObject::~ThreatObject()
{
	freeThreatObject();
	if (ThreatAmoList.size() > 0)
	{
		for (int k = 0; k < ThreatAmoList.size(); k++)
		{
			AmoObject* clearAmo = ThreatAmoList.at(k);
			if (clearAmo != NULL)
			{
				delete clearAmo;
				clearAmo = NULL;
			}
		}
		ThreatAmoList.clear();
	}
}

void ThreatObject::freeThreatObject()
{
	if (threatObjectImg != NULL)
	{
		SDL_DestroyTexture(threatObjectImg);
		threatObjectImg = NULL;
		posX = 0;
		posY = 0;
		ThreatObjectTexWidth = 0;
		ThreatObjectTexHeight = 0;
	}
}

bool ThreatObject::loadThreatObjectImg(string threatObjectPath, SDL_Renderer* gRender)
{
	SDL_Texture* ThreatNewTexture = NULL;
	SDL_Surface* ThreatNewSurface = IMG_Load(threatObjectPath.c_str());

	if (ThreatNewSurface == NULL)
	{
		cout << "Unable to load ThreatObject : " << IMG_GetError();
	}
	else
	{
		ThreatNewTexture = SDL_CreateTextureFromSurface(gRender, ThreatNewSurface);
		if (ThreatNewTexture == NULL)
		{
			cout << "Unable init Image Threat: " << SDL_GetError();
		}
		else
		{
			ThreatObjectTexWidth = ThreatNewSurface->w;
			ThreatObjectTexHeight = ThreatNewSurface->h;
		}
	}

	threatObjectImg = ThreatNewTexture;

	return threatObjectImg != NULL;
}

void ThreatObject::ThreatObjectMove()
{
	posX -= ThreatVal;
	if (posX < 0)
	{
		posX = SCREEN_WIDTH;
	}
}

void ThreatObject::setThreatObjectPos(int PosX, int PosY)
{
	posX = PosX;
	posY = PosY;
}

void ThreatObject::RenderThreatObject(SDL_Renderer* gRender)
{
	SDL_Rect ThreatObjectQuad = { posX, posY, ThreatObjectTexWidth, ThreatObjectTexHeight };
	SDL_RenderCopy(gRender, threatObjectImg, NULL, &ThreatObjectQuad);
}

void ThreatObject::createAmoObject(SDL_Renderer* gRender, AmoObject* new_amo)
{
	if (new_amo)
	{
		if (new_amo->loadAmoObjectImg("images/circle.png", gRender))
		{
			new_amo->setAmoObjectPos(posX, posY + ThreatObjectTexHeight / 2);
			new_amo->setIsShot(true);
			ThreatAmoList.push_back(new_amo);
		}
	}
}

bool ThreatObject::autoShot(SDL_Renderer* gRender, int rectX, int rectY, const SDL_Rect& amoObjectRect, Explosion explosion)
{
	for (int i = 0; i < ThreatAmoList.size(); i++)
	{
		AmoObject* tempAmo = ThreatAmoList.at(i);
		if (tempAmo)
		{
			if (tempAmo->getIsShot())
			{
				tempAmo->HandleMoveRightToLeft();
				tempAmo->RenderAmoObject(gRender);
				if (tempAmo->checkCol(amoObjectRect, tempAmo->getAmoObjectRect()))
				{
					return true;
				}
			}
			else
			{
				tempAmo->setIsShot(true);
				tempAmo->setAmoObjectPos(posX, posY + ThreatObjectTexHeight / 2);
			}
		}
	}
	return false;
}

void ThreatObject::createThreatObject(SDL_Renderer* gRender, ThreatObject* newThreat, int numberThreat)
{
	for (int i = 0; i < numberThreat; i++)
	{
		ThreatObject* tempThreatObject = (newThreat + i);
		if (tempThreatObject)
		{
			if (!tempThreatObject->loadThreatObjectImg("images/feaze.png", gRender))
			{
				cout << "Unable to load image ThreatObject: " << SDL_GetError();
			}
			else
			{
				int newRandY = rand() % 500;
				if (newRandY > SCREEN_HEIGHT)
				{
					newRandY = SCREEN_HEIGHT / 2;
				}
				tempThreatObject->setThreatObjectPos(SCREEN_WIDTH + i * 1000, newRandY);

				AmoObject* p_amo = new AmoObject();
				tempThreatObject->createAmoObject(gRender, p_amo);
			}
		}
	}
}

bool ThreatObject::ThreatAttack(SDL_Renderer* gRender, SDL_Window* gWindow, ThreatObject* newThreat, int numberThreat,
	const SDL_Rect& mainObjectRect, vector<AmoObject*> amo_list, Mix_Chunk* explosionSound, Explosion explosion, int& markValue, Explosion explosionMain)
{
	for (int j = 0; j < numberThreat; j++)
	{
		ThreatObject* tempThreatObject = (newThreat + j);
		if (tempThreatObject)
		{
			tempThreatObject->ThreatObjectMove();
			tempThreatObject->RenderThreatObject(gRender);
			if (tempThreatObject->autoShot(gRender, SCREEN_WIDTH, SCREEN_HEIGHT, mainObjectRect, explosion))
			{
				for (int exp = 0; exp < NUMBER_FRAME; exp++)
				{
					int exp_x = mainObjectRect.x - explosion.getExplosionWidth() * 0.5 + 30;
					int exp_y = mainObjectRect.y - explosion.getExplosionHeight() * 0.5 + 30;

					explosionMain.setExplosion(exp);
					explosionMain.setExplosionPos(exp_x, exp_y);
					explosionMain.RenderExplosion(gRender);
					SDL_Delay(25);
					SDL_RenderPresent(gRender);
				}
				return true;
			}

			checkColAmoVsThreat(amo_list, tempThreatObject, tempThreatObject->getThreatObjectRect(), j, explosionSound, gRender, explosion, markValue);

			if (checkColAmoAndThreat(mainObjectRect, tempThreatObject->getThreatObjectRect()))
			{
				for (int exp = 0; exp < NUMBER_FRAME; exp++)
				{
					int exp_x = mainObjectRect.x - explosion.getExplosionWidth() * 0.5 + 30;
					int exp_y = mainObjectRect.y - explosion.getExplosionHeight() * 0.5 + 30;

					explosionMain.setExplosion(exp);
					explosionMain.setExplosionPos(exp_x, exp_y);
					explosionMain.RenderExplosion(gRender);
					SDL_Delay(25);
					SDL_RenderPresent(gRender);
				}
				return true;
			}
		}
	}

	return false;
}

void ThreatObject::checkColAmoVsThreat(vector<AmoObject*> amo_check, ThreatObject* colthreat, const SDL_Rect& threatObjectRect,
	int reset, Mix_Chunk* explosionSound, SDL_Renderer* gRender, Explosion explosion, int& markValue)
{
	for (int im = 0; im < amo_check.size(); im++)
	{
		AmoObject* currentAmo = amo_check.at(im);
		if (currentAmo)
		{
			if (checkColAmoAndThreat(currentAmo->getAmoObjectRect(), threatObjectRect))
			{
				Mix_PlayChannel(-1, explosionSound, 0);
				markValue++;

				for (int exp = 0; exp < NUMBER_FRAME; exp++)
				{
					int exp_x = currentAmo->getAmoObjectRect().x - explosion.getExplosionWidth() * 0.5 + 30;
					int exp_y = currentAmo->getAmoObjectRect().y - explosion.getExplosionHeight() * 0.5;

					explosion.setExplosion(exp);
					explosion.setExplosionPos(exp_x, exp_y);
					explosion.RenderExplosion(gRender);
				}

				colthreat->resetThreat(SCREEN_WIDTH + reset * 1000);
				currentAmo->setAmoObjectPos(-5, -5);
				currentAmo->removeAmoObject(im);
			}
		}
	}
}

void ThreatObject::resetThreat(int e_reset)
{
	posX = e_reset;
	int newRandY = rand() % 500;
	if (newRandY > SCREEN_HEIGHT)
	{
		newRandY = SCREEN_HEIGHT / 2;
	}
	posY = newRandY;

	for (int n = 0; n < ThreatAmoList.size(); n++)
	{
		AmoObject* p_amo = ThreatAmoList.at(n);
		if (p_amo)
		{
			resetAmo(p_amo);
		}
	}
}

void ThreatObject::resetAmo(AmoObject* amo_)
{
	amo_->setAmoObjectPos(posX, posY + ThreatObjectTexHeight / 2);
}

void ThreatObject::resetAllThreat(ThreatObject* allThreat, int numOfThreat)
{
	for (int i = 0; i < numOfThreat; i++)
	{
		ThreatObject* current_ThreatObject = (allThreat + i);
		current_ThreatObject->resetThreat(SCREEN_WIDTH + i * 1000);
	}
}

bool ThreatObject::checkColMainAndThreat(const SDL_Rect& mainObjectRect, const SDL_Rect& threatObjectRect)
{
	int left_1 = mainObjectRect.x;
	int right_1 = mainObjectRect.x + mainObjectRect.w;
	int top_1 = mainObjectRect.y;
	int bot_1 = mainObjectRect.y + mainObjectRect.h;

	int left_2 = threatObjectRect.x;
	int right_2 = threatObjectRect.x + threatObjectRect.w;
	int top_2 = threatObjectRect.y;
	int bot_2 = threatObjectRect.y + threatObjectRect.h;

	if (right_1 - 30 > left_2 + 30 && right_1 - 30 < left_2 + threatObjectRect.w * 0.1)
	{
		if ((top_1 > top_2 && top_1 < bot_2) || (bot_1 > top_2 && bot_1 < bot_2))
		{
			return true;
		}
	}
	else if (right_2 > left_1 + 30 && right_2 < right_1)
	{
		if (top_2 + threatObjectRect.h * 0.4 > top_1 && top_2 + threatObjectRect.h * 0.4 < bot_1)
		{
			return true;
		}
	}
	else if (left_1 + 20 > left_2 + threatObjectRect.w * 0.7 && left_1 + 20 < right_2)
	{
		if (top_2 + threatObjectRect.h * 0.4 > top_1 && top_2 + threatObjectRect.h * 0.4 < bot_1 - 20)
		{
			return true;
		}
	}
	else if (left_2 > left_1 && left_2 < right_1)
	{
		if (bot_2 > top_1 + mainObjectRect.h * 0.5 && bot_2 < bot_1)
		{
			return true;
		}
	}
	//
	else if (left_1 > left_2 && left_1 < left_2 + threatObjectRect.w * 0.7)
	{
		if (top_1 + 30 < bot_2 && top_1 > top_2)
		{
			return true;
		}
	}
	//
	else if (left_1 > left_2 + threatObjectRect.w * 0.7 && left_1 < right_2)
	{
		if (bot_1 - 20 > top_2 + threatObjectRect.h * 0.3 && bot_1 < bot_2)
		{
			return true;
		}
	}
	//
	else if (left_1 > left_2 && left_1 < left_2 + threatObjectRect.w * 0.7)
	{
		if (bot_1 > top_2 && bot_1 < bot_2)
		{
			return true;
		}
	}

	return false;
}

bool ThreatObject::checkColAmoAndThreat(const SDL_Rect& amoObjectRect, const SDL_Rect& threatObjectRect)
{
	int left_1 = amoObjectRect.x;
	int right_1 = amoObjectRect.x + amoObjectRect.w;
	int top_1 = amoObjectRect.y;
	int bot_1 = amoObjectRect.y + amoObjectRect.h;

	int left_2 = threatObjectRect.x;
	int right_2 = threatObjectRect.x + threatObjectRect.w;
	int top_2 = threatObjectRect.y;
	int bot_2 = threatObjectRect.y + threatObjectRect.h;

	if (right_1 > left_2 && right_1 < right_2)
	{
		if (top_1 > top_2 && top_1 < bot_2)
		{
			return true;
		}
	}

	return false;
}

SDL_Rect ThreatObject::getThreatObjectRect()
{
	SDL_Rect newThreatObjectRect = { posX, posY, ThreatObjectTexWidth, ThreatObjectTexHeight };
	return newThreatObjectRect;
}

int ThreatObject::getThreatObjectTexWidth()
{
	return ThreatObjectTexWidth;
}

int ThreatObject::getThreatObjectTexHeight()
{
	return ThreatObjectTexHeight;
}

int ThreatObject::getThreatObjectPosX()
{
	return posX;
}

int ThreatObject::getThreatObjectPosY()
{
	return posY;
}
