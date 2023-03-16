#pragma once
#include <raylib.h>

typedef struct button{
	Rectangle position;
	const char* text;
	Color textcolor;
	Color backcolor;
	Color frontcolor;
}button;

char renderbutton(button* b, Font* f);

void loadclicksound(void);

void unloadclicksound(void);

Sound* getclicksound(void);