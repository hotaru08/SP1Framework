#include "pressureplate.h"
#include "game.h"

extern Console g_Console;
extern SGameChar g_sChar;
extern SGameChar g_block[blockNum];

const unsigned int plates = 2;
bool underpressure = false;

extern char maze[77][19];

void pressureplate()
{
	COORD c = g_Console.getConsoleSize();

	//for the pressure part of the plate
	//map 1 pressure plate
	/*if (currentMap == Map1)
	{*/
	for (int number = 0;number < blockNum;number++)
	if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == 'P')
	{
		underpressure = true;
	}
	else if (maze[g_block[number].m_cLocation.X][g_block[number].m_cLocation.Y] == 'P')
	{
		underpressure = true;
	}
	else
	{
		underpressure = false;
	}
	/*}*/

	////maps 2 pressure plate
	//if (currentMap == Map2)
	//{
	//	if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == 'P')
	//	{
	//		underpressure = true;
	//	}
	//	else if (maze[g_block[1].m_cLocation.X][g_block[1].m_cLocation.Y] == 'P')
	//	{
	//		underpressure = true;
	//	}
	//	else
	//	{
	//		underpressure = false;
	//	}
	//}

	////map 3 pressure plate
	//if (currentMap == Map3)
	//{
	//	if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == 'P')
	//	{
	//		underpressure = true;
	//	}
	//	else if (maze[g_block[2].m_cLocation.X][g_block[2].m_cLocation.Y] == 'P')
	//	{
	//		underpressure = true;
	////	}
	//	else
	//	{
	//		underpressure = false;
	//	}
	//}
	
	//when true
	if (underpressure)
	for (int y = 0; y < 19; y++)
	{
		c.Y = y;
		for (int x = 0; x < 77; x++)
		{
			if (maze[x][y] == 'T')
			{
				maze[x][y] = ' ';
			}
			else if (maze[x][y] == 'T' && !(underpressure))
			{
				maze[x][y] = 'T';
			}
			c.X = x;
		}
	}
	
}