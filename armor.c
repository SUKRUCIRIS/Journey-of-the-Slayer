#include "armor.h"
#include "character.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Texture2D helmettexture;
Texture2D chestplatetexture;
Texture2D gauntletstexture;
Texture2D leggingstexture;
Rectangle armsource = { 0,0,16,16 };
Color wood = { 150, 111, 51 ,255 };
Color stone = { 188,182,179 ,255 };
Color iron = { 94,94,94 ,255 };
Color steel = { 67,70,75 ,255 };
Color backcolorarm = { 48,0,74,255 };
Vector2 originarmor = { 0,0 };
Vector2 vector = { 0,0 };
Rectangle infotexturerect;

void loadarmortextures(void) {
	helmettexture = LoadTexture("data/armors/helmet.png");
	chestplatetexture = LoadTexture("data/armors/chestplate.png");
	gauntletstexture = LoadTexture("data/armors/gauntlets.png");
	leggingstexture = LoadTexture("data/armors/leggings.png");
}

void unloadarmortextures(void) {
	UnloadTexture(helmettexture);
	UnloadTexture(chestplatetexture);
	UnloadTexture(gauntletstexture);
	UnloadTexture(leggingstexture);
}

armor* createrandomarmor(long long unsigned int levelx) {
	armor* arm = malloc(sizeof(armor));
	if (arm) {
		if (ishappened(levelx)) {
			arm->rarity = 3;
			sprintf(arm->name, "Legendary ");
		}
		else if (ishappened(2 * levelx)) {
			arm->rarity = 2;
			sprintf(arm->name, "Epic ");
		}
		else if (ishappened(3 * levelx)) {
			arm->rarity = 1;
			sprintf(arm->name, "Rare ");
		}
		else {
			arm->rarity = 0;
			sprintf(arm->name, "Common ");
		}
		if (ishappened(levelx)) {
			arm->materialtype = 3;
			strcat(arm->name, "Steel ");
			sprintf(arm->explanation, "+%%16 damage reduction ");
			arm->tint = &steel;
		}
		else if (ishappened(2 * levelx)) {
			arm->materialtype = 2;
			strcat(arm->name, "Iron ");
			sprintf(arm->explanation, "+%%12 damage reduction ");
			arm->tint = &iron;
		}
		else if (ishappened(3 * levelx)) {
			arm->materialtype = 1;
			strcat(arm->name, "Stone ");
			sprintf(arm->explanation, "+%%8 damage reduction ");
			arm->tint = &stone;
		}
		else {
			arm->materialtype = 0;
			strcat(arm->name, "Wood ");
			sprintf(arm->explanation, "+%%4 damage reduction ");
			arm->tint = &wood;
		}
		arm->armortype = rand() % 4;
		if (arm->armortype == 0) {
			arm->texture = &helmettexture;
			strcat(arm->name, "Helmet");
		}
		else if (arm->armortype == 1) {
			arm->texture = &chestplatetexture;
			strcat(arm->name, "Chestplate");
		}
		else if (arm->armortype == 2) {
			arm->texture = &gauntletstexture;
			strcat(arm->name, "Gauntlets");
		}
		else if (arm->armortype == 3) {
			arm->texture = &leggingstexture;
			strcat(arm->name, "Leggings");
		}
		arm->pasif = rand() % 7;
		char x[50] = { 0 };
		if (arm->pasif == 0) {
			sprintf(x, "+%%%d life steal", 5 * (arm->rarity + 1));
		}
		else if (arm->pasif == 1) {
			sprintf(x, "+%d health regeneration", 5 * (arm->rarity + 1));
		}
		else if (arm->pasif == 2) {
			sprintf(x, "+%d max health", 5 * (arm->rarity + 1));
		}
		else if (arm->pasif == 3) {
			sprintf(x, "+%d max ap", 1 * (arm->rarity + 1));
		}
		else if (arm->pasif == 4) {
			sprintf(x, "+%%%d damage bonus", 5 * (arm->rarity + 1));
		}
		else if (arm->pasif == 5) {
			sprintf(x, "+%%%d dodge chance", 5 * (arm->rarity + 1));
		}
		else if (arm->pasif == 6) {
			sprintf(x, "+%%%d critical hit chance", 5 * (arm->rarity + 1));
		}
		strcat(arm->explanation, x);
		arm->source = &armsource;
	}
	return arm;
}

void destroyarmor(armor* arm) {
	free(arm);
}

void armorputon(void* mainc, armor* arm) {
	if (arm && mainc) {
		character* x = mainc;
		if (arm->armortype == 0) {
			destroyarmor(x->headarmor);
			x->headarmor = arm;
		}
		else if (arm->armortype == 1) {
			destroyarmor(x->torsoarmor);
			x->torsoarmor = arm;
		}
		else if (arm->armortype == 2) {
			destroyarmor(x->armarmor);
			x->armarmor = arm;
		}
		else if (arm->armortype == 3) {
			destroyarmor(x->legarmor);
			x->legarmor = arm;
		}
		x->protectperc += (arm->materialtype + 1) * 4;
		if (arm->pasif == 0) {
			x->lifesteal += 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 1) {
			x->liferegen += 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 2) {
			x->maxhealth += 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 3) {
			x->maxactionpoint += 1 * (arm->rarity + 1);
		}
		else if (arm->pasif == 4) {
			x->damageincperc += 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 5) {
			x->dodgeperc += 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 6) {
			x->critichitchance += 5 * (arm->rarity + 1);
		}
	}
}

void armortakeoff(void* mainc, armor* arm) {
	if (arm && mainc) {
		character* x = mainc;
		x->protectperc -= (arm->materialtype + 1) * 4;
		if (arm->pasif == 0) {
			x->lifesteal -= 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 1) {
			x->liferegen -= 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 2) {
			x->maxhealth -= 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 3) {
			x->maxactionpoint -= 1 * (arm->rarity + 1);
		}
		else if (arm->pasif == 4) {
			x->damageincperc -= 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 5) {
			x->dodgeperc -= 5 * (arm->rarity + 1);
		}
		else if (arm->pasif == 6) {
			x->critichitchance -= 5 * (arm->rarity + 1);
		}
		destroyarmor(arm);
		if (arm->armortype == 0) {
			x->headarmor = 0;
		}
		else if (arm->armortype == 1) {
			x->torsoarmor = 0;
		}
		else if (arm->armortype == 2) {
			x->armarmor = 0;
		}
		else if (arm->armortype == 3) {
			x->legarmor = 0;
		}
	}
}

void renderarmorinfo(armor* arm, Font* myfont, Rectangle* rec) {
	DrawRectangleRec(*rec, backcolorarm);
	DrawRectangleLinesEx(*rec, 2, WHITE);
	if (arm) {
		infotexturerect.x = rec->x + rec->width / 4;
		infotexturerect.y = rec->y + rec->width / 4;
		infotexturerect.width = rec->width / 2;
		infotexturerect.height = rec->width / 2;
		DrawRectangleRec(infotexturerect, *getraritycolor(arm->rarity));
		DrawTexturePro(*(arm->texture), *arm->source, infotexturerect, originarmor, 0, *arm->tint);
		DrawRectangleLinesEx(infotexturerect, 2, WHITE);

		vector = MeasureTextEx(*myfont, arm->name, 30, 0);
		vector.x = rec->x + ((rec->width - vector.x) / 2);
		vector.y = infotexturerect.y + infotexturerect.width + 10;
		DrawTextPro(*myfont, arm->name, vector, originarmor, 0, 30, 0, WHITE);

		writeinrectangle(myfont, arm->explanation, rec->x, vector.y + 40, rec->width, 30, 10, &WHITE);
	}
	else {
		vector = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		vector.x = rec->x + ((rec->width - vector.x) / 2);
		vector.y = rec->y + ((rec->height - vector.y) / 2);
		DrawTextPro(*myfont, "EMPTY", vector, originarmor, 0, 30, 0, WHITE);
	}
}