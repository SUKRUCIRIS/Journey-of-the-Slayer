#include "enemy.h"
#include <stdlib.h>
#include "character.h"
#include <math.h>

enemy** allenemies = 0;

int enemynumber = 0;

Texture2D hellslimetexture;

void loadenemytextures(void) {
	hellslimetexture = LoadTexture("data/characters/slime.png");
}

void unloadenemytextures(void) {
	UnloadTexture(hellslimetexture);
}

enemy* createrandomenemy(int tilex, int tiley, float size, tile* tileset, int x, int type) {
	enemy* c = malloc(sizeof(enemy));
	if (c) {
		if (type == 0) {
			c->m = createmapobject(&hellslimetexture, tilex, tiley, size, tileset, x, 0, 0, 16, 16);
			c->maxhealth = rand() % 50 + 20.0f;
			c->health = c->maxhealth;
			c->maxactionpoint = 4;
			c->actionpoint = c->maxactionpoint;
			c->lifesteal = rand() % 5 + 1.0f;
			c->liferegen = rand() % 5 + 1.0f;
			c->damageincperc = rand() % 5 + 1.0f;
			c->protectperc = rand() % 5 + 1.0f;
			c->dodgeperc = rand() % 20 + 5.0f;
			c->critichitchance = rand() % 5 + 1.0f;
			c->range = 1;
			c->damage = 10;
			c->attackap = 2;
			strcpy(c->name, "Hell Slime");
			tileset[(tilex * x) + tiley].obstacle = 1;
		}
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

void playenemy(void* mainc, void* tileset, enemy* c) {
	if (c->actionpoint == 0) {
		return;
	}
	character* m = mainc;
	tile* t = tileset;
	int* distance = 0;
	int optimized = 0;
	int optimizedi = 0;
	if (max(abs((int)m->m->tileposition.x - (int)c->m->tileposition.x), abs((int)m->m->tileposition.y - (int)c->m->tileposition.y)) <= c->range) {
		if (c->actionpoint >= c->attackap) {
			setattackanimation(c->m, m->m, t);
			enemygivedamage(c, c->damage, mainc);
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
	}
	else {
		optimized = 1453;
		distance = calculatedistance((int)c->m->tileposition.x, (int)c->m->tileposition.y, tileset);
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
		addanimationmapobject(c->m, setmoveanimationpoints(optimizedi / 7, optimizedi % 7, tileset, mainc, 1), distance[optimizedi]);
		c->actionpoint -= distance[optimizedi];
		moveenemy(c, optimizedi / 7, optimizedi % 7, tileset, 7);
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
	for (int i = 0; i < enemynumber; i++) {
		enemynextturn(allenemies[i]);
		deneme = 0;
	a:
		BeginTextureMode(target);
		ClearBackground(BLACK);
		rendertileset(tileset, 7);
		renderallmapobjects();
		rendercharacterinfo(mainc, font);
		EndTextureMode();
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
		animation--;
		if (!isthereanimation() && animation <= 0) {
			playenemy(mainc, tileset, allenemies[i]);
		}
		else {
			if (animation <= 0) {
				animation = 30;
			}
			goto a;
		}
		if (allenemies[i]->actionpoint > 0 && deneme < 10) {
			deneme++;
			goto a;
		}
	}
	while (isthereanimation()) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		rendertileset(tileset, 7);
		renderallmapobjects();
		rendercharacterinfo(mainc, font);
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
		EndTextureMode();
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	UnloadRenderTexture(target);
	characternextturn(mainc);
}

enemy** getallenemies(void) {
	return allenemies;
}

int getenemynumber(void) {
	return enemynumber;
}

void enemytakedamage(enemy* c, float x) {
	if (!ishappened(c->dodgeperc)) {
		x = x * ((100 - c->protectperc) / 100);
		c->health -= x;
	}
}

void enemygivedamage(enemy* c, float x, void* e) {
	x *= ((100 + c->damageincperc) / 100);
	if (ishappened(c->critichitchance)) {
		x *= 2;
	}
	charactertakedamage(e, x);
	enemyheal(c, x * (c->lifesteal / 100));
}

void enemyheal(enemy* c, float x) {
	c->health += x;
	if (c->health > c->maxhealth) {
		c->health = c->maxhealth;
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