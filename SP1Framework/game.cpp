// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "dialogue.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

char maze[77][19];
EMAPS currentMap = Map1; 
double  g_dElapsedTime;
double g_dElapsedTimeSec;
int g_dElapsedTimeMin;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
SGameNPC _NPC[npcNum];
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
 Console g_Console(77, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;
	g_dElapsedTimeMin = 0;
	g_dElapsedTimeSec = 0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;
	PlaySound(TEXT("playMUSIC/Music/MainMenusnd.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    g_sChar.m_cLocation.X = 45;
    g_sChar.m_cLocation.Y = 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
	Npc();
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);

	g_abKeyPressed[K_SELECTUP] = isKeyPressed(0x57);
	g_abKeyPressed[K_SELECTDOWN] = isKeyPressed(0x53);

    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;
	timeDelay();

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
		case S_SPLASHSCREEN2 : splashScreenWait2(); // game logic for the splash screen (lea)
			break;
		case S_SPLASHSCREEN3: splashScreenWait3(); // game logic for the splash screen (credits)
			break;
		case S_SPLASHSCREEN4: splashScreenWait4(); // game logic for the splash screen (credits)
			break;
		case S_SELECTLEA: renderLeaderboardlogic(); //game logic for the leaderboard screen
			break;
		case S_SELECTCRE: renderCreditsLogic(); //game logic for the credits
			break;
		case S_SELECTMODE:  renderSelectmodeLogic();//game logic for the select mode
			break;
		case S_SELECTMODE2:  renderSelectmode2Logic();//game logic for the select mode
			break;
		case S_SELECTMODE3:  renderSelectmode3Logic();//game logic for the select mode
			break;
		case S_SELECTMODE4:  renderSelectmode4Logic();//game logic for the select mode
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
		case S_SPLASHSCREEN2 : renderSplashScreen2();
			break;
		case S_SPLASHSCREEN3: renderSplashScreen3();
			break;
		case S_SPLASHSCREEN4: renderSplashScreen4();
			break;
		case S_SELECTMODE: renderSelectmode();
			break;
		case S_SELECTMODE2: renderSelectmode2();
			break;
		case S_SELECTMODE3: renderSelectmode3();
			break;
		case S_SELECTMODE4: renderSelectmode4();
			break;
		case S_SELECTLEA: renderLeaderboard();
			break;
		case S_SELECTCRE: renderCredits();
			break;
        case S_GAME: renderGame();
            break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void setBounceTime(float delay)
{
	g_dBounceTime = g_dElapsedTime + delay;
}

void splashScreenWait()    //for the options on the splashscreen
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER]) // when enter go to select screen
	{
		setBounceTime(0.3);
		g_eGameState = S_SELECTMODE;
	}
	if (g_abKeyPressed[K_SELECTDOWN])
	{
		setBounceTime(0.3);
		g_eGameState = S_SPLASHSCREEN2;
	}
}

void splashScreenWait2()    //for the options on the splashscreen
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER]) // when enter go to select screen
	{
		setBounceTime(0.3);
		g_eGameState = S_SELECTLEA;
	}
	if (g_abKeyPressed[K_SELECTDOWN])
	{
		setBounceTime(0.3);
		g_eGameState = S_SPLASHSCREEN3;
	}
	if (g_abKeyPressed[K_SELECTUP])
	{
		setBounceTime(0.3);
		g_eGameState = S_SPLASHSCREEN;
	}
}

void splashScreenWait3()
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER]) // when enter go to select screen
	{
		setBounceTime(0.3);
		g_eGameState = S_SELECTCRE;
	}
	if (g_abKeyPressed[K_SELECTDOWN])
	{
		setBounceTime(0.3);
		g_eGameState = S_SPLASHSCREEN4;
	}
	if (g_abKeyPressed[K_SELECTUP])
	{
		setBounceTime(0.3);
		g_eGameState = S_SPLASHSCREEN2;
	}
}

void splashScreenWait4()
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER]) // when enter go to select screen
	{
		setBounceTime(0.3);
		g_bQuitGame = true;
	}
	if (g_abKeyPressed[K_SELECTUP])
	{
		setBounceTime(0.3);
		g_eGameState = S_SPLASHSCREEN3;
	}
}

void gameplay()         // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;
		if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '|')
		{
			g_sChar.m_cLocation.Y++;
		}
	}

	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.X--;
		bSomethingHappened = true;
		if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '|')
		{
			g_sChar.m_cLocation.X++;
		}
	}

	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.Y++;
		bSomethingHappened = true;
		if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '|')
		{
			g_sChar.m_cLocation.Y--;
		}
	}

	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.X++;
		bSomethingHappened = true;
		if (maze[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '|')
		{
			g_sChar.m_cLocation.X--;
		}
	}

	for (int i = 0; i < npcNum; i++)//loop 2 times
	{
		if (!(g_sChar.m_cLocation.X >(_NPC[i].m_cLocation.X) + 1) && !(g_sChar.m_cLocation.X < (_NPC[i].m_cLocation.X) - 1) && //check horizontal by 1 and vertical by 1
			!(g_sChar.m_cLocation.Y >(_NPC[i].m_cLocation.Y) + 1) && !(g_sChar.m_cLocation.Y < (_NPC[i].m_cLocation.Y) - 1))
		{
			if (g_abKeyPressed[K_SPACE])
			{
				bSomethingHappened = true;

				switch (i)
				{
				case 0:
					_NPC[0].talked = true;
					_NPC[0].tolerance++;
					break;
				case 1:
					_NPC[1].talked = true;
					_NPC[1].tolerance++;
					break;
				}
			}
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x40);
}

void renderSplashScreen()  // renders the splash screen (title screen)
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 25;

	string line;
	ifstream myfile("main_menu.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}//0x70

	c.Y += 3;
	c.X = c.X / 2 + 27;
	g_Console.writeToBuffer(c, "Start game", 0x74);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Leaderboard", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Credits", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 4;
	g_Console.writeToBuffer(c, "Quit", 0x47);

	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 15;
	g_Console.writeToBuffer(c, "w - select up, s - select down", 0x47);
}

void renderSplashScreen2()  // renders the splash screen (title screen)
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 25;

	string line;
	ifstream myfile("main_menu.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}//0x70

	c.Y += 3;
	c.X = c.X / 2 + 27;
	g_Console.writeToBuffer(c, "Start game", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Leaderboard", 0x74);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Credits", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 4;
	g_Console.writeToBuffer(c, "Quit", 0x47);

	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 15;
	g_Console.writeToBuffer(c, "w - select up, s - select down", 0x47);
}

void  renderSplashScreen3()
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 25;

	string line;
	ifstream myfile("main_menu.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}//0x70

	c.Y += 3;
	c.X = c.X / 2 + 27;
	g_Console.writeToBuffer(c, "Start game", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Leaderboard", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Credits", 0x74);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 4;
	g_Console.writeToBuffer(c, "Quit", 0x47);

	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 15;
	g_Console.writeToBuffer(c, "w - select up, s - select down", 0x47);
}

void  renderSplashScreen4()
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 25;

	string line;
	ifstream myfile("main_menu.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}//0x70

	c.Y += 3;
	c.X = c.X / 2 + 27;
	g_Console.writeToBuffer(c, "Start game", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Leaderboard", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Credits", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 4;
	g_Console.writeToBuffer(c, "Quit", 0x74);

	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 15;
	g_Console.writeToBuffer(c, "w - select up, s - select down", 0x47);
}

void renderSelectmode()
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 18;

	string line;
	ifstream myfile("selectmode.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}

	c.Y += 3;
	c.X = c.X / 2 + 23;
	g_Console.writeToBuffer(c, "Story", 0x74);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Level editor", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 5;
	g_Console.writeToBuffer(c, "Quit", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Back", 0x47);
}

void renderSelectmode2()
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 18;

	string line;
	ifstream myfile("selectmode.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}

	c.Y += 3;
	c.X = c.X / 2 + 23;
	g_Console.writeToBuffer(c, "Story", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Level editor", 0x74);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 5;
	g_Console.writeToBuffer(c, "Quit", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Back", 0x47);
}

void renderSelectmode3()
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 18;

	string line;
	ifstream myfile("selectmode.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}

	c.Y += 3;
	c.X = c.X / 2 + 23;
	g_Console.writeToBuffer(c, "Story", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Level editor", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 5;
	g_Console.writeToBuffer(c, "Quit", 0x74);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Back", 0x47);
}

void renderSelectmode4()
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 18;

	string line;
	ifstream myfile("selectmode.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}

	c.Y += 3;
	c.X = c.X / 2 + 23;
	g_Console.writeToBuffer(c, "Story", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Level editor", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 5;
	g_Console.writeToBuffer(c, "Quit", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Back", 0x74);
}

void renderSelectmodeLogic()
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER]) // when enter go to select screen
	{
		setBounceTime(0.3);
		g_eGameState = S_GAME;
		g_dElapsedTime = 0;
		g_dBounceTime = 0;
	}
	if (g_abKeyPressed[K_SELECTDOWN])
	{
		setBounceTime(0.3);
		g_eGameState = S_SELECTMODE2;
	}
}

void renderSelectmode2Logic()
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	//if (g_abKeyPressed[K_ENTER]) // when enter go to LEVEL EDITOR screen
	//{
	//	setBounceTime(0.3);
	//	g_eGameState = S_GAME;
	//}
	if (g_abKeyPressed[K_SELECTDOWN])
	{
		setBounceTime(0.3);
		g_eGameState = S_SELECTMODE3;
	}
	if (g_abKeyPressed[K_SELECTUP])
	{
		setBounceTime(0.3);
		g_eGameState = S_SELECTMODE;
	}
}

void renderSelectmode3Logic()
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER]) // when ENTER ,QUIT
	{
		setBounceTime(0.3);
		g_bQuitGame = true; ;
	}
	if (g_abKeyPressed[K_SELECTDOWN])
	{
		setBounceTime(0.3);
		g_eGameState = S_SELECTMODE4;
	}
	if (g_abKeyPressed[K_SELECTUP])
	{
		setBounceTime(0.3);
		g_eGameState = S_SELECTMODE2;
	}
}

void renderSelectmode4Logic()
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER]) // when enter go to select screen
	{
		setBounceTime(0.3);
		g_eGameState = S_SPLASHSCREEN;
	}
	if (g_abKeyPressed[K_SELECTUP])
	{
		setBounceTime(0.3);
		g_eGameState = S_SELECTMODE3;
	}
}

void renderLeaderboard()
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 25;

	string line;
	ifstream myfile("leaderboard.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}

	c.Y = 22;
	c.X = 70;
	g_Console.writeToBuffer(c, "Back", 0x74);
}

void renderLeaderboardlogic()
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER])
	{
		setBounceTime(0.3);
		g_eGameState = S_SPLASHSCREEN;
	}
}

void renderCredits()
{
	COORD c = g_Console.getConsoleSize();

	c.Y = 0;
	c.X = c.X / 2 - 20;

	string line;
	ifstream myfile("credits.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			g_Console.writeToBuffer(c, line, 0x37);
			c.Y++;
		}
		myfile.close();
	}
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, " ", 0x47); c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, " ", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Done by : ", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, " ", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Wafieqa", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Jolyn", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Brandon", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Meng Wei", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, " ", 0x47);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 6;
	g_Console.writeToBuffer(c, "Back", 0x74);
}

void renderCreditsLogic()
{
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER])
	{
		setBounceTime(0.3);
		g_eGameState = S_SPLASHSCREEN;
	}
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
	renderNPC();
	renderDialogue();
}


void maps()
{
	COORD c = g_Console.getConsoleSize();

	int height = 0;
	int width = 0;

	//start
	if (g_abKeyPressed[K_ENTER])
	{
		currentMap = Map1;
		ifstream file("map1.txt");
		if (file.is_open())
		{
			PlaySound(TEXT("playMUSIC/Music/Mapsnd.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
			while (height < 19)
			{
				while (width < 77)
				{
					file >> maze[width][height];
					width++;
				}
				width = 0;
				height++;
			}
			file.close();
		}
	}

	//goto the maps

	if (currentMap == Map1)
	{
		//towards
		if (g_sChar.m_cLocation.X == 75 && g_sChar.m_cLocation.Y == 9)
		{
			currentMap = Map2;
			ifstream file("map2.txt");
			if (file.is_open())
			{
				while (height < 19)
				{
					while (width < 77)
					{
						file >> maze[width][height];
						width++;
					}
					width = 0;
					height++;
				}
				file.close();
			}
		}
	}

	if (currentMap == Map2)
	{
		//towards
		if (g_sChar.m_cLocation.X == 1 && g_sChar.m_cLocation.Y == 4)
		{
			currentMap = Map3;
			ifstream file("map3.txt");
			if (file.is_open())
			{
				while (height < 19)
				{
					while (width < 77)
					{
						file >> maze[width][height];
						width++;
					}
					width = 0;
					height++;
				}
				file.close();
			}
		}
	}

	if (currentMap == Map3)
	{
		if (g_sChar.m_cLocation.X == 3 && g_sChar.m_cLocation.Y == 9)
		{
			currentMap = Map4;
			ifstream file("fairymap.txt");
			if (file.is_open())
			{
				PlaySound(TEXT("playMUSIC/Music/Fairysnd.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				while (height < 19)
				{
					while (width < 77)
					{
						file >> maze[width][height];
						width++;
					}
					width = 0;
					height++;
				}
				file.close();
			}
		}
	}

}

void renderMap()
{
	maps();

	COORD c = g_Console.getConsoleSize();

	/*int height = 0;
	int width = 0;*/

	for (int y = 0; y < 19; y++)
	{
		c.Y = y /*+ 1*/;
		for (int x = 0; x < 77; x++)
		{

			if (maze[x][y] == '0')
			{
				maze[x][y] = ' ';
			}

			if (maze[x][y] == 'E')
			{
				maze[x][y] = '*';
			}
			c.X = x;
			g_Console.writeToBuffer(c, maze[x][y]);
		}
	}


}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}

void renderNPC()
{
	// Draw the location of the Npc
	WORD charColor = 0x0D;
	for (int i = 0; i < 2; i++)
	{
		g_Console.writeToBuffer(_NPC[i].m_cLocation, (char)1, charColor);
	}
}

void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	if (g_eGameState == S_GAME)
	{
		ss.str("");
		ss << " " << g_dElapsedTimeMin << "mins " << (g_dElapsedTime) << "secs ";
		c.X = c.X / 2 - 4;
		c.Y = 24;
		g_Console.writeToBuffer(c, ss.str(), 0x70);
		if (g_dElapsedTime >= 60)
		{
			g_dElapsedTime = 0.0;
			g_dBounceTime = 0;
			g_dElapsedTimeMin++;
		}
	}
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

//interaction with the npc and fairy
void renderDialogue()
{
	COORD c = g_Console.getConsoleSize();
	c.X = (c.X);
	c.Y = (c.Y / 2) + 7;
	string value;

	for (int i = 0; i < npcNum; i++)
	{
		if (_NPC[i].talked == true)
		{
			value = dialogue(_NPC[i].tolerance);
			g_Console.writeToBuffer(c, value);
		}
	}
}