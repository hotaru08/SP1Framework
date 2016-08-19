#include "Npc.h"

void Npc()
{
	for (int i = 0; i < npcNum; i++)
	{
		switch (i)
		{
		case 0:
			_NPC[0].m_cLocation.X = 10;
			_NPC[0].m_cLocation.Y = 10;
			_NPC[0].str1 = "ENVY : I  wish I had PRIDE popularity, I think it would be great to have so much attention from everyone. I also want to be able to eat as much as GLUTTONY and not get fat after so much food...But I would want SLOTHs ability to just laze around because I am always so stressed all the time!!";
			_NPC[0].str2 = "ENVY : Go away, you have nothing i want.";
			_NPC[0].talked = false;
			break;

		case 1:
			_NPC[1].m_cLocation.X = 15;
			_NPC[1].m_cLocation.Y = 10;
			_NPC[1].str1 = "SLOTH : I had always been lazy and took the chance to slack off whenever I had the chance to, or in some cases, procrastinating to do my Ruby programming and wait until the day of the deadline. Maybe I should also try to work my way out of this labyrinth… Right after this nap...";
			_NPC[1].str2 = "SLOTH : Zzzz...";
			_NPC[1].talked = false;
			break;

		/*case 2:
			_NPC[2].m_cLocation.X = 20;
			_NPC[2].m_cLocation.Y = 10;
			_NPC[2].str1 = "GREED : I always liked to have many things to myself, especially my hard-earned money $$$. I never liked to share my own possessions, even if it’s just a few cents. My measly income of $22.5k/month isn’t going to let me live a comfortable life.";
			_NPC[2].str2 = "GREED : Any more information about me is gonna cost you $$$.";
			_NPC[2].talked = false;
			break;*/
		}
	}

}