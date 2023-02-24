#include "character.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "enemy.h"
#include <math.h>
#include "weapon.h"
#include "fx.h"

Texture2D texture;
Font* fontc;
#define warinfonumber 6
Color warinfo[warinfonumber];
Vector2 warinfopos[warinfonumber];
char info[warinfonumber][100];
int i = 0;

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
Rectangle weaponimrect = { 55,255,80,80 };
Rectangle helmetrect = { 20,360,150,150 };
Rectangle helmetimrect = { 55,415,80,80 };
Rectangle chestplatetrect = { 20,520,150,150 };
Rectangle chestplatetimrect = { 55,575,80,80 };
Rectangle gauntletsrect = { 20,680,150,150 };
Rectangle gauntletsimrect = { 55,735,80,80 };
Rectangle leggingsrect = { 20,840,150,150 };
Rectangle leggingsimrect = { 55,895,80,80 };
Rectangle weaponinforect = { 175,200,200,300 };
Rectangle helmetinforect = { 175,360,200,300 };
Rectangle chestplateinforect = { 175,520,200,300 };
Rectangle gauntletsinforect = { 175,680,200,300 };
Rectangle leggingsinforect = { 175,775,200,300 };
char apblink = 0;
Color blink = { 48, 131, 74,255 };
Color legendary = { 231,31,31 ,255 };
Color epic = { 131,31,231 ,255 };
Color rare = { 0,131,231 ,255 };
Color common = { 31,231,0 ,255 };
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
		c->weaponinfo = getfistweapon();
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
		DrawRectangleRec(weaponimrect, legendary);
		DrawTexturePro(*(c->weaponinfo->texture), *(c->weaponinfo->source), weaponimrect, origin, 0, WHITE);
		DrawRectangleLinesEx(weaponimrect, 2, WHITE);
	}
	else {
		center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		center.x = weaponimrect.x + ((weaponimrect.width - center.x) / 2);
		center.y = weaponimrect.y + ((weaponimrect.height - center.y) / 2);
		DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
	}
	if (c->headarmor) {
		if (c->headarmor->rarity == 0) {
			DrawRectangleRec(helmetimrect, common);
		}
		else if (c->headarmor->rarity == 1) {
			DrawRectangleRec(helmetimrect, rare);
		}
		else if (c->headarmor->rarity == 2) {
			DrawRectangleRec(helmetimrect, epic);
		}
		else if (c->headarmor->rarity == 3) {
			DrawRectangleRec(helmetimrect, legendary);
		}
		DrawTexturePro(*(c->headarmor->texture), *c->headarmor->source, helmetimrect, origin, 0, *c->headarmor->tint);
		DrawRectangleLinesEx(helmetimrect, 2, WHITE);
	}
	else {
		center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		center.x = helmetimrect.x + ((helmetimrect.width - center.x) / 2);
		center.y = helmetimrect.y + ((helmetimrect.height - center.y) / 2);
		DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
	}
	if (c->torsoarmor) {
		if (c->torsoarmor->rarity == 0) {
			DrawRectangleRec(chestplatetimrect, common);
		}
		else if (c->torsoarmor->rarity == 1) {
			DrawRectangleRec(chestplatetimrect, rare);
		}
		else if (c->torsoarmor->rarity == 2) {
			DrawRectangleRec(chestplatetimrect, epic);
		}
		else if (c->torsoarmor->rarity == 3) {
			DrawRectangleRec(chestplatetimrect, legendary);
		}
		DrawTexturePro(*(c->torsoarmor->texture), *c->torsoarmor->source, chestplatetimrect, origin, 0, *c->torsoarmor->tint);
		DrawRectangleLinesEx(chestplatetimrect, 2, WHITE);
	}
	else {
		center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		center.x = chestplatetimrect.x + ((chestplatetimrect.width - center.x) / 2);
		center.y = chestplatetimrect.y + ((chestplatetimrect.height - center.y) / 2);
		DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
	}
	if (c->armarmor) {
		if (c->armarmor->rarity == 0) {
			DrawRectangleRec(gauntletsimrect, common);
		}
		else if (c->armarmor->rarity == 1) {
			DrawRectangleRec(gauntletsimrect, rare);
		}
		else if (c->armarmor->rarity == 2) {
			DrawRectangleRec(gauntletsimrect, epic);
		}
		else if (c->armarmor->rarity == 3) {
			DrawRectangleRec(gauntletsimrect, legendary);
		}
		DrawTexturePro(*(c->armarmor->texture), *c->armarmor->source, gauntletsimrect, origin, 0, *c->armarmor->tint);
		DrawRectangleLinesEx(gauntletsimrect, 2, WHITE);
	}
	else {
		center = MeasureTextEx(*myfont, "EMPTY", 30, 0);
		center.x = gauntletsimrect.x + ((gauntletsimrect.width - center.x) / 2);
		center.y = gauntletsimrect.y + ((gauntletsimrect.height - center.y) / 2);
		DrawTextPro(*myfont, "EMPTY", center, origin, 0, 30, 0, WHITE);
	}
	if (c->legarmor) {
		if (c->legarmor->rarity == 0) {
			DrawRectangleRec(leggingsimrect, common);
		}
		else if (c->legarmor->rarity == 1) {
			DrawRectangleRec(leggingsimrect, rare);
		}
		else if (c->legarmor->rarity == 2) {
			DrawRectangleRec(leggingsimrect, epic);
		}
		else if (c->legarmor->rarity == 3) {
			DrawRectangleRec(leggingsimrect, legendary);
		}
		DrawTexturePro(*(c->legarmor->texture), *c->legarmor->source, leggingsimrect, origin, 0, *c->legarmor->tint);
		DrawRectangleLinesEx(leggingsimrect, 2, WHITE);
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
		DrawRectangleLinesEx(charinfodetback, 2, WHITE);
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
		DrawRectangleLinesEx(weaponinforect, 2, WHITE);
		if (c->weaponinfo) {
			writeinrectangle(myfont, c->weaponinfo->name, weaponinforect.x, weaponinforect.y, weaponinforect.width, 30, 5, &WHITE);

			writeinrectangle(myfont, c->weaponinfo->explanation, weaponinforect.x, weaponinforect.y +
				calculateheight(myfont, c->weaponinfo->name, weaponinforect.x, weaponinforect.y, weaponinforect.width, 30, 5),
				weaponinforect.width, 30, 10, &WHITE);
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
		DrawRectangleLinesEx(helmetinforect, 2, WHITE);
		if (c->headarmor) {
			writeinrectangle(myfont, c->headarmor->name, helmetinforect.x, helmetinforect.y, helmetinforect.width, 30, 5, &WHITE);

			writeinrectangle(myfont, c->headarmor->explanation, helmetinforect.x, helmetinforect.y +
				calculateheight(myfont, c->headarmor->name, helmetinforect.x, helmetinforect.y, helmetinforect.width, 30, 5),
				helmetinforect.width, 30, 10, &WHITE);
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
		DrawRectangleLinesEx(chestplateinforect, 2, WHITE);
		if (c->torsoarmor) {
			writeinrectangle(myfont, c->torsoarmor->name, chestplateinforect.x, chestplateinforect.y, chestplateinforect.width, 30, 5, &WHITE);

			writeinrectangle(myfont, c->torsoarmor->explanation, chestplateinforect.x, chestplateinforect.y +
				calculateheight(myfont, c->torsoarmor->name, chestplateinforect.x, chestplateinforect.y, chestplateinforect.width, 30, 5),
				chestplateinforect.width, 30, 10, &WHITE);
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
		DrawRectangleLinesEx(gauntletsinforect, 2, WHITE);
		if (c->armarmor) {
			writeinrectangle(myfont, c->armarmor->name, gauntletsinforect.x, gauntletsinforect.y, gauntletsinforect.width, 30, 5, &WHITE);

			writeinrectangle(myfont, c->armarmor->explanation, gauntletsinforect.x, gauntletsinforect.y +
				calculateheight(myfont, c->armarmor->name, gauntletsinforect.x, gauntletsinforect.y, gauntletsinforect.width, 30, 5),
				gauntletsinforect.width, 30, 10, &WHITE);
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
		DrawRectangleLinesEx(leggingsinforect, 2, WHITE);
		if (c->legarmor) {
			writeinrectangle(myfont, c->legarmor->name, leggingsinforect.x, leggingsinforect.y, leggingsinforect.width, 30, 5, &WHITE);

			writeinrectangle(myfont, c->legarmor->explanation, leggingsinforect.x, leggingsinforect.y +
				calculateheight(myfont, c->legarmor->name, leggingsinforect.x, leggingsinforect.y, leggingsinforect.width, 30, 5),
				leggingsinforect.width, 30, 10, &WHITE);
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
	return (rand() / (float)RAND_MAX) * 100 <= percentage;
}

void charactertakedamage(character* c, float x) {
	if (!ishappened(c->dodgeperc)) {
		x = x * ((100 - c->protectperc) / 100);
		c->health -= x;
		char text[20] = { 0 };
		sprintf(text, "%.1f Damage", x);
		setwarinfo(text, c->m);
	}
	else {
		setwarinfo("Dodged", c->m);
	}
}

void charactergivedamage(character* c, float x, enemy* e) {
	x *= ((100 + c->damageincperc) / 100);
	if (ishappened(c->critichitchance)) {
		x *= 2;
		setwarinfo("CRITICAL HIT", e->m);
	}
	enemytakedamage(e, x);
	characterheal(c, x * (c->lifesteal / 100));
}

void characterheal(character* c, float x) {
	c->health += x;
	if (x > 0) {
		char text[20] = { 0 };
		sprintf(text, "%.1f Heal", x);
		setwarinfo(text, c->m);
	}
	if (c->health > c->maxhealth) {
		c->health = c->maxhealth;
	}
}

void characternextturn(character* c) {
	characterheal(c, c->liferegen);
	c->actionpoint = c->maxactionpoint;
}

void setattackanimation(map_object* attacker, map_object* attacked) {
	if (attacker && attacked && attacker->tileon && attacked->tileon) {
		Vector2* attackerpoints = malloc(sizeof(Vector2) * 2);
		Vector2* attackedpoints = malloc(sizeof(Vector2) * 4);
		if (attackerpoints && attackedpoints) {
			calculateposmapobject(attacker->tileon, attacker, &(attackerpoints[1]), 1);
			calculateposmapobject(attacked->tileon, attacked, &(attackedpoints[1]), 1);
			calculateposmapobject(attacked->tileon, attacked, &(attackedpoints[3]), 1);
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
			Rectangle x = { attackedpoints[1].x - 15, attackedpoints[1].y - 50,attacked->position.width + 40,attacked->position.height + 40 };
			if (attacked->position.x > attacker->position.x) {
				x.x += 20;
				addfx(getattackfx(), &x, 0, 0);
			}
			else {
				x.x -= 20;
				addfx(getattackfx(), &x, 0, 1);
			}
		}
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

void setwarinfo(const char* text, map_object* m) {
	if (i >= warinfonumber) {
		i = 0;
	}
	strcpy(info[i], text);
	warinfopos[i] = MeasureTextEx(*fontc, info[i], 30, 0);
	warinfopos[i].x = m->position.x + (m->position.width - warinfopos[i].x) / 2;
	warinfopos[i].y = m->position.y - 40;
	warinfo[i].a = 255;
	for (int i2 = 0; i2 < warinfonumber; i2++) {
		if (i != i2 && fabsf(warinfopos[i].x - warinfopos[i2].x) < 50 && fabsf(warinfopos[i].y - warinfopos[i2].y) < 20) {
			warinfopos[i].y += 40;
		}
	}
	i++;
}

void setwarinfofont(Font* font) {
	fontc = font;
	for (int i2 = 0; i2 < warinfonumber; i2++) {
		warinfo[i2].r = 255;
		warinfo[i2].g = 130;
		warinfo[i2].b = 0;
		warinfo[i2].a = 0;
	}
}

void renderwarinfo(void) {
	for (int i2 = 0; i2 < warinfonumber; i2++) {
		if (warinfo[i2].a > 0) {
			warinfo[i2].a--;
			warinfopos[i2].y--;
		}
		DrawTextEx(*fontc, info[i2], warinfopos[i2], 30, 0, warinfo[i2]);
	}
}

Color* getraritycolor(char rarity) {
	if (rarity == 0) {
		return &common;
	}
	else if (rarity == 1) {
		return &rare;
	}
	else if (rarity == 2) {
		return &epic;
	}
	else if (rarity == 3) {
		return &legendary;
	}
	return 0;
}