#include "menus.h"
#include <raylib.h>
#include "tile.h"
#include "character.h"
#include <raylib.h> 
#include <stdlib.h>
#include <time.h>
#include "button.h"
#include <stdio.h>
#include "enemy.h"
#include "village.h"
#include "game.h"

char reselect = 0;
char fullscreen = 0;
float musicvolume = 0.25f;
float effectvolume = 1;

Music main_music;

int defaultwidth;
int defaultheight;

long long unsigned int maxlevel = 0;
char maxleveltext[100] = { 0 };
Vector2 maxlevelpos = { 50,300 };
Vector2 maxlevelorigin = { 0,0 };
float maxlevelfontsize = 30;
float fontsizechange = 1;

button playbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1500,650,400,75},
	.text = "NEW JOURNEY",
	.textcolor = {255,255,255,255}
};

button settingsbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1500,750,400,75},
	.text = "SETTINGS",
	.textcolor = {255,255,255,255}
};

button creditbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1500,850,400,75},
	.text = "CREDITS",
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
	Music intro_sound = LoadMusicStream("data/sound/intro_sound.mp3");
	SetMusicVolume(intro_sound, 0);
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
	PlayMusicStream(intro_sound);
	int intodur = 480;
	float musicvolumeintro = 0;
	for (int i = 0; i < intodur; i++) {
		SetMusicVolume(intro_sound, musicvolumeintro);
		UpdateMusicStream(intro_sound);
		if (i < 127) {
			textc.a += 2;
			musicvolumeintro += 0.002;
		}
		else if (i > intodur - 127) {
			textc.a -= 2;
			musicvolumeintro -= 0.002;
			if (musicvolumeintro < 0) {
				musicvolumeintro = 0;
			}
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
	UnloadMusicStream(intro_sound);
	UnloadRenderTexture(target);
	UnloadFont(myfont);
	UnloadTexture(logo);
	for (int i = 0; i < 30; i++) {
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}
}

char mainmenuinput(Font* f, Vector2* a) {
	sprintf(maxleveltext, "Your farthest journey: %lld level", maxlevel);
	if (maxlevelfontsize > 31) {
		fontsizechange = -0.02f;
	}
	if (maxlevelfontsize < 30) {
		fontsizechange = 0.02f;
	}
	maxlevelfontsize += fontsizechange;
	DrawTextPro(*f, maxleveltext, maxlevelpos, maxlevelorigin, -30, maxlevelfontsize, 0, WHITE);
	DrawTextEx(*f, "Journey of the Slayer", *a, 70, 0, WHITE);
	if (WindowShouldClose() || renderbutton(&quitbutton, f)) {
		return 0;
	}
	else if (renderbutton(&playbutton, f)) {
		return 1;
	}
	else if (renderbutton(&settingsbutton, f)) {
		return 2;
	}
	else if (renderbutton(&creditbutton, f)) {
		return 3;
	}
	return 111;
}

char tilesetintromainmenu(tile* t, int speed, int x, float ratio, Font* f, Vector2* a) {
	for (int i = 0; i < x * x; i++) {
		t[i].position.y = t[i].absposition.y + 1080;
	}
	char y = 111;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	while (t[(x * x) - 1].position.y != t[(x * x) - 1].absposition.y) {
		UpdateMusicStream(main_music);
		BeginTextureMode(target);
		ClearBackground(BLACK);
		y = mainmenuinput(f, a);
		if (y != 111) {
			UnloadRenderTexture(target);
			return y;
		}
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
	for (int i = 0; i < 30; i++) {
		UpdateMusicStream(main_music);
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
	while (t[0].position.y <= t[0].absposition.y + 1080) {
		UpdateMusicStream(main_music);
		BeginTextureMode(target);
		ClearBackground(BLACK);
		y = mainmenuinput(f, a);
		if (y != 111) {
			UnloadRenderTexture(target);
			return y;
		}
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
	return 111;
}

void writesavefile(long long unsigned int level) {
	FILE* f = 0;
	f = fopen("data/savefile/slayer.save", "wb");
	fprintf(f, "%llu", level);
	fclose(f);
}

long long unsigned int readsavefile(void) {
	FILE* f = 0;
	f = fopen("data/savefile/slayer.save", "rb");
	long long unsigned int x = 0;
	if (f) {
		fscanf(f, "%llu", &x);
		fclose(f);
	}
	else {
		writesavefile(0);
	}
	return x;
}

void writesettingsavefile(void) {
	FILE* f = fopen("data/savefile/settings.save", "wb");
	fprintf(f, "%c\n%c\n%f\n%f", reselect, fullscreen, musicvolume, effectvolume);
	fclose(f);
}

void readsettingsavefile(void) {
	FILE* f = 0;
	f = fopen("data/savefile/settings.save", "rb");
	if (f) {
		fscanf(f, "%c\n%c\n%f\n%f", &reselect, &fullscreen, &musicvolume, &effectvolume);
		fclose(f);
		switch (reselect)
		{
		case 0:
			SetWindowSize(defaultwidth, defaultheight);
			break;
		case 1:
			SetWindowSize(1280, 720);
			break;
		case 2:
			SetWindowSize(1366, 768);
			break;
		case 3:
			SetWindowSize(1600, 900);
			break;
		case 4:
			SetWindowSize(1920, 1080);
			break;
		case 5:
			SetWindowSize(2560, 1440);
			break;
		case 6:
			SetWindowSize(3840, 2160);
			break;
		default:
			break;
		}
		if (IsWindowFullscreen() != fullscreen) {
			ToggleFullscreen();
		}
		SetMusicVolume(main_music, musicvolume);
		SetMusicVolume(*getwarmusic(), musicvolume);
		SetSoundVolume(*getwalksound(), effectvolume);
		SetSoundVolume(*getdeathsound(), effectvolume);
		SetSoundVolume(*getattacksound(), effectvolume);
	}
	else {
		writesettingsavefile();
	}
}

char mainmenu(long long unsigned int level) {
	if (level > maxlevel) {
		maxlevel = level;
	}
	if (readsavefile() > maxlevel) {
		maxlevel = readsavefile();
	}
	else {
		writesavefile(maxlevel);
	}
	loadtiletextures();
	loadenemytextures();
	loadcharactertextures();
	loadvillagetextures();
	Font myfont = LoadFontEx("data/fonts/font1.ttf", 70, 0, 0);
	tile* tileset = createtileset(4, 192, 0, 0, 1, 1, 1, 5);
	character* mainc = createcharacter(1, 1, 48, tileset, 4);
	char x = 111;
	int tilex = 4;
	int tilexchar = 1;
	int tileychar = 1;
	Vector2 a = MeasureTextEx(myfont, "Journey of the Slayer", 70, 0);
	a.x = (1920 - a.x) / 2;
	a.y = 100;
	while (!WindowShouldClose() && x == 111) {
		x = tilesetintromainmenu(tileset, 25, tilex, 0.85f, &myfont, &a);
		if (WindowShouldClose() || x != 111) {
			break;
		}
		x = tilesetoutromainmenu(tileset, 25, tilex, 0.15f, &myfont, &a);
		destroytileset(tileset);
		destroycharacter(mainc);
		destroyallenemies();
		destroyallvillages();
		destroyallmapobjects();
		tilex = rand() % 3 + 2;
		tilexchar = rand() % tilex;
		tileychar = rand() % tilex;
		tileset = createtileset(tilex, 192, 0, 0, 1, tilexchar, tileychar, 5);
		mainc = createcharacter(tilexchar, tileychar, 48, tileset, tilex);
	}
	if (x == 1) {
		Image ss = LoadImageFromScreen();
		Texture2D sst = LoadTextureFromImage(ss);
		Rectangle ssource = { 0,0,ss.width,ss.height };
		UnloadImage(ss);
		RenderTexture2D target = LoadRenderTexture(1920, 1080);
		Rectangle targetsource = { 0,0,1920,-1080 };
		Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
		Vector2 origin = { 0,0 };
		Rectangle screen = { 0,0,1920,1080 };
		float volume = musicvolume;
		for (int i = 0; i < 120; i++) {
			musicvolume -= (volume / 120);
			SetMusicVolume(main_music, musicvolume);
			UpdateMusicStream(main_music);
			BeginTextureMode(target);
			ClearBackground(BLACK);
			DrawTexturePro(sst, ssource, screen, origin, 0, WHITE);
			EndTextureMode();

			BeginDrawing();
			ClearBackground(BLACK);
			DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
			EndDrawing();
			screen.y += 15;
		}
		musicvolume = volume;
		UnloadTexture(sst);
		UnloadRenderTexture(target);
	}
	destroytileset(tileset);
	destroycharacter(mainc);
	deletetiletextures();
	UnloadFont(myfont);
	unloadenemytextures();
	destroyallenemies();
	destroyallvillages();
	unloadcharactertextures();
	destroyallmapobjects();
	unloadvillagetextures();
	return x;
}

void settingsmenu(void) {
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	Font myfont = LoadFontEx("data/fonts/font1.ttf", 70, 0, 0);
	Vector2 fullscreentextpos = { 100,100 };
	Rectangle fullscreenbox = { 410,105,80,80 };
	Rectangle fullscreentick = { 430,125,40,40 };
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
	sprintf(restext, "Default: %dx%d", defaultwidth, defaultheight);
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
	button _1600x900res = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,600,800,75},
		.text = "1600x900",
		.textcolor = {0,0,0,255}
	};
	button _1920x1080res = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,700,800,75},
		.text = "1920x1080",
		.textcolor = {0,0,0,255}
	};
	button _2560x1440res = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,800,800,75},
		.text = "2560x1440",
		.textcolor = {0,0,0,255}
	};
	button _3840x2160res = {
		.backcolor = {255, 255, 255,255},
		.frontcolor = {96, 0, 148,255},
		.position = {100,900,800,75},
		.text = "3840x2160",
		.textcolor = {0,0,0,255}
	};
	Rectangle musicvolumerect = { 1000,300,800,75 };
	Rectangle musicvolumerectx = { 1010,310,780,55 };
	Rectangle effectvolumerect = { 1000,500,800,75 };
	Rectangle effectvolumerectx = { 1010,510,780,55 };
	while (!WindowShouldClose()) {
		UpdateMusicStream(main_music);
		BeginTextureMode(target);
		ClearBackground(BLACK);
		fullscreentextpos.x = 100;
		fullscreentextpos.y = 100;
		DrawTextEx(myfont, "Fullscreen:", fullscreentextpos, 70, 0, WHITE);
		DrawTextEx(myfont, "Resolution:", resolutiontextpos, 70, 0, WHITE);
		e.x = GetMousePosition().x * (1920.0f / GetRenderWidth());
		e.y = GetMousePosition().y * (1080.0f / GetRenderHeight());
		if (CheckCollisionPointRec(e, fullscreenbox)) {
			DrawRectangleLinesEx(fullscreenbox, 10, _3840x2160res.frontcolor);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				SetSoundVolume(*getclicksound(), geteffectvolume());
				PlaySound(*getclicksound());
				ToggleFullscreen();
				switch (reselect)
				{
				case 0:
					SetWindowSize(defaultwidth, defaultheight);
					break;
				case 1:
					SetWindowSize(1280, 720);
					break;
				case 2:
					SetWindowSize(1366, 768);
					break;
				case 3:
					SetWindowSize(1600, 900);
					break;
				case 4:
					SetWindowSize(1920, 1080);
					break;
				case 5:
					SetWindowSize(2560, 1440);
					break;
				case 6:
					SetWindowSize(3840, 2160);
					break;
				default:
					break;
				}
			}
		}
		else {
			DrawRectangleLinesEx(fullscreenbox, 10, WHITE);
		}
		if (IsWindowFullscreen()) {
			fullscreen = 1;
			DrawRectangleRec(fullscreentick, WHITE);
		}
		else {
			fullscreen = 0;
		}
		if (renderbutton(&backbutton, &myfont)) {
			break;
		}
		else if (renderbutton(&defaultres, &myfont)) {
			SetWindowSize(defaultwidth, defaultheight);
			reselect = 0;
		}
		else if (renderbutton(&_1280x720res, &myfont)) {
			SetWindowSize(1280, 720);
			reselect = 1;
		}
		else if (renderbutton(&_1366x768res, &myfont)) {
			SetWindowSize(1366, 768);
			reselect = 2;
		}
		else if (renderbutton(&_1600x900res, &myfont)) {
			SetWindowSize(1600, 900);
			reselect = 3;
		}
		else if (renderbutton(&_1920x1080res, &myfont)) {
			SetWindowSize(1920, 1080);
			reselect = 4;
		}
		else if (renderbutton(&_2560x1440res, &myfont)) {
			SetWindowSize(2560, 1440);
			reselect = 5;
		}
		else if (renderbutton(&_3840x2160res, &myfont)) {
			SetWindowSize(3840, 2160);
			reselect = 6;
		}
		else if (CheckCollisionPointRec(e, musicvolumerect) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			if (e.x - musicvolumerectx.x >= 780) {
				e.x = musicvolumerectx.x + 780;
			}
			else if (e.x - musicvolumerectx.x <= 0) {
				e.x = musicvolumerectx.x;
			}
			musicvolumerectx.width = e.x - musicvolumerectx.x;
			musicvolume = (e.x - musicvolumerectx.x) / 780;
			SetMusicVolume(main_music, musicvolume);
			SetMusicVolume(*getwarmusic(), musicvolume);
		}
		else if (CheckCollisionPointRec(e, effectvolumerect) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			if (e.x - musicvolumerectx.x >= 780) {
				e.x = musicvolumerectx.x + 780;
			}
			else if (e.x - musicvolumerectx.x <= 0) {
				e.x = musicvolumerectx.x;
			}
			effectvolumerectx.width = e.x - musicvolumerectx.x;
			effectvolume = (e.x - musicvolumerectx.x) / 780;
			SetSoundVolume(*getwalksound(), effectvolume);
			SetSoundVolume(*getdeathsound(), effectvolume);
			SetSoundVolume(*getattacksound(), effectvolume);
		}
		restick.y = 280 + (reselect * 100.0f);
		DrawRectangleLinesEx(restick, 10, WHITE);
		fullscreentextpos.x = 1000;
		fullscreentextpos.y = 200;
		DrawTextEx(myfont, "Music Volume:", fullscreentextpos, 70, 0, WHITE);
		fullscreentextpos.x = 1000;
		fullscreentextpos.y = 400;
		DrawTextEx(myfont, "SFX Volume:", fullscreentextpos, 70, 0, WHITE);
		DrawRectangleLinesEx(musicvolumerect, 10, WHITE);
		DrawRectangleLinesEx(effectvolumerect, 10, WHITE);
		effectvolumerectx.width = effectvolume * 780;
		musicvolumerectx.width = musicvolume * 780;
		DrawRectangleRec(musicvolumerectx, _3840x2160res.frontcolor);
		DrawRectangleRec(effectvolumerectx, _3840x2160res.frontcolor);
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
	writesettingsavefile();
}

void setdeafultwh(int width, int height) {
	defaultwidth = width;
	defaultheight = height;
}

void creditsmenu(void) {
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	Font myfont = LoadFontEx("data/fonts/font1.ttf", 70, 0, 0);
	Font myfont2 = LoadFontEx("data/fonts/font1.ttf", 200, 0, 350);
	button backbutton = {
	.backcolor = {48, 0, 74,255},
	.frontcolor = {96, 0, 148,255},
	.position = {1680,20,220,75},
	.text = "BACK",
	.textcolor = {255,255,255,255}
	};
	Vector2 vec = MeasureTextEx(myfont2, "-EVERYTHING-", 50, 0);
	vec.x = (1920 - vec.x) / 2;
	vec.y = 1080;
	Vector2 vec2 = MeasureTextEx(myfont2, u8"��KR� ��R��", 200, 0);
	vec2.x = (1920 - vec2.x) / 2;
	vec2.y = 1120;
	while (!WindowShouldClose()) {
		UpdateMusicStream(main_music);
		BeginTextureMode(target);
		ClearBackground(BLACK);
		if (renderbutton(&backbutton, &myfont)) {
			break;
		}
		DrawTextEx(myfont2, "-EVERYTHING-", vec, 50, 0, WHITE);
		DrawTextEx(myfont2, u8"��KR� ��R��", vec2, 200, 0, WHITE);
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		targetdest.width = (float)GetRenderWidth();
		targetdest.height = (float)GetRenderHeight();
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
		if (vec.y > 300) {
			vec.y--;
			vec2.y--;
		}
	}
	UnloadFont(myfont);
	UnloadFont(myfont2);
	UnloadRenderTexture(target);
}

void loadmainmenumusic(void) {
	if (!main_music.ctxData) {
		main_music = LoadMusicStream("data/sound/main_sound.mp3");
		SetMusicVolume(main_music, musicvolume);
		PlayMusicStream(main_music);
	}
}

void unloadmainmenumusic(void) {
	UnloadMusicStream(main_music);
	main_music.ctxData = 0;
}

float getmusicvolume(void) {
	return musicvolume;
}

float geteffectvolume(void) {
	return effectvolume;
}

char getreselect(void) {
	return reselect;
}