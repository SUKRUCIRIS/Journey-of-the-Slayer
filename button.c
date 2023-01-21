#include "button.h"

Vector2 e;

char renderbutton(button* b, Font* f) {
	e.x = GetMousePosition().x * (1920.0f / GetRenderWidth());
	e.y = GetMousePosition().y * (1080.0f / GetRenderHeight());
	if (CheckCollisionPointRec(e, b->position)) {
		DrawRectangleRec(b->position, b->frontcolor);
		e = MeasureTextEx(*f, b->text, (float)f->baseSize, 0);
		e.x = b->position.x + (b->position.width - e.x) / 2.0f;
		e.y = b->position.y + (b->position.height - e.y) / 2.0f;
		DrawTextEx(*f, b->text, e, (float)f->baseSize, 0, b->textcolor);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			return 1;
		}
	}
	else {
		DrawRectangleRec(b->position, b->backcolor);
		e = MeasureTextEx(*f, b->text, (float)f->baseSize, 0);
		e.x = b->position.x + (b->position.width - e.x) / 2.0f;
		e.y = b->position.y + (b->position.height - e.y) / 2.0f;
		DrawTextEx(*f, b->text, e, (float)f->baseSize, 0, b->textcolor);
	}
	return 0;
}