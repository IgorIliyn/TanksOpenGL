#pragma  once

#include "Headers.h"
#include "Menu.h"
#include "Mapa.h"
#include "Settings.h"
#include "BaseTank.h"
#include "EnemyTank.h"
#include "UserTank.h"
#include "Bullet.h"

class Engine{

public:

	//Constructors
	Engine();
	~Engine();

	//Variables
	static ALLEGRO_SAMPLE          *t_menu_sound;
	static ALLEGRO_SAMPLE_INSTANCE *t_menu_sound_instance; 
	static ALLEGRO_SAMPLE          *back_music;
	static ALLEGRO_SAMPLE_INSTANCE *back_music_inst;
	static ALLEGRO_SAMPLE          *tank_driwe;	
	static ALLEGRO_SAMPLE          *tank_wait; 	
	static ALLEGRO_SAMPLE          *tank_shot;
	static ALLEGRO_SAMPLE          *tank_reload;
	static ALLEGRO_SAMPLE_INSTANCE *driwe_inst;
	static ALLEGRO_SAMPLE_INSTANCE *wait_inst;
	GLFWwindow                     *t_window;
	GLint                          WINDOW_WIDTH;
	GLint                          WINDOW_HEIGHT;
	Mapa                           mapaObj;
	Menu                           menuObj;
	Settings                       settingsObj;
	Bullet                         *bullets[6];
	static eGameState              GAME_STATE;
	static int                     loadstage;
	static char                    *lStage;
	static bool                    press[5];
	static bool                    userShot;
	static bool                    endGame;
	BaseTank                       *TANKS[6];

	//Functions
	void initEngine();
	void runEngine();

	static char *genStage(int stage);

	void gameLoop();
	void menuLoop();
	void menuDraw();
	void gameDraw();

	void userAction();
	void bulletsAction(BaseTank *TANK);
	bool freeWay(BaseTank *TANK);
	bool freeFlyEnemy(Bullet *bullet);
	bool userFly(Bullet *bullet);
	void A_IAction();
	void generationNewPosition(BaseTank *TANK);
	void A_IChangeDD(BaseTank *TANK);
	void A_IMove(BaseTank *TANK);
	int  random_btwn( const int min, const int max);
	static void musicControl();
	void gameStatus();

	static void error_callback_engine(int error, const char* description);
	static void key_callback_main_menu(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void key_callback_new_menu(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void key_callback_continue_menu(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void key_callback_load_menu(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void key_callback_exit_menu(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	bool initGL();
};