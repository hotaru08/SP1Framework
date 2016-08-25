#include "blocks.h"
#include "pressureplate.h"

extern Console g_Console;

extern SGameChar g_block[blockNum];

void renderblocks()
{
	WORD charColor = 0x0E;

	for (int numberforblock= 0; numberforblock < blockNum; numberforblock++)
	{
		if (currentMap == Map1)
		{
			g_Console.writeToBuffer(g_block[0].m_cLocation, "#", charColor);
		}

		if (currentMap == Map2)
		{
			g_Console.writeToBuffer(g_block[1].m_cLocation, "#", charColor);
		}

		if (currentMap == Map3)
		{
			g_Console.writeToBuffer(g_block[2].m_cLocation, "#", charColor);
		}
	}
}
	

void blocks()
{
	COORD c = g_Console.getConsoleSize();

	//for (int number = 0; number < blockNum; number++)
	//{
	//	if (currentMap == Map1)
	//	{
	//		g_block[0].m_cLocation.X = 35;
	//		g_block[0].m_cLocation.Y = 7;
	//	}

	//	if (currentMap == Map2)
	//	{
	//		g_block[1].m_cLocation.X = 31;
	//		g_block[1].m_cLocation.Y = 15;
	//	}

	//	if (currentMap == Map3)
	//	{
	//		g_block[2].m_cLocation.X = 76;
	//		g_block[2].m_cLocation.Y = 10;
	//	}
	//}
}