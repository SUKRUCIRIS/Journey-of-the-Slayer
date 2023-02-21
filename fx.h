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
	unsigned char* inverse;
	Color color;
	float* rotation;
}fx;

fx* createfxfromgif(const char* path, char framedelay, Color color);

void addfx(fx* effect, Rectangle* position, float rotation, unsigned char inverse);

void renderallfx(void);

void destroyfx(fx* effect);

void destroyallfx(void);

void loadallfx(void);

fx* getattackfx(void);

fx* getdeathfx(void);

char istherefx(void);