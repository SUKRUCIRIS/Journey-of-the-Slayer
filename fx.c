#include "fx.h"
#include <stdlib.h>
#include <string.h>

Vector2 origin;

#define fx_number 1

fx* allfx[fx_number];

fx* createfxfromgif(const char* path, char framedelay) {
	fx* r = malloc(sizeof(fx));
	if (r) {
		Image x = LoadImageAnim(path, &(r->framenumber));
		r->texture = malloc(sizeof(Texture2D) * r->framenumber);
		if (r->texture) {
			for (int i = 0; i < r->framenumber; i++) {
				r->texture[i] = LoadTextureFromImage(x);
				UpdateTexture(r->texture[i], ((unsigned char*)x.data) + x.width * x.height * 4 * i);
			}
		}
		r->source.x = 0;
		r->source.y = 0;
		r->source.width = x.width;
		r->source.height = x.height;
		UnloadImage(x);
		r->position = 0;
		r->positionnumber = 0;
		r->whichframe = 0;
		r->framedelay = framedelay;
		r->delaycounter = 0;
	}
	return r;
}

void addfx(fx* effect, Rectangle* position) {
	if (effect && position) {
		Rectangle* x = malloc(sizeof(Rectangle) * (effect->positionnumber+1));
		for (int i = 0; i < effect->positionnumber; i++) {
			x[i] = effect->position[i];
		}
		x[effect->positionnumber] = *position;
		free(effect->position);
		effect->position = x;

		unsigned char* x2 = malloc(sizeof(unsigned char) * (effect->positionnumber + 1));
		for (int i = 0; i < effect->positionnumber; i++) {
			x2[i] = effect->whichframe[i];
		}
		x2[effect->positionnumber] = 0;
		free(effect->whichframe);
		effect->whichframe = x2;

		x2 = malloc(sizeof(unsigned char) * (effect->positionnumber + 1));
		for (int i = 0; i < effect->positionnumber; i++) {
			x2[i] = effect->delaycounter[i];
		}
		x2[effect->positionnumber] = 0;
		free(effect->delaycounter);
		effect->delaycounter = x2;

		effect->positionnumber++;
	}
}

void renderallfx(void) {
	for (int i = 0; i < fx_number; i++) {
		for (int i2 = 0; i2 < allfx[i]->positionnumber; i2++) {
			if (allfx[i]->delaycounter[i2] < allfx[i]->framedelay) {
				allfx[i]->delaycounter[i2]++;
			}
			else {
				allfx[i]->delaycounter[i2] = 0;
				allfx[i]->whichframe[i2]++;
				if (allfx[i]->whichframe[i2] >= allfx[i]->framenumber) {
					allfx[i]->whichframe[i2] = 0;

					Rectangle* x = malloc(sizeof(Rectangle) * (allfx[i]->positionnumber - 1));
					char found = 0;
					for (int i3 = 0; i3 < allfx[i]->positionnumber; i3++) {
						if (allfx[i]->position[i3].x == allfx[i]->position[i2].x && allfx[i]->position[i3].y == allfx[i]->position[i2].y) {
							found = 1;
							continue;
						}
						if (!found) {
							x[i3] = allfx[i]->position[i3];
						}
						else {
							x[i3 - 1] = allfx[i]->position[i3];
						}
					}
					free(allfx[i]->position);
					allfx[i]->position = x;

					unsigned char* x2 = malloc(sizeof(unsigned char) * (allfx[i]->positionnumber - 1));
					found = 0;
					for (int i3 = 0; i3 < allfx[i]->positionnumber; i3++) {
						if (allfx[i]->whichframe[i3] == allfx[i]->whichframe[i2]) {
							found = 1;
							continue;
						}
						if (!found) {
							x2[i3] = allfx[i]->whichframe[i3];
						}
						else {
							x2[i3 - 1] = allfx[i]->whichframe[i3];
						}
					}
					free(allfx[i]->whichframe);
					allfx[i]->whichframe = x2;

					x2 = malloc(sizeof(unsigned char) * (allfx[i]->positionnumber - 1));
					found = 0;
					for (int i3 = 0; i3 < allfx[i]->positionnumber; i3++) {
						if (allfx[i]->delaycounter[i3] == allfx[i]->whichframe[i2]) {
							found = 1;
							continue;
						}
						if (!found) {
							x2[i3] = allfx[i]->delaycounter[i3];
						}
						else {
							x2[i3 - 1] = allfx[i]->delaycounter[i3];
						}
					}
					free(allfx[i]->delaycounter);
					allfx[i]->delaycounter = x2;
					
					allfx[i]->positionnumber--;
					i2--;
					continue;
				}
			}
			DrawTexturePro(allfx[i]->texture[allfx[i]->whichframe[i2]], allfx[i]->source, allfx[i]->position[i2], origin, 0, WHITE);
		}
	}
}

void destroyfx(fx* effect) {
	free(effect->position);
	free(effect->whichframe);
	free(effect->delaycounter);
	for (int i = 0; i < effect->framenumber; i++) {
		UnloadTexture(effect->texture[i]);
	}
	free(effect->texture);
	free(effect);
}

void destroyallfx(void) {
	destroyfx(allfx[0]);
}

void loadallfx(void) {
	allfx[0] = createfxfromgif("data/effects/attack.gif", 5);
}

fx* getattackfx(void) {
	return allfx[0];
}