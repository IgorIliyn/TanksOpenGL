#pragma  once

#include "Headers.h"
#include "Settings.h"

class Menu{

private:

	//Variables
	

	GLuint            general_textures[5];
	GLuint            new_textures[2];
	GLuint            continue_textures[2];
	GLuint            load_textures[18];
	GLuint            exit_textures[2];

	int               WINDOW_WIDTH;
	int               WINDOW_HEIGHT;

	//functions
	void LoadTextures();
	

public:

	static eMainMenuState    main_menuState;
	static eNewMenuState     new_menuState;
	static eContinueState    continue_menuState;
	static eLoadMenuState    load_menuState;
	static eSaveMenuState    save_menuState;
	static eExitState        exit_menuState;
	//Constructors
	Menu();
	Menu(int w, int h);
	~Menu();

	
	static bool mainActive;
	static bool newActive;
	static bool continueActive;
	static bool loadActive;
	static bool saveActive;
	static bool exitActive;
	
	//Getters

	
	//Functions
	static void incMainMenuState();    
	static void decMainMenuState();
	static void incNewMenuState();    
	static void decNewMenuState();
	static void incContinueMenuState();    
	static void decContinueMenuState();
	static void incLoadMenuState();    
	static void decLoadMenuState();
	static void incExitMenuState();    
	static void decExitMenuState();

	void menuDraw();

	
};