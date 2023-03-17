#include <raylib.h>
#include "game.h"
#include "menus.h"
#include <time.h>
#include <stdlib.h>
#include "button.h"

//Code is written by Þükrü Çiriþ
//2023
//linker commandline: /NODEFAULTLIB:LIBCMT /subsystem:windows /entry:mainCRTStartup
//linker: raylib.lib msvcrt.lib winmm.lib

int main() {
	SetMouseCursor(0);
	Image icon = LoadImage("data/characters/character.png");
	srand((unsigned int)time(0));
	InitWindow(GetScreenWidth(), GetScreenHeight(), "Journey of the Slayer");
	SetWindowIcon(icon);
	InitAudioDevice();
	setdeafultwh(GetScreenWidth(), GetScreenHeight());
	SetWindowState(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | FLAG_WINDOW_ALWAYS_RUN |
		FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED | FLAG_FULLSCREEN_MODE | FLAG_MSAA_4X_HINT);
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	ToggleFullscreen();
	readsettingsavefile();
	intromenu();
	loadclicksound();
	long long unsigned int level = 0;
mainm:
	loadmainmenumusic();
	char a = mainmenu(level);
	if (a == 1) {
		unloadmainmenumusic();
		level = maingameloop(0);
		goto mainm;
	}
	else if (a == 2) {
		settingsmenu();
		goto mainm;
	}
	else if (a == 3) {
		creditsmenu();
		goto mainm;
	}
	UnloadImage(icon);
	unloadclicksound();
	unloadmainmenumusic();
	CloseAudioDevice();
	CloseWindow();
	return 0;
}