#pragma once
#include "map_object.h"

typedef struct enemy {
	map_object* m;
	float maxhealth;
	float health;
	char maxactionpoint;
	char actionpoint;
	float lifesteal;
	float liferegen;
	float damageincperc;
	float protectperc;
	float dodgeperc;
	float critichitchance;
	int range;
	float damage;
	char name[20];
}enemy;

void loadenemytextures(void);

void unloadenemytextures(void);

enemy* createrandomenemy(int tilex, int tiley, float size, tile* tileset, int x, int type);
//type 0 hell slime

void destroyenemy(enemy* c);

void destroyallenemies(void);

void playenemy(enemy* c);

void playallenemies(void);

enemy** getallenemies(void);

int getenemynumber(void);