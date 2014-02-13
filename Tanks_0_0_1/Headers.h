#pragma  once

#include <glut.h>
#include <glaux.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro5.h>

using namespace std;

enum eBlockType        {B_FENCE = 0, B_BRICK, B_ARMOUR, B_BUSH};
enum eBulletType       {BT_LITE = 0, BT_MIDDLE, BT_MIDDLE_UP, BT_HEAVY};
enum eDirection        {D_UNKNOWN = 0, D_UP, D_DOWN, D_LEFT, D_RIGHT};
enum eType             {T_UNKNOWN = 0, T_LITE, T_MIDDLE, T_MIDDLE_UP, T_HEAVY};
enum eGameState        {GS_EXIT = 0, GS_GAME, GS_MENU, GS_INIT};
enum eMainMenuState    {MS_START_NEW_ACTIVE = 0, MS_CONTINUE_ACTIVE,
				        MS_LOAD_ACTIVE, MS_SAVE_ACTIVE, MS_EXIT_ACTIVE};
enum eLoadMenuState    {LS_LEVEL1 = 0,LS_LEVEL2 ,LS_LEVEL3 ,LS_LEVEL4 ,LS_LEVEL5 ,
					    LS_LEVEL6 ,LS_LEVEL7 ,LS_LEVEL8 ,LS_LEVEL9 , LS_LEVEL10 ,
					    LS_LEVEL11 ,LS_LEVEL12 ,LS_LEVEL13 ,LS_LEVEL14 ,LS_LEVEL15 ,
					    LS_LEVEL16 ,LS_LEVEL17 ,LS_LEVEL18 };
enum eSaveMenuState    {SS_SAVED};
enum eNewMenuState     {NS_NO = 0, NS_YES};
enum eContinueState    {CS_NO = 0, CS_YES};
enum eExitState        {ES_NO = 0, ES_YES};

enum eKeys             {UP = 0, DOWN, LEFT, RIGHT, SPASE}; 
enum eBlockState       {BS_GOOD = 0, BS_HIT, BS_DOUBLEHIT, BS_DESTROYED};