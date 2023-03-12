#include "game.h"
#include "tile.h"
#include "character.h"
#include <raylib.h>
#include "button.h"
#include "enemy.h"
#include <stdio.h>
#include "fx.h"
#include <stdlib.h>

long long unsigned int maingameloop(long long unsigned int levelx) {
	loadallfx();
	loadenemytextures();
	loadtiletextures();
	loadskillbuttontextures();
	loadcharactertextures();
	loadweapontextures();
	loadarmortextures();
	character* oldchar = 0;
	char nextlevelexit = 1;
	char exit = 0;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	SetTextureFilter(target.texture, TEXTURE_FILTER_ANISOTROPIC_16X);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	Rectangle screen = { 0,0,1920,1080 };
	Color pausecolor = { 0,0,0,200 };
	Font myfont = LoadFontEx("data/fonts/font1.ttf", 70, 0, 0);
	setwarinfofont(&myfont);
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
	long long unsigned int level = levelx;
	char leveltext[100] = { 0 };
	Vector2 leveltextpos = { 0,0 };
levelstart:
	tileset = createtileset(7, 192, 0, 0, 1, 3, 0, level);
	mainc = createcharacter(3, 0, 48, tileset, 7);
	if (oldchar) {
		transfercharacter(mainc, oldchar);
		destroycharacter(oldchar);
	}
	tilesetintro(tileset, 25, 7, 0.85f);
	if (rand() % 2 == 0) {
		enemyturn = 1;
		setwarning("DEMONS WILL PLAY FIRST");
	}
	else {
		enemyturn = 0;
		setwarning("YOU WILL PLAY FIRST");
	}
	while (1) {
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
		renderenemybars();
		renderallfx();
		renderwarinfo();
		//game logic end
		sprintf(leveltext, "Level: %lld", level);
		leveltextpos=MeasureTextEx(myfont, leveltext, 40, 0);
		leveltextpos.x = (1920 - leveltextpos.x) / 2;
		leveltextpos.y = 1050 - leveltextpos.y;
		DrawTextPro(myfont, leveltext, leveltextpos, origin, 0, 40, 0, WHITE);
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
		if ((exit || areallenemiesdead() || mainc->health <= 0) && !isthereanimation()) {
			if (mainc->health <= 0) {
				Image ss = LoadImageFromScreen();
				Texture2D sst = LoadTextureFromImage(ss);
				Rectangle ssource = { 0,0,ss.width,ss.height };
				UnloadImage(ss);
				Color bg = { 0,0,0,1 };
				Color text = { 255,255,255,1 };
				Vector2 e = MeasureTextEx(myfont, "JOURNEY OVER", 100, 0);
				e.x = (1920 - e.x) / 2;
				e.y = 300;
				char leveltext[150] = { 0 };
				sprintf(leveltext, "Your journey ended at %lld. level. Better luck next time Slayer...", level);
				Vector2 e2 = MeasureTextEx(myfont, leveltext, 50, 0);
				e2.x = (1920 - e2.x) / 2;
				e2.y = e.y + 100;
				while (1) {
					BeginTextureMode(target);
					ClearBackground(BLACK);
					DrawTexturePro(sst, ssource, screen, origin, 0, WHITE);
					DrawRectangle(0, 0, 1920, 1080, bg);
					DrawTextEx(myfont, "JOURNEY OVER", e, 100, 0, text);
					DrawTextEx(myfont, leveltext, e2, 50, 0, text);
					if (text.a == 255) {
						if (renderbutton(&menubutton, &myfont)) {
							break;
						}
					}
					EndTextureMode();

					BeginDrawing();
					ClearBackground(BLACK);
					DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
					EndDrawing();
					if (bg.a < 200) {
						bg.a += 2;
					}
					if (text.a < 255) {
						text.a += 2;
					}
				}
				UnloadTexture(sst);
				nextlevelexit = 0;
			}
			break;
		}
	}
	removewarning();
	setwarinfofont(&myfont);
	if (nextlevelexit) {
		armor* newarmor = createrandomarmor(level);
		Image ss = LoadImageFromScreen();
		Texture2D sst = LoadTextureFromImage(ss);
		Rectangle ssource = { 0,0,ss.width,ss.height };
		Color bg = { 0,0,0,200 };
		Rectangle armor1rect = { 310,100,600,700 };
		Rectangle armor2rect = { 1010,100,600,700 };
		UnloadImage(ss);
		button keepoldbutton = {
		.backcolor = {48, 0, 74,255},
		.frontcolor = {96, 0, 148,255},
		.position = {310,900,600,75},
		.text = "Keep Old Item",
		.textcolor = {255,255,255,255}
		};
		button takenewbutton = {
		.backcolor = {48, 0, 74,255},
		.frontcolor = {96, 0, 148,255},
		.position = {1010,900,600,75},
		.text = "Take New Item",
		.textcolor = {255,255,255,255}
		};
		while (1) {
			BeginTextureMode(target);
			ClearBackground(BLACK);
			DrawTexturePro(sst, ssource, screen, origin, 0, WHITE);
			DrawRectangle(0, 0, 1920, 1080, bg);
			if (newarmor->armortype == 0) {
				renderarmorinfo(mainc->headarmor, &myfont, &armor1rect);
			}
			else if (newarmor->armortype == 1) {
				renderarmorinfo(mainc->torsoarmor, &myfont, &armor1rect);
			}
			else if (newarmor->armortype == 2) {
				renderarmorinfo(mainc->armarmor, &myfont, &armor1rect);
			}
			else if (newarmor->armortype == 3) {
				renderarmorinfo(mainc->legarmor, &myfont, &armor1rect);
			}
			renderarmorinfo(newarmor, &myfont, &armor2rect);
			if (renderbutton(&keepoldbutton, &myfont)) {
				break;
			}
			else if (renderbutton(&takenewbutton, &myfont)) {
				if (newarmor->armortype == 0) {
					armortakeoff(mainc, mainc->headarmor);
				}
				else if (newarmor->armortype == 1) {
					armortakeoff(mainc, mainc->torsoarmor);
				}
				else if (newarmor->armortype == 2) {
					armortakeoff(mainc, mainc->armarmor);
				}
				else if (newarmor->armortype == 3) {
					armortakeoff(mainc, mainc->legarmor);
				}
				armorputon(mainc, newarmor);
				break;
			}
			EndTextureMode();

			BeginDrawing();
			ClearBackground(BLACK);
			DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
			EndDrawing();
		}
		UnloadTexture(sst);
		tilesetoutro(tileset, 25, 7, 0.15f);
	}
	destroytileset(tileset);
	destroyallenemies();
	destroyallmapobjects();
	mainc->m = 0;
	if (nextlevelexit && mainc->health > 0) {
		mainc->actionpoint = mainc->maxactionpoint;
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
	unloadweapontextures();
	UnloadFont(myfont);
	destroyallfx();
	unloadarmortextures();
	return level;
}