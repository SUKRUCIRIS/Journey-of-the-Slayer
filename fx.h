#pragma once
#include <raylib.h>

typedef struct fx {
	Rectangle* position;
	Rectangle source;
	unsigned int positionnumber;
	Texture2D* texture;
	int framenumber;
	unsigned char* whichframe;
	unsigned char framedelay;
	unsigned char* delaycounter;
}fx;

fx* createfxfromgif(const char* path, char framedelay);

void addfx(fx* effect, Rectangle* position);

void renderallfx(void);

void destroyfx(fx* effect);

void destroyallfx(void);

void loadallfx(void);

fx* getattackfx(void);