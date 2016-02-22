#include <stdlib.h>
#include <ctime>
#include <string>
#include <sstream>
#include <queue>
#include "character.h"
#include "battle.h"
#include "HealItem.h"
#include "GraphicsInterface.h"
       
       


class GameDriver
{
public:

	static void glutResize(int,int);
	static void glutDisplay();
	static void glutInput(unsigned char, int, int);
	static void glutSpecialInput(int, int, int);
	
	static void glutBattleInput(unsigned char, int, int);
	static void glutSpecialBattleInput(int, int, int);
	
	static void glutMessageInput(unsigned char, int, int);
	static void glutSpecialMessageInput(int, int, int);
	static void glutIdle();

	static GameDriver* getObject();
            attack atkL;
private:  
            
	// ADD YOUR CODE STARTING HERE
	
	
	string names[32];
	int counts[32];
	
	bool walkable[17][22];
	
	Character* enemies[4];
	
	Character* you;
	Character* enemyGuy;
	Battle battle;
	int currentMap;
	SpriteGridObject* map;
	SpriteObject* player;
	int px,py;		
	
	SpriteObject* enemy;
	int ex,ey;
	
	SpriteObject* sign;
	
	int cursorPos;
	int cursorLevel;
	bool isBattle;
	SpriteGridObject* batMap;
	TextObject* interfaceWords[6];
	TextObject* menuWords[4];
	TextObject* atkWords[4];
	bool isItem;
	
	std::queue<std::string> messageQueue;
	
	void startBattle(Character& you, Character& them);
	void endBattle();
	//Todo--add character input to endbattle
	
	void startMessage(std::string message);
	void endMessage(int inputType = 0);
	
	void loadLevelFile(std::string name,std::string tiles[15][20]);
	void loadCollisionFile(std::string name);
	void movePlayer(int x, int y);
	void loadMap(int dir, float sec);
	void dispHP(Character& you, Character& them);
	int attackTarget(Character& attacker, Character &target, int attkNum);
	
	void restartGame();
	
	// ADD YOUR CODE ENDING HERE
	
	GraphicsInterface graphics;  
	
	void gameStep(double timeSinceLastFrame);

	GameDriver();
	~GameDriver(); 

	GameDriver(GameDriver&);
	GameDriver& operator=(GameDriver&);
      
};
