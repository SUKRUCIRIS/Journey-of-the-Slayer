#include "skillbutton.h"
#include "character.h"
#include "tile.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

Vector2 e;

Vector2 e2;

Rectangle source = { 0,0,16,16 };

Font myfont;

char x;

Rectangle moveskillposition = { 1740,40,128,128 };
Rectangle jumpskillposition = { 1740,200,128,128 };
Color skillbackcolor = { 48, 0, 74,255 };
Color skillfrontcolor = { 96, 0, 148,255 };
Texture2D jumpskilltexture;
Texture2D moveskilltexture;

int distance[49] = { 0 };

//warning
char warning[100] = { 0 };
Color warningcolor = { 231,31,31,0 };
//warning

char jumpskill(tile* tileset, character* mainc) {
	if (mainc->actionpoint >= 3) {
		renderrange((int)mainc->m->tileposition.x, (int)mainc->m->tileposition.y, 2, 1, 7, tileset, 0);
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 7; y++) {
				if (tile_status(&(tileset[(7 * x) + y])) == 3) {
					if (tileset[(7 * x) + y].obstacle == 0 &&
						abs((int)mainc->m->tileposition.x - x) <= 2 &&
						abs((int)mainc->m->tileposition.y - y) <= 2 &&
						tileset[(7 * x) + y].type != 2) {
						Vector2* animationpos = malloc(sizeof(Vector2) * 2);
						if (animationpos) {
							calculateposmapobject(&(tileset[(7 * x) + y]), mainc->m, &(animationpos[1]), 1);
							animationpos[0].x = (animationpos[1].x + mainc->m->position.x) / 2;
							animationpos[0].y = ((animationpos[1].y + mainc->m->position.y) / 2) - 100;
							addanimationmapobject(mainc->m, animationpos, 2);
						}
						movecharacter(mainc, x, y, tileset, 7);
						mainc->actionpoint -= 3;
						return 1;
					}
					else {
						return -1;
					}
				}
			}
		}
	}
	else {
		return 0;
	}
	return 2;
}

Vector2* setmoveanimationpoints(int x, int y, tile* tileset, character* mainc) {
	int max = distance[7 * x + y];
	Vector2* result = malloc(sizeof(Vector2) * max);
	if (result) {
		for (int i = max - 1; i >= 0; i--) {
			calculateposmapobject(&(tileset[(7 * x) + y]), mainc->m, &(result[i]), 1);
			if (x - 1 >= 0 && distance[7 * (x - 1) + y] == i) {
				x = x - 1;
			}
			else if (x + 1 < 7 && distance[7 * (x + 1) + y] == i) {
				x = x + 1;
			}
			else if (y - 1 >= 0 && distance[7 * x + y - 1] == i) {
				y = y - 1;
			}
			else if (y + 1 < 7 && distance[7 * x + y + 1] == i) {
				y = y + 1;
			}
			else if (y - 1 >= 0 && x - 1 >= 0 && distance[7 * (x - 1) + y - 1] == i) {
				y = y - 1;
				x = x - 1;
			}
			else if (y - 1 >= 0 && x + 1 < 7 && distance[7 * (x + 1) + y - 1] == i) {
				y = y - 1;
				x = x + 1;
			}
			else if (y + 1 < 7 && x - 1 >= 0 && distance[7 * (x - 1) + y + 1] == i) {
				y = y + 1;
				x = x - 1;
			}
			else if (y + 1 < 7 && x + 1 < 7 && distance[7 * (x + 1) + y + 1] == i) {
				y = y + 1;
				x = x + 1;
			}
		}
	}
	return result;
}

char move(tile* tileset, character* mainc) {
	if (mainc->actionpoint > 0) {
		calculatedistance((int)mainc->m->tileposition.x, (int)mainc->m->tileposition.y, tileset);
		for (int x2 = 0; x2 < 7; x2++) {
			for (int y2 = 0; y2 < 7; y2++) {
				if (distance[7 * x2 + y2] <= mainc->actionpoint) {
					warningcolor.a = 255;
					e.x = ((tile*)tileset)[(x2 * 7) + y2].position.x + ((tile*)tileset)[(x2 * 7) + y2].position.width / 2;
					e.y = ((tile*)tileset)[(x2 * 7) + y2].position.y + ((tile*)tileset)[(x2 * 7) + y2].position.height / 6;
					e2.x = ((tile*)tileset)[(x2 * 7) + y2].position.x + ((tile*)tileset)[(x2 * 7) + y2].position.width / 3;
					e2.y = ((tile*)tileset)[(x2 * 7) + y2].position.y + ((tile*)tileset)[(x2 * 7) + y2].position.height / 4;
					DrawLineEx(e, e2, 3, warningcolor);
					e = e2;
					e2.x = ((tile*)tileset)[(x2 * 7) + y2].position.x + ((tile*)tileset)[(x2 * 7) + y2].position.width / 2;
					e2.y = ((tile*)tileset)[(x2 * 7) + y2].position.y + ((tile*)tileset)[(x2 * 7) + y2].position.height / 3;
					DrawLineEx(e, e2, 3, warningcolor);
					e = e2;
					e2.x = ((tile*)tileset)[(x2 * 7) + y2].position.x + 2 * ((tile*)tileset)[(x2 * 7) + y2].position.width / 3;
					e2.y = ((tile*)tileset)[(x2 * 7) + y2].position.y + ((tile*)tileset)[(x2 * 7) + y2].position.height / 4;
					DrawLineEx(e, e2, 3, warningcolor);
					e = e2;
					e2.x = ((tile*)tileset)[(x2 * 7) + y2].position.x + ((tile*)tileset)[(x2 * 7) + y2].position.width / 2;
					e2.y = ((tile*)tileset)[(x2 * 7) + y2].position.y + ((tile*)tileset)[(x2 * 7) + y2].position.height / 6;
					DrawLineEx(e, e2, 3, warningcolor);
					warningcolor.a = 0;
					if (tile_status(&(tileset[(7 * x2) + y2])) == 3) {
						addanimationmapobject(mainc->m, setmoveanimationpoints(x2, y2, tileset, mainc), distance[7 * x2 + y2]);
						movecharacter(mainc, x2, y2, tileset, 7);
						mainc->actionpoint -= distance[7 * x2 + y2];
						return 1;
					}
				}
				else if (tile_status(&(tileset[(7 * x2) + y2])) == 3) {
					return -1;
				}
			}
		}
	}
	else {
		return 0;
	}
	return 2;
}

skillbutton jumpskillbutton = {
	.position = &jumpskillposition,
	.name = "Jump",
	.texture = &jumpskilltexture,
	.passive = 0,
	.pressed = 0,
	.mouseon = 0,
	.explanation = "Use 3 action points for jumping into a tile in 2 unit range.",
	.function = &jumpskill
};

skillbutton moveskillbutton = {
	.position = &moveskillposition,
	.name = "Move",
	.texture = &moveskilltexture,
	.passive = 0,
	.pressed = 0,
	.mouseon = 0,
	.explanation = "Use 1 action point for every tile you passed on.",
	.function = &move
};

void neighcalcul(int x, int y, tile* tileset) {
	if (tileset[7 * x + y].obstacle == 0 && tileset[7 * x + y].type != 2) {
		if (x - 1 >= 0 && distance[7 * x + y] > distance[7 * (x - 1) + y] + 1) {
			distance[7 * x + y] = distance[7 * (x - 1) + y] + 1;
		}
		if (x + 1 < 7 && distance[7 * x + y] > distance[7 * (x + 1) + y] + 1) {
			distance[7 * x + y] = distance[7 * (x + 1) + y] + 1;
		}
		if (y - 1 >= 0 && distance[7 * x + y] > distance[7 * x + y - 1] + 1) {
			distance[7 * x + y] = distance[7 * x + y - 1] + 1;
		}
		if (y + 1 < 7 && distance[7 * x + y] > distance[7 * x + y + 1] + 1) {
			distance[7 * x + y] = distance[7 * x + y + 1] + 1;
		}
		if (y - 1 >= 0 && x - 1 >= 0 && distance[7 * x + y] > distance[7 * (x - 1) + y - 1] + 1) {
			distance[7 * x + y] = distance[7 * (x - 1) + y - 1] + 1;
		}
		if (y - 1 >= 0 && x + 1 < 7 && distance[7 * x + y] > distance[7 * (x + 1) + y - 1] + 1) {
			distance[7 * x + y] = distance[7 * (x + 1) + y - 1] + 1;
		}
		if (y + 1 < 7 && x - 1 >= 0 && distance[7 * x + y] > distance[7 * (x - 1) + y + 1] + 1) {
			distance[7 * x + y] = distance[7 * (x - 1) + y + 1] + 1;
		}
		if (y + 1 < 7 && x + 1 < 7 && distance[7 * x + y] > distance[7 * (x + 1) + y + 1] + 1) {
			distance[7 * x + y] = distance[7 * (x + 1) + y + 1] + 1;
		}
	}
}

int* calculatedistance(int x, int y, void* tileset) {
	for (int i = 0; i < 49; i++) {
		distance[i] = 1453;
	}
	distance[7 * x + y] = 0;
	for (int i = 0; i < 100; i++) {
		for (int x2 = 0; x2 < 7; x2++) {
			for (int y2 = 0; y2 < 7; y2++) {
				neighcalcul(x2, y2, tileset);
			}
		}
	}
	if (((tile*)tileset)[7 * x + y].obstacle == 1 || ((tile*)tileset)[7 * x + y].type == 2) {
		distance[7 * x + y] = 1453;
	}
	return distance;
}

void renderrange(int x, int y, int range, char which, int max, void* tileset, char obstacle) {
	for (int x2 = 0; x2 < max; x2++) {
		for (int y2 = 0; y2 < max; y2++) {
			if (abs(x - x2) <= range && abs(y - y2) <= range &&
				(which == 0 || ((tile*)tileset)[(x2 * max) + y2].type == which) &&
				(obstacle == 2 || ((tile*)tileset)[(x2 * max) + y2].obstacle == obstacle)) {
				warningcolor.a = 255;
				e.x = ((tile*)tileset)[(x2 * max) + y2].position.x + ((tile*)tileset)[(x2 * max) + y2].position.width / 2;
				e.y = ((tile*)tileset)[(x2 * max) + y2].position.y + ((tile*)tileset)[(x2 * max) + y2].position.height / 6;
				e2.x = ((tile*)tileset)[(x2 * max) + y2].position.x + ((tile*)tileset)[(x2 * max) + y2].position.width / 3;
				e2.y = ((tile*)tileset)[(x2 * max) + y2].position.y + ((tile*)tileset)[(x2 * max) + y2].position.height / 4;
				DrawLineEx(e, e2, 3, warningcolor);
				e = e2;
				e2.x = ((tile*)tileset)[(x2 * max) + y2].position.x + ((tile*)tileset)[(x2 * max) + y2].position.width / 2;
				e2.y = ((tile*)tileset)[(x2 * max) + y2].position.y + ((tile*)tileset)[(x2 * max) + y2].position.height / 3;
				DrawLineEx(e, e2, 3, warningcolor);
				e = e2;
				e2.x = ((tile*)tileset)[(x2 * max) + y2].position.x + 2 * ((tile*)tileset)[(x2 * max) + y2].position.width / 3;
				e2.y = ((tile*)tileset)[(x2 * max) + y2].position.y + ((tile*)tileset)[(x2 * max) + y2].position.height / 4;
				DrawLineEx(e, e2, 3, warningcolor);
				e = e2;
				e2.x = ((tile*)tileset)[(x2 * max) + y2].position.x + ((tile*)tileset)[(x2 * max) + y2].position.width / 2;
				e2.y = ((tile*)tileset)[(x2 * max) + y2].position.y + ((tile*)tileset)[(x2 * max) + y2].position.height / 6;
				DrawLineEx(e, e2, 3, warningcolor);
				warningcolor.a = 0;
			}
		}
	}
}

void setwarning(const char* text) {
	strcpy(warning, text);
	warningcolor.a = 255;
}

void renderwarning(Font* font) {
	e = MeasureTextEx(*font, warning, 30, 0);
	e.x = (GetRenderWidth() - e.x) / 2;
	e.y = 200;
	e2.x = 0;
	e2.y = 0;
	DrawTextPro(*font, warning, e, e2, 0, 30, 0, warningcolor);
	if (warningcolor.a > 0) {
		if (warningcolor.a == 1) {
			warningcolor.a = 0;
		}
		else {
			warningcolor.a -= 2;
		}
	}
}

void writeinrectangle(Font* font, const char* text, float x, float y, float w, float size, float borderwidth, Color* color) {
	int count = 0;
	const char** splitted = TextSplit(text, ' ', &count);
	float xlast = x + borderwidth;
	float ylast = y + borderwidth;
	float spacewidth = MeasureTextEx(*font, " ", size, 0).x;
	float spaceheight = MeasureTextEx(*font, " ", size, 0).y;
	float width = 0;
	e.x = 0;
	e.y = 0;
	for (int i = 0; i < count; i++) {
		width = MeasureTextEx(*font, splitted[i], size, 0).x;
		if (xlast + width > x + w - borderwidth) {
			xlast = x + borderwidth;
			ylast = ylast + spaceheight;
			e2.x = xlast;
			e2.y = ylast;
			DrawTextPro(*font, splitted[i], e2, e, 0, size, 0, *color);
			xlast = xlast + width + spacewidth;
		}
		else {
			e2.x = xlast;
			e2.y = ylast;
			DrawTextPro(*font, splitted[i], e2, e, 0, size, 0, *color);
			xlast = xlast + width + spacewidth;
		}
	}
}

void renderskillbutton(skillbutton* s, void* mainc, void* tileset) {
	e.x = GetMousePosition().x * (1920.0f / GetRenderWidth());
	e.y = GetMousePosition().y * (1080.0f / GetRenderHeight());
	s->mouseon = 0;
	if (CheckCollisionPointRec(e, *(s->position))) {
		s->mouseon = 1;
		if (!(s->passive) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			s->pressed = 1;
			if (((character*)mainc)->jumpskill != s) {
				((character*)mainc)->jumpskill->pressed = 0;
			}
			if (((character*)mainc)->moveskill != s) {
				((character*)mainc)->moveskill->pressed = 0;
			}
			if (((character*)mainc)->weaponinfo) {
				if (((character*)mainc)->weaponinfo->skill1 != s) {
					((character*)mainc)->weaponinfo->skill1->pressed = 0;
				}
				if (((character*)mainc)->weaponinfo->skill2 != s) {
					((character*)mainc)->weaponinfo->skill2->pressed = 0;
				}
			}
		}
	}
	if (s->pressed && s->function) {
		x = s->function(tileset, mainc);
		if (x != 2) {
			s->pressed = 0;
			if (x == 0) {
				setwarning("You don't have enough action point.");
			}
			else if (x == -1) {
				setwarning("Wrong target.");
			}
		}
	}
	if (s->mouseon || s->pressed) {
		DrawRectangle((int)s->position->x - 10, (int)s->position->y - 10, (int)s->position->width + 20, (int)s->position->height + 20, skillfrontcolor);
	}
	else {
		DrawRectangle((int)s->position->x - 10, (int)s->position->y - 10, (int)s->position->width + 20, (int)s->position->height + 20, skillbackcolor);
	}
	e.x = 0;
	e.y = 0;
	if (s->mouseon) {
		DrawRectangle((int)s->position->x - 215, (int)s->position->y - 10, 200, 300, skillfrontcolor);
		DrawRectangleLines((int)s->position->x - 215, (int)s->position->y - 10, 200, 300, WHITE);

		e2 = MeasureTextEx(myfont, s->name, 40, 0);
		e2.x = s->position->x - 215 + (200 - e2.x) / 2;
		e2.y = s->position->y - 8;
		DrawTextPro(myfont, s->name, e2, e, 0, 40, 0, WHITE);

		writeinrectangle(&myfont, s->explanation, s->position->x - 215, s->position->y + 30, 200, 30, 10, &WHITE);
	}
	DrawTexturePro(*(s->texture), source, *(s->position), e, 0, WHITE);
}

void loadskillbuttontextures(void) {
	jumpskilltexture = LoadTexture("data/skills/jumpskill.png");
	moveskilltexture = LoadTexture("data/skills/moveskill.png");
	myfont = LoadFontEx("data/fonts/font1.ttf", 40, 0, 0);
}

void unloadskillbuttontextures(void) {
	UnloadTexture(jumpskilltexture);
	UnloadTexture(moveskilltexture);
	UnloadFont(myfont);
}

skillbutton* getjumpskillbutton(void) {
	return &jumpskillbutton;
}

skillbutton* getmoveskillbutton(void) {
	return &moveskillbutton;
}