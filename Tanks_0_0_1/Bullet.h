#pragma  once
#include "Headers.h"
#include "BaseTank.h"
#include "Mapa.h"

class Bullet{

private:

	//Variables
	eBulletType bType;
	GLfloat     bSpeed;
	GLfloat     bX;
	GLfloat     bY;
	eDirection  bDirection;
	bool        bActive;
	GLuint      btextures[4];
 	GLfloat     bTextureSize;
	void loadTextures();

public:

	//Constructors
	Bullet();
	~Bullet();

	//Setters
	void setType(eBulletType type){bType = type;}
	void setSpeed(GLfloat speed){bSpeed = speed;}
	void setX(GLfloat x){bX = x;}
	void setY(GLfloat y){bY = y;}
	void setDirection(eDirection direction){bDirection = direction;}
	void setActive(bool active){bActive = active;}

	//Getters
	eBulletType getType(){return bType;}
	GLfloat     getSpeed(){return bSpeed;}
	GLfloat     getX(){return bX;}
	GLfloat     getY(){return bY;}
	eDirection  getDirection(){return bDirection;}
	bool        getActive(){return bActive;}

	//Functions
	void moveBullet();
	void setDemage(BaseTank *TANK);
	void drawBullet();
	void shot(BaseTank *TANK);
};