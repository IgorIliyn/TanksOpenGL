#include "EnemyTank.h"

EnemyTank::EnemyTank():BaseTank(T_LITE)
{
	tX         = 0.f;
	tY         = 0.f;
	tSpeed     = 1.f;
	tHealth    = 2.f;
	tDirection = D_DOWN;
	//tType      = T_LITE;
	LoadTextures();
}

EnemyTank::~EnemyTank()
{
}

void EnemyTank::Draw()
{
	glBindTexture(GL_TEXTURE_2D, tTextures[tType-1]);
	glBegin(GL_QUADS);

	if (tDirection == D_UP)
	{
		glTexCoord2f(0.0f, tY1_4); glVertex2f(tX, tY + tTextureSize);
		glTexCoord2f(0.0f, tY2_3); glVertex2f(tX, tY);
		glTexCoord2f(1.0f, tY2_3); glVertex2f(tX + tTextureSize, tY);
		glTexCoord2f(1.0f, tY1_4); glVertex2f(tX + tTextureSize, tY + tTextureSize);
	}
	if (tDirection == D_DOWN)
	{
		glTexCoord2f(0.0f, tY1_4); glVertex2f(tX + tTextureSize, tY);
		glTexCoord2f(0.0f, tY2_3); glVertex2f(tX + tTextureSize, tY + tTextureSize);
		glTexCoord2f(1.0f, tY2_3); glVertex2f(tX, tY + tTextureSize);
		glTexCoord2f(1.0f, tY1_4); glVertex2f(tX, tY);
	}
	if (tDirection == D_LEFT)
	{
		glTexCoord2f(0.0f, tY1_4); glVertex2f(tX + tTextureSize, tY + tTextureSize);
		glTexCoord2f(0.0f, tY2_3); glVertex2f(tX, tY + tTextureSize);
		glTexCoord2f(1.0f, tY2_3); glVertex2f(tX, tY);
		glTexCoord2f(1.0f, tY1_4); glVertex2f(tX + tTextureSize, tY);
	}
	if (tDirection == D_RIGHT)
	{
		glTexCoord2f(0.0f, tY1_4); glVertex2f(tX, tY);
		glTexCoord2f(0.0f, tY2_3); glVertex2f(tX + tTextureSize, tY);
		glTexCoord2f(1.0f, tY2_3); glVertex2f(tX + tTextureSize, tY + tTextureSize);
		glTexCoord2f(1.0f, tY1_4); glVertex2f(tX, tY + tTextureSize);
	}
	glEnd();
}

void EnemyTank::LoadTextures()
{
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("source/tankLite.bmp"),
					*texture2 = auxDIBImageLoadA("source/tankMiddle.bmp"),
					*texture3 = auxDIBImageLoadA("source/tankMiddleUp.bmp"),
					*texture4 = auxDIBImageLoadA("source/tankHeavy.bmp");
	glGenTextures(4, &tTextures[0]);
	glBindTexture(GL_TEXTURE_2D, tTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	glBindTexture(GL_TEXTURE_2D, tTextures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);

	glBindTexture(GL_TEXTURE_2D, tTextures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture3->data);

	glBindTexture(GL_TEXTURE_2D, tTextures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture4->sizeX, texture4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture4->data);
}