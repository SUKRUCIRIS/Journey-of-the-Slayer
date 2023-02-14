#pragma once
#include <raylib.h>
#include "map_object.h"
#include "skillbutton.h"
#include "weapon.h"
#include "armor.h"

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