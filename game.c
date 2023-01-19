#include "game.h"
#include "tile.h"
#include "character.h"
#include <raylib.h>

void maingameloop(void) {
	loadtiletextures();
	tile* tileset = createtileset(6, 192, 0, 0, 1);
	character* mainc = createcharacter(2, 0, 48, tileset, 6);
	tilesetintro(tileset, 25, 6);
	char nextlevelexit = 1;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		rendertileset(tileset, 6);
		renderallmapobjects();
		EndDrawing();
	}
	if (nextlevelexit) {
		tilesetoutro(tileset, 25, 6);
	}
	destroytileset(tileset);
	destroycharacter(mainc);
	deletetiletextures();
}