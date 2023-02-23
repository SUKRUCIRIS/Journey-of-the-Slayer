#include <raylib.h>
#include "game.h"
#include "menus.h"
#include <time.h>
#include <stdlib.h>

//linker commandline: /NODEFAULTLIB:LIBCMT /subsystem:windows /entry:mainCRTStartup /ignore:4099
//linker: raylib.lib msvcrt.lib winmm.lib

int main() {
	srand((unsigned int)time(0));
	InitWindow(GetScreenWidth(), GetScreenHeight(), u8"ÞÜKRÜ ÇÝRÝÞ GAMES");
	setdeafultwh(GetScreenWidth(), GetScreenHeight());
	SetWindowState(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | FLAG_WINDOW_ALWAYS_RUN |
		FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED | FLAG_FULLSCREEN_MODE | FLAG_MSAA_4X_HINT);
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	ToggleFullscreen();
	intromenu();
	long long unsigned int level = 0;
mainm:
	char a = mainmenu(level);
	if (a == 1) {
		level = maingameloop(0);
		goto mainm;
	}
	else if (a == 2) {
		settingsmenu();
		goto mainm;
	}
	CloseWindow();
	return 0;
}