#pragma once
#include "tile.h"
#include "map_object.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "skillbutton.h"
#include "enemy.h"
#include "village.h"

Vector2 a, b, c, d, e;

Rectangle tile_source = { 0,0,64,64 };

Texture2D grasstile;
Texture2D seatile;
Texture2D tree;

unsigned char tile_status(tile* t) {
	a.x = t->absposition.x;
	a.y = t->absposition.y + (t->absposition.height / 4);
	b.x = t->absposition.x + (t->absposition.width / 2);
	b.y = t->absposition.y;
	c.x = t->absposition.x + t->absposition.width;
	c.y = t->absposition.y + (t->absposition.height / 4);
	d.x = t->absposition.x + (t->absposition.width / 2);
	d.y = t->absposition.y + (t->absposition.height / 2);
	e.x = GetMousePosition().x * (1920.0f / GetRenderWidth());
	e.y = GetMousePosition().y * (1080.0f / GetRenderHeight());
	if (CheckCollisionPointTriangle(e, a, b, c) ||
		CheckCollisionPointTriangle(e, a, d, c) ||
		CheckCollisionPointTriangle(e, a, d, b) ||
		CheckCollisionPointTriangle(e, c, d, b)) {
		if (t->position.y == t->absposition.y && !isthereanimation()) {
			t->position.y -= (t->absposition.width / 8);
		}
		if (isthereanimation()) {
			t->position.y = t->absposition.y;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			return 3;
		}
		return 2;
	}
	t->position.y = t->absposition.y;
	return 1;
}

void tile_render(tile* t) {
	a.x = 0;
	a.y = 0;
	DrawTexturePro(*(t->texture), tile_source, t->position, a, 0, WHITE);
}

tile* createtileset(int x, int size, float startx, float starty, char middle, int tilexchar, int tileychar, long long unsigned int level) {
	tile* t = malloc(sizeof(tile) * x * x);
	if (middle == 1) {
		startx = ((1920 - (size * x)) / 2.0f) + (((x - 1) / 2.0f) * size);
		starty = (1080 - ((size / 2.0f) * (x - 1)) - size) / 2.0f;
	}
	int seatilen = 0;
	int enemyn = 0;
	int villagen = 0;
	int maxvillagen = 1;
	if (x != 7) {
		maxvillagen = 2;
	}
	int* rows = malloc(sizeof(int) * x);
	int* columns = malloc(sizeof(int) * x);
	for (int i = 0; i < x; i++) {
		rows[i] = 0;
		columns[i] = 0;
	}
	for (int i = 0; i < x; i++) {
		for (int i2 = 0; i2 < x; i2++) {
			t[(i * x) + i2].obstacle = 0;
			t[(i * x) + i2].position.x = startx + (i2 * (size / 2.0f)) - (i * (size / 2.0f));
			t[(i * x) + i2].position.y = starty + (i2 * (size / 4.0f)) + (i * (size / 4.0f));
			t[(i * x) + i2].position.width = (float)size;
			t[(i * x) + i2].position.height = (float)size;
			t[(i * x) + i2].absposition.x = t[(i * x) + i2].position.x;
			t[(i * x) + i2].absposition.y = t[(i * x) + i2].position.y;
			t[(i * x) + i2].absposition.width = t[(i * x) + i2].position.width;
			t[(i * x) + i2].absposition.height = t[(i * x) + i2].position.height;
			if (rand() % 2 == 0 && max(abs(tilexchar - i), abs(tileychar - i2)) > 1 &&
				seatilen < (x * x) / 3.0f && rows[i] < 3 && columns[i2] < 4) {
				if (rand() % 3 == 1 && !(i == 0 && i2 == 6) && !(i == 6 && i2 == 0)) {
					t[(i * x) + i2].texture = &grasstile;
					t[(i * x) + i2].type = 1;
					if (rand() % 2 == 0) {
						createmapobject(&tree, i, i2, 48, t, x, 0, 0, 16, 16);
					}
					else {
						createmapobject(&tree, i, i2, 48, t, x, 0, 0, -16, 16);
					}
					t[(i * x) + i2].obstacle = 1;
				}
				else {
					t[(i * x) + i2].texture = &seatile;
					t[(i * x) + i2].type = 2;
				}
				seatilen++;
				rows[i]++;
				columns[i2]++;
			}
			else {
				t[(i * x) + i2].texture = &grasstile;
				t[(i * x) + i2].type = 1;
				if (x != 7 && max(abs(tilexchar - i), abs(tileychar - i2)) > 0 && rand() % 3 == 1 && enemyn < 3) {
					createrandomenemy(i, i2, 48, t, x, rand() % MAX_ENEMY_TYPES, level);
					enemyn++;
				}
				else if (x != 7 && rand() % 3 == 1 && villagen < maxvillagen && max(abs(tilexchar - i), abs(tileychar - i2)) > 0) {
					createvillage(i, i2, 48, t, x, min(100 + rand() % 5 + level, 150 + rand() % 5));
					villagen++;
				}
			}
		}
	}
	free(rows);
	free(columns);
	if (x == 7) {
		int loop = 0;
		while (enemyn < (level / 5 + 2) && loop < 100) {
			seatilen = rand() % 3 + 4;
			x = rand() % 7;
			if (t[x * 7 + seatilen].obstacle == 0 && t[x * 7 + seatilen].type != 2 && !(x == 0 && seatilen == 6)) {
				if (MAX_ENEMY_TYPES > level) {
					if (level == 0) {
						createrandomenemy(x, seatilen, 48, t, 7, 0, level);
					}
					else if (level == 1) {
						createrandomenemy(x, seatilen, 48, t, 7, rand() % 2, level);
					}
					else {
						createrandomenemy(x, seatilen, 48, t, 7, rand() % level, level);
					}
				}
				else {
					createrandomenemy(x, seatilen, 48, t, 7, rand() % MAX_ENEMY_TYPES, level);
				}
				enemyn++;
			}
			loop++;
		}
		loop = 0;
		while (villagen < maxvillagen && loop < 100) {
			seatilen = rand() % 3 + 2;
			x = rand() % 3 + 2;
			if (t[x * 7 + seatilen].obstacle == 0 && t[x * 7 + seatilen].type != 2 && !(x == 6 && seatilen == 0)) {
				createvillage(x, seatilen, 48, t, 7, min(100 + rand() % 5 + level, 150 + rand() % 5));
				villagen++;
			}
			loop++;
		}
	}
	return t;
}

void rendertileset(tile* t, int x) {
	for (int i = 0; i < x * x; i++) {
		tile_render(&(t[i]));
		tile_status(&(t[i]));
	}
}

void destroytileset(tile* t) {
	free(t);
}

void loadtiletextures(void) {
	grasstile = LoadTexture("data/map_assets/grass_tile.png");
	seatile = LoadTexture("data/map_assets/sea_tile.png");
	tree = LoadTexture("data/map_assets/tree.png");
}

void deletetiletextures(void) {
	UnloadTexture(grasstile);
	UnloadTexture(seatile);
	UnloadTexture(tree);
}

void tilesetintro(tile* t, int speed, int x, float ratio) {
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	for (int i = 0; i < x * x; i++) {
		t[i].position.y += 1080;
	}
	while (t[(x * x) - 1].position.y != t[(x * x) - 1].absposition.y) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		for (int i = 0; i < x * x; i++) {
			if (t[i].position.y > t[i].absposition.y) {
				if ((i == 0) || (t[i - 1].position.y <= t[i - 1].absposition.y + (1080 * ratio))) {
					t[i].position.y -= speed;
				}
			}
			else {
				t[i].position.y = t[i].absposition.y;
			}
			tile_render(&(t[i]));
		}
		renderallmapobjects();
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	UnloadRenderTexture(target);
}

void tilesetoutro(tile* t, int speed, int x, float ratio) {
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	for (int i = 0; i < x * x; i++) {
		t[i].position = t[i].absposition;
	}
	while (t[0].position.y <= t[0].absposition.y + 1080) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		for (int i = (x * x) - 1; i >= 0; i--) {
			if ((i == (x * x) - 1) || (t[i + 1].position.y >= t[i + 1].absposition.y + (1080 * ratio))) {
				t[i].position.y += speed;
			}
		}
		for (int i = 0; i < x * x; i++) {
			tile_render(&(t[i]));
		}
		renderallmapobjects();
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	UnloadRenderTexture(target);
}