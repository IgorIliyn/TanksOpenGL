#pragma  once
#include "BaseTank.h"

class EnemyTank : public BaseTank{

public:

	//Constructors
	EnemyTank();
	~EnemyTank();

	//Variables
	GLuint tTextures[4];

	//Functions
	void Draw();

private:

	void LoadTextures();

};