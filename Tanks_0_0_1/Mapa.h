#pragma  once 

#include "Headers.h"


class MapaObject{

private:

	//Variables
	eBlockType  type;
	eBlockState state;
	GLfloat     x_coord;
	GLfloat     y_coord;
	bool        active;

public:

	//Constructors
	MapaObject();
	~MapaObject();

	//Setters
	void setType(eBlockType b_type){type = b_type;}
	void setX(GLfloat x){x_coord = x;}
	void setY(GLfloat y){y_coord = y;}
	void setActive(bool b_active){active = b_active;}
	void setState(eBlockState bstate){state = bstate;}

	//Getters
	eBlockType  getType(){return type;}
	GLfloat     getX(){return x_coord;}
	GLfloat     getY(){return y_coord;}
	bool        getActive(){return active;}
	eBlockState getState(){return state;}

};

class Mapa{

public:

	//Constructors
	Mapa();
	~Mapa();

	//Variables
	vector<MapaObject> stage_obj;

	GLfloat     bY1_4;
	GLfloat     bY2_3;

	//Functions
	void loadMap(vector<int> stage_vector);
	void drawMap();

private:

	GLuint textures[4];

	void loadTextures();

};