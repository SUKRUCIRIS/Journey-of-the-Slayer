#include "village.h"
#include <stdlib.h>
#include <stdio.h>

Texture2D villagetexture;

village** allvillages = 0;
int villagenumber = 0;

Rectangle villagebar;

//rendervillageinfo
Rectangle villageinfoback = { 1500,680,400,380 };
Color backcolorv = { 48,0,74,255 };
char villageinfo[100] = { 0 };
Vector2 positionv;
Rectangle portraitv = { 1668,700,64,64 };
//rendervillageinfo

void loadvillagetextures(void) {
	villagetexture = LoadTexture("data/characters/village.png");
}

void unloadvillagetextures(void) {
	UnloadTexture(villagetexture);
}

village* createvillage(int tilex, int tiley, float size, tile* tileset, int x, float health) {
	village* vil = malloc(sizeof(village));
	if (vil) {
		vil->m = createmapobject(&villagetexture, tilex, tiley, size, tileset, x, 0, 0, 16, 16);
		vil->health = health;
		vil->maxhealth = health;
		village** allvillages2 = malloc(sizeof(village*) * (villagenumber + 1));
		if (allvillages2) {
			for (int i = 0; i < villagenumber; i++) {
				allvillages2[i] = allvillages[i];
			}
			allvillages2[villagenumber] = vil;
			villagenumber++;
			free(allvillages);
			allvillages = allvillages2;
		}
	}
	return vil;
}

void destroyallvillages(void) {
	for (int i = 0; i < villagenumber; i++) {
		destroymapobject(allvillages[i]->m);
		free(allvillages[i]);
	}
	free(allvillages);
	villagenumber = 0;
	allvillages = 0;
}

void rendervillagebars(void) {
	for (int i = 0; i < villagenumber; i++) {
		villagebar.x = allvillages[i]->m->position.x - 5;
		villagebar.y = allvillages[i]->m->position.y + allvillages[i]->m->position.height + 5;
		villagebar.width = allvillages[i]->m->position.width + 10;
		villagebar.height = 12;
		DrawRectangleRec(villagebar, BLACK);
		DrawRectangle(villagebar.x, villagebar.y, villagebar.width * (allvillages[i]->health / allvillages[i]->maxhealth), villagebar.height, RED);
		DrawRectangleLinesEx(villagebar, 2, WHITE);
	}
}

void rendervillageinfos(Font* myfont) {
	for (int i = 0; i < villagenumber; i++) {
		if (allvillages[i]->m->tileon && tile_status(allvillages[i]->m->tileon) == 2) {
			if (allvillages[i]->health > 0) {
				DrawRectangleRec(villageinfoback, backcolorv);
				DrawRectangleLinesEx(villageinfoback, 2, WHITE);
				sprintf(villageinfo, "Village %d", i + 1);
				positionv = MeasureTextEx(*myfont, villageinfo, 30, 0);
				positionv.x = 1500 + (400 - positionv.x) / 2;
				positionv.y = 784;
				DrawTextEx(*myfont, villageinfo, positionv, 30, 0, WHITE);
				sprintf(villageinfo, "Health: %.1f/%.1f", allvillages[i]->health, allvillages[i]->maxhealth);
				positionv = MeasureTextEx(*myfont, villageinfo, 30, 0);
				positionv.x = 1500 + (400 - positionv.x) / 2;
				positionv.y = 850;
				DrawTextEx(*myfont, villageinfo, positionv, 30, 0, WHITE);
				positionv.x = 0;
				positionv.y = 0;
				DrawTexturePro(villagetexture, allvillages[i]->m->source, portraitv, positionv, 0, WHITE);
			}
		}
	}
}