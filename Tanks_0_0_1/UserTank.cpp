#include "UserTank.h"

UserTank::UserTank():BaseTank(T_LITE)
{
	tX         = 0.f;
	tY         = 0.f;
	tSpeed     = 1.f;
	tHealth    = 3.f;
	tDirection = D_UP;
	//tType      = T_LITE;
	LoadTextures();
}

UserTank::~UserTank()
{
}

void UserTank::Draw()
{
	glBindTexture(GL_TEXTURE_2D, tTextures[tType-1]);
	glBegin(GL_QUADS);

	if (tDirection == D_UP && tHealth > 0)
	{
		glTexCoord2f(0.0f, tY1_4); glVertex2f(tX, tY + tTextureSize);
		glTexCoord2f(0.0f, tY2_3); glVertex2f(tX, tY);
		glTexCoord2f(1.0f, tY2_3); glVertex2f(tX + tTextureSize, tY);
		glTexCoord2f(1.0f, tY1_4); glVertex2f(tX + tTextureSize, tY + tTextureSize);
	}
	if (tDirection == D_DOWN && tHealth > 0)
	{
		glTexCoord2f(0.0f, tY1_4); glVertex2f(tX + tTextureSize, tY);
		glTexCoord2f(0.0f, tY2_3); glVertex2f(tX + tTextureSize, tY + tTextureSize);
		glTexCoord2f(1.0f, tY2_3); glVertex2f(tX, tY + tTextureSize);
		glTexCoord2f(1.0f, tY1_4); glVertex2f(tX, tY);
	}
	if (tDirection == D_LEFT && tHealth > 0)
	{
		glTexCoord2f(0.0f, tY1_4); glVertex2f(tX + tTextureSize, tY + tTextureSize);
		glTexCoord2f(0.0f, tY2_3); glVertex2f(tX, tY + tTextureSize);
		glTexCoord2f(1.0f, tY2_3); glVertex2f(tX, tY);
		glTexCoord2f(1.0f, tY1_4); glVertex2f(tX + tTextureSize, tY);
	}
	if (tDirection == D_RIGHT && tHealth > 0)
	{
		glTexCoord2f(0.0f, tY1_4); glVertex2f(tX, tY);
		glTexCoord2f(0.0f, tY2_3); glVertex2f(tX + tTextureSize, tY);
		glTexCoord2f(1.0f, tY2_3); glVertex2f(tX + tTextureSize, tY + tTextureSize);
		glTexCoord2f(1.0f, tY1_4); glVertex2f(tX, tY + tTextureSize);
	}
	glEnd();
}

void UserTank::LoadTextures()
{
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("source/uTankLite.bmp"),
					*texture2 = auxDIBImageLoadA("source/uTankMiddle.bmp"),
					*texture3 = auxDIBImageLoadA("source/uTankMiddleUp.bmp"),
					*texture4 = auxDIBImageLoadA("source/uTankHeavy.bmp");
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