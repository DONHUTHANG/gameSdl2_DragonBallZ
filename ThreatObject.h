#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "CommonFunc.h"
#include "AmoObject.h"
#include "Explosion.h"

class ThreatObject
{
public:

	ThreatObject();
	~ThreatObject();

	void freeThreatObject();

	bool loadThreatObjectImg(string threatObjectPath, SDL_Renderer* gRender);

	void ThreatObjectMove();

	void setThreatObjectPos(int PosX, int PosY);

	void RenderThreatObject(SDL_Renderer* gRender);

	void createAmoObject(SDL_Renderer* gRender, AmoObject* new_amo);

	bool autoShot(SDL_Renderer* gRender, int rectX, int rectY, const SDL_Rect& amoObjectRect, Explosion explosion);

	void createThreatObject(SDL_Renderer* gRender, ThreatObject* newThreat, int numberThreat);

	bool ThreatAttack(SDL_Renderer* gRender, SDL_Window* gWindow, ThreatObject* newThreat, int numberThreat, const SDL_Rect& mainObjectRect,
		vector<AmoObject*> amo_list, Mix_Chunk* explosionSound, Explosion explosion, int& markValue, Explosion explosionMain);

	bool checkColMainAndThreat(const SDL_Rect& mainObjectRect, const SDL_Rect& threatObjectRect);

	bool checkColAmoAndThreat(const SDL_Rect& amoObjectRect, const SDL_Rect& threatObjectRect);

	void checkColAmoVsThreat(vector<AmoObject*> amo_check, ThreatObject* colthreat, const SDL_Rect& threatObjectRect,
		int reset, Mix_Chunk* explosionSound, SDL_Renderer* gRender, Explosion explosion, int& markValue);

	void resetThreat(int _reset);

	void resetAllThreat(ThreatObject* allThreat, int numOfThreat);

	void resetAmo(AmoObject* amo_);

	SDL_Rect getThreatObjectRect();
	vector<AmoObject*> getThreatAmoList() const { return ThreatAmoList; }
	int getThreatObjectTexWidth();
	int getThreatObjectTexHeight();
	int getThreatObjectPosX();
	int getThreatObjectPosY();

private:

	SDL_Texture* threatObjectImg;

	vector<AmoObject*> ThreatAmoList;

	int ThreatObjectTexWidth;
	int ThreatObjectTexHeight;
	int posX;
	int posY;
	int ThreatVal;

};

#endif
