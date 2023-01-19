#pragma once
#include "tile.h"
#include "map_object.h"
#include <stdlib.h>

Vector2 a, b, c, d;

Rectangle tile_source = { 0,0,64,64 };

Texture2D grasstile;

unsigned char tile_status(tile* t) {
	a.x = t->absposition.x;
	a.y = t->absposition.y + (t->absposition.height / 4);
	b.x = t->absposition.x + (t->absposition.width / 2);
	b.y = t->absposition.y;
	c.x = t->absposition.x + t->absposition.width;
	c.y = t->absposition.y + (t->absposition.height / 4);
	d.x = t->absposition.x + (t->absposition.width / 2);
	d.y = t->absposition.y + (t->absposition.height / 2);
	if (CheckCollisionPointTriangle(GetMousePosition(), a, b, c) ||
		CheckCollisionPointTriangle(GetMousePosition(), a, d, c) ||
		CheckCollisionPointTriangle(GetMousePosition(), a, d, b) ||
		CheckCollisionPointTriangle(GetMousePosition(), c, d, b)) {
		if (t->position.y == t->absposition.y) {
			t->position.y -= (t->absposition.width / 8);
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
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

tile* createtileset(int x, int size, float startx, float starty, char middle) {
	tile* t = malloc(sizeof(tile) * x * x);
	if (middle == 1) {
		startx = ((GetRenderWidth() - (size * x)) / 2.0f) + (((x - 1) / 2.0f) * size);
		starty = (GetRenderHeight() - ((size / 2.0f) * (x - 1)) - size) / 2.0f;
	}
	for (int i = 0; i < x; i++) {
		for (int i2 = 0; i2 < x; i2++) {
			t[(i * x) + i2].obstacle = 0;
			t[(i * x) + i2].texture = &grasstile;
			t[(i * x) + i2].position.x = startx + (i2 * (size / 2.0f)) - (i * (size / 2.0f));
			t[(i * x) + i2].position.y = starty + (i2 * (size / 4.0f)) + (i * (size / 4.0f));
			t[(i * x) + i2].position.width = (float)size;
			t[(i * x) + i2].position.height = (float)size;
			t[(i * x) + i2].absposition.x = t[(i * x) + i2].position.x;
			t[(i * x) + i2].absposition.y = t[(i * x) + i2].position.y;
			t[(i * x) + i2].absposition.width = t[(i * x) + i2].position.width;
			t[(i * x) + i2].absposition.height = t[(i * x) + i2].position.height;
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
}

void deletetiletextures(void) {
	UnloadTexture(grasstile);
}

void tilesetintro(tile* t, int speed, int x) {
	for (int i = 0; i < x * x; i++) {
		t[i].position.y += GetScreenHeight();
	}
	while (t[(x * x) - 1].position.y != t[(x * x) - 1].absposition.y) {
		BeginDrawing();
		ClearBackground(BLACK);
		for (int i = 0; i < x * x; i++) {
			if (t[i].position.y > t[i].absposition.y) {
				if ((i == 0) || (t[i - 1].position.y <= t[i - 1].absposition.y + (GetScreenHeight() * (3 / 4.0f)))) {
					t[i].position.y -= speed;
				}
			}
			else {
				t[i].position.y = t[i].absposition.y;
			}
			tile_render(&(t[i]));
		}
		renderallmapobjects();
		EndDrawing();
	}
}

void tilesetoutro(tile* t, int speed, int x) {
	while (t[0].position.y <= t[0].absposition.y + GetScreenHeight()) {
		BeginDrawing();
		ClearBackground(BLACK);
		for (int i = (x * x) - 1; i >= 0; i--) {
			if ((i == (x * x) - 1) || (t[i + 1].position.y >= t[i + 1].absposition.y + (GetScreenHeight() * (1 / 4.0f)))) {
				t[i].position.y += speed;
			}
		}
		for (int i = 0; i < x * x; i++) {
			tile_render(&(t[i]));
		}
		renderallmapobjects();
		EndDrawing();
	}
}