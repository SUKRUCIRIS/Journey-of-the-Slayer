#include "enemy.h"
#include <stdlib.h>
#include "character.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "fx.h"
#include "village.h"

enemy** allenemies = 0;

int enemynumber = 0;

Texture2D hellslimetexture;
Texture2D spitterdemontexture;
Texture2D cageddemontexture;

//renderenemyinfo
Rectangle enemyinfoback = { 1500,680,400,380 };
Color backcolore = { 48,0,74,255 };
char enemyinfo[300] = { 0 };
Vector2 position;
Rectangle portrait = { 1800,700,64,64 };
//renderenemyinfo

Rectangle enemybar;

void loadenemytextures(void) {
	hellslimetexture = LoadTexture("data/characters/slime.png");
	spitterdemontexture = LoadTexture("data/characters/spitterdemon.png");
	cageddemontexture = LoadTexture("data/characters/cageddemon.png");
}

void unloadenemytextures(void) {
	UnloadTexture(hellslimetexture);
	UnloadTexture(spitterdemontexture);
	UnloadTexture(cageddemontexture);
}

enemy* createrandomenemy(int tilex, int tiley, float size, tile* tileset, int x, int type, long long unsigned int level) {
	enemy* c = malloc(sizeof(enemy));
	if (c) {
		if (type == 0) {
			c->m = createmapobject(&hellslimetexture, tilex, tiley, size, tileset, x, 0, 0, 16, 16);
			c->maxhealth = rand() % 10 + 11.0f + level;
			c->health = c->maxhealth;
			c->maxactionpoint = 4;
			c->actionpoint = c->maxactionpoint;
			c->lifesteal = rand() % 3 + 1.0f;
			c->liferegen = rand() % 3 + 1.0f;
			c->damageincperc = rand() % 3 + 1.0f;
			c->protectperc = rand() % 3 + 1.0f;
			c->dodgeperc = min(rand() % 3 + 5.0f + level / 5.0f, 50 + rand() % 2);
			c->critichitchance = rand() % 5 + 1.0f;
			c->range = 1;
			c->damage = min(3.0f + (level / 5.0f) + rand() % 4, 45 + rand() % 4);
			c->attackap = 2;
			strcpy(c->name, "Hell Slime");
		}
		else if (type == 1) {
			c->m = createmapobject(&spitterdemontexture, tilex, tiley, size, tileset, x, 0, 0, 16, 16);
			c->maxhealth = rand() % 10 + 15.0f + level;
			c->health = c->maxhealth;
			c->maxactionpoint = 4;
			c->actionpoint = c->maxactionpoint;
			c->lifesteal = rand() % 3 + 1.0f;
			c->liferegen = rand() % 3 + 1.0f;
			c->damageincperc = rand() % 3 + 1.0f;
			c->protectperc = rand() % 3 + 1.0f;
			c->dodgeperc = min(rand() % 3 + 3.0f + level / 5.0f, 50 + rand() % 2);
			c->critichitchance = min(rand() % 3 + 3.0f + level / 5.0f, 50 + rand() % 2);
			c->range = 2 + rand() % 2;
			c->damage = min(3.0f + (level / 5.0f) + rand() % 4, 50 + rand() % 4);
			c->attackap = 2;
			strcpy(c->name, "Spitter Demon");
		}
		else if (type == 2) {
			c->m = createmapobject(&cageddemontexture, tilex, tiley, size, tileset, x, 0, 0, 16, 16);
			c->maxhealth = rand() % 10 + 20.0f + level;
			c->health = c->maxhealth;
			c->maxactionpoint = 4;
			c->actionpoint = c->maxactionpoint;
			c->lifesteal = rand() % 3 + 1.0f;
			c->liferegen = rand() % 3 + 2.0f;
			c->damageincperc = rand() % 3 + 1.0f;
			c->protectperc = min(rand() % 3 + 5.0f + level / 5.0f, 50 + rand() % 2);
			c->dodgeperc = rand() % 3 + 1.0f;
			c->critichitchance = rand() % 3 + 1.0f;
			c->range = 1;
			c->damage = min(3.0f + (level / 5.0f) + rand() % 4, 40 + rand() % 4);
			c->attackap = 2;
			strcpy(c->name, "Caged Demon");
		}
		tileset[(tilex * x) + tiley].obstacle = 1;
		enemy** allenemies2 = malloc(sizeof(map_object*) * (enemynumber + 1));
		for (int i = 0; i < enemynumber; i++) {
			allenemies2[i] = allenemies[i];
		}
		allenemies2[enemynumber] = c;
		free(allenemies);
		allenemies = allenemies2;
		enemynumber++;
	}
	return c;
}

void destroyenemy(enemy* c) {
	enemy** allenemies2 = malloc(sizeof(map_object*) * (enemynumber - 1));
	char found = 0;
	for (int i = 0; i < enemynumber; i++) {
		if (allenemies[i] == c) {
			found = 1;
			continue;
		}
		if (found == 0) {
			allenemies2[i] = allenemies[i];
		}
		else {
			allenemies2[i - 1] = allenemies[i];
		}
	}
	free(allenemies);
	allenemies = allenemies2;
	enemynumber--;
	destroymapobject(c->m);
	free(c);
}

void destroyallenemies(void) {
	for (int i = 0; i < enemynumber; i++) {
		destroymapobject(allenemies[i]->m);
		free(allenemies[i]);
	}
	free(allenemies);
	allenemies = 0;
	enemynumber = 0;
}

void calculateoptimized(character* m, enemy* c, tile* t, int* optimized, int* optimizedi) {
	int* distance = calculatedistance((int)c->m->tileposition.x, (int)c->m->tileposition.y, t);
	for (int i = 0; i < 49; i++) {
		if (distance[i] <= c->actionpoint &&
			max(abs((int)m->m->tileposition.x - i / 7), abs((int)m->m->tileposition.y - i % 7)) == c->range) {
			if (*optimized > distance[i]) {
				*optimized = distance[i];
				*optimizedi = i;
			}
		}
	}
	if (*optimized == 1453) {
		int loop = 0;
		int distance2[49] = { 0 };
		memcpy(distance2, distance, sizeof(int) * 49);
		distance = calculatedistance((int)m->m->tileposition.x, (int)m->m->tileposition.y, t);
		while (*optimized == 1453 && loop < 100) {
			for (int i = 0; i < 49; i++) {
				if (distance2[i] <= c->actionpoint && distance[i] < *optimized) {
					*optimized = distance[i];
					*optimizedi = i;
				}
			}
			loop++;
		}
		memcpy(distance, distance2, sizeof(int) * 49);
	}
}

void playenemy(void* mainc, void* tileset, enemy* c) {
	if (c->actionpoint == 0 || c->health <= 0) {
		return;
	}
	character* m = mainc;
	tile* t = tileset;
	int* distance = 0;
	int optimized = 0;
	int optimizedi = 0;
	if (max(abs((int)m->m->tileposition.x - (int)c->m->tileposition.x), abs((int)m->m->tileposition.y - (int)c->m->tileposition.y)) <= c->range) {
		if (c->actionpoint >= c->attackap) {
			setattackanimation(c->m, m->m);
			enemygivedamage(c, c->damage, mainc, 0);
			c->actionpoint -= c->attackap;
		}
		else if (c->health <= (2 * c->maxhealth) / 3) {
			distance = calculatedistance((int)c->m->tileposition.x, (int)c->m->tileposition.y, tileset);
			for (int i = 0; i < 49; i++) {
				if (distance[i] <= c->actionpoint &&
					max(abs((int)m->m->tileposition.x - i / 7), abs((int)m->m->tileposition.y - i % 7)) >
					max(abs((int)m->m->tileposition.x - (int)c->m->tileposition.x), abs((int)m->m->tileposition.y - (int)c->m->tileposition.y))) {
					if (optimized < max(abs((int)m->m->tileposition.x - i / 7), abs((int)m->m->tileposition.y - i % 7))) {
						optimized = max(abs((int)m->m->tileposition.x - i / 7), abs((int)m->m->tileposition.y - i % 7));
						optimizedi = i;
					}
				}
			}
			addanimationmapobject(c->m, setmoveanimationpoints(optimizedi / 7, optimizedi % 7, tileset, mainc, 1), distance[optimizedi]);
			c->actionpoint -= distance[optimizedi];
			moveenemy(c, optimizedi / 7, optimizedi % 7, tileset, 7);
		}
		return;
	}
	for (int i = 0; i < getvillagenumber(); i++) {
		if (max(abs((int)getallvillages()[i]->m->tileposition.x - (int)c->m->tileposition.x),
			abs((int)getallvillages()[i]->m->tileposition.y - (int)c->m->tileposition.y)) <= c->range) {
			if (c->actionpoint >= c->attackap) {
				setattackanimation(c->m, getallvillages()[i]->m);
				enemygivedamage(c, c->damage, getallvillages()[i], 1);
				c->actionpoint -= c->attackap;
			}
			return;
		}
	}
	{
		optimized = 1453;
		distance = calculatedistance((int)c->m->tileposition.x, (int)c->m->tileposition.y, tileset);
		calculateoptimized(m, c, t, &optimized, &optimizedi);
		for (int i = 0; i < getvillagenumber(); i++) {
			if (getallvillages()[i]->m->tileon) {
				calculateoptimized(getallvillages()[i], c, t, &optimized, &optimizedi);
			}
		}
		if (optimized == 1453) {
			int loop = 0;
			while (optimized == 1453) {
				for (int i = 0; i < 49; i++) {
					if (distance[i] <= c->actionpoint &&
						max(abs((int)m->m->tileposition.x - i / 7), abs((int)m->m->tileposition.y - i % 7)) == c->range + loop) {
						if (optimized > distance[i]) {
							optimized = distance[i];
							optimizedi = i;
						}
					}
				}
				loop++;
			}
		}
		addanimationmapobject(c->m, setmoveanimationpoints(optimizedi / 7, optimizedi % 7, tileset, mainc, 1), distance[optimizedi]);
		c->actionpoint -= distance[optimizedi];
		moveenemy(c, optimizedi / 7, optimizedi % 7, tileset, 7);
		return;
	}
}

void playallenemies(void* mainc, void* tileset, void* font) {
	int deneme = 0;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	char animation = 0;
	Vector2 v1, v2, v3;
	int lasti = 0;
	for (int i = 0; i < enemynumber; i++) {
		if (allenemies[i]->health > 0) {
			enemynextturn(allenemies[i]);
		}
	}
	for (int i = 0; i < 30; i++) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		rendertileset(tileset, 7);
		renderallmapobjects();
		rendercharacterinfo(mainc, font);
		renderenemyinfo(allenemies[lasti], font);
		v1.x = allenemies[lasti]->m->position.x + allenemies[lasti]->m->position.width / 2;
		v1.y = allenemies[lasti]->m->position.y - 5;
		v2.x = allenemies[lasti]->m->position.x + 5;
		v2.y = v1.y - allenemies[lasti]->m->position.width / 2;
		v3.x = allenemies[lasti]->m->position.x + allenemies[lasti]->m->position.width - 5;
		v3.y = v2.y;
		DrawTriangle(v3, v2, v1, RED);
		renderwarning(font);
		renderenemybars();
		rendervillagebars();
		renderallfx();
		renderwarinfo();
		EndTextureMode();
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	for (int i = 0; i < enemynumber && ((character*)mainc)->health>0; i++) {
		if (allenemies[i]->health > 0) {
			deneme = 0;
		a:
			BeginTextureMode(target);
			ClearBackground(BLACK);
			rendertileset(tileset, 7);
			renderallmapobjects();
			rendercharacterinfo(mainc, font);
			renderenemyinfo(allenemies[lasti], font);
			v1.x = allenemies[lasti]->m->position.x + allenemies[lasti]->m->position.width / 2;
			v1.y = allenemies[lasti]->m->position.y - 5;
			v2.x = allenemies[lasti]->m->position.x + 5;
			v2.y = v1.y - allenemies[lasti]->m->position.width / 2;
			v3.x = allenemies[lasti]->m->position.x + allenemies[lasti]->m->position.width - 5;
			v3.y = v2.y;
			DrawTriangle(v3, v2, v1, RED);
			renderwarning(font);
			renderenemybars();
			rendervillagebars();
			renderallfx();
			renderwarinfo();
			EndTextureMode();
			BeginDrawing();
			ClearBackground(BLACK);
			DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
			EndDrawing();
			animation--;
			if (!isthereanimation() && animation <= 0) {
				playenemy(mainc, tileset, allenemies[i]);
				if (((character*)mainc)->health <= 0) {
					break;
				}
				lasti = i;
			}
			else {
				if (animation <= 0) {
					animation = 60;
				}
				goto a;
			}
			if (allenemies[i]->actionpoint > 0 && deneme < 10) {
				deneme++;
				goto a;
			}
		}
	}
	if (((character*)mainc)->health <= 0) {
		killenemy(mainc);
	}
	while (isthereanimation()) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		rendertileset(tileset, 7);
		renderallmapobjects();
		rendercharacterinfo(mainc, font);
		renderenemyinfo(allenemies[lasti], font);
		v1.x = allenemies[lasti]->m->position.x + allenemies[lasti]->m->position.width / 2;
		v1.y = allenemies[lasti]->m->position.y - 5;
		v2.x = allenemies[lasti]->m->position.x + 5;
		v2.y = v1.y - allenemies[lasti]->m->position.width / 2;
		v3.x = allenemies[lasti]->m->position.x + allenemies[lasti]->m->position.width - 5;
		v3.y = v2.y;
		DrawTriangle(v3, v2, v1, RED);
		renderwarning(font);
		renderenemybars();
		rendervillagebars();
		renderallfx();
		renderwarinfo();
		EndTextureMode();
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	for (int i = 0; i < 30; i++) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		rendertileset(tileset, 7);
		renderallmapobjects();
		rendercharacterinfo(mainc, font);
		renderenemyinfo(allenemies[lasti], font);
		v1.x = allenemies[lasti]->m->position.x + allenemies[lasti]->m->position.width / 2;
		v1.y = allenemies[lasti]->m->position.y - 5;
		v2.x = allenemies[lasti]->m->position.x + 5;
		v2.y = v1.y - allenemies[lasti]->m->position.width / 2;
		v3.x = allenemies[lasti]->m->position.x + allenemies[lasti]->m->position.width - 5;
		v3.y = v2.y;
		DrawTriangle(v3, v2, v1, RED);
		renderwarning(font);
		renderenemybars();
		rendervillagebars();
		renderallfx();
		renderwarinfo();
		EndTextureMode();
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	UnloadRenderTexture(target);
	if (((character*)mainc)->health > 0) {
		characternextturn(mainc);
	}
}

enemy** getallenemies(void) {
	return allenemies;
}

int getenemynumber(void) {
	return enemynumber;
}

void killenemy(enemy* c) {
	if (c->m->tileon) {
		Rectangle x = c->m->tileon->absposition;
		x.y -= 100;
		addfx(getdeathfx(), &x, 0, 0);
		c->health = 0;
		c->m->tileon->obstacle = 0;
		c->m->position.x = -100;
		c->m->position.x = -100;
		c->m->tileposition.x = -100;
		c->m->tileposition.y = -100;
		removeanimation(c->m);
		c->m->tileon = 0;
	}
}

float enemytakedamage(enemy* c, float x) {
	if (!ishappened(c->dodgeperc)) {
		x = x * ((100 - c->protectperc) / 100);
		c->health -= x;
		char text[20] = { 0 };
		sprintf(text, "%.1f Damage", x);
		setwarinfo(text, c->m);
		if (c->health <= 0) {
			killenemy(c);
		}
		return x;
	}
	else {
		setwarinfo("Dodged", c->m);
		return 0;
	}
}

void enemygivedamage(enemy* c, float x, void* e, char isvillage) {
	x *= ((100 + c->damageincperc) / 100);
	if (ishappened(c->critichitchance)) {
		x *= 2;
		setwarinfo("CRITICAL HIT", ((character*)e)->m);
	}
	if (isvillage) {
		villagetakedamage(e, x);
	}
	else {
		x = charactertakedamage(e, x);
	}
	enemyheal(c, x * (c->lifesteal / 100));
}

void enemyheal(enemy* c, float x) {
	if (c->health < c->maxhealth) {
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
}

void moveenemy(enemy* c, int targetx, int targety, tile* tileset, int x) {
	tileset[((int)c->m->tileposition.x * x) + (int)c->m->tileposition.y].obstacle = 0;
	movemapobject(c->m, targetx, targety, tileset, x);
	tileset[((int)c->m->tileposition.x * x) + (int)c->m->tileposition.y].obstacle = 1;
}

void enemynextturn(enemy* c) {
	enemyheal(c, c->liferegen);
	c->actionpoint = c->maxactionpoint;
}

void renderenemyinfo(enemy* c, Font* myfont) {
	if (c->health > 0) {
		DrawRectangleRec(enemyinfoback, backcolore);
		DrawRectangleLinesEx(enemyinfoback, 2, WHITE);
		sprintf(enemyinfo, "Health: %.1f/%.1f\nAction Point: %d/%d\nBase Damage: %.1f\nBase Range: %d\nAttack Cost: %dAP\nDamage Reduction: %.1f%%\nDodge Chance: %.1f%%\nCritical Hit Chance: %.1f%%\nDamage Bonus: %.1f%%\nLife Steal: %.1f%%\nHealth Regeneration: %.1f",
			c->health, c->maxhealth, c->actionpoint, c->maxactionpoint, c->damage, c->range, c->attackap, c->protectperc,
			c->dodgeperc, c->critichitchance, c->damageincperc, c->lifesteal, c->liferegen);
		position = MeasureTextEx(*myfont, c->name, 30, 0);
		position.x = enemyinfoback.x + ((enemyinfoback.width - position.x) / 2);
		position.y = enemyinfoback.y + 2;
		DrawTextEx(*myfont, c->name, position, 30, 0, WHITE);
		writeinfo(myfont, enemyinfo, enemyinfoback.x + 10, enemyinfoback.y + 40, 30, &WHITE);
		position.x = 0;
		position.y = 0;
		DrawTexturePro(*(c->m->texture), c->m->source, portrait, position, 0, WHITE);
	}
}

void renderchosenenemyinfo(Font* myfont) {
	for (int i = 0; i < enemynumber; i++) {
		if (allenemies[i]->m->tileon && tile_status(allenemies[i]->m->tileon) == 2) {
			renderenemyinfo(allenemies[i], myfont);
		}
	}
}

void renderenemybars(void) {
	for (int i = 0; i < enemynumber; i++) {
		enemybar.x = allenemies[i]->m->position.x - 5;
		enemybar.y = allenemies[i]->m->position.y + allenemies[i]->m->position.height + 5;
		enemybar.width = allenemies[i]->m->position.width + 10;
		enemybar.height = 12;
		DrawRectangleRec(enemybar, BLACK);
		DrawRectangle(enemybar.x, enemybar.y, enemybar.width * (allenemies[i]->health / allenemies[i]->maxhealth), enemybar.height, RED);
		DrawRectangleLinesEx(enemybar, 2, WHITE);
	}
}

char areallenemiesdead(void) {
	for (int i = 0; i < enemynumber; i++) {
		if (allenemies[i]->health > 0) {
			return 0;
		}
	}
	return 1;
}