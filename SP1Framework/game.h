#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include "Framework\timer.h"

using namespace std;

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;
const unsigned int npcNum = 2;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_SELECTUP,
	K_SELECTDOWN,
	K_ESCAPE,
	K_SPACE,
	K_ENTER,
	K_START,
	K_BACK,
	K_LEADERBOARD,
	K_CREDITS,
	K_COUNT,
};

//Emumeration for going to different mpas 
enum EMAPS
{
	Map1,
	Map2,
	Map3,
	Map4,
	Map5
};
extern EMAPS currentMap;

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_SPLASHSCREEN2,
	S_SPLASHSCREEN3,
	S_SPLASHSCREEN4,
	S_GAME,
	S_SELECTMODE,
	S_SELECTMODE2,
	S_SELECTMODE3,
	S_SELECTMODE4,
	S_SELECTLEA,
	S_SELECTCRE,
    S_COUNT
};

//Enumeration for the title screen selection
enum EMENU
{
	K_STARTGAME,
	K_QUIT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

// struct for npc
struct SGameNPC
{
	COORD m_cLocation;
	int tolerance = 0;
	string str1;
	string str2;
	bool talked;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void splashScreenWait2();	// render splash screen with hightlighted leaderboard
void splashScreenWait3();	// render splash screen with hightlighted CREDITS
void splashScreenWait4();	// render splash screen with hightlighted QUIT

void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

void renderSplashScreen();  // renders the splash screen (START GAME)
void renderSplashScreen2(); // renders the splash screen (LEA)
void renderSplashScreen3(); // renders the splash screen (CREDITS)
void renderSplashScreen4(); // renders the splash screen (QUIT)

void renderSelectmode();	// render the select mode menu (STORY)
void renderSelectmode2();	// render the select mode menu (LEVEL)
void renderSelectmode3();	// render the select mode menu (QUIT)
void renderSelectmode4();	// render the select mode menu (BACK)

void renderSelectmodeLogic(); // update theselect mode menu 
void renderSelectmode2Logic(); // update theselect mode menu 
void renderSelectmode3Logic(); // update theselect mode menu 
void renderSelectmode4Logic(); // update theselect mode menu 

void renderCredits();		//render the credits
void renderCreditsLogic();	// update the credits

void renderLeaderboard();	//render the leaderbroad
void renderLeaderboardlogic(); // update the leaderbroad

void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void maps();				//maps to be put into renderMap and renderGame

void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

void renderDialogue();		//render the dialouge of the npc
void renderNPC();			//render NPC
void Npc();					//game logic for the npc
void breakTime();			//
void timeDelay();			//

#endif // _GAME_H