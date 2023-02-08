#include "skillbutton.h"
#include "character.h"

Vector2 e;

Vector2 e2;

Rectangle source = { 0,0,16,16 };

Font myfont;

Rectangle moveskillposition = { 1740,40,128,128 };
Rectangle jumpskillposition = { 1740,200,128,128 };
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
	.actionpoint = 3,
	.explanation = "Use 3 action\npoints for\njumping into\na tile in 2\nunit range."
};

skillbutton moveskillbutton = {
	.position = &moveskillposition,
	.name = "Move",
	.texture = &moveskilltexture,
	.passive = 0,
	.pressed = 0,
	.mouseon = 0,
	.actionpoint = 1,
	.explanation = "Use 1 action\npoint for\nevery tile\nyou passed\non."
};

void renderskillbutton(skillbutton* s, void* mainc) {
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

		e2 = MeasureTextEx(myfont, s->name, 40, 0);
		e2.x = s->position->x - 215 + (200 - e2.x) / 2;
		e2.y = s->position->y - 8;
		DrawTextPro(myfont, s->name, e2, e, 0, 40, 0, WHITE);

		e2 = MeasureTextEx(myfont, s->explanation, 30, 0);
		e2.x = s->position->x - 215 + (200 - e2.x) / 2;
		e2.y = s->position->y + 30;
		DrawTextPro(myfont, s->explanation, e2, e, 0, 30, 0, WHITE);
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