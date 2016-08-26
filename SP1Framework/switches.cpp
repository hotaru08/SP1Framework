#include "switches.h"

extern Console g_Console;
extern SGameChar g_sChar;
extern char maze[77][19];

void switches()
{
	COORD c = g_Console.getConsoleSize();

	bool on = false;

	//when character stands on switch
	if (currentMap == Map1)
	{
		if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '/')
		{
			on = true;
		}
	}

	if (currentMap == Map2)
	{
		if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '/')
		{
			on = true;
		}
	}

	if (currentMap == Map3)
	{
		if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '/')
		{
			on = true;
		}
	}

	if (on)
	{
		for (int y = 0; y < 19; y++)
		{
			c.Y = y;
			for (int x = 0; x < 77; x++)
			{

				if (maze[x][y] == 'X')
				{
					maze[x][y] = ' ';
				}
				c.X = x;
			}
		}
	}
}