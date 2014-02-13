#include "Settings.h"

Settings::Settings()
{
	stage_path = "stages.iig";
	save_path  = "saved.iig";
}

Settings::~Settings()
{
}

bool Settings::loadGame(char *_stage)
{
	char buf[128];
	stage_buffer.erase(stage_buffer.begin(), stage_buffer.end());
	strcpy(stage,_stage);
	
	ifstream read(stage_path);

	if (read)
	{
		while(!read.eof())
		{
			read >> buf;
			if (strcmp(buf,_stage) == 0)
			{
				int atribut = 0;
				for(int i = 0; atribut != -1; i++)
				{
					read >> atribut;
					if (atribut != -1)
					{
						stage_buffer.push_back(atribut);
					}
				}
			}
		}
	}else{
		cout << "Can't open file\n";
		return false;
	}
	
	read.close();

	return true;
}

void Settings::saveGame()
{

}