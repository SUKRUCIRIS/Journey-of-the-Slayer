#pragma once
#include <raylib.h>

typedef struct armor {
	char name[50];
	char armortype;//0 head, 1 torso, 2 arms, 3 legs
	char materialtype;//0 wood %4, 1 stone %8, 2 iron %12, 3 steel %16: her seviye zýrhýn hasar azaltma özelliðini güçlendirir
	char pasif;//0 %5 can çalma, 1 5 can yenile her tur, 2 extra 5 can, 3 extra 1 ap, 4 hasarýný %5 arttýr, 5 %5 dodge þansý, 6 %5 kritik hit
	char rarity;//0 common, 1 rare, 2 epic, 3 legendary: her seviye pasif özellikleri güçlenir
	Texture2D* texture;
	Rectangle* source;
	Color* tint;
	char explanation[150];
}armor;

void loadarmortextures(void);

void unloadarmortextures(void);

armor* createrandomarmor(long long unsigned int levelx);

void destroyarmor(armor* arm);

void armorputon(void* mainc, armor* arm);

void armortakeoff(void* mainc, armor* arm);

void renderarmorinfo(armor* arm, Font* myfont, Rectangle* rec);