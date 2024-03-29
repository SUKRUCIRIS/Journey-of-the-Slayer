#pragma once
#include <raylib.h>

typedef struct skillbutton {
	Rectangle* position;
	const char* name;
	const Texture2D* texture;
	const char passive;
	char pressed;
	char mouseon;
	const char* explanation;
	char(*function)(void*, void*);//0 ap yok, 1 oldu, -1 yanl�� hedef, 2 input bekle, -2 input bekle
}skillbutton;

void renderrange(int x, int y, int range, char which, int max, void* tileset, char obstacle);
//which->0 hepsi, 1 sadece kara, 2 sadece deniz;obstacle 1 engel olan, 0 engel olmayan, 2 hepsi

int* calculatedistance(int x, int y, void* tileset);

Vector2* setmoveanimationpoints(int x, int y, void* tileset, void* mainc, char abs);

void setwarning(const char* text);

void renderwarning(Font* font);

void removewarning(void);

void writeinrectangle(Font* font, const char* text, float x, float y, float w, float size, float borderwidth, Color* color);

void loadskillbuttontextures(void);

void unloadskillbuttontextures(void);

void renderskillbutton(skillbutton* s, void* mainc, void* tileset);

float calculateheight(Font* font, const char* text, float x, float y, float w, float size, float borderwidth);

skillbutton* getjumpskillbutton(void);

skillbutton* getmoveskillbutton(void);

skillbutton* getfist1skillbutton(void);

skillbutton* getfist2skillbutton(void);

skillbutton* getestoc1skillbutton(void);

skillbutton* getestoc2skillbutton(void);

skillbutton* getbow1skillbutton(void);

skillbutton* getbow2skillbutton(void);