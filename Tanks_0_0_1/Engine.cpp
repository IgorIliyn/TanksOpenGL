#include "Engine.h"
#include <windows.h>

eGameState              Engine::GAME_STATE = GS_MENU;
int                     Engine::loadstage  = 1;
char                    *Engine::lStage    = "Stage1";
bool                    Engine::press[5]   = {false,false,false,false,false};
bool                    Engine::userShot   = true;
bool                    Engine::endGame    = false;
ALLEGRO_SAMPLE          *Engine::tank_shot;
ALLEGRO_SAMPLE          *Engine::tank_reload;
ALLEGRO_SAMPLE          *Engine::t_menu_sound;
ALLEGRO_SAMPLE_INSTANCE *Engine::t_menu_sound_instance; 
ALLEGRO_SAMPLE          *Engine::back_music;
ALLEGRO_SAMPLE_INSTANCE *Engine::back_music_inst;
ALLEGRO_SAMPLE          *Engine::tank_driwe;	
ALLEGRO_SAMPLE          *Engine::tank_wait; 	
ALLEGRO_SAMPLE_INSTANCE *Engine::driwe_inst;
ALLEGRO_SAMPLE_INSTANCE *Engine::wait_inst;

Engine::Engine():WINDOW_WIDTH(800),WINDOW_HEIGHT(600)
{
	initGL();
	mapaObj     = Mapa();
	menuObj     = Menu(WINDOW_WIDTH,WINDOW_HEIGHT);
	settingsObj = Settings();
	TANKS[0]   = new UserTank();
	TANKS[0]->setX(480.f);
	TANKS[0]->setY(568.f);
	TANKS[0]->setID(0);
	TANKS[0]->setDirection(D_UP);
	TANKS[1] = new EnemyTank();
	TANKS[1]->setX(64.f);
	TANKS[1]->setID(1);
	TANKS[1]->setDirection(D_DOWN);
	TANKS[1]->setType(T_MIDDLE);
	TANKS[2] = new EnemyTank();
	TANKS[2]->setX(224.f);
	TANKS[2]->setID(2);
	TANKS[2]->setDirection(D_DOWN);
	TANKS[2]->setType(T_LITE);
	TANKS[3] = new EnemyTank();
	TANKS[3]->setX(384.f);
	TANKS[3]->setID(3);
	TANKS[3]->setDirection(D_DOWN);
	TANKS[3]->setType(T_HEAVY);
	TANKS[4] = new EnemyTank();
	TANKS[4]->setX(544.f);
	TANKS[4]->setID(4);
	TANKS[4]->setDirection(D_DOWN);
	TANKS[4]->setType(T_LITE);
	TANKS[5] = new EnemyTank();
	TANKS[5]->setX(704.f);
	TANKS[5]->setID(5);
	TANKS[5]->setDirection(D_DOWN);
	TANKS[5]->setType(T_MIDDLE_UP);
	bullets[0] = new Bullet();
	bullets[1] = new Bullet();
	bullets[2] = new Bullet();
	bullets[3] = new Bullet();
	bullets[4] = new Bullet();
	bullets[5] = new Bullet();
	al_init();
	al_init_acodec_addon();
	al_install_audio();
	al_reserve_samples(10);	
	Engine::back_music    = al_load_sample("source/back_music.wav");
	Engine::tank_driwe    = al_load_sample("source/tank_engine.WAV");
	Engine::tank_wait     = al_load_sample("source/tank_engine.WAV");
	Engine::tank_shot     = al_load_sample("source/shot.wav");
	Engine::tank_reload   = al_load_sample("source/reload.wav");
	Engine::t_menu_sound  = al_load_sample("source/SP0000.WAV");
	Engine::back_music_inst = al_create_sample_instance(Engine::back_music);
	Engine::t_menu_sound_instance = al_create_sample_instance(Engine::t_menu_sound);
	Engine::driwe_inst    = al_create_sample_instance(Engine::tank_driwe);
	Engine::wait_inst     = al_create_sample_instance(Engine::tank_wait);
	al_attach_sample_instance_to_mixer(Engine::driwe_inst,al_get_default_mixer());
	al_attach_sample_instance_to_mixer(Engine::wait_inst,al_get_default_mixer());
	al_attach_sample_instance_to_mixer(Engine::t_menu_sound_instance,al_get_default_mixer());
	al_attach_sample_instance_to_mixer(Engine::back_music_inst,al_get_default_mixer());
	al_set_sample_instance_playmode(Engine::t_menu_sound_instance,ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(Engine::back_music_inst,ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(Engine::driwe_inst,ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(Engine::wait_inst,ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(Engine::t_menu_sound_instance,0.7);
	al_set_sample_instance_gain(Engine::back_music_inst,0.7);
	al_set_sample_instance_gain(Engine::driwe_inst,0.5);
	al_set_sample_instance_gain(Engine::wait_inst,0.3);
	
}

Engine::~Engine()
{
	al_destroy_sample(Engine::back_music);
	al_destroy_sample(Engine::tank_driwe);
	al_destroy_sample(Engine::tank_wait);
	al_destroy_sample(Engine::tank_shot);
	al_destroy_sample(Engine::tank_reload);
	al_destroy_sample(Engine::t_menu_sound);
	al_destroy_sample_instance(t_menu_sound_instance);
	al_destroy_sample_instance(Engine::driwe_inst);
	al_destroy_sample_instance(Engine::wait_inst);
}

void Engine::initEngine()
{
	settingsObj.loadGame(genStage(loadstage));
	mapaObj.loadMap(settingsObj.stage_buffer);
	TANKS[0]->setX(480.f);
	TANKS[0]->setY(568.f);
	TANKS[0]->setHealth(3.f);
	TANKS[0]->setDirection(D_UP);
	TANKS[1]->setX(64.f);
	TANKS[1]->setY(0.f);
	TANKS[1]->setDirection(D_DOWN);
	TANKS[2]->setX(224.f);
	TANKS[2]->setY(0.f);
	TANKS[2]->setDirection(D_DOWN);
	TANKS[3]->setX(384.f);
	TANKS[3]->setY(0.f);
	TANKS[3]->setDirection(D_DOWN);
	TANKS[4]->setX(544.f);
	TANKS[4]->setY(0.f);
	TANKS[4]->setDirection(D_DOWN);
	TANKS[5]->setX(704.f);
	TANKS[5]->setY(0.f);
	TANKS[5]->setDirection(D_DOWN);
	bullets[0]->setActive(false);
	bullets[1]->setActive(false);
	bullets[2]->setActive(false);
	bullets[3]->setActive(false);
	bullets[4]->setActive(false);
	bullets[5]->setActive(false);
}

bool Engine::initGL()
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	t_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BF", NULL, NULL);
	if (!t_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(t_window);
	glfwSetErrorCallback(error_callback_engine);
	glfwSetKeyCallback(t_window, key_callback_main_menu);
	glfwSetWindowPos(t_window, 100, 100);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	return true;
}

void Engine::gameLoop()
{
	
	gameDraw();
}

void Engine::menuLoop()
{
	
	endGame = true;
	menuDraw();
}

void Engine::menuDraw()
{
	Sleep(25);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwGetFramebufferSize(t_window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//////////////////
	menuObj.menuDraw();
	//////////////////
	glfwSwapBuffers(t_window);
}

void Engine::gameDraw()
{
	Sleep(25);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwGetFramebufferSize(t_window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//////////////////
	mapaObj.drawMap();
	userAction();
	A_IAction();
	//////////////////
	glfwSwapBuffers(t_window);
	if (TANKS[0]->getHealth() <= 0)
	{
		GAME_STATE = GS_MENU;
		Sleep(3000);
	}
	
	
}

void Engine::runEngine()
{
	srand(time(NULL));
	while (!glfwWindowShouldClose(t_window))
	{
		glfwPollEvents();
		switch(GAME_STATE)
		{
		    case GS_INIT:
				initEngine();
				GAME_STATE = GS_GAME;
				break;
			case GS_MENU:
				menuLoop();
				break;
			case GS_GAME:
				gameLoop();
				break;
			case GS_EXIT:
				glfwSetWindowShouldClose(t_window,GL_TRUE);
				break;
		}
		Engine::musicControl();
	}
	glfwDestroyWindow(t_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Engine::gameStatus()
{
	if (TANKS[0]->getHealth() <= 0)
	{
		
	}
}

char *Engine::genStage(int stage)
{
	switch(stage)
	{
	case 1:
		lStage = "Stage1";
		break;
	case 2:
		lStage = "Stage2";
		break;
	case 3:
		lStage = "Stage3";
		break;
	case 4:
		lStage = "Stage4";
		break;
	case 5:
		lStage = "Stage5";
		break;
	case 6:
		lStage = "Stage6";
		break;
	case 7:
		lStage = "Stage7";
		break;
	case 8:
		lStage = "Stage8";
		break;
	case 9:
		lStage = "Stage9";
		break;
	case 10:
		lStage = "Stage10";
		break;
	case 11:
		lStage = "Stage11";
		break;
	case 12:
		lStage = "Stage12";
		break;
	case 13:
		lStage = "Stage13";
		break;
	case 14:
		lStage = "Stage14";
		break;
	case 15:
		lStage = "Stage15";
		break;
	case 16:
		lStage = "Stage16";
		break;
	case 17:
		lStage = "Stage17";
		break;
	case 18:
		lStage = "Stage18";
		break;
	}
	return lStage;
} 

void Engine::userAction()
{
	if (press[UP])
	{
		TANKS[0]->setDirection(D_UP);
	}else if (press[DOWN])
	{
		TANKS[0]->setDirection(D_DOWN);
	}else if (press[LEFT])
	{
		TANKS[0]->setDirection(D_LEFT);
	}else if (press[RIGHT])
	{
		TANKS[0]->setDirection(D_RIGHT);
	}
	if (freeWay(TANKS[0]))
	{
		if (press[UP])
		{
			TANKS[0]->Drive(D_UP);
		}else if (press[DOWN])
		{
			TANKS[0]->Drive(D_DOWN);
		}else if (press[LEFT])
		{
			TANKS[0]->Drive(D_LEFT);
		}else if (press[RIGHT])
		{
			TANKS[0]->Drive(D_RIGHT);
		}
	}
	for (int i = 0; i < 6; i++)
	{
		TANKS[i]->Draw();
	}
	bulletsAction(TANKS[0]);
}

void Engine::bulletsAction(BaseTank *TANK)
{
	if (!bullets[TANK->getID()]->getActive())
	{
		if (TANK->getID() == 0 && !userShot)
		{
			bullets[TANK->getID()]->shot(TANK);
		}
		if (TANK->getID() != 0)
		{
			bullets[TANK->getID()]->shot(TANK);
		}
		
	}else{
		if (TANK->getID() == 0)
		{
			if (userFly(bullets[TANK->getID()]) && TANK->getHealth() > 0)
			{
				bullets[TANK->getID()]->moveBullet();
				bullets[TANK->getID()]->drawBullet();
			}
		}else{
			if (freeFlyEnemy(bullets[TANK->getID()]) && TANK->getHealth() > 0)
			{
				bullets[TANK->getID()]->moveBullet();
				bullets[TANK->getID()]->drawBullet();
			}
		}
	}
}

bool Engine::freeWay(BaseTank *TANK)
{
	bool way = true;
	switch(TANK->getDirection())
	{
	case D_UP:
		if (TANK->getY() <= 0)
		{
			way = false;
			return way;
		}
		break;
	case D_DOWN:
		if (TANK->getY() >= WINDOW_HEIGHT - 32)
		{
			way = false;
			return way;
		}
		break;
	case D_LEFT:
		if (TANK->getX() <= 0)
		{
			way = false;
			return way;
		}
		break;
	case D_RIGHT:
		if (TANK->getX() >= WINDOW_WIDTH - 32)
		{
			way = false;
			return way;
		}
		break;
	}
	for (int i = 0; i < mapaObj.stage_obj.size(); i++)
	{
		switch(TANK->getDirection())
		{
		case D_UP:
			if (TANK->getY() <= mapaObj.stage_obj[i].getY() + 32 && mapaObj.stage_obj[i].getActive() &&
			  abs(mapaObj.stage_obj[i].getX() - TANK->getX()) < 32 && TANK->getY() + 32 > mapaObj.stage_obj[i].getY())
			{
				way = false;
				return way;
			}
			break;
		case D_DOWN:
			if (TANK->getY() + 32 >= mapaObj.stage_obj[i].getY() && mapaObj.stage_obj[i].getActive() &&
			  abs(mapaObj.stage_obj[i].getX() - TANK->getX()) < 32 && TANK->getY()  < mapaObj.stage_obj[i].getY() + 32)
			{
				way = false;
				return way;
			}
			break;
		case D_LEFT:
			if (TANK->getX() <= mapaObj.stage_obj[i].getX() + 32 && mapaObj.stage_obj[i].getActive() &&
				abs(mapaObj.stage_obj[i].getY() - TANK->getY()) < 32 && TANK->getX() + 32 > mapaObj.stage_obj[i].getX())
			{
				way = false;
				return way;
			}
			break;
		case D_RIGHT:
			if (TANK->getX() + 32 >= mapaObj.stage_obj[i].getX() && mapaObj.stage_obj[i].getActive() &&
				abs(mapaObj.stage_obj[i].getY() - TANK->getY()) < 32 && TANK->getX() < mapaObj.stage_obj[i].getX() + 32)
			{
				way = false;
				return way;
			}
			break;
		}
	}
	for (int i = 1; i < 6; i++)
	{
		if (TANK->getID() != TANKS[i]->getID())
		{
			switch(TANK->getDirection())
			{
			case D_UP:
				if (TANK->getY() <= TANKS[i]->getY() + 32 && 
					abs(TANKS[i]->getX() - TANK->getX()) < 32 && TANK->getY() + 32 > TANKS[i]->getY())
				{
					way = false;
					return way;
				}
				break;
			case D_DOWN:
				if (TANK->getY() + 32 >=TANKS[i]->getY() && 
					abs(TANKS[i]->getX() - TANK->getX()) < 32 && TANK->getY()  < TANKS[i]->getY() + 32)
				{
					way = false;
					return way;
				}
				break;
			case D_LEFT:
				if (TANK->getX() <= TANKS[i]->getX() + 32 &&
					abs(TANKS[i]->getY() - TANK->getY()) < 32 && TANK->getX() + 32 > TANKS[i]->getX())
				{
					way = false;
					return way;
				}
				break;
			case D_RIGHT:
				if (TANK->getX() + 32 >= TANKS[i]->getX() &&
					abs(TANKS[i]->getY() - TANK->getY()) < 32 && TANK->getX() < TANKS[i]->getX() + 32)
				{
					way = false;
					return way;
				}
				break;
			}
		}
	}
	if (TANK->getID() != 0)
	{
		for (int i = 1; i < 6; i++)
		{
			switch(TANK->getDirection())
			{
			case D_UP:
				if (TANK->getY() <= TANKS[0]->getY() + 32 && TANKS[0]->getHealth() > 0 &&
					abs(TANKS[0]->getX() - TANK->getX()) < 32 && TANK->getY() + 31 > TANKS[0]->getY())
				{
					way = false;
					return way;
				}
				break;
			case D_DOWN:
				if (TANK->getY() + 32 >=TANKS[0]->getY() &&  TANKS[0]->getHealth() > 0 &&
					abs(TANKS[0]->getX() - TANK->getX()) < 32 && TANK->getY()  < TANKS[0]->getY() + 31)
				{
					way = false;
					return way;
				}
				break;
			case D_LEFT:
				if (TANK->getX() <= TANKS[0]->getX() + 32 && TANKS[0]->getHealth() > 0 &&
					abs(TANKS[0]->getY() - TANK->getY()) < 32 && TANK->getX() + 31 > TANKS[0]->getX())
				{
					way = false;
					return way;
				}
				break;
			case D_RIGHT:
				if (TANK->getX() + 32 >= TANKS[0]->getX() && TANKS[0]->getHealth() > 0 &&
					abs(TANKS[0]->getY() - TANK->getY()) < 32 && TANK->getX() < TANKS[0]->getX() + 31)
				{
					way = false;
					return way;
				}
				break;
			}
		}
	}
	return way;
}

bool Engine::freeFlyEnemy(Bullet *bullet)
{
	bool fly = true;
	switch(bullet->getDirection())
	{
	case D_UP:
		if (bullet->getY() <= 0)
		{
			bullet->setActive(false);
			return !fly;
		}
		break;
	case D_DOWN:
		if (bullet->getY() >= WINDOW_HEIGHT - 8)
		{
			bullet->setActive(false);
			return !fly;
		}
		break;
	case D_LEFT:
		if (bullet->getX() <= 0)
		{
			bullet->setActive(false);
				return !fly;
		}
		break;
	case D_RIGHT:
		if (bullet->getX() >= WINDOW_WIDTH - 8)
		{
			bullet->setActive(false);
			return !fly;
		}
		break;
	}
	for (int i = 0; i < mapaObj.stage_obj.size(); i++)
	{
		switch(bullet->getDirection())
		{
		case D_UP:
			if (bullet->getY() <= mapaObj.stage_obj[i].getY() + 32 && mapaObj.stage_obj[i].getActive() &&
				 bullet->getX() >= mapaObj.stage_obj[i].getX() - 7 && bullet->getX() <= mapaObj.stage_obj[i].getX() + 32 && 
				 bullet->getY() + 8 > mapaObj.stage_obj[i].getY())
			{
				switch (mapaObj.stage_obj[i].getState())
				{
				case BS_GOOD:
					mapaObj.stage_obj[i].setState(BS_HIT);
					break;
				case BS_HIT:
					mapaObj.stage_obj[i].setState(BS_DOUBLEHIT);
					break;
				case BS_DOUBLEHIT:
					mapaObj.stage_obj[i].setState(BS_DESTROYED);
					if (mapaObj.stage_obj[i].getType() != B_ARMOUR)
					{
						mapaObj.stage_obj[i].setActive(false);
					}
					break;
				}
				bullet->setActive(false);
				fly = !fly;
			}
			break;
		case D_DOWN:
			if (bullet->getY() + 8 >= mapaObj.stage_obj[i].getY() && mapaObj.stage_obj[i].getActive() &&
				 bullet->getX() >= mapaObj.stage_obj[i].getX() - 7 && bullet->getX() <= mapaObj.stage_obj[i].getX() + 32 &&
				 bullet->getY()  < mapaObj.stage_obj[i].getY() + 32)
			{
				switch (mapaObj.stage_obj[i].getState())
				{
				case BS_GOOD:
					mapaObj.stage_obj[i].setState(BS_HIT);
					break;
				case BS_HIT:
					mapaObj.stage_obj[i].setState(BS_DOUBLEHIT);
					break;
				case BS_DOUBLEHIT:
					mapaObj.stage_obj[i].setState(BS_DESTROYED);
					if (mapaObj.stage_obj[i].getType() != B_ARMOUR)
					{
						mapaObj.stage_obj[i].setActive(false);
					}
					break;
				}
				bullet->setActive(false);
				fly = !fly;
			}
			break;
		case D_LEFT:
			if (bullet->getX() <= mapaObj.stage_obj[i].getX() + 32 && mapaObj.stage_obj[i].getActive() &&
				bullet->getY() >= mapaObj.stage_obj[i].getY() - 7 && bullet->getY() <= mapaObj.stage_obj[i].getY() + 32 &&
				bullet->getX() + 8 > mapaObj.stage_obj[i].getX())
			{
				switch (mapaObj.stage_obj[i].getState())
				{
				case BS_GOOD:
					mapaObj.stage_obj[i].setState(BS_HIT);
					break;
				case BS_HIT:
					mapaObj.stage_obj[i].setState(BS_DOUBLEHIT);
					break;
				case BS_DOUBLEHIT:
					mapaObj.stage_obj[i].setState(BS_DESTROYED);
					if (mapaObj.stage_obj[i].getType() != B_ARMOUR)
					{
						mapaObj.stage_obj[i].setActive(false);
					}
					break;
				}
				bullet->setActive(false);
				fly = !fly;
			}
			break;
		case D_RIGHT:
			if (bullet->getX() + 8 >= mapaObj.stage_obj[i].getX() && mapaObj.stage_obj[i].getActive() &&
				bullet->getY() >= mapaObj.stage_obj[i].getY() - 7 && bullet->getY() <= mapaObj.stage_obj[i].getY() + 32 &&
				bullet->getX() < mapaObj.stage_obj[i].getX() + 32)
			{
				switch (mapaObj.stage_obj[i].getState())
				{
				case BS_GOOD:
					mapaObj.stage_obj[i].setState(BS_HIT);
					break;
				case BS_HIT:
					mapaObj.stage_obj[i].setState(BS_DOUBLEHIT);
					break;
				case BS_DOUBLEHIT:
					mapaObj.stage_obj[i].setState(BS_DESTROYED);
					if (mapaObj.stage_obj[i].getType() != B_ARMOUR)
					{
						mapaObj.stage_obj[i].setActive(false);
					}
					break;
				}
				bullet->setActive(false);
				fly = !fly;
			}
			break;
		}
	}
		switch(bullet->getDirection())
		{
		case D_UP:
			if (bullet->getY() <= TANKS[0]->getY() + 32 && abs(bullet->getY() - TANKS[0]->getY()) < 32 && TANKS[0]->getHealth() > 0 &&
				bullet->getX() >= TANKS[0]->getX() - 7 && bullet->getX() <= TANKS[0]->getX() + 32)
			{
				switch(bullet->getType())
				{
				case BT_LITE:
				case BT_MIDDLE:
					TANKS[0]->setHealth(TANKS[0]->getHealth() - 1.f);
					break;
				case BT_MIDDLE_UP:
				case BT_HEAVY:
					TANKS[0]->setHealth(TANKS[0]->getHealth() - 2.f);
						break;
				}
				bullet->setActive(false);
				fly = !fly;
			}
			break;
		case D_DOWN:
			if (bullet->getY() + 8 >= TANKS[0]->getY() && abs(bullet->getY() - TANKS[0]->getY()) < 32 && TANKS[0]->getHealth() > 0 &&
				bullet->getX() >= TANKS[0]->getX() - 7 && bullet->getX() <= TANKS[0]->getX() + 32)
			{
				switch(bullet->getType())
				{
				case BT_LITE:
				case BT_MIDDLE:
					TANKS[0]->setHealth(TANKS[0]->getHealth() - 1.f);
						break;
				case BT_MIDDLE_UP:
				case BT_HEAVY:
					TANKS[0]->setHealth(TANKS[0]->getHealth() - 2.f);
						break;
				}
				bullet->setActive(false);
				fly = !fly;
			}
			break;
		case D_LEFT:
			if (bullet->getX() <= TANKS[0]->getX() + 32 && abs(bullet->getX() - TANKS[0]->getX()) < 32 && TANKS[0]->getHealth() > 0 &&
				bullet->getY() >= TANKS[0]->getY() - 7 && bullet->getY() <= TANKS[0]->getY() + 32)
			{
				switch(bullet->getType())
				{
				case BT_LITE:
				case BT_MIDDLE:
					TANKS[0]->setHealth(TANKS[0]->getHealth() - 1.f);
						break;
				case BT_MIDDLE_UP:
				case BT_HEAVY:
					TANKS[0]->setHealth(TANKS[0]->getHealth() - 2.f);
						break;
				}
				bullet->setActive(false);
				fly = !fly;
			}
			break;
		case D_RIGHT:
			if (bullet->getX() + 8 >= TANKS[0]->getX() && abs(bullet->getX() - TANKS[0]->getX()) < 32 && TANKS[0]->getHealth() > 0 &&
				bullet->getY() >= TANKS[0]->getY() - 7 && bullet->getY() <= TANKS[0]->getY() + 32)
			{
				switch(bullet->getType())
				{
				case BT_LITE:
				case BT_MIDDLE:
					TANKS[0]->setHealth(TANKS[0]->getHealth() - 1.f);
						break;
				case BT_MIDDLE_UP:
				case BT_HEAVY:
					TANKS[0]->setHealth(TANKS[0]->getHealth() - 2.f);
						break;
				}
				bullet->setActive(false);
				fly = !fly;
			}
			break;
		}
	return fly;
}

bool Engine::userFly(Bullet *bullet)
{
	bool fly = true;
	switch(bullet->getDirection())
	{
	case D_UP:
		if (bullet->getY() <= 0)
		{
			bullet->setActive(false);
			userShot = true;
			return !fly;
		}
		break;
	case D_DOWN:
		if (bullet->getY() >= WINDOW_HEIGHT - 8)
		{
			bullet->setActive(false);
			userShot = true;
			return !fly;
		}
		break;
	case D_LEFT:
		if (bullet->getX() <= 0)
		{
			bullet->setActive(false);
			userShot = true;
			return !fly;
		}
		break;
	case D_RIGHT:
		if (bullet->getX() >= WINDOW_WIDTH - 8)
		{
			bullet->setActive(false);
			userShot = true;
			return !fly;
		}
		break;
	}
	for (int i = 0; i < mapaObj.stage_obj.size(); i++)
	{
		switch(bullet->getDirection())
		{
		case D_UP:
			if (bullet->getY() <= mapaObj.stage_obj[i].getY() + 32 && mapaObj.stage_obj[i].getActive() &&
				bullet->getX() >= mapaObj.stage_obj[i].getX() - 7 && bullet->getX() <= mapaObj.stage_obj[i].getX() + 32 && 
				bullet->getY() + 8 > mapaObj.stage_obj[i].getY())
			{
				switch (mapaObj.stage_obj[i].getState())
				{
				case BS_GOOD:
					mapaObj.stage_obj[i].setState(BS_HIT);
					break;
				case BS_HIT:
					mapaObj.stage_obj[i].setState(BS_DOUBLEHIT);
					break;
				case BS_DOUBLEHIT:
					mapaObj.stage_obj[i].setState(BS_DESTROYED);
					if (mapaObj.stage_obj[i].getType() != B_ARMOUR)
					{
						mapaObj.stage_obj[i].setActive(false);
					}
					break;
				}
				bullet->setActive(false);
				userShot = true;
				fly = !fly;
			}
			break;
		case D_DOWN:
			if (bullet->getY() + 8 >= mapaObj.stage_obj[i].getY() && mapaObj.stage_obj[i].getActive() &&
				bullet->getX() >= mapaObj.stage_obj[i].getX() - 7 && bullet->getX() <= mapaObj.stage_obj[i].getX() + 32 &&
				bullet->getY()  < mapaObj.stage_obj[i].getY() + 32)
			{
				switch (mapaObj.stage_obj[i].getState())
				{
				case BS_GOOD:
					mapaObj.stage_obj[i].setState(BS_HIT);
					break;
				case BS_HIT:
					mapaObj.stage_obj[i].setState(BS_DOUBLEHIT);
					break;
				case BS_DOUBLEHIT:
					mapaObj.stage_obj[i].setState(BS_DESTROYED);
					if (mapaObj.stage_obj[i].getType() != B_ARMOUR)
					{
						mapaObj.stage_obj[i].setActive(false);
					}
					break;
				}
				bullet->setActive(false);
				userShot = true;
				fly = !fly;
			}
			break;
		case D_LEFT:
			if (bullet->getX() <= mapaObj.stage_obj[i].getX() + 32 && mapaObj.stage_obj[i].getActive() &&
				bullet->getY() >= mapaObj.stage_obj[i].getY() - 7 && bullet->getY() <= mapaObj.stage_obj[i].getY() + 32 &&
				bullet->getX() + 8 > mapaObj.stage_obj[i].getX())
			{
				switch (mapaObj.stage_obj[i].getState())
				{
				case BS_GOOD:
					mapaObj.stage_obj[i].setState(BS_HIT);
					break;
				case BS_HIT:
					mapaObj.stage_obj[i].setState(BS_DOUBLEHIT);
					break;
				case BS_DOUBLEHIT:
					mapaObj.stage_obj[i].setState(BS_DESTROYED);
					if (mapaObj.stage_obj[i].getType() != B_ARMOUR)
					{
						mapaObj.stage_obj[i].setActive(false);
					}
					break;
				}
				bullet->setActive(false);
				userShot = true;
				fly = !fly;
			}
			break;
		case D_RIGHT:
			if (bullet->getX() + 8 >= mapaObj.stage_obj[i].getX() && mapaObj.stage_obj[i].getActive() &&
				bullet->getY() >= mapaObj.stage_obj[i].getY() - 7 && bullet->getY() <= mapaObj.stage_obj[i].getY() + 32 &&
				bullet->getX() < mapaObj.stage_obj[i].getX() + 32)
			{
				switch (mapaObj.stage_obj[i].getState())
				{
				case BS_GOOD:
					mapaObj.stage_obj[i].setState(BS_HIT);
					break;
				case BS_HIT:
					mapaObj.stage_obj[i].setState(BS_DOUBLEHIT);
					break;
				case BS_DOUBLEHIT:
					mapaObj.stage_obj[i].setState(BS_DESTROYED);
					if (mapaObj.stage_obj[i].getType() != B_ARMOUR)
					{
						mapaObj.stage_obj[i].setActive(false);
					}
					break;
				}
				bullet->setActive(false);
				userShot = true;
				fly = !fly;
			}
			break;
		}
	}
	for (int i = 1; i < 6; i++)
	{
		switch(bullet->getDirection())
		{
		case D_UP:
			if (bullet->getY() <= TANKS[i]->getY() + 32 && abs(bullet->getY() - TANKS[i]->getY()) < 32 && TANKS[i]->getHealth() > 0 &&
				bullet->getX() >= TANKS[i]->getX() - 7 && bullet->getX() <= TANKS[i]->getX() + 32)
			{
				switch(bullet->getType())
				{
				case BT_LITE:
				case BT_MIDDLE:
					TANKS[i]->setHealth(TANKS[i]->getHealth() - 1.f);
					break;
				case BT_MIDDLE_UP:
				case BT_HEAVY:
					TANKS[i]->setHealth(TANKS[i]->getHealth() - 2.f);
					break;
				}
				bullet->setActive(false);
				userShot = true;
				fly = !fly;
			}
			break;
		case D_DOWN:
			if (bullet->getY() + 8 >= TANKS[i]->getY() && abs(bullet->getY() - TANKS[i]->getY()) < 32 && TANKS[i]->getHealth() > 0 &&
				bullet->getX() >= TANKS[i]->getX() - 7 && bullet->getX() <= TANKS[i]->getX() + 32)
			{
				switch(bullet->getType())
				{
				case BT_LITE:
				case BT_MIDDLE:
					TANKS[i]->setHealth(TANKS[i]->getHealth() - 1.f);
					break;
				case BT_MIDDLE_UP:
				case BT_HEAVY:
					TANKS[i]->setHealth(TANKS[i]->getHealth() - 2.f);
					break;
				}
				bullet->setActive(false);
				userShot = true;
				fly = !fly;
			}
			break;
		case D_LEFT:
			if (bullet->getX() <= TANKS[i]->getX() + 32 && abs(bullet->getX() - TANKS[i]->getX()) < 32 && TANKS[i]->getHealth() > 0 &&
				bullet->getY() >= TANKS[i]->getY() - 7 && bullet->getY() <= TANKS[i]->getY() + 32)
			{
				switch(bullet->getType())
				{
				case BT_LITE:
				case BT_MIDDLE:
					TANKS[i]->setHealth(TANKS[i]->getHealth() - 1.f);
					break;
				case BT_MIDDLE_UP:
				case BT_HEAVY:
					TANKS[i]->setHealth(TANKS[i]->getHealth() - 2.f);
					break;
				}
				bullet->setActive(false);
				userShot = true;
				fly = !fly;
			}
			break;
		case D_RIGHT:
			if (bullet->getX() + 8 >= TANKS[i]->getX() && abs(bullet->getX() - TANKS[i]->getX()) < 32 && TANKS[i]->getHealth() > 0 &&
				bullet->getY() >= TANKS[i]->getY() - 7 && bullet->getY() <= TANKS[i]->getY() + 32)
			{
				switch(bullet->getType())
				{
				case BT_LITE:
				case BT_MIDDLE:
					TANKS[i]->setHealth(TANKS[i]->getHealth() - 1.f);
					break;
				case BT_MIDDLE_UP:
				case BT_HEAVY:
					TANKS[i]->setHealth(TANKS[i]->getHealth() - 2.f);
					break;
				}
				bullet->setActive(false);
				userShot = true;
				fly = !fly;
			}
			break;
		}
	}
	return fly;
}

void Engine::generationNewPosition(BaseTank *TANK)
{
	TANK->setY(0.f);
	switch(TANK->getType())
	{
	case T_LITE:
		TANK->setHealth(2.f);
		break;
	case T_MIDDLE:
		TANK->setHealth(3.f);
		break;
	case T_MIDDLE_UP:
		TANK->setHealth(4.f);
		break;
	case T_HEAVY:
		TANK->setHealth(5.f);
		break;
	}
	bool cicle = true;
	while (cicle)
	{
		int x = random_btwn(0, 768);
		for (int i = 0; i < 6; i++)
		{
			if (abs(x - TANKS[i]->getX()) < 32 && TANK->getID() != TANKS[i]->getID())//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			{
				cicle = false;
			}
		}	
		if (!cicle)
		{
			cicle = true;
		}else{
			TANK->setX(x);
			cicle = false;
		}
	}
}

void Engine::A_IAction()
{
	for (int i = 1; i < 6; i++)
	{
		if (freeWay(TANKS[i]) && TANKS[i]->getDistance() > 0)
		{
			A_IMove(TANKS[i]);
		}else{
			A_IChangeDD(TANKS[i]);
		}
		if (TANKS[i]->getHealth() <= 0)
		{
			generationNewPosition(TANKS[i]);
		}
		bulletsAction(TANKS[i]);
	}
}

void Engine::A_IMove(BaseTank *TANK)
{
	switch(TANK->getDirection())
	{
	case D_UP:
		TANK->Drive(D_UP);
		TANK->decDistance();
		break;
	case D_DOWN:
		TANK->Drive(D_DOWN);
		TANK->decDistance();
		break;
	case D_LEFT:
		TANK->Drive(D_LEFT);
		TANK->decDistance();
		break;
	case D_RIGHT:
		TANK->Drive(D_RIGHT);
		TANK->decDistance();
		break;
	}
}

void Engine::A_IChangeDD(BaseTank *TANK)
{
	if (TANK->getDistance() <= 0)
	{
		TANK->setDistance(random_btwn(100, 350));
		TANK->setDirection((eDirection)random_btwn(1, 5));
	}else{
		TANK->setDirection((eDirection)random_btwn(1, 5));
	}
}

int Engine::random_btwn( const int min, const int max)
{
	int range = max - min;
	return rand() % range + min;
}

void Engine::musicControl()
{
	switch(GAME_STATE)
	{
	case GS_MENU:
		al_stop_sample_instance(Engine::back_music_inst);
		al_play_sample_instance(Engine::t_menu_sound_instance);
		break;
	case GS_GAME:
		al_stop_sample_instance(Engine::t_menu_sound_instance);
		al_play_sample_instance(Engine::back_music_inst);
		break;
	}
	
}

void Engine::error_callback_engine(int error, const char* description)
{
	fputs(description, stderr);
}

void Engine::key_callback_main_menu(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (GAME_STATE)
	{
	case GS_GAME:
		if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		{
			press[UP] = true;
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		{
			press[DOWN] = true;
		}
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		{
			press[LEFT] = true;
		}
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		{
			press[RIGHT] = true;
		}
		if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
		{
			press[UP] = false;
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		{
			press[DOWN] = false;
		}
		if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		{
			press[LEFT] = false;
		}
		if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		{
			press[RIGHT] = false;
		}
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		{
			if (userShot)
			{
				al_play_sample(Engine::tank_shot,0.5,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				al_play_sample(Engine::tank_reload,0.8,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				userShot = false;
			}
		}
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			GAME_STATE = GS_MENU;
		}
		if (key == GLFW_KEY_ESCAPE)
		{
			if (action == GLFW_PRESS)
			{
				Menu::mainActive = true;
				Menu::loadActive = false;
				Menu::newActive  = false;
				Menu::main_menuState = MS_CONTINUE_ACTIVE;
			}
		}
		break;
	case GS_MENU:
		if (key == GLFW_KEY_UP)
		{
			if (action == GLFW_PRESS && Menu::mainActive)
			{
				Menu::decMainMenuState();
			}
			if(action == GLFW_PRESS && Menu::newActive)
			{
				Menu::decNewMenuState();
			}
			if(action == GLFW_PRESS && Menu::continueActive)
			{
				Menu::decContinueMenuState();
			}
			if(action == GLFW_PRESS && Menu::loadActive)
			{
				Menu::decLoadMenuState();
			}
			if (action == GLFW_REPEAT && Menu::loadActive)
			{
				Menu::decLoadMenuState();
			}
			if (action == GLFW_PRESS && Menu::saveActive)
			{
			}
			if (action == GLFW_PRESS && Menu::exitActive)
			{
				Menu::decExitMenuState();
			}
		}
		if (key == GLFW_KEY_DOWN)
		{
			if (action == GLFW_PRESS && Menu::mainActive)
			{
				Menu::incMainMenuState();
			}
			if(action == GLFW_PRESS && Menu::newActive)
			{
				Menu::incNewMenuState();
			}
			if(action == GLFW_PRESS && Menu::continueActive)
			{
				Menu::incContinueMenuState();
			}
			if(action == GLFW_PRESS && Menu::loadActive)
			{
				Menu::incLoadMenuState();
			}
			if(action == GLFW_REPEAT && Menu::loadActive)
			{
				Menu::incLoadMenuState();
			}
			if (action == GLFW_PRESS && Menu::saveActive)
			{
			}
			if (action == GLFW_PRESS && Menu::exitActive)
			{
				Menu::incExitMenuState();
			}
		}
		if (key == GLFW_KEY_ENTER)
		{
			if (action == GLFW_PRESS && Menu::mainActive)
			{
				switch(Menu::main_menuState)
				{
				case MS_START_NEW_ACTIVE:
					Menu::newActive = true;
					Menu::mainActive = false;
					break;
				case MS_CONTINUE_ACTIVE:
					Menu::continueActive = true;
					Menu::mainActive = false;
					break;
				case MS_LOAD_ACTIVE:
					Menu::loadActive = true;
					Menu::mainActive = false;
					break;
				case MS_SAVE_ACTIVE:
					break;
				case MS_EXIT_ACTIVE:
					Menu::exitActive = true;
					Menu::mainActive = false;
					break;
				}
			}else if (action == GLFW_PRESS && Menu::exitActive && Menu::exit_menuState == ES_YES)
			{
				GAME_STATE = GS_EXIT;
			}else if (action == GLFW_PRESS && Menu::exitActive && Menu::exit_menuState == ES_NO)
			{
				Menu::mainActive = true;
				Menu::exitActive = false;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL1)
			{
				loadstage = 1;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL2)
			{
				loadstage = 2;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL3)
			{
				loadstage = 3;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL4)
			{
				loadstage = 4;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL5)
			{
				loadstage = 5;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL6)
			{
				loadstage = 6;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL7)
			{
				loadstage = 7;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL8)
			{
				loadstage = 8;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL9)
			{
				loadstage = 9;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL10)
			{
				loadstage = 10;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL11)
			{
				loadstage = 11;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL12)
			{
				loadstage = 12;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL13)
			{
				loadstage = 13;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL14)
			{
				loadstage = 14;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL15)
			{
				loadstage = 15;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL16)
			{
				loadstage = 16;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL17)
			{
				loadstage = 17;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::loadActive && Menu::load_menuState == LS_LEVEL18)
			{
				loadstage = 18;
				GAME_STATE = GS_INIT;
			}else if (action == GLFW_PRESS && Menu::newActive && Menu::new_menuState == NS_NO)
			{
				Menu::mainActive = true;
				Menu::newActive  = false;
			}else if (action == GLFW_PRESS && Menu::newActive && Menu::new_menuState == NS_YES)
			{
				loadstage = 1;
				GAME_STATE = GS_INIT;
				Menu::new_menuState = NS_NO;
				//Load some game:)
			}else if (action == GLFW_PRESS && Menu::continueActive && Menu::continue_menuState == CS_NO)
			{
				Menu::mainActive = true;
				Menu::continueActive  = false;
			}else if (action == GLFW_PRESS && Menu::continueActive && Menu::continue_menuState == CS_YES)
			{
				//Load some game:)
			}
		}
		if (key == GLFW_KEY_ESCAPE)
		{
			if (action == GLFW_PRESS && Menu::loadActive)
			{
				Menu::mainActive = true;
				Menu::loadActive = false;
				Menu::load_menuState = LS_LEVEL1;
			}
		}
		break;
	}
	
}
