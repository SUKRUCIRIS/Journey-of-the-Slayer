#include "game.h"
#include "tile.h"
#include "character.h"
#include <raylib.h>
#include "button.h"

void gamelogic(tile* tileset, character* mainc) {
	renderskillbutton(mainc->jumpskill);
	renderskillbutton(mainc->moveskill);
}

void maingameloop(void) {
	loadtiletextures();
	loadskillbuttontextures();
	tile* tileset = createtileset(7, 192, 0, 0, 1, 3, 0);
	character* mainc = createcharacter(3, 0, 48, tileset, 7);
	tilesetintro(tileset, 25, 7, 0.85f);
	char nextlevelexit = 0;
	char exit = 0;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetRenderWidth(),(float)GetRenderHeight() };
	Vector2 origin = { 0,0 };
	Rectangle screen = { 0,0,1920,1080 };
	Color pausecolor = { 0,0,0,200 };
	Font myfont = LoadFontEx("data/fonts/font1.ttf", 50, 0, 0);
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
	char escpressed = 0;
	while (!WindowShouldClose()) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		rendertileset(tileset, 7);
		renderallmapobjects();
		gamelogic(tileset, mainc);
		EndTextureMode();

		if (IsKeyPressed(KEY_ESCAPE)) {
			escpressed = 1;
			while (!WindowShouldClose()) {
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
	UnloadRenderTexture(target);
	destroytileset(tileset);
	destroycharacter(mainc);
	unloadskillbuttontextures();
	deletetiletextures();
}