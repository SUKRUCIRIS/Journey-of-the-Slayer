#include "character.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "enemy.h"
#include <math.h>

Texture2D texture;

//rendercharacterinfo
Vector2 origin = { 0,0 };
Rectangle charinfodes = { 60,60,60,60 };
Rectangle charinfoback = { 40,40,100,100 };
Color backcolor = { 48,0,74,255 };
Rectangle healthback = { 157,47,286,25 };
Rectangle healthfront = { 155,45,290,29 };
Vector2 center = { 170,104 };
char charinfodet[250] = { 0 };
Rectangle charinfodetback = { 145,40,350,300 };
Rectangle weaponrect = { 20,200,150,150 };
Rectangle weaponimrect = { 55,235,80,80 };
Rectangle helmetrect = { 20,360,150,150 };
Rectangle helmetimrect = { 55,395,80,80 };
Rectangle chestplatetrect = { 20,520,150,150 };
Rectangle chestplatetimrect = { 55,555,80,80 };
Rectangle gauntletsrect = { 20,680,150,150 };
Rectangle gauntletsimrect = { 55,715,80,80 };
Rectangle leggingsrect = { 20,840,150,150 };
Rectangle leggingsimrect = { 55,875,80,80 };
Rectangle weaponinforect = { 175,200,200,300 };
Rectangle helmetinforect = { 175,360,200,300 };
Rectangle chestplateinforect = { 175,520,200,300 };
Rectangle gauntletsinforect = { 175,680,200,300 };
Rectangle leggingsinforect = { 175,775,200,300 };
char apblink = 0;
Color blink = { 48, 131, 74,255 };
//rendercharacterinfo

void loadcharactertextures(void) {
	texture = LoadTexture("data/characters/character.png");
}

void unloadcharactertextures(void) {
	UnloadTexture(texture);
}

void transfercharacter(character* now, character* old) {
	now->maxhealth = old->maxhealth;
	now->health = old->health;
	now->maxactionpoint = old->maxactionpoint;
	now->actionpoint = old->actionpoint;
	now->moveskill = old->moveskill;
	now->jumpskill = old->jumpskill;
	now->weaponinfo = old->weaponinfo;
	now->headarmor = old->headarmor;
	now->torsoarmor = old->torsoarmor;
	now->armarmor = old->armarmor;
	now->legarmor = old->legarmor;
	now->lifesteal = old->lifesteal;
	now->liferegen = old->liferegen;
	now->damageincperc = old->damageincperc;
	now->protectperc = old->protectperc;
	now->dodgeperc = old->dodgeperc;
	now->critichitchance = old->critichitchance;
}

character* createcharacter(int tilex, int tiley, float size, tile* tileset, int x) {
	character* c = malloc(sizeof(character));
	if (c) {
		c->m = createmapobject(&texture, tilex, tiley, size, tileset, x, 0, 0, 16, 16);
		c->maxhealth = 100;
		c->health = 100;
		c->maxactionpoint = 5;
		c->actionpoint = 5;
		c->moveskill = getmoveskillbutton();
		c->jumpskill = getjumpskillbutton();
		c->weaponinfo = 0;
		c->headarmor = 0;
		c->torsoarmor = 0;
		c->armarmor = 0;
		c->legarmor = 0;
		c->lifesteal = 0;
		c->liferegen = 0;
		c->damageincperc = 0;
		c->protectperc = 0;
		c->dodgeperc = 0;
		c->critichitchance = 0;
		strcpy(c->name, "Slayer");
		tileset[(tilex * x) + tiley].obstacle = 1;
	}
	return c;
}

void movecharacter(character* c, int targetx, int targety, tile* tileset, int x) {
	tileset[((int)c->m->tileposition.x * x) + (int)c->m->tileposition.y].obstacle = 0;
	movemapobject(c->m, targetx, targety, tileset, x);
	tileset[((int)c->m->tileposition.x * x) + (int)c->m->tileposition.y].obstacle = 1;
}

void destroycharacter(character* c) {
	destroymapobject(c->m);
	free(c);
}

void rendercharacterinfo(character* c, Font* myfont) {
	healthfront.width = (c->health / c->maxhealth) * 290;
	DrawRectangleRounded(charinfoback, 0.4f, 0, backcolor);
	DrawTexturePro(*(c->m->texture), c->m->source, charinfodes, origin, 0, WHITE);
	DrawRectangleRounded(healthfront, 0.3f, 0, RED);
	DrawRectangleRoundedLines(healthback, 0.3f, 0, 4, WHITE);
	center.y = 104;
	blink.a -= 10;
	backcolor.g = 131;
	for (int i = 0; i < c->maxactionpoint; i++) {
		center.x = 170 + i * 45.0f;
		if (i < c->actionpoint) {
			if (c->actionpoint - i <= apblink) {
				DrawCircleV(center, 15, blink);
			}
			else {
				DrawCircleV(center, 15, backcolor);
			}
		}
		DrawRing(center, 15, 20, 0, 360, 0, WHITE);
	}
	backcolor.g = 0;
	DrawRectangleRec(weaponrect, backcolor);
	center = MeasureTextEx(*myfont, "Weapon", 30, 0);
	center.x = weaponrect.x + ((weaponrect.width - center.x) / 2);
	center.y = weaponrect.y + 2;
	DrawTextPro(*myfont, "Weapon", center, origin, 0, 30, 0, WHITE);
	DrawRectangleRec(helmetrect, backcolor);
	center = MeasureTextEx(*myfont, "Helmet", 30, 0);
	center.x = helmetrect.x + ((helmetrect.width - center.x) / 2);
	center.y = helmetrect.y + 2;
	DrawTextPro(*myfont, "Helmet", center, origin, 0, 30, 0, WHITE);
	DrawRectangleRec(chestplatetrect, backcolor);
	center = MeasureTextEx(*myfont, "Chestplate", 30, 0);
	center.x = chestplatetrect.x + ((chestplatetrect.width - center.x) / 2);
	center.y = chestplatetrect.y + 2;
	DrawTextPro(*myfont, "Chestplate", center, origin, 0, 30, 0, WHITE);
	DrawRectangleRec(gauntletsrect, backcolor);
	center = MeasureTextEx(*myfont, "Gauntlets", 30, 0);
	center.x = gauntletsrect.x + ((gauntletsrect.width - center.x) / 2);
	center.y = gauntletsrect.y + 2;
	DrawTextPro(*myfont, "Gauntlets", center, origin, 0, 30, 0, WHITE);
	DrawRectangleRec(leggingsrect, backcolor);
	center = MeasureTextEx(*myfont, "Leggings", 30, 0);
	center.x = leggingsrect.x + ((leggingsrect.width - center.x) / 2);
	center.y = leggingsrect.y + 2;
	DrawTextPro(*myfont, "Leggings", center, origin, 0, 30, 0, WHITE);
	if (c->weaponinfo) {
		DrawTexturePro(*(c->weaponinfo->texture), c->weaponinfo->source, weaponimrect, origin, 0, WHITE);
	}
	else {
		center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		center.x = weaponimrect.x + ((weaponimrect.width - center.x) / 2);
		center.y = weaponimrect.y + ((weaponimrect.height - center.y) / 2);
		DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
	}
	if (c->headarmor) {
		DrawTexturePro(*(c->headarmor->texture), c->headarmor->source, helmetimrect, origin, 0, WHITE);
	}
	else {
		center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		center.x = helmetimrect.x + ((helmetimrect.width - center.x) / 2);
		center.y = helmetimrect.y + ((helmetimrect.height - center.y) / 2);
		DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
	}
	if (c->torsoarmor) {
		DrawTexturePro(*(c->torsoarmor->texture), c->torsoarmor->source, chestplatetimrect, origin, 0, WHITE);
	}
	else {
		center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		center.x = chestplatetimrect.x + ((chestplatetimrect.width - center.x) / 2);
		center.y = chestplatetimrect.y + ((chestplatetimrect.height - center.y) / 2);
		DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
	}
	if (c->armarmor) {
		DrawTexturePro(*(c->armarmor->texture), c->armarmor->source, gauntletsimrect, origin, 0, WHITE);
	}
	else {
		center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		center.x = gauntletsimrect.x + ((gauntletsimrect.width - center.x) / 2);
		center.y = gauntletsimrect.y + ((gauntletsimrect.height - center.y) / 2);
		DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
	}
	if (c->legarmor) {
		DrawTexturePro(*(c->legarmor->texture), c->legarmor->source, leggingsimrect, origin, 0, WHITE);
	}
	else {
		center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		center.x = leggingsimrect.x + ((leggingsimrect.width - center.x) / 2);
		center.y = leggingsimrect.y + ((leggingsimrect.height - center.y) / 2);
		DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
	}
	//infos
	center.x = GetMousePosition().x * (1920.0f / GetRenderWidth());
	center.y = GetMousePosition().y * (1080.0f / GetRenderHeight());
	if (CheckCollisionPointRec(center, charinfoback)) {
		DrawRectangleRec(charinfodetback, backcolor);
		DrawRectangleLinesEx(charinfodetback, 1, WHITE);
		center = MeasureTextEx(*myfont, c->name, 30, 0);
		center.x = charinfodetback.x + ((charinfodetback.width - center.x) / 2);
		center.y = charinfodetback.y + 2;
		DrawTextPro(*myfont, c->name, center, origin, 0, 30, 0, WHITE);
		sprintf(charinfodet, "Health: %.1f/%.1f\nAction Point: %d/%d\nDamage Reduction: %.1f%%\nDodge Chance: %.1f%%\nCritical Hit Chance: %.1f%%\nDamage Bonus: %.1f%%\nLife Steal: %.1f%%\nHealth Regeneration: %.1f",
			c->health, c->maxhealth, c->actionpoint, c->maxactionpoint, c->protectperc,
			c->dodgeperc, c->critichitchance, c->damageincperc, c->lifesteal, c->liferegen);
		writeinfo(myfont, charinfodet, charinfodetback.x + 10, charinfodetback.y + 40, 30, &WHITE);
	}
	else if (CheckCollisionPointRec(center, weaponrect)) {
		DrawRectangleRec(weaponinforect, backcolor);
		DrawRectangleLinesEx(weaponinforect, 1, WHITE);
		if (c->weaponinfo) {
			center = MeasureTextEx(*myfont, c->weaponinfo->name, 30, 0);
			center.x = weaponinforect.x + ((weaponinforect.width - center.x) / 2);
			center.y = weaponinforect.y + 2;
			DrawTextPro(*myfont, c->weaponinfo->name, center, origin, 0, 30, 0, WHITE);

			writeinrectangle(myfont, c->weaponinfo->explanation, weaponinforect.x, weaponinforect.y + 30, weaponinforect.width, 30, 10, &WHITE);
		}
		else {
			center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
			center.x = weaponinforect.x + ((weaponinforect.width - center.x) / 2);
			center.y = weaponinforect.y + ((weaponinforect.height - center.y) / 2);
			DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
		}
	}
	else if (CheckCollisionPointRec(center, helmetrect)) {
		DrawRectangleRec(helmetinforect, backcolor);
		DrawRectangleLinesEx(helmetinforect, 1, WHITE);
		if (c->headarmor) {
			center = MeasureTextEx(*myfont, c->headarmor->name, 30, 0);
			center.x = helmetinforect.x + ((helmetinforect.width - center.x) / 2);
			center.y = helmetinforect.y + 2;
			DrawTextPro(*myfont, c->headarmor->name, center, origin, 0, 30, 0, WHITE);

			writeinrectangle(myfont, c->headarmor->explanation, helmetinforect.x, helmetinforect.y + 30, helmetinforect.width, 30, 10, &WHITE);
		}
		else {
			center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
			center.x = helmetinforect.x + ((helmetinforect.width - center.x) / 2);
			center.y = helmetinforect.y + ((helmetinforect.height - center.y) / 2);
			DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
		}
	}
	else if (CheckCollisionPointRec(center, chestplatetrect)) {
		DrawRectangleRec(chestplateinforect, backcolor);
		DrawRectangleLinesEx(chestplateinforect, 1, WHITE);
		if (c->torsoarmor) {
			center = MeasureTextEx(*myfont, c->torsoarmor->name, 30, 0);
			center.x = chestplateinforect.x + ((chestplateinforect.width - center.x) / 2);
			center.y = chestplateinforect.y + 2;
			DrawTextPro(*myfont, c->torsoarmor->name, center, origin, 0, 30, 0, WHITE);

			writeinrectangle(myfont, c->torsoarmor->explanation, chestplateinforect.x, chestplateinforect.y + 30, chestplateinforect.width, 30, 10, &WHITE);
		}
		else {
			center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
			center.x = chestplateinforect.x + ((chestplateinforect.width - center.x) / 2);
			center.y = chestplateinforect.y + ((chestplateinforect.height - center.y) / 2);
			DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
		}
	}
	else if (CheckCollisionPointRec(center, gauntletsrect)) {
		DrawRectangleRec(gauntletsinforect, backcolor);
		DrawRectangleLinesEx(gauntletsinforect, 1, WHITE);
		if (c->armarmor) {
			center = MeasureTextEx(*myfont, c->armarmor->name, 30, 0);
			center.x = gauntletsinforect.x + ((gauntletsinforect.width - center.x) / 2);
			center.y = gauntletsinforect.y + 2;
			DrawTextPro(*myfont, c->armarmor->name, center, origin, 0, 30, 0, WHITE);

			writeinrectangle(myfont, c->armarmor->explanation, gauntletsinforect.x, gauntletsinforect.y + 30, gauntletsinforect.width, 30, 10, &WHITE);
		}
		else {
			center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
			center.x = gauntletsinforect.x + ((gauntletsinforect.width - center.x) / 2);
			center.y = gauntletsinforect.y + ((gauntletsinforect.height - center.y) / 2);
			DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
		}
	}
	else if (CheckCollisionPointRec(center, leggingsrect)) {
		DrawRectangleRec(leggingsinforect, backcolor);
		DrawRectangleLinesEx(leggingsinforect, 1, WHITE);
		if (c->legarmor) {
			center = MeasureTextEx(*myfont, c->legarmor->name, 30, 0);
			center.x = leggingsinforect.x + ((leggingsinforect.width - center.x) / 2);
			center.y = leggingsinforect.y + 2;
			DrawTextPro(*myfont, c->legarmor->name, center, origin, 0, 30, 0, WHITE);

			writeinrectangle(myfont, c->legarmor->explanation, leggingsinforect.x, leggingsinforect.y + 30, leggingsinforect.width, 30, 10, &WHITE);
		}
		else {
			center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
			center.x = leggingsinforect.x + ((leggingsinforect.width - center.x) / 2);
			center.y = leggingsinforect.y + ((leggingsinforect.height - center.y) / 2);
			DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
		}
	}
}

void setcharacterapblink(char ap) {
	apblink = ap;
}

char ishappened(float percentage) {
	srand((unsigned int)time(0));
	return (rand() / (float)RAND_MAX) * 100 <= percentage;
}

void charactertakedamage(character* c, float x) {
	if (!ishappened(c->dodgeperc)) {
		x = x * ((100 - c->protectperc) / 100);
		c->health -= x;
	}
}

void charactergivedamage(character* c, float x, enemy* e) {
	x *= ((100 + c->damageincperc) / 100);
	if (ishappened(c->critichitchance)) {
		x *= 2;
	}
	enemytakedamage(e, x);
	characterheal(c, x * (c->lifesteal / 100));
}

void characterheal(character* c, float x) {
	c->health += x;
	if (c->health > c->maxhealth) {
		c->health = c->maxhealth;
	}
}

void characternextturn(character* c) {
	characterheal(c, c->liferegen);
	c->actionpoint = c->maxactionpoint;
}

void setattackanimation(map_object* attacker, map_object* attacked, tile* tileset) {
	Vector2* attackerpoints = malloc(sizeof(Vector2) * 2);
	Vector2* attackedpoints = malloc(sizeof(Vector2) * 4);
	if (attackerpoints && attackedpoints) {
		calculateposmapobject(&(tileset[(7 * (int)attacker->tileposition.x) + (int)attacker->tileposition.y]), attacker, &(attackerpoints[1]), 1);
		calculateposmapobject(&(tileset[(7 * (int)attacked->tileposition.x) + (int)attacked->tileposition.y]), attacked, &(attackedpoints[1]), 1);
		calculateposmapobject(&(tileset[(7 * (int)attacked->tileposition.x) + (int)attacked->tileposition.y]), attacked, &(attackedpoints[3]), 1);
		attackerpoints[0].x = attackerpoints[1].x + (attackedpoints[1].x - attackerpoints[1].x) * 50 /
			(fabsf(attackedpoints[1].x - attackerpoints[1].x) + fabsf(attackedpoints[1].y - attackerpoints[1].y));
		attackerpoints[0].y = attackerpoints[1].y + (attackedpoints[1].y - attackerpoints[1].y) * 50 /
			(fabsf(attackedpoints[1].x - attackerpoints[1].x) + fabsf(attackedpoints[1].y - attackerpoints[1].y));
		attackedpoints[0].x = attackedpoints[1].x - (attackerpoints[1].x - attackedpoints[1].x) * 25 /
			(fabsf(attackedpoints[1].x - attackerpoints[1].x) + fabsf(attackedpoints[1].y - attackerpoints[1].y));
		attackedpoints[0].y = attackedpoints[1].y - (attackerpoints[1].y - attackedpoints[1].y) * 25 /
			(fabsf(attackedpoints[1].x - attackerpoints[1].x) + fabsf(attackedpoints[1].y - attackerpoints[1].y));
		attackedpoints[2].x = attackedpoints[1].x + (attackerpoints[1].x - attackedpoints[1].x) * 25 /
			(fabsf(attackedpoints[1].x - attackerpoints[1].x) + fabsf(attackedpoints[1].y - attackerpoints[1].y));
		attackedpoints[2].y = attackedpoints[1].y + (attackerpoints[1].y - attackedpoints[1].y) * 25 /
			(fabsf(attackedpoints[1].x - attackerpoints[1].x) + fabsf(attackedpoints[1].y - attackerpoints[1].y));
		addanimationmapobject(attacker, attackerpoints, 2);
		addanimationmapobject(attacked, attackedpoints, 4);
	}
}

void writeinfo(Font* font, const char* text, float x, float y, float size, Color* color) {
	int count = 0;
	const char** splitted = TextSplit(text, '\n', &count);
	float spaceheight = MeasureTextEx(*font, " ", size, 0).y;
	center.x = x;
	center.y = y;
	for (int i = 0; i < count; i++) {
		DrawTextEx(*font, splitted[i], center, size, 0, *color);
		center.y += spaceheight;
	}
}