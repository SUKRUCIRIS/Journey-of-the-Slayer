#include "enemy.h"
#include <stdlib.h>

enemy** allenemies = 0;

int enemynumber = 0;

Texture2D hellslimetexture;

void loadenemytextures(void) {
	hellslimetexture = LoadTexture("data/characters/slime.png");
}

void unloadenemytextures(void) {
	UnloadTexture(hellslimetexture);
}

enemy* createrandomenemy(int tilex, int tiley, float size, tile* tileset, int x, int type) {
	enemy* c = malloc(sizeof(enemy));
	if (c) {
		if (type == 0) {
			c->m = createmapobject(&hellslimetexture, tilex, tiley, size, tileset, x, 0, 0, 16, 16);
			c->maxhealth = rand() % 50 + 20;
			c->health = c->maxhealth;
			c->maxactionpoint = 4;
			c->actionpoint = c->maxactionpoint;
			c->lifesteal = rand() % 5;
			c->liferegen = rand() % 5;
			c->damageincperc = rand() % 5;
			c->protectperc = rand() % 5;
			c->dodgeperc = rand() % 20 + 5.0f;
			c->critichitchance = rand() % 5;
			c->range = 1;
			c->damage = 10;
			strcpy(c->name, "Hell Slime");
			tileset[(tilex * x) + tiley].obstacle = 1;
		}
		enemy** allenemies2 = malloc(sizeof(map_object*) * (enemynumber + 1));
		for (int i = 0; i < enemynumber; i++) {
			allenemies2[i] = allenemies[i];
		}
		allenemies2[enemynumber] = c;
		free(allenemies);
		allenemies = allenemies2;
		enemynumber++;
	}
	return c;
}

void destroyenemy(enemy* c) {
	enemy** allenemies2 = malloc(sizeof(map_object*) * (enemynumber - 1));
	char found = 0;
	for (int i = 0; i < enemynumber; i++) {
		if (allenemies[i] == c) {
			found = 1;
			continue;
		}
		if (found == 0) {
			allenemies2[i] = allenemies[i];
		}
		else {
			allenemies2[i - 1] = allenemies[i];
		}
	}
	free(allenemies);
	allenemies = allenemies2;
	enemynumber--;
	destroymapobject(c->m);
	free(c);
}

void destroyallenemies(void) {
	for (int i = 0; i < enemynumber; i++) {
		destroymapobject(allenemies[i]->m);
		free(allenemies[i]);
	}
	free(allenemies);
	allenemies = 0;
	enemynumber = 0;
}

void playenemy(enemy* c) {

}

void playallenemies(void) {

}

enemy** getallenemies(void) {
	return allenemies;
}

int getenemynumber(void) {
	return enemynumber;
}