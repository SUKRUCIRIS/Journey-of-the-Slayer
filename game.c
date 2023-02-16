#include "game.h"
#include "tile.h"
#include "character.h"
#include <raylib.h>
#include "button.h"
#include "enemy.h"

void maingameloop(void) {
	loadenemytextures();
	loadtiletextures();
	loadskillbuttontextures();
	loadcharactertextures();
	character* oldchar = 0;
	char nextlevelexit = 1;
	char exit = 0;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	Rectangle screen = { 0,0,1920,1080 };
	Color pausecolor = { 0,0,0,200 };
	Font myfont = LoadFontEx("data/fonts/font1.ttf", 70, 0, 0);
	button menubutton = {
		.backcolor = {48, 0, 74,255},
		.frontcolor = {96, 0, 148,255},
		.position = {760,700,400,75},
		.text = "MAINMENU",
		.textcolor = {255,255,255,255}
	};
	button resumebutton = {
		.backcolor = {48, 0, 74,255},
		.frontcolor = {96, 0, 148,255},
		.position = {760,600,400,75},
		.text = "RESUME",
		.textcolor = {255,255,255,255}
	};
	button endturnbutton = {
		.backcolor = {48, 0, 74,255},
		.frontcolor = {96, 0, 148,255},
		.position = {825,40,270,75},
		.text = "End Turn",
		.textcolor = {255,255,255,255}
	};
	char escpressed = 0;
	char enemyturn = 0;
	tile* tileset = 0;
	character* mainc = 0;
	long long unsigned int level= 0;
levelstart:
	tileset = createtileset(7, 192, 0, 0, 1, 3, 0, level);
	mainc = createcharacter(3, 0, 48, tileset, 7);
	if (oldchar) {
		transfercharacter(mainc, oldchar);
		destroycharacter(oldchar);
	}
	tilesetintro(tileset, 25, 7, 0.85f);
	while (!WindowShouldClose()) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		rendertileset(tileset, 7);
		//game logic start
		if (enemyturn == 0) {
			renderskillbutton(mainc->jumpskill, mainc, tileset);
			renderskillbutton(mainc->moveskill, mainc, tileset);
			if (mainc->weaponinfo && mainc->weaponinfo->skill1) {
				renderskillbutton(mainc->weaponinfo->skill1, mainc, tileset);
			}
			if (mainc->weaponinfo && mainc->weaponinfo->skill2) {
				renderskillbutton(mainc->weaponinfo->skill2, mainc, tileset);
			}
			if (renderbutton(&endturnbutton, &myfont)) {
				enemyturn = 1;
			}
		}
		else {
			playallenemies(mainc, tileset, &myfont);
			enemyturn = 0;
			continue;
		}
		renderallmapobjects();
		rendercharacterinfo(mainc, &myfont);
		renderwarning(&myfont);
		renderchosenenemyinfo(&myfont);
		//game logic end
		EndTextureMode();

		if (IsKeyPressed(KEY_ESCAPE)) {
			escpressed = 1;
			while (!WindowShouldClose() && !(mainc->jumpskill->pressed) && !(mainc->moveskill->pressed) &&
				(!(mainc->weaponinfo) || !(mainc->weaponinfo->skill1->pressed)) &&
				(!(mainc->weaponinfo) || !(mainc->weaponinfo->skill2->pressed))) {
				BeginTextureMode(target);
				ClearBackground(BLACK);
				for (int i = 0; i < 49; i++) {
					tile_render(&(tileset[i]));
				}
				renderallmapobjects();
				DrawRectangleRec(screen, pausecolor);
				if (renderbutton(&resumebutton, &myfont) || (escpressed == 0 && IsKeyPressed(KEY_ESCAPE))) {
					break;
				}
				if (renderbutton(&menubutton, &myfont)) {
					nextlevelexit = 0;
					exit = 1;
					break;
				}
				EndTextureMode();

				BeginDrawing();
				ClearBackground(BLACK);
				DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
				EndDrawing();
				escpressed = 0;
			}
			mainc->jumpskill->pressed = 0;
			mainc->moveskill->pressed = 0;
			if (mainc->weaponinfo) {
				mainc->weaponinfo->skill1->pressed = 0;
				mainc->weaponinfo->skill2->pressed = 0;
			}
			setcharacterapblink(0);
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
		if (exit) {
			break;
		}
	}
	if (nextlevelexit) {
		tilesetoutro(tileset, 25, 7, 0.15f);
	}
	destroytileset(tileset);
	destroyallenemies();
	if (nextlevelexit) {
		oldchar = mainc;
		level++;
		goto levelstart;
	}
	destroycharacter(mainc);
	UnloadRenderTexture(target);
	unloadskillbuttontextures();
	deletetiletextures();
	unloadenemytextures();
	unloadcharactertextures();
}