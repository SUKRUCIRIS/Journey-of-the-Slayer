#include "weapon.h"
#include "character.h"
#include <stdlib.h>

Texture2D fist_texture;
Texture2D sword_texture;
Texture2D bow_texture;
Rectangle sourcew = { 0,0,16,16 };

weapon fist = {
	.name = "Fists of Slayer",
	.source = &sourcew,
	.texture = &fist_texture,
	.explanation = "Bare hands of the slayer. Covered in demon blood."
};

weapon estoc = {
	.name = "Hell Estoc",
	.source = &sourcew,
	.texture = &sword_texture,
	.explanation = "A sharpened old demon bone. Slayer feel agony when holding it."
};

weapon bow = {
	.name = "Recurve Bow",
	.source = &sourcew,
	.texture = &bow_texture,
	.explanation = "Bow of a long gone ranger. Slayer can see his ghost guiding fired arrows."
};

Rectangle infotexturerectwep;
Color backcolorwep = { 48,0,74,255 };
Vector2 originwep = { 0,0 };
Vector2 vectorwep = { 0,0 };
Rectangle* tempskillrect;
Rectangle tempskillrect2;

void loadweapontextures(void) {
	fist_texture = LoadTexture("data/weapons/fist.png");
	sword_texture = LoadTexture("data/weapons/sword.png");
	bow_texture = LoadTexture("data/weapons/bow.png");
}

void unloadweapontextures(void) {
	UnloadTexture(fist_texture);
	UnloadTexture(sword_texture);
	UnloadTexture(bow_texture);
}

weapon* getfistweapon(void) {
	fist.skill1 = getfist1skillbutton();
	fist.skill2 = getfist2skillbutton();
	return &fist;
}

weapon* getestocweapon(void) {
	estoc.skill1 = getestoc1skillbutton();
	estoc.skill2 = getestoc2skillbutton();
	return &estoc;
}

weapon* getbowweapon(void) {
	bow.skill1 = getbow1skillbutton();
	bow.skill2 = getbow2skillbutton();
	return &bow;
}

weapon* getrandomweaponwithoutfist(void) {
	if (rand() % 2 == 0) {
		return &estoc;
	}
	else {
		return &bow;
	}
}

void renderweaponinfo(weapon* w, Font* myfont, Rectangle* rec, void* mainc, void* tileset) {
	DrawRectangleRec(*rec, backcolorwep);
	DrawRectangleLinesEx(*rec, 2, WHITE);
	if (w) {
		infotexturerectwep.x = rec->x + rec->width / 4;
		infotexturerectwep.y = rec->y + rec->width / 16;
		infotexturerectwep.width = rec->width / 2;
		infotexturerectwep.height = rec->width / 2;
		DrawRectangleRec(infotexturerectwep, *getraritycolor(3));
		DrawTexturePro(*(w->texture), *w->source, infotexturerectwep, originwep, 0, WHITE);
		DrawRectangleLinesEx(infotexturerectwep, 2, WHITE);

		vectorwep = MeasureTextEx(*myfont, w->name, 40, 0);
		vectorwep.x = rec->x + ((rec->width - vectorwep.x) / 2);
		vectorwep.y = infotexturerectwep.y + infotexturerectwep.width + 10;
		DrawTextPro(*myfont, w->name, vectorwep, originwep, 0, 40, 0, WHITE);

		writeinrectangle(myfont, w->explanation, rec->x, vectorwep.y + 40, rec->width, 35, 10, &WHITE);
		tempskillrect = w->skill1->position;
		tempskillrect2.x = rec->x + rec->width / 6;
		tempskillrect2.y = rec->y + rec->height - rec->width / 4 - 20;
		tempskillrect2.width = rec->width / 4;
		tempskillrect2.height = rec->width / 4;
		w->skill1->position = &tempskillrect2;
		renderskillbutton(w->skill1, mainc, tileset);
		tempskillrect2.x -= 10;
		tempskillrect2.y -= 10;
		tempskillrect2.width += 20;
		tempskillrect2.height += 20;
		DrawRectangleLinesEx(tempskillrect2, 2, WHITE);
		w->skill1->position = tempskillrect;
		tempskillrect = w->skill2->position;
		tempskillrect2.x += 10;
		tempskillrect2.y += 10;
		tempskillrect2.width -= 20;
		tempskillrect2.height -= 20;
		tempskillrect2.x = tempskillrect2.x + tempskillrect2.width + rec->width / 6;
		w->skill2->position = &tempskillrect2;
		renderskillbutton(w->skill2, mainc, tileset);
		tempskillrect2.x -= 10;
		tempskillrect2.y -= 10;
		tempskillrect2.width += 20;
		tempskillrect2.height += 20;
		DrawRectangleLinesEx(tempskillrect2, 2, WHITE);
		w->skill2->position = tempskillrect;
	}
	else {
		vectorwep = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		vectorwep.x = rec->x + ((rec->width - vectorwep.x) / 2);
		vectorwep.y = rec->y + ((rec->height - vectorwep.y) / 2);
		DrawTextPro(*myfont, "EMPTY", vectorwep, originwep, 0, 30, 0, WHITE);
	}
}