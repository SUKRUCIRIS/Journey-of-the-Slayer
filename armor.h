#pragma once

typedef struct armor {
	char name[20];
	char armortype;//0 head, 1 torso, 2 arms, 3 legs
	char materialtype;//0 wood, 1 stone, 2 iron, 3 steel
	float armorvalue;
}armor;