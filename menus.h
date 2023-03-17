#pragma once

void intromenu(void);

char mainmenu(long long unsigned int level);

void settingsmenu(void);

void setdeafultwh(int width, int height);

void creditsmenu(void);

void loadmainmenumusic(void);

void unloadmainmenumusic(void);

float getmusicvolume(void);

float geteffectvolume(void);

void writesettingsavefile(void);

void readsettingsavefile(void);

char getreselect(void);