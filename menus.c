#include "menus.h"
#include <raylib.h>
#include "tile.h"
#include "character.h"
#include <raylib.h> 
#include <stdlib.h>
#include <time.h>
#include "button.h"

button playbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1400,600,500,75},
	.text = "PLAY",
	.textcolor = {255,255,255,255}
};

button settingsbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1400,750,500,75},
	.text = "SETTINGS",
	.textcolor = {255,255,255,255}
};

button quitbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1400,900,500,75},
	.text = "QUIT",
	.textcolor = {255,255,255,255}
};

button backbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1680,20,220,75},
	.text = "BACK",
	.textcolor = {255,255,255,255}
};

void intromenu(void) {
	Font myfont = LoadFontEx("data/fonts/font2.ttf", 150, 0, 350);
	Vector2 a = MeasureTextEx(myfont, u8"A Þükrü Çiriþ Game", 150, 0);
	Color textc = { 255,255,255,0 };
	a.x = (1920 - a.x) / 2;
	a.y = 700;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() };
	Vector2 origin = { 0,0 };
	Texture2D logo = LoadTexture("data/characters/logo.png");
	Rectangle logorect = { 810,200,300,300 };
	Rectangle logosrc = { 0,0,11,11 };
	for (int i = 0; i < 434; i++) {
		if (i < 127) {
			textc.a += 2;
		}
		else if (i > 307) {
			textc.a -= 2;
		}
		BeginTextureMode(target);
		ClearBackground(BLACK);
		DrawTextEx(myfont, u8"A Þükrü Çiriþ Game", a, 150, 0, textc);
		DrawTexturePro(logo, logosrc, logorect, origin, 0, textc);
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	UnloadRenderTexture(target);
	UnloadFont(myfont);
}

char mainmenuinput(Font* f, Vector2* a) {
	DrawTextEx(*f, "Codename Demon Project", *a, 50, 0, WHITE);
	if (WindowShouldClose() || renderbutton(&quitbutton, f)) {
		return 0;
	}
	else if (renderbutton(&playbutton, f)) {
		return 1;
	}
	else if (renderbutton(&settingsbutton, f)) {
		return 2;
	}
	return 111;
}

char tilesetintromainmenu(tile* t, int speed, int x, float ratio, Font* f, Vector2* a) {
	for (int i = 0; i < x * x; i++) {
		t[i].position.y = t[i].absposition.y + GetScreenHeight();
	}
	char y = 111;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() };
	Vector2 origin = { 0,0 };
	while (t[(x * x) - 1].position.y != t[(x * x) - 1].absposition.y) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		y = mainmenuinput(f, a);
		if (y != 111) {
			UnloadRenderTexture(target);
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
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	for (int i = 0; i < 30; i++) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		y = mainmenuinput(f, a);
		if (y != 111) {
			UnloadRenderTexture(target);
			return y;
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
	return 111;
}

char tilesetoutromainmenu(tile* t, int speed, int x, float ratio, Font* f, Vector2* a) {
	char y = 111;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() };
	Vector2 origin = { 0,0 };
	while (t[0].position.y <= t[0].absposition.y + GetScreenHeight()) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		y = mainmenuinput(f, a);
		if (y != 111) {
			UnloadRenderTexture(target);
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
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	UnloadRenderTexture(target);
	return 111;
}

char mainmenu(void) {
	loadtiletextures();
	Font myfont = LoadFontEx("data/fonts/font1.ttf", 50, 0, 0);
	tile* tileset = createtileset(4, 192, 0, 0, 1, 1, 1);
	character* mainc = createcharacter(1, 1, 48, tileset, 4);
	char x = 111;
	int tilex = 4;
	int tilexchar = 1;
	int tileychar = 1;
	Vector2 a = MeasureTextEx(myfont, "Codename Demon Project", 50, 0);
	a.x = (1920 - a.x) / 2;
	a.y = 100;
	while (!WindowShouldClose() && x == 111) {
		srand((unsigned int)time(0));
		x = tilesetintromainmenu(tileset, 25, tilex, 0.85f, &myfont, &a);
		if (WindowShouldClose() || x != 111) {
			break;
		}
		x = tilesetoutromainmenu(tileset, 25, tilex, 0.15f, &myfont, &a);
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
	UnloadFont(myfont);
	return x;
}

void settingsmenu(void) {
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() };
	Vector2 origin = { 0,0 };
	Font myfont = LoadFontEx("data/fonts/font1.ttf", 50, 0, 0);
	Vector2 fullscreentextpos = { 100,100 };
	Rectangle fullscreenbox = { 550,85,80,80 };
	Rectangle fullscreentick = { 570,105,40,40 };
	Vector2 e;
	while (!WindowShouldClose()) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		DrawTextEx(myfont, "Fullscreen:", fullscreentextpos, 50, 0, WHITE);
		DrawRectangleLinesEx(fullscreenbox, 10, WHITE);
		if (IsWindowFullscreen()) {
			DrawRectangleRec(fullscreentick, WHITE);
		}
		if (renderbutton(&backbutton, &myfont)) {
			break;
		}
		e.x = GetMousePosition().x * (1920.0f / GetScreenWidth());
		e.y = GetMousePosition().y * (1080.0f / GetScreenHeight());
		if (CheckCollisionPointRec(e, fullscreenbox)) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				ToggleFullscreen();
			}
		}
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	UnloadFont(myfont);
	UnloadRenderTexture(target);
}