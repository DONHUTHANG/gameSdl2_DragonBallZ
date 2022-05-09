#ifndef TEXT_H_
#define TEXT_H_

#include "CommonFunc.h"

class Text
{
public:

	Text();
	~Text();

	enum TypeColor
	{
		WHITE = 0,
		RED = 1,
		YELLOW = 2
	};

	bool loadFromRenderTex(TTF_Font* texFont, SDL_Renderer* render);

	void freeTex();

	void setTexColor(Uint8 red, Uint8 green, Uint8 blue);

	void setColorWithType(int type);

	void setTexPos(int tex_x, int tex_y);

	void texRender(SDL_Renderer* render);

	void setText(const string& text_) { texString = text_; }
	string getText();

	int getTexWidth();
	int getTexHeight();

private:

	string texString;
	SDL_Texture* texImg;
	SDL_Color texColor;
	int texWidth;
	int texHeight;
	int texPosX;
	int texPosY;

};

#endif
