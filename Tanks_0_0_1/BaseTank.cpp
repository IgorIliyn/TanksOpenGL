#include "BaseTank.h"

BaseTank::BaseTank(eType type):
	tId(0),
	tDistance(0),
	tX(0.f),
	tY(0.f),
	tSpeed(0.f),
	tHealth(0.f),
	tTextureSize(32.f),
	tY1_4(0.75f),
	tY2_3(1.f),
	tType(type),
	tDirection(D_UNKNOWN)
{
}

BaseTank::~BaseTank()
{
}

void BaseTank::Drive(eDirection direction)
{
	tY1_4 += 0.25;
	tY2_3 += 0.25;
	if (tY1_4 >= 0.75)
	{
		tY1_4 = 0.0f;
		tY2_3 = 0.25f;
	}
	tDirection = direction;
	switch(direction)
	{
	case D_UP:
		tY -= tSpeed;
		break;
	case D_DOWN:
		tY += tSpeed;
		break;
	case D_LEFT:
		tX -= tSpeed;
		break;
	case D_RIGHT:
		tX += tSpeed;
		break;
	}
}