#pragma once
#include "skillbutton.h"

typedef struct weapon {
	skillbutton* skill1;
	skillbutton* skill2;
	char name[20];
	Texture2D* texture;
	Rectangle* source;
	char explanation[100];
}weapon;

void loadweapontextures(void);

void unloadweapontextures(void);

weapon* getfistweapon(void);

weapon* getestocweapon(void);

weapon* getbowweapon(void);