#pragma once
#include <raylib.h>
#include "tile.h"

typedef struct map_object {
	Rectangle position;
	Texture2D texture;
	Vector2 tileposition;
	Rectangle source;
	tile* tileon;
}map_object;

map_object* createmapobject(const char* filename, int tilex, int tiley, float size, tile* tileset, 
	int x, int sourcex, int sourcey, int sourcewidth, int sourceheight);

void destroymapobject(map_object* m);

void rendermapobject(map_object* m);

void renderallmapobjects(void);