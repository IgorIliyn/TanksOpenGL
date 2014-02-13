#pragma  once
#include "Headers.h"

class BaseTank{

public:

	//Constructors
	BaseTank(eType type = T_UNKNOWN);
	virtual ~BaseTank();
	
protected:

	//Variables
	int     tId;
	GLfloat tDistance;
	GLfloat tX;
	GLfloat tY;
	GLfloat tSpeed;
	GLfloat tHealth;
	GLfloat tTextureSize;
	//Texture coord//
	GLfloat tY1_4;
	GLfloat tY2_3;
	////////////////
	eType      tType;
	eDirection tDirection;

public:

	//Setters
	void setID(int i){tId = i;}
	void setDistance(int distance){tDistance = distance;}
	void setX(GLfloat x){tX = x;}
	void setY(GLfloat y){tY = y;}
	void setSpeed(GLfloat speed){tSpeed = speed;}
	void setHealth(GLfloat health){tHealth = health;}
	void setType(eType type){tType = type;}
	void setDirection(eDirection direction){tDirection = direction;}

	//Getters
	int getID(){return tId;}
	GLfloat    getDistance(){return tDistance;}
	GLfloat    getX(){return tX;}
	GLfloat    getY(){return tY;}
	GLfloat    getSpeed(){return tSpeed;}
	GLfloat    getHealth(){return tHealth;}
	eType      getType(){return tType;}
	eDirection getDirection(){return tDirection;}

	//Functions
	virtual void Draw() = 0;
	void Drive(eDirection direction);
	void decDistance(){tDistance--;}
};



