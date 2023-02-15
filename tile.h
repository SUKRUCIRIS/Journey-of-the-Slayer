#pragma once
#include <raylib.h>

typedef struct tile{
	Rectangle absposition;
	Rectangle position;
	Texture2D* texture;
	char obstacle;//eðer düþman veya agaç gibi þeyler varsa 1 olucak
	unsigned char type;//1 grass, 2 sea
}tile;

unsigned char tile_status(tile* t);

void tile_render(tile* t);

tile* createtileset(int x, int size, float startx, float starty, char middle, int tilexchar, int tileychar, long long unsigned int level);

void rendertileset(tile* t, int x);

void destroytileset(tile* t);

void loadtiletextures(void);

void deletetiletextures(void);

void tilesetintro(tile* t, int speed, int x, float ratio);

void tilesetoutro(tile* t, int speed, int x, float ratio);