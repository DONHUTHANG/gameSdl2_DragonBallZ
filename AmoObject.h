#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_

#include "CommonFunc.h"

class AmoObject
{
public:

	AmoObject();
	~AmoObject();

	bool loadAmoObjectImg(string amoObjectPath, SDL_Renderer* gRender);

	void freeAmoObject();

	void AmoObjectMove(int rectx, int recty);

	void HandleMoveRightToLeft();

	void RenderAmoObject(SDL_Renderer* gRender);

	void setAmoObjectPos(int PosX, int PosY);

	void handleInputAmoObject(SDL_Event gEvent, SDL_Renderer* gRender, Mix_Chunk* laserSound, int PosX, int PosY);

	void handleAmoObject(SDL_Renderer* gRender);

	bool checkCol(const SDL_Rect& mainObjectRect, const SDL_Rect& threatObjectRect);

	void removeAmoObject(const int pos);

	int getVal() const { return AmoObject_val; }
	void setVal(int val) { AmoObject_val = val; }

	bool getIsShot() const { return isShot; };
	void setIsShot(bool shot) { isShot = shot; }

	void setBulletList(vector<AmoObject*> AmoObject) { AmoObjectList = AmoObject; }
	vector<AmoObject*> getAmoObjectList() const { return AmoObjectList; }

	SDL_Rect getAmoObjectRect();
	int getPosX();
	int getPosY();
	int getAmoObjectWidth();
	int getAmoObjectHeight();

private:

	SDL_Texture* AmoObjectImg;

	vector<AmoObject*> AmoObjectList;

	int posX;
	int posY;
	int AmoObjectTexWidth;
	int AmoObjectTexHeight;
	int AmoObject_val;
	bool isShot;

};

#endif