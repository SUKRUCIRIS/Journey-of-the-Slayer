#include "weapon.h"

Texture2D fist_texture;
Texture2D sword_texture;
Texture2D bow_texture;
Rectangle sourcew = { 0,0,16,16 };

weapon fist = {
	.name = "Fists of Slayer",
	.source = &sourcew,
	.texture = &fist_texture,
	.explanation = "Bare hands of the slayer. Covered in demon blood."
};

void loadweapontextures(void) {
	fist_texture = LoadTexture("data/weapons/fist.png");
	sword_texture = LoadTexture("data/weapons/sword.png");
	bow_texture = LoadTexture("data/weapons/bow.png");
}

void unloadweapontextures(void) {
	UnloadTexture(fist_texture);
	UnloadTexture(sword_texture);
	UnloadTexture(bow_texture);
}

weapon* getfistweapon(void) {
	fist.skill1 = getfist1skillbutton();
	fist.skill2 = getfist2skillbutton();
	return &fist;
}