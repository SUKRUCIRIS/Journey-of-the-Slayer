#include "skillbutton.h"

Vector2 e;

Vector2 e2;

Rectangle source = { 0,0,16,16 };

Font myfont;

Rectangle moveskillposition = { 1740,100,128,128 };
Rectangle jumpskillposition = { 1740,350,128,128 };
Color skillbackcolor = { 48, 0, 74,255 };
Color skillfrontcolor = { 96, 0, 148,255 };
Texture2D jumpskilltexture;
Texture2D moveskilltexture;

skillbutton jumpskillbutton = {
	.position = &jumpskillposition,
	.name = "Jump",
	.texture = &jumpskilltexture,
	.passive = 0,
	.pressed = 0,
	.mouseon = 0,
	.actionpoint = 3
};

skillbutton moveskillbutton = {
	.position = &moveskillposition,
	.name = "Move",
	.texture = &moveskilltexture,
	.passive = 0,
	.pressed = 0,
	.mouseon = 0,
	.actionpoint = 1
};

void renderskillbutton(skillbutton* s) {
	e.x = GetMousePosition().x * (1920.0f / GetRenderWidth());
	e.y = GetMousePosition().y * (1080.0f / GetRenderHeight());
	s->mouseon = 0;
	if (CheckCollisionPointRec(e, *(s->position))) {
		s->mouseon = 1;
		if (!(s->passive) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			s->pressed = 1;
		}
	}
	if (s->pressed) {
		s->mouseon = 1;
	}
	if (s->mouseon) {
		DrawRectangle((int)s->position->x - 40, (int)s->position->y - 40, (int)s->position->width + 80, (int)s->position->height + 80, skillfrontcolor);
	}
	else {
		DrawRectangle((int)s->position->x - 40, (int)s->position->y - 40, (int)s->position->width + 80, (int)s->position->height + 80, skillbackcolor);
	}
	e.x = 0;
	e.y = 0;
	e2 = MeasureTextEx(myfont, s->name, (float)myfont.baseSize, 0);
	e2.x = s->position->x - 40 + (s->position->width + 80 - e2.x) / 2;
	e2.y = s->position->y - 40 + (40 - e2.y) / 2;
	DrawTextPro(myfont, s->name, e2, e, 0, (float)myfont.baseSize, 0, WHITE);
	DrawTexturePro(*(s->texture), source, *(s->position), e, 0, WHITE);
}

void loadskillbuttontextures(void) {
	jumpskilltexture = LoadTexture("data/skills/jumpskill.png");
	moveskilltexture = LoadTexture("data/skills/moveskill.png");
	myfont = LoadFontEx("data/fonts/font1.ttf", 25, 0, 0);
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