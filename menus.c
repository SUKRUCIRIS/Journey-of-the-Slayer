#include "menus.h"
#include <raylib.h>
#include "tile.h"
#include "character.h"
#include <raylib.h> 
#include <stdlib.h>
#include <time.h>
#include "button.h"
#include <stdio.h>

char reselect = 0;

button playbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1500,750,400,75},
	.text = "PLAY",
	.textcolor = {255,255,255,255}
};

button settingsbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1500,850,400,75},
	.text = "SETTINGS",
	.textcolor = {255,255,255,255}
};

button quitbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1500,950,400,75},
	.text = "QUIT",
	.textcolor = {255,255,255,255}
};

void intromenu(void) {
	Font myfont = LoadFontEx("data/fonts/font2.ttf", 150, 0, 350);
	Vector2 a = MeasureTextEx(myfont, u8"A ��kr� �iri� Game", 150, 0);
	Color textc = { 255,255,255,0 };
	a.x = (1920 - a.x) / 2;
	a.y = 700;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
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
		DrawTextEx(myfont, u8"A ��kr� �iri� Game", a, 150, 0, textc);
		DrawTexturePro(logo, logosrc, logorect, origin, 0, textc);
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	UnloadRenderTexture(target);
	UnloadFont(myfont);
	UnloadTexture(logo);
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
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
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
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
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
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	Font myfont = LoadFontEx("data/fonts/font1.ttf", 50, 0, 0);
	Vector2 fullscreentextpos = { 100,100 };
	Rectangle fullscreenbox = { 550,85,80,80 };
	Rectangle fullscreentick = { 570,105,40,40 };
	Vector2 e = { 0,0 };
	button backbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1680,20,220,75},
	.text = "BACK",
	.textcolor = {255,255,255,255}
	};
	Vector2 resolutiontextpos = { 100,200 };
	char restext[20] = { 0 };
	sprintf(restext, "Default: %dx%d", GetScreenWidth(), GetScreenHeight());
	Rectangle restick = { 80,0,840,115 };
	button defaultres = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,300,800,75},
		.text = restext,
		.textcolor = {0,0,0,255}
	};
	button _1280x720res = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,400,800,75},
		.text = "1280x720",
		.textcolor = {0,0,0,255}
	};
	button _1366x768res = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,500,800,75},
		.text = "1366x768",
		.textcolor = {0,0,0,255}
	};
	button _1920x1080res = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,600,800,75},
		.text = "1920x1080",
		.textcolor = {0,0,0,255}
	};
	button _2560x1440res = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,700,800,75},
		.text = "2560x1440",
		.textcolor = {0,0,0,255}
	};
	button _3840x2160res = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,800,800,75},
		.text = "3840x2160",
		.textcolor = {0,0,0,255}
	};
	while (!WindowShouldClose()) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		DrawTextEx(myfont, "Fullscreen:", fullscreentextpos, 50, 0, WHITE);
		DrawTextEx(myfont, "Resolution:", resolutiontextpos, 50, 0, WHITE);
		e.x = GetMousePosition().x * (1920.0f / GetRenderWidth());
		e.y = GetMousePosition().y * (1080.0f / GetRenderHeight());
		if (CheckCollisionPointRec(e, fullscreenbox)) {
			DrawRectangleLinesEx(fullscreenbox, 10, _3840x2160res.frontcolor);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				ToggleFullscreen();
			}
		}
		else {
			DrawRectangleLinesEx(fullscreenbox, 10, WHITE);
		}
		if (IsWindowFullscreen()) {
			DrawRectangleRec(fullscreentick, WHITE);
		}
		if (renderbutton(&backbutton, &myfont)) {
			break;
		}
		if (renderbutton(&defaultres, &myfont)) {
			SetWindowSize(GetScreenWidth(), GetScreenHeight());
			reselect = 0;
		}
		if (renderbutton(&_1280x720res, &myfont)) {
			SetWindowSize(1280, 720);
			reselect = 1;
		}
		if (renderbutton(&_1366x768res, &myfont)) {
			SetWindowSize(1366, 768);
			reselect = 2;
		}
		if (renderbutton(&_1920x1080res, &myfont)) {
			SetWindowSize(1920, 1080);
			reselect = 3;
		}
		if (renderbutton(&_2560x1440res, &myfont)) {
			SetWindowSize(2560, 1440);
			reselect = 4;
		}
		if (renderbutton(&_3840x2160res, &myfont)) {
			SetWindowSize(3840, 2160);
			reselect = 5;
		}
		restick.y = 280 + (reselect * 100.0f);
		DrawRectangleLinesEx(restick, 10, WHITE);
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		targetdest.width = (float)GetRenderWidth();
		targetdest.height = (float)GetRenderHeight();
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	UnloadFont(myfont);
	UnloadRenderTexture(target);
}