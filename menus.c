#include "menus.h"
#include <raylib.h>
#include "tile.h"
#include "character.h"
#include <raylib.h> 
#include <stdlib.h>
#include <time.h>

void intromenu(void) {
	Font myfont = LoadFontEx("data/fonts/font2.ttf", 200, 0, 350);
	Vector2 a = MeasureTextEx(myfont, u8"A Þükrü Çiriþ Game", 200, 0);
	Color textc = { 255,255,255,0 };
	a.x = (GetScreenWidth() - a.x) / 2;
	a.y = (GetScreenHeight() - a.y) / 2;
	for (int i = 0; i < 254; i++) {
		if (i < 127) {
			textc.a += 2;
		}
		else {
			textc.a -= 2;
		}
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextEx(myfont, u8"A Þükrü Çiriþ Game", a, 200, 0, textc);
		EndDrawing();
	}
	UnloadFont(myfont);
}

char mainmenuinput(void) {
	if (WindowShouldClose()) {
		return 0;
	}
	return 111;
}

char tilesetintromainmenu(tile* t, int speed, int x, float ratio) {
	for (int i = 0; i < x * x; i++) {
		t[i].position.y = t[i].absposition.y + GetScreenHeight();
	}
	char y = 111;
	while (t[(x * x) - 1].position.y != t[(x * x) - 1].absposition.y) {
		BeginDrawing();
		ClearBackground(BLACK);
		y = mainmenuinput();
		if (y != 111) {
			return y;
		}
		for (int i = 0; i < x * x; i++) {
			if (t[i].position.y > t[i].absposition.y) {
				if ((i == 0) || (t[i - 1].position.y <= t[i - 1].absposition.y + (GetScreenHeight() * ratio))) {
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
	return 111;
}

char tilesetoutromainmenu(tile* t, int speed, int x, float ratio) {
	char y = 111;
	while (t[0].position.y <= t[0].absposition.y + GetScreenHeight()) {
		BeginDrawing();
		ClearBackground(BLACK);
		y = mainmenuinput();
		if (y != 111) {
			return y;
		}
		for (int i = (x * x) - 1; i >= 0; i--) {
			if ((i == (x * x) - 1) || (t[i + 1].position.y >= t[i + 1].absposition.y + (GetScreenHeight() * ratio))) {
				t[i].position.y += speed;
			}
		}
		for (int i = 0; i < x * x; i++) {
			tile_render(&(t[i]));
		}
		renderallmapobjects();
		EndDrawing();
	}
	return 111;
}

char mainmenu(void) {
	loadtiletextures();
	tile* tileset = createtileset(4, 192, 0, 0, 1, 1, 1);
	character* mainc = createcharacter(1, 1, 48, tileset, 4);
	char x = 111;
	int tilex = 4;
	int tilexchar = 1;
	int tileychar = 1;
	while (!WindowShouldClose() && x == 111) {
		srand((unsigned int)time(0));
		x = tilesetintromainmenu(tileset, 25, tilex, 0.85f);
		WaitTime(1);
		if (WindowShouldClose() || x != 111) {
			break;
		}
		x = tilesetoutromainmenu(tileset, 25, tilex, 0.15f);
		WaitTime(0.5f);
		destroytileset(tileset);
		destroycharacter(mainc);
		tilex = rand() % 3 + 2;
		tilexchar = rand() % tilex;
		tileychar = rand() % tilex;
		tileset = createtileset(tilex, 192, 0, 0, 1, tilexchar, tileychar);
		mainc = createcharacter(tilexchar, tileychar, 48, tileset, tilex);
	}
	destroytileset(tileset);
	destroycharacter(mainc);
	deletetiletextures();
	return x;
}