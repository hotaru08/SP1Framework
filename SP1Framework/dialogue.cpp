#include "dialogue.h"
#include "Npc.h"

string dialogue(int tolerance)
{
	string toReturn;

	if (_NPC[0].talked == true)
	{
		switch (tolerance)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			toReturn = _NPC[0].str1;
			break;
		default:
			toReturn = _NPC[0].str2;
			break;
		}
	}

	if (_NPC[1].talked == true)
	{
		switch (tolerance)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			toReturn = _NPC[1].str1;
			break;
		default:
			toReturn = _NPC[1].str2;
			break;
		}
	}

	/*if (_NPC[2].talked == true)
	{
		switch (tolerance)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			toReturn = _NPC[2].str1;
			break;
		default:
			toReturn = _NPC[2].str2;
			break;
		}
	}*/


	return toReturn;
}