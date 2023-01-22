#pragma once
#include <raylib.h>

Rectangle moveskillposition = { 1740,200,128,128 };
Rectangle jumpskillposition = { 1740,380,128,128 };
Color skillbackcolor = { 48, 0, 74,255 };
Color skillfrontcolor = { 96, 0, 148,255 };

typedef struct skillbutton {
	Rectangle* position;
	const char* name;
	Texture2D texture;
	char passive;
	char pressed;
	char mouseon;
}skillbutton;

void renderskillbutton(skillbutton* s);