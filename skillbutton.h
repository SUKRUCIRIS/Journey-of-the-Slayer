#pragma once
#include <raylib.h>

typedef struct skillbutton {
	const Rectangle* position;
	const char* name;
	const Texture2D* texture;
	const char passive;
	char pressed;
	char mouseon;
	char actionpoint;
	const char* explanation;
}skillbutton;

void writeinrectangle(Font* font, const char* text, float x, float y, float w, float size, float borderwidth, Color* color);

void loadskillbuttontextures(void);

void unloadskillbuttontextures(void);

void renderskillbutton(skillbutton* s, void* mainc);

skillbutton* getjumpskillbutton(void);

skillbutton* getmoveskillbutton(void);