#include "Mapa.h"

Mapa::Mapa():
bY1_4(0.f),
bY2_3(0.25f)
{
	loadTextures();
}
Mapa::~Mapa()
{

}

MapaObject::MapaObject():
type(B_FENCE), 
x_coord(0.f),
y_coord(0.f),
active(true),
state(BS_GOOD)
{
}

MapaObject::~MapaObject()
{
}

void Mapa::loadTextures()
{
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("source/blocks/fence.bmp"),
					*texture2 = auxDIBImageLoadA("source/blocks/brick.bmp"),
					*texture3 = auxDIBImageLoadA("source/blocks/armour_plating.bmp"),
					*texture4 = auxDIBImageLoadA("source/blocks/bush.bmp");
	glGenTextures(4, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture3->data);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture4->sizeX, texture4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture4->data);
}

void Mapa::loadMap(vector<int> stage_vector)
{
	stage_obj.erase(stage_obj.begin(), stage_obj.end());
	MapaObject temp = MapaObject();
	for (unsigned int i = 0, j = 0; j < stage_vector.size(); i++, j++)
	{
		switch(stage_vector[j])
		{
		case 0:
			temp.setType(B_FENCE);
			break;
		case 1:
			temp.setType(B_BRICK);
			break;
		case 2:
			temp.setType(B_ARMOUR);
			break;
		case 3:
			temp.setType(B_BUSH);
		}
		j++;
		temp.setX((GLfloat)stage_vector[j]);
		j++;
		temp.setY((GLfloat)stage_vector[j]);
		stage_obj.push_back(temp);
	}
}

void Mapa::drawMap()
{
	for (unsigned int i = 0; i < stage_obj.size(); i++)
	{
		switch(stage_obj[i].getState())
		{
		case BS_GOOD:
			bY1_4 = 0.f;
			bY2_3 = 0.25;
			break;
		case BS_HIT:
			bY1_4 = 0.25f;
			bY2_3 = 0.50;
			break;
		case BS_DOUBLEHIT:
			bY1_4 = 0.50f;
			bY2_3 = 0.75;
			break;
		case  BS_DESTROYED:
			bY1_4 = 0.75f;
			bY2_3 = 1.f;
			break;
		}
		switch(stage_obj[i].getType())
		{
		case B_FENCE:
			glBindTexture(GL_TEXTURE_2D, textures[B_FENCE]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.f, bY1_4); glVertex2f(stage_obj[i].getX(), stage_obj[i].getY() + 32);
			glTexCoord2f(0.f, bY2_3); glVertex2f(stage_obj[i].getX(), stage_obj[i].getY());
			glTexCoord2f(1.f, bY2_3); glVertex2f(stage_obj[i].getX() + 32, stage_obj[i].getY());
			glTexCoord2f(1.f, bY1_4); glVertex2f(stage_obj[i].getX() + 32, stage_obj[i].getY() + 32);
			glEnd();
			break;
		case B_BRICK:
			glBindTexture(GL_TEXTURE_2D, textures[B_BRICK]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.f, bY1_4); glVertex2f(stage_obj[i].getX(), stage_obj[i].getY() + 32);
			glTexCoord2f(0.f, bY2_3); glVertex2f(stage_obj[i].getX(), stage_obj[i].getY());
			glTexCoord2f(1.f, bY2_3); glVertex2f(stage_obj[i].getX() + 32, stage_obj[i].getY());
			glTexCoord2f(1.f, bY1_4); glVertex2f(stage_obj[i].getX() + 32, stage_obj[i].getY() + 32);
			glEnd();
			break;
		case B_ARMOUR:
			glBindTexture(GL_TEXTURE_2D, textures[B_ARMOUR]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.f, bY1_4); glVertex2f(stage_obj[i].getX(), stage_obj[i].getY() + 32);
			glTexCoord2f(0.f, bY2_3); glVertex2f(stage_obj[i].getX(), stage_obj[i].getY());
			glTexCoord2f(1.f, bY2_3); glVertex2f(stage_obj[i].getX() + 32, stage_obj[i].getY());
			glTexCoord2f(1.f, bY1_4); glVertex2f(stage_obj[i].getX() + 32, stage_obj[i].getY() + 32);
			glEnd();
			break;
		case B_BUSH:
			glBindTexture(GL_TEXTURE_2D, textures[B_BUSH]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.f, bY1_4); glVertex2f(stage_obj[i].getX(), stage_obj[i].getY() + 32);
			glTexCoord2f(0.f, bY2_3); glVertex2f(stage_obj[i].getX(), stage_obj[i].getY());
			glTexCoord2f(1.f, bY2_3); glVertex2f(stage_obj[i].getX() + 32, stage_obj[i].getY());
			glTexCoord2f(1.f, bY1_4); glVertex2f(stage_obj[i].getX() + 32, stage_obj[i].getY() + 32);
			glEnd();
			break;
		}
	}
}

