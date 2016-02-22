#include <stdlib.h>
#include <ctime>

#include "GraphicsInterface.h"

class GameDriver
{
public:

	static void glutResize(int,int);
	static void glutDisplay();
	static void glutInput(unsigned char, int, int);
	static void glutSpecialInput(int, int, int);
	static void glutIdle();

	static GameDriver* getObject();
            
private:  
            
	// ADD YOUR CODE STARTING HERE
	
	TextObject* text;
	
	SpriteGridObject* map;
	SpriteObject* player;
	int px,py;	
	
	void loadLevelFile(std::string name,std::string tiles[15][20]);
	void movePlayer(int x, int y);
	void loadMap(int dir, float sec);
	
	// ADD YOUR CODE ENDING HERE
	
	GraphicsInterface graphics;  
	
	void gameStep(double timeSinceLastFrame);

	GameDriver();
	~GameDriver(); 

	GameDriver(GameDriver&);
	GameDriver& operator=(GameDriver&);
      
};
