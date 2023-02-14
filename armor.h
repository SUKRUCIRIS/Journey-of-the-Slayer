#pragma once
#include <raylib.h>

typedef struct armor {
	char name[20];
	char armortype;//0 head, 1 torso, 2 arms, 3 legs
	char materialtype;//0 wood %2, 1 stone %4, 2 iron %8, 3 steel %10: her seviye z�rh�n hasar azaltma �zelli�ini g��lendirir
	char pasif;//0 yok, 1 %5 can �alma, 2 5 can yenile her tur, 3 extra 5 can, 4 extra 1 ap, 5 hasar�n� %5 artt�r, 6 %5 dodge �ans�, 7 %5 kritik hit
	char rarity;//0 common, 1 rare, 2 epic, 3 legendary: her seviye pasif �zellikleri g��lenir
	char(*putonfunction)(void*);
	char(*takeofffunction)(void*);
	Texture2D* texture;
	Rectangle source;
	char explanation[100];
}armor;