#include "character.h"
#include <stdlib.h>

Texture2D texture;

character* createcharacter(int tilex, int tiley, float size, tile* tileset, int x) {
	character* c = malloc(sizeof(character));
	if (c) {
		texture = LoadTexture("data/characters/character.png");
		c->m = createmapobject(&texture, tilex, tiley, size, tileset, x, 0, 0, 16, 16);
		c->maxhealth = 5;
		c->health = 5;
		c->maxactionpoint = 5;
		c->actionpoint = 5;
		c->moveskill = getmoveskillbutton();
		c->jumpskill = getjumpskillbutton();
		c->weaponinfo = 0;
		c->headarmor = 0;
		c->torsoarmor = 0;
		c->armarmor = 0;
		c->legarmor = 0;
		tileset[(tilex * x) + tiley].obstacle = 1;
	}
	return c;
}

void movecharacter(character* c, int targetx, int targety, tile* tileset, int x) {
	tileset[((int)c->m->tileposition.x * x) + (int)c->m->tileposition.y].obstacle = 0;
	movemapobject(c->m, targetx, targety, tileset, x);
	tileset[((int)c->m->tileposition.x * x) + (int)c->m->tileposition.y].obstacle = 1;
}

void destroycharacter(character* c) {
	destroymapobject(c->m);
	free(c);
	UnloadTexture(texture);
}