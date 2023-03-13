#pragma once
#include "map_object.h"

#define MAX_ENEMY_TYPES 3

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
	char attackap;
	char name[20];
}enemy;

void loadenemytextures(void);

void unloadenemytextures(void);

enemy* createrandomenemy(int tilex, int tiley, float size, tile* tileset, int x, int type, long long unsigned int level);
//type 0 hell slime

void destroyenemy(enemy* c);

void destroyallenemies(void);

void moveenemy(enemy* c, int targetx, int targety, tile* tileset, int x);

void playenemy(void* mainc, void* tileset, enemy* c);

void playallenemies(void* mainc, void* tileset, void* font);

enemy** getallenemies(void);

int getenemynumber(void);

void enemytakedamage(enemy* c, float x);

void enemygivedamage(enemy* c, float x, void* e, char isvillage);

void enemyheal(enemy* c, float x);

void enemynextturn(enemy* c);

void renderenemyinfo(enemy* c, Font* myfont);

void renderchosenenemyinfo(Font* myfont);

void renderenemybars(void);

void killenemy(enemy* c);

char areallenemiesdead(void);