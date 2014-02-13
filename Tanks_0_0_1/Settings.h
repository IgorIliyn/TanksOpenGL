#pragma once

#include "Headers.h"

class Settings{

public:

	//Variables
	char        stage[9];
	vector<int> stage_buffer;

private:

	char      *stage_path;  //Should be exist
	char      *save_path;   //Should be exist

public:

	//Constructors
	Settings();
	~Settings();

	//Functions
	bool loadGame(char *_stage);
	void saveGame();

};