#pragma once
#include <raylib.h>

typedef struct armor {
	char name[20];
	char armortype;//0 head, 1 torso, 2 arms, 3 legs
	char materialtype;//0 wood %2, 1 stone %4, 2 iron %8, 3 steel %10: her seviye z�rh�n hasar azaltma �zelli�ini g��lendirir
	char pasif;//0 %5 can �alma, 1 5 can yenile her tur, 2 extra 5 can, 3 extra 1 ap, 4 hasar�n� %5 artt�r, 5 %5 dodge �ans�, 6 %5 kritik hit
	char rarity;//0 common, 1 rare, 2 epic, 3 legendary: her seviye pasif �zellikleri g��lenir
	char(*putonfunction)(void*);
	char(*takeofffunction)(void*);
	Texture2D* texture;
	Rectangle source;
	char explanation[100];
}armor;

void loadarmortextures(void);

void unloadarmortextures(void);

armor* createrandomarmor(long long unsigned int levelx);

void destroyarmor(armor* arm);