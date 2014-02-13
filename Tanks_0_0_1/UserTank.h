#pragma  once
#include "BaseTank.h"

class UserTank : public BaseTank{

public:

	//Constructors
	UserTank();
	~UserTank();

	//Variables
	GLuint tTextures[4];

	//Functions
	void Draw();

private:

	void LoadTextures();

};