#pragma once
#include "map_object.h"

typedef struct village {
	map_object* m;
	float maxhealth;
	float health;
}village;

void loadvillagetextures(void);

void unloadvillagetextures(void);

village* createvillage(int tilex, int tiley, float size, tile* tileset, int x, float health);

void destroyallvillages(void);

void rendervillagebars(void);

void rendervillageinfos(Font* myfont);