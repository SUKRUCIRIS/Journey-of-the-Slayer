#include <raylib.h>
#include "game.h"
#include "menus.h"

//linker commandline: /NODEFAULTLIB:LIBCMT /subsystem:windows /entry:mainCRTStartup /ignore:4099
//linker: raylib.lib msvcrt.lib winmm.lib

int main() {
	InitWindow(GetScreenWidth(), GetScreenHeight(), u8"ÞÜKRÜ ÇÝRÝÞ GAMES");//aspect ratio hep 16:9 olmalý
	SetWindowState(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_ALWAYS_RUN |
		FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED | FLAG_FULLSCREEN_MODE);
	ToggleFullscreen();
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	intromenu();
	mainm:
	char a = mainmenu();
	if (a == 1) {
		maingameloop();
		goto mainm;
	}
	CloseWindow();
	return 0;
}