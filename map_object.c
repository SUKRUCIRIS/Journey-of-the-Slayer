#include "map_object.h"
#include <stdlib.h>
#include <math.h>

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
	m->inanimation = 0;
	m->animationpositions = 0;
	m->maxanimationposition = 0;
	m->inanimationposition = 0;
	m->animationspeed = 500;
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
	if (!m->inanimation) {
		calculateposmapobject(m->tileon, m, &(m->position), 0);
	}
	else {
		a.x = m->position.x + (m->animationspeed * GetFrameTime() * (m->animationpositions[m->inanimationposition].x - m->position.x)) /
			(fabsf(m->animationpositions[m->inanimationposition].y - m->position.y) + fabsf(m->animationpositions[m->inanimationposition].x - m->position.x));
		a.y = m->position.y + (m->animationspeed * GetFrameTime() * (m->animationpositions[m->inanimationposition].y - m->position.y)) /
			(fabsf(m->animationpositions[m->inanimationposition].y - m->position.y) + fabsf(m->animationpositions[m->inanimationposition].x - m->position.x));
		if (a.x > m->position.x) {
			if (a.x >= m->animationpositions[m->inanimationposition].x) {
				m->position.x = m->animationpositions[m->inanimationposition].x;
			}
			else {
				m->position.x = a.x;
			}
		}
		else if (a.x < m->position.x) {
			if (a.x <= m->animationpositions[m->inanimationposition].x) {
				m->position.x = m->animationpositions[m->inanimationposition].x;
			}
			else {
				m->position.x = a.x;
			}
		}
		if (a.y > m->position.y) {
			if (a.y >= m->animationpositions[m->inanimationposition].y) {
				m->position.y = m->animationpositions[m->inanimationposition].y;
			}
			else {
				m->position.y = a.y;
			}
		}
		else if (a.y < m->position.y) {
			if (a.y <= m->animationpositions[m->inanimationposition].y) {
				m->position.y = m->animationpositions[m->inanimationposition].y;
			}
			else {
				m->position.y = a.y;
			}
		}
		if (m->position.x == m->animationpositions[m->inanimationposition].x &&
			m->position.y == m->animationpositions[m->inanimationposition].y) {
			m->inanimationposition++;
			if (m->inanimationposition >= m->maxanimationposition) {
				free(m->animationpositions);
				m->animationpositions = 0;
				m->inanimationposition = 0;
				m->maxanimationposition = 0;
				m->inanimation = 0;
			}
		}
	}
	a.x = 0;
	a.y = 0;
	DrawTexturePro(*(m->texture), m->source, m->position, a, 0, WHITE);
}

void renderallmapobjects(void) {
	for (int i = 0; i < arraysize; i++) {
		rendermapobject(allmapobjects[i]);
	}
}

void addanimationmapobject(map_object* m, Vector2* animationpositions, unsigned char maxanimationposition) {
	m->animationpositions = animationpositions;
	m->maxanimationposition = maxanimationposition;
	m->inanimation = 1;
}

void setanimationspeedmapobject(map_object* m, float animationspeed) {
	m->animationspeed = animationspeed;
}

void calculateposmapobject(tile* t, map_object* m, Vector2* v, char abs) {
	if (!abs) {
		v->x = t->position.x + ((t->position.width - m->position.width) / 2);
		v->y = t->position.y + (m->position.width * 0.3f);
	}
	else {
		v->x = t->absposition.x + ((t->absposition.width - m->position.width) / 2);
		v->y = t->absposition.y + (m->position.width * 0.3f);
	}
}

char isthereanimation(void) {
	for (int i = 0; i < arraysize; i++) {
		if (allmapobjects[i]->inanimation) {
			return 1;
		}
	}
	return 0;
}