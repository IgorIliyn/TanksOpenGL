#include "Menu.h"


eMainMenuState    Menu::main_menuState;
eNewMenuState     Menu::new_menuState;
eContinueState    Menu::continue_menuState;
eLoadMenuState    Menu::load_menuState;
eSaveMenuState    Menu::save_menuState;
eExitState        Menu::exit_menuState;

bool Menu::mainActive;
bool Menu::newActive;
bool Menu::continueActive;
bool Menu::loadActive;
bool Menu::saveActive;
bool Menu::exitActive;

Menu::Menu()
{

}
Menu::Menu(int w, int h)
{
	WINDOW_WIDTH        = w;
	WINDOW_HEIGHT       = h;
	mainActive          = true;
	newActive           = false;
	continueActive      = false;
	loadActive          = false;
	saveActive          = false; 
	exitActive          = false; 
	main_menuState      = MS_START_NEW_ACTIVE;
	new_menuState       = NS_NO;
	continue_menuState  = CS_NO;
	load_menuState      = LS_LEVEL1;
	save_menuState      = SS_SAVED;
	exit_menuState      = ES_NO;
	LoadTextures();
}
Menu::~Menu()
{

}

void Menu::LoadTextures()
{
	AUX_RGBImageRec *gtexture1 = auxDIBImageLoadA("source/New_game_active.bmp"),
					*gtexture2 = auxDIBImageLoadA("source/Continue_active.bmp"),
					*gtexture3 = auxDIBImageLoadA("source/Load_active.bmp"),
					*gtexture4 = auxDIBImageLoadA("source/Save_active.bmp"),
					*gtexture5 = auxDIBImageLoadA("source/Exit_active.bmp");

	AUX_RGBImageRec	*ntexture1 = auxDIBImageLoadA("source/StartNewGame_no_active.bmp"),
					*ntexture2 = auxDIBImageLoadA("source/StartNewGame_yes_active.bmp");

	AUX_RGBImageRec *ctexture1 = auxDIBImageLoadA("source/Continue_no_active.bmp"),
					*ctexture2 = auxDIBImageLoadA("source/Continue_yes_active.bmp");

	AUX_RGBImageRec *ltexture1 = auxDIBImageLoadA("source/Load_1_active.bmp"),
					*ltexture2 = auxDIBImageLoadA("source/Load_2_active.bmp"),
					*ltexture3 = auxDIBImageLoadA("source/Load_3_active.bmp"),
					*ltexture4 = auxDIBImageLoadA("source/Load_4_active.bmp"),		
					*ltexture5 = auxDIBImageLoadA("source/Load_5_active.bmp"),
					*ltexture6 = auxDIBImageLoadA("source/Load_6_active.bmp"),
					*ltexture7 = auxDIBImageLoadA("source/Load_7_active.bmp"),
					*ltexture8 = auxDIBImageLoadA("source/Load_8_active.bmp"),
					*ltexture9 = auxDIBImageLoadA("source/Load_9_active.bmp"),
					*ltexture10 = auxDIBImageLoadA("source/Load_10_active.bmp"),
					*ltexture11 = auxDIBImageLoadA("source/Load_11_active.bmp"),
					*ltexture12 = auxDIBImageLoadA("source/Load_12_active.bmp"),
					*ltexture13 = auxDIBImageLoadA("source/Load_13_active.bmp"),
					*ltexture14 = auxDIBImageLoadA("source/Load_14_active.bmp"),
					*ltexture15 = auxDIBImageLoadA("source/Load_15_active.bmp"),
					*ltexture16 = auxDIBImageLoadA("source/Load_16_active.bmp"),
					*ltexture17 = auxDIBImageLoadA("source/Load_17_active.bmp"),
					*ltexture18 = auxDIBImageLoadA("source/Load_18_active.bmp");

	AUX_RGBImageRec	*etexture1 = auxDIBImageLoadA("source/ExitGame_no_active.bmp"),
					*etexture2 = auxDIBImageLoadA("source/ExitGame_yes_active.bmp");


	//LOAD General Textures
	glGenTextures(5, &general_textures[0]);
	glBindTexture(GL_TEXTURE_2D, general_textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, gtexture1->sizeX, gtexture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, gtexture1->data);

	glBindTexture(GL_TEXTURE_2D, general_textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, gtexture2->sizeX, gtexture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, gtexture2->data);
	
	glBindTexture(GL_TEXTURE_2D, general_textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, gtexture3->sizeX, gtexture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, gtexture3->data);
	
	glBindTexture(GL_TEXTURE_2D, general_textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, gtexture4->sizeX, gtexture4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, gtexture4->data);
	
	glBindTexture(GL_TEXTURE_2D, general_textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, gtexture5->sizeX, gtexture5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, gtexture5->data);
	

	//LOAD New textures
	glGenTextures(2, &new_textures[0]);
	glBindTexture(GL_TEXTURE_2D, new_textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ntexture1->sizeX, ntexture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ntexture1->data);
	
	glBindTexture(GL_TEXTURE_2D, new_textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ntexture2->sizeX, ntexture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ntexture2->data);
	

	//LOAD Continue textures
	glGenTextures(2, &continue_textures[0]);
	glBindTexture(GL_TEXTURE_2D, continue_textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ctexture1->sizeX, ctexture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ctexture1->data);

	glBindTexture(GL_TEXTURE_2D, continue_textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ctexture2->sizeX, ctexture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ctexture2->data);


	//LOAD load Textures
	glGenTextures(18, &load_textures[0]);
	glBindTexture(GL_TEXTURE_2D, load_textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture1->sizeX, ltexture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture1->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture2->sizeX, ltexture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture2->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture3->sizeX, ltexture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture3->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture4->sizeX, ltexture4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture4->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture5->sizeX, ltexture5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture5->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture6->sizeX, ltexture6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture6->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture7->sizeX, ltexture7->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture7->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture8->sizeX, ltexture8->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture8->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture9->sizeX, ltexture9->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture9->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[9]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture10->sizeX, ltexture10->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture10->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[10]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture11->sizeX, ltexture11->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture11->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[11]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture12->sizeX, ltexture12->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture12->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[12]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture13->sizeX, ltexture13->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture13->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[13]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture14->sizeX, ltexture14->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture14->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[14]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture15->sizeX, ltexture15->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture15->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[15]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture16->sizeX, ltexture16->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture16->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[16]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture17->sizeX, ltexture17->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture17->data);

	glBindTexture(GL_TEXTURE_2D, load_textures[17]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ltexture18->sizeX, ltexture18->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ltexture18->data);



	//LOAD Exit textures
	glGenTextures(2, &exit_textures[0]);
	glBindTexture(GL_TEXTURE_2D, exit_textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, etexture1->sizeX, etexture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, etexture1->data);

	glBindTexture(GL_TEXTURE_2D, exit_textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, etexture2->sizeX, etexture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, etexture2->data);
}

void Menu::menuDraw()
{
	if (mainActive)
	{
		glBindTexture(GL_TEXTURE_2D, general_textures[main_menuState]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex2f(0.f, WINDOW_HEIGHT);
		glTexCoord2f(0.f, 1.f); glVertex2f(0.f, 0.f);
		glTexCoord2f(1.f, 1.f); glVertex2f(WINDOW_WIDTH, 0.f);
		glTexCoord2f(1.f, 0.f); glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		glEnd();
	}
	if (newActive)
	{
		glBindTexture(GL_TEXTURE_2D, new_textures[new_menuState]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex2f(0.f, WINDOW_HEIGHT);
		glTexCoord2f(0.f, 1.f); glVertex2f(0.f, 0.f);
		glTexCoord2f(1.f, 1.f); glVertex2f(WINDOW_WIDTH, 0.f);
		glTexCoord2f(1.f, 0.f); glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		glEnd();
	}
	if (continueActive)
	{
		glBindTexture(GL_TEXTURE_2D, continue_textures[continue_menuState]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex2f(0.f, WINDOW_HEIGHT);
		glTexCoord2f(0.f, 1.f); glVertex2f(0.f, 0.f);
		glTexCoord2f(1.f, 1.f); glVertex2f(WINDOW_WIDTH, 0.f);
		glTexCoord2f(1.f, 0.f); glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		glEnd();
	}
	if (loadActive)
	{
		glBindTexture(GL_TEXTURE_2D, load_textures[load_menuState]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex2f(0.f, WINDOW_HEIGHT);
		glTexCoord2f(0.f, 1.f); glVertex2f(0.f, 0.f);
		glTexCoord2f(1.f, 1.f); glVertex2f(WINDOW_WIDTH, 0.f);
		glTexCoord2f(1.f, 0.f); glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		glEnd();
	}
	if (exitActive)
	{
		glBindTexture(GL_TEXTURE_2D, exit_textures[exit_menuState]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex2f(0.f, WINDOW_HEIGHT);
		glTexCoord2f(0.f, 1.f); glVertex2f(0.f, 0.f);
		glTexCoord2f(1.f, 1.f); glVertex2f(WINDOW_WIDTH, 0.f);
		glTexCoord2f(1.f, 0.f); glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		glEnd();
	}
}

void Menu::incMainMenuState()
{
	if (main_menuState != MS_EXIT_ACTIVE)
	{
		switch(main_menuState)
		{
		case MS_START_NEW_ACTIVE:
			main_menuState = MS_CONTINUE_ACTIVE;
			break;
		case MS_CONTINUE_ACTIVE:
			main_menuState = MS_LOAD_ACTIVE;
			break;
		case MS_LOAD_ACTIVE:
			main_menuState = MS_SAVE_ACTIVE;
			break;
		case MS_SAVE_ACTIVE:
			main_menuState = MS_EXIT_ACTIVE;
			break;
		}
	}
}

void Menu::decMainMenuState()
{
	if (main_menuState != MS_START_NEW_ACTIVE)
	{
		switch(main_menuState)
		{
		case MS_CONTINUE_ACTIVE:
			main_menuState = MS_START_NEW_ACTIVE;
			break;
		case MS_LOAD_ACTIVE:
			main_menuState = MS_CONTINUE_ACTIVE;
			break;
		case MS_SAVE_ACTIVE:
			main_menuState = MS_LOAD_ACTIVE;
			break;
		case MS_EXIT_ACTIVE:
			main_menuState = MS_SAVE_ACTIVE;
			break;
		}
	}
}

void Menu::incNewMenuState()    
{
	if (new_menuState != NS_NO)
	{
		new_menuState = NS_NO;
	}
}

void Menu::decNewMenuState()
{
	if (new_menuState != NS_YES)
	{
		new_menuState = NS_YES;
	}
}

void Menu::incContinueMenuState()    
{
	if (continue_menuState != CS_NO)
	{
		continue_menuState = CS_NO;
	}
}

void Menu::decContinueMenuState()
{
	if (continue_menuState != CS_YES)
	{
		continue_menuState = CS_YES;
	}
}

void Menu::incLoadMenuState()    
{
	if (load_menuState != LS_LEVEL18)
	{
		switch(load_menuState)
		{
		case LS_LEVEL1:
			load_menuState = LS_LEVEL2;
			break;
		case LS_LEVEL2:
			load_menuState = LS_LEVEL3;
			break;
		case LS_LEVEL3:
			load_menuState = LS_LEVEL4;
			break;
		case LS_LEVEL4:
			load_menuState = LS_LEVEL5;
			break;
		case LS_LEVEL5:
			load_menuState = LS_LEVEL6;
			break;
		case LS_LEVEL6:
			load_menuState = LS_LEVEL7;
			break;
		case LS_LEVEL7:
			load_menuState = LS_LEVEL8;
			break;
		case LS_LEVEL8:
			load_menuState = LS_LEVEL9;
			break;
		case LS_LEVEL9:
			load_menuState = LS_LEVEL10;
			break;
		case LS_LEVEL10:
			load_menuState = LS_LEVEL11;
			break;
		case LS_LEVEL11:
			load_menuState = LS_LEVEL12;
			break;
		case LS_LEVEL12:
			load_menuState = LS_LEVEL13;
			break;
		case LS_LEVEL13:
			load_menuState = LS_LEVEL14;
			break;
		case LS_LEVEL14:
			load_menuState = LS_LEVEL15;
			break;
		case LS_LEVEL15:
			load_menuState = LS_LEVEL16;
			break;
		case LS_LEVEL16:
			load_menuState = LS_LEVEL17;
			break;
		case LS_LEVEL17:
			load_menuState = LS_LEVEL18;
			break;
		}
	}
}

void Menu::decLoadMenuState()
{
	if (load_menuState != LS_LEVEL1)
	{
		switch(load_menuState)
		{
		case LS_LEVEL18:
			load_menuState = LS_LEVEL17;
			break;
		case LS_LEVEL17:
			load_menuState = LS_LEVEL16;
			break;
		case LS_LEVEL16:
			load_menuState = LS_LEVEL15;
			break;
		case LS_LEVEL15:
			load_menuState = LS_LEVEL14;
			break;
		case LS_LEVEL14:
			load_menuState = LS_LEVEL13;
			break;
		case LS_LEVEL13:
			load_menuState = LS_LEVEL12;
			break;
		case LS_LEVEL12:
			load_menuState = LS_LEVEL11;
			break;
		case LS_LEVEL11:
			load_menuState = LS_LEVEL10;
			break;
		case LS_LEVEL10:
			load_menuState = LS_LEVEL9;
			break;
		case LS_LEVEL9:
			load_menuState = LS_LEVEL8;
			break;
		case LS_LEVEL8:
			load_menuState = LS_LEVEL7;
			break;
		case LS_LEVEL7:
			load_menuState = LS_LEVEL6;
			break;
		case LS_LEVEL6:
			load_menuState = LS_LEVEL5;
			break;
		case LS_LEVEL5:
			load_menuState = LS_LEVEL4;
			break;
		case LS_LEVEL4:
			load_menuState = LS_LEVEL3;
			break;
		case LS_LEVEL3:
			load_menuState = LS_LEVEL2;
			break;
		case LS_LEVEL2:
			load_menuState = LS_LEVEL1;
			break;
		}
	}
}

void Menu::incExitMenuState()    
{
	if (exit_menuState == ES_YES)
	{
		exit_menuState = ES_NO;
	}
}

void Menu::decExitMenuState()
{
	if (exit_menuState == ES_NO)
	{
		exit_menuState = ES_YES;
	}
}

