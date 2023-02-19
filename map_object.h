#pragma once
#include <raylib.h>
#include "tile.h"

typedef struct map_object {
	Rectangle position;
	Texture2D* texture;
	Vector2 tileposition;
	Rectangle source;
	tile* tileon;
	char inanimation;
	Vector2* animationpositions;//animasyon bittiðinde kendini free edicek
	unsigned char maxanimationposition;
	unsigned char inanimationposition;
	float animationspeed;
}map_object;

map_object* createmapobject(Texture2D* texture, int tilex, int tiley, float size, tile* tileset,
	int x, int sourcex, int sourcey, int sourcewidth, int sourceheight);

void movemapobject(map_object* m, int targetx, int targety, tile* tileset, int x);

void destroymapobject(map_object* m);

void rendermapobject(map_object* m);

void renderallmapobjects(void);

void addanimationmapobject(map_object* m, Vector2* animationpositions, unsigned char maxanimationposition);

void setanimationspeedmapobject(map_object* m, float animationspeed);

void calculateposmapobject(tile* t, map_object* m, Vector2* v, char abs);

char isthereanimation(void);

void removeanimation(map_object* m);