#include "map_object.h"
#include <stdlib.h>

Vector2 a;

map_object** allmapobjects = 0;

int arraysize = 0;

map_object* createmapobject(Texture2D* texture, int tilex, int tiley, float size, tile* tileset,
	int x, int sourcex, int sourcey, int sourcewidth, int sourceheight) {
	map_object* m = malloc(sizeof(map_object));
	m->tileposition.x = (float)tilex;
	m->tileposition.y = (float)tiley;
	m->texture = texture;
	m->tileon = &(tileset[(tilex * x) + tiley]);
	m->position.x = m->tileon->position.x + ((m->tileon->position.width - size) / 2);
	m->position.y = m->tileon->position.y + (size * 0.3f);
	m->position.width = size;
	m->position.height = size;
	m->source.x = (float)sourcex;
	m->source.y = (float)sourcey;
	m->source.width = (float)sourcewidth;
	m->source.height = (float)sourceheight;
	map_object** allmapobjects2 = malloc(sizeof(map_object*) * (arraysize + 1));
	for (int i = 0; i < arraysize; i++) {
		allmapobjects2[i] = allmapobjects[i];
	}
	allmapobjects2[arraysize] = m;
	free(allmapobjects);
	allmapobjects = allmapobjects2;
	arraysize++;
	return m;
}

void movemapobject(map_object* m, int targetx, int targety, tile* tileset, int x) {
	m->tileposition.x = (float)targetx;
	m->tileposition.y = (float)targety;
	m->tileon = &(tileset[(x * targetx) + targety]);
	m->position.x = m->tileon->position.x + ((m->tileon->position.width - m->position.width) / 2);
	m->position.y = m->tileon->position.y + (m->position.width * 0.3f);
}

void destroymapobject(map_object* m) {
	map_object** allmapobjects2 = malloc(sizeof(map_object*) * (arraysize - 1));
	char found = 0;
	for (int i = 0; i < arraysize; i++) {
		if (allmapobjects[i] == m) {
			found = 1;
			continue;
		}
		if (found == 0) {
			allmapobjects2[i] = allmapobjects[i];
		}
		else {
			allmapobjects2[i - 1] = allmapobjects[i];
		}
	}
	free(allmapobjects);
	allmapobjects = allmapobjects2;
	arraysize--;
	free(m);
}

void rendermapobject(map_object* m) {
	a.x = 0;
	a.y = 0;
	m->position.x = m->tileon->position.x + ((m->tileon->position.width - m->position.width) / 2);
	m->position.y = m->tileon->position.y + (m->position.width * 0.3f);
	DrawTexturePro(*(m->texture), m->source, m->position, a, 0, WHITE);
}

void renderallmapobjects(void) {
	for (int i = 0; i < arraysize; i++) {
		rendermapobject(allmapobjects[i]);
	}
}