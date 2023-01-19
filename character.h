#pragma once
#include <raylib.h>
#include "map_object.h"

typedef struct character{
	map_object* m;
	int maxhealth;                           
	int health;
	int maxactionpoint; 
	int actionpoint;
}character;

character* createcharacter(int tilex, int tiley, float size, tile* tileset, int x);

void destroycharacter(character* c);