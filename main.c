#include <raylib.h>
#include "game.h"
#include "menus.h"

//linker commandline: /NODEFAULTLIB:LIBCMT /subsystem:windows /entry:mainCRTStartup /ignore:4099
//linker: raylib.lib msvcrt.lib winmm.lib

int main() {
	InitWindow(1920, 1080, u8"ÞÜKRÜ ÇÝRÝÞ GAMES");//aspect ratio hep 16:9 olmalý
	SetWindowState(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | FLAG_FULLSCREEN_MODE | FLAG_MSAA_4X_HINT | FLAG_WINDOW_ALWAYS_RUN);
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	intromenu();
	char a = mainmenu();
	if (a == 1) {
		maingameloop();
	}
	CloseWindow();
	return 0;
}