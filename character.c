#include "character.h"
#include <stdlib.h>

character* createcharacter(int tilex, int tiley, float size, tile* tileset, int x) {
	character* c = malloc(sizeof(character));
	c->m = createmapobject("data/characters/character.png", tilex, tiley, size, tileset, x, 0, 0, 16, 16);
	c->maxhealth = 5;
	c->health = 5;
	c->maxactionpoint = 5;
	c->actionpoint = 5;
	c->moveskill = 0;
	c->jumpskill = 0;
	c->weaponinfo = 0;
	c->headarmor = 0;
	c->torsoarmor = 0;
	c->armarmor = 0;
	c->legarmor = 0;
	return c;
}

void destroycharacter(character* c) {
	destroymapobject(c->m);
	free(c);
}