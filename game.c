#include "game.h"
#include "tile.h"
#include "character.h"
#include <raylib.h>

void maingameloop(void) {
	loadtiletextures();
	tile* tileset = createtileset(7, 192, 0, 0, 1, 3, 0);
	character* mainc = createcharacter(3, 0, 48, tileset, 7);
	tilesetintro(tileset, 25, 7, 0.85f);
	char nextlevelexit = 0;
	RenderTexture2D target = LoadRenderTexture(1920, 1080);
	Rectangle targetsource = { 0,0,1920,-1080 };
	Rectangle targetdest = { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() };
	Vector2 origin = { 0,0 };
	while (!WindowShouldClose()) {
		BeginTextureMode(target);
		ClearBackground(BLACK);
		rendertileset(tileset, 7);
		renderallmapobjects();
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetsource, targetdest, origin, 0, WHITE);
		EndDrawing();
	}
	if (nextlevelexit) {
		tilesetoutro(tileset, 25, 7, 0.15f);
	}
	UnloadRenderTexture(target);
	destroytileset(tileset);
	destroycharacter(mainc);
	deletetiletextures();
}