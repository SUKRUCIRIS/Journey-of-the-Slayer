#pragma once
#include <raylib.h>
#include "map_object.h"
#include "skillbutton.h"
#include "weapon.h"
#include "armor.h"
#include "enemy.h"

typedef struct character{
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
	skillbutton* moveskill;
	skillbutton* jumpskill;
	weapon* weaponinfo;
	armor* headarmor;
	armor* torsoarmor;
	armor* armarmor;
	armor* legarmor;
	char name[20];
}character;

character* createcharacter(int tilex, int tiley, float size, tile* tileset, int x);

void destroycharacter(character* c);

void movecharacter(character* c, int targetx, int targety, tile* tileset, int x);

void rendercharacterinfo(character* c, Font* myfont);

void setcharacterapblink(char ap);

void transfercharacter(character* now, character* old);

char ishappened(float percentage);

void charactertakedamage(character* c, float x);

void charactergivedamage(character* c, float x, enemy* e);

void characterheal(character* c, float x);