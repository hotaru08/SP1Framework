#include "game.h"
#include "Npc.h"

void timeDelay()
{
	//delay for dialogue
	for (int i = 0; i < npcNum; i++)
	{
		if (_NPC[i].talked == true)
		{
			_sleep(8000);
			_NPC[i].talked = false;
		}
	}
}