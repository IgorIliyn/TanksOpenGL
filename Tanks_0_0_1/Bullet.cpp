#include "Bullet.h"


Bullet::Bullet():bType(BT_LITE), bSpeed(3.f), bX(0.f), bY(0.f), bDirection(D_UP), bActive(false), bTextureSize(8.f)
{
	loadTextures();
}

Bullet::~Bullet()
{

}

void Bullet::loadTextures()
{
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("source/bullet/lite_bullet.bmp"),
		            *texture2 = auxDIBImageLoadA("source/bullet/middle_bullet.bmp"),
		            *texture3 = auxDIBImageLoadA("source/bullet/middle_up_bullet.bmp"),
		            *texture4 = auxDIBImageLoadA("source/bullet/heavy_bullet.bmp");
	glGenTextures(4, &btextures[0]);
	glBindTexture(GL_TEXTURE_2D, btextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	glBindTexture(GL_TEXTURE_2D, btextures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);

	glBindTexture(GL_TEXTURE_2D, btextures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture3->data);

	glBindTexture(GL_TEXTURE_2D, btextures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture4->sizeX, texture4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture4->data);
}

void Bullet::drawBullet()
{
	glBindTexture(GL_TEXTURE_2D, btextures[bType]);
	glBegin(GL_QUADS);

	if (bDirection == D_UP && bActive)
	{
		glTexCoord2f(0.0f, 0.f); glVertex2f(bX, bY + bTextureSize);
		glTexCoord2f(0.0f, 1.f); glVertex2f(bX, bY);
		glTexCoord2f(1.0f, 1.f); glVertex2f(bX + bTextureSize, bY);
		glTexCoord2f(1.0f, 0.f); glVertex2f(bX + bTextureSize, bY + bTextureSize);
	}
	if (bDirection == D_DOWN && bActive)
	{
		glTexCoord2f(0.0f, 0.f); glVertex2f(bX + bTextureSize, bY);
		glTexCoord2f(0.0f, 1.f); glVertex2f(bX + bTextureSize, bY + bTextureSize);
		glTexCoord2f(1.0f, 1.f); glVertex2f(bX, bY + bTextureSize);
		glTexCoord2f(1.0f, 0.f); glVertex2f(bX, bY);
	}
	if (bDirection == D_LEFT && bActive)
	{
		glTexCoord2f(0.0f, 0.f); glVertex2f(bX + bTextureSize, bY + bTextureSize);
		glTexCoord2f(0.0f, 1.f); glVertex2f(bX, bY + bTextureSize);
		glTexCoord2f(1.0f, 1.f); glVertex2f(bX, bY);
		glTexCoord2f(1.0f, 0.f); glVertex2f(bX + bTextureSize, bY);
	}
	if (bDirection == D_RIGHT && bActive)
	{
		glTexCoord2f(0.0f, 0.f); glVertex2f(bX, bY);
		glTexCoord2f(0.0f, 1.f); glVertex2f(bX + bTextureSize, bY);
		glTexCoord2f(1.0f, 1.f); glVertex2f(bX + bTextureSize, bY + bTextureSize);
		glTexCoord2f(1.0f, 0.f); glVertex2f(bX, bY + bTextureSize);
	}
	glEnd();
}

void Bullet::moveBullet()
{
	if (bActive)
	{
		switch(bDirection)
		{
		case D_UP:
			bY -= bSpeed;
			break;
		case D_DOWN:
			bY += bSpeed;
			break;
		case D_LEFT:
			bX -= bSpeed;
			break;
		case D_RIGHT:
			bX += bSpeed;
			break;
		}
	}
}

void Bullet::setDemage(BaseTank *TANK)
{

}

void Bullet::shot(BaseTank *TANK)
{
	switch(TANK->getDirection())
	{
	case D_UP:
		bDirection = D_UP;
		bX = TANK->getX()+12;
		bY = TANK->getY()-bTextureSize;
		break;
	case D_DOWN:
		bDirection = D_DOWN;
		bX = TANK->getX()+12;
		bY = TANK->getY()+32;
		break;
	case D_LEFT:
		bDirection = D_LEFT;
		bX = TANK->getX()-bTextureSize;
		bY = TANK->getY()+12;
		break;
	case D_RIGHT:
		bDirection = D_RIGHT;
		bX = TANK->getX()+32;
		bY = TANK->getY()+12;
		break;
	}
	switch(TANK->getType())
	{
	case T_LITE:
		bType = BT_LITE;
		break;
	case T_MIDDLE:
		bType = BT_MIDDLE;
		break;
	case T_MIDDLE_UP:
		bType = BT_MIDDLE_UP;
		break;
	case T_HEAVY:
		bType = BT_HEAVY;
		break;
	}
	bActive = true;
}