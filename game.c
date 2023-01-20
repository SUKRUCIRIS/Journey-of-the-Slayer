#include "game.h"
#include "tile.h"
#include "character.h"
#include <raylib.h>

void maingameloop(void) {
	loadtiletextures();
	tile* tileset = createtileset(7, 192, 0, 0, 1, 3, 0);
	character* mainc = createcharacter(3, 0, 48, tileset, 7);
	tilesetintro(tileset, 25, 7, 0.85f);
	char nextlevelexit = 1;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		rendertileset(tileset, 7);
		renderallmapobjects();
		EndDrawing();
	}
	if (nextlevelexit) {
		tilesetoutro(tileset, 25, 7, 0.15f);
	}
	destroytileset(tileset);
	destroycharacter(mainc);
	deletetiletextures();
}