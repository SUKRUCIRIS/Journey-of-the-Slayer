#include "skillbutton.h"

Vector2 e;

Rectangle source = { 0,0,16,16 };

void renderskillbutton(skillbutton* s) {
	e.x = GetMousePosition().x * (1920.0f / GetRenderWidth());
	e.y = GetMousePosition().y * (1080.0f / GetRenderHeight());
	s->mouseon = 0;
	if (CheckCollisionPointRec(e,*(s->position))) {
		s->mouseon = 1;
		if (!(s->passive) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			s->pressed = 1;
		}
	}
	if (s->pressed) {
		s->mouseon = 1;
	}
	if (s->mouseon) {
		DrawRectangle(s->position->x - 20, s->position->y - 20, s->position->width + 40, s->position->height + 40, skillfrontcolor);
	}
	else {
		DrawRectangle(s->position->x - 20, s->position->y - 20, s->position->width + 40, s->position->height + 40, skillbackcolor);
	}
	e.x = 0;
	e.y = 0;
	DrawTexturePro(s->texture, source, *(s->position), e, 0, WHITE);
}