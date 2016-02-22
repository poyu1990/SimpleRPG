#include "GameDriver.h"

GameDriver::GameDriver() {
	
	player = graphics.newSpriteObject("player_down");
	// x y z angle scale animation_time
	player->changePosition(20,20, -0.5, 0, 1.0f,0.0f);
	px = 20;
	py = 20;
	
	std::string tileNames[15][20];
	
	loadLevelFile("test level.txt",tileNames);
	
	map = graphics.newSpriteGridObject( tileNames, -0.9f );
	
	text = graphics.newTextObject("Hello World!");
    text->changePosition(100.0f,400,-0.1f,0,0.8f,3.0f);
    text->changeColor(255,0,0,150,3.0f);	
}

GameDriver::~GameDriver() {

	delete map;
	delete player;
	delete text;
	
}

void GameDriver::gameStep(double timeSinceLastFrame){
	 
	
}

void GameDriver::movePlayer(int x, int y){

	if( player->isAnimating() )
		return;
	
	if( x == 40 ){
		player->changeSprite("player_right");
		
		if( px == 780 ){
			loadMap(1,1.5f);		
			player->move(px=20,py=py+y,1.5f);
		}
		else{
			player->move(px=px+x,py=py+y,0.2f);
		}
		
	}
	else if( x == -40 ){
		player->changeSprite("player_left");
		
		if( px == 20 ){
			loadMap(2,1.5f);		
			player->move(px=780,py=py+y,1.5f);
		}
		else{
			player->move(px=px+x,py=py+y,0.2f);			
		}	
	}
	else if( y == 40 ){
		player->changeSprite("player_up");		

		if( py == 580 ){
			loadMap(3,1.5f);		
			player->move(px=px+x,py=20,1.5f);
		}
		else{
			player->move(px=px+x,py=py+y,0.2f);			
		}
	}
	else if( y == -40){
		player->changeSprite("player_down");
		
		if( py == 20 ){
			loadMap(4,1.5f);		
			player->move(px=px+x,py=580,1.5f);
		}
		else{
			player->move(px=px+x,py=py+y,0.2f);			
		}
	}
	
}

void GameDriver::loadMap(int dir,float sec){
	
	std::string tileNames[15][20];
	
	loadLevelFile("test level.txt",tileNames);
	
	map->changeSprites(tileNames,dir,sec);
	
}

void GameDriver::loadLevelFile(std::string name,std::string tiles[15][20]){
	
	std::ifstream is;
	is.open (name.c_str(), std::ios::binary );
	
	if( !is.is_open() )
		printf("Error loading level file");
	else{
		
		for(int y=0;y<15;++y)
			for(int x=0;x<20;++x)
				is >> tiles[y][x];
		
		is.close();
		
	}    
	
}

void GameDriver::glutInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'Q':
    case 'q': 
         exit(0);                   
         break;

    default:
        break;
    }

}

void GameDriver::glutSpecialInput(int key, int x, int y)
{
	
    switch (key)
    {
	case GLUT_KEY_LEFT:
			
		getObject()->movePlayer(-40,0);
			
		break;
	case GLUT_KEY_RIGHT:
			
		getObject()->movePlayer(40,0);
			
		break;
	case GLUT_KEY_UP:
		
		getObject()->movePlayer(0,40);
			
		break;
	case GLUT_KEY_DOWN:
			
		getObject()->movePlayer(0,-40);
			
		break;
    default:
        break;
    }
	 
}





 // @@@@@@@@@@@@@@@@@@@@@@@@ NO TOUCHING BELOW THIS LINE  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

GameDriver* GameDriver::getObject() {
             
     static GameDriver object;
                 
     return &object;
}

void GameDriver::glutResize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0.0,width,0.0,height,0.0,1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void GameDriver::glutDisplay(void)
{
	double timeSinceLastFrame =  1.0/60.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    getObject()->gameStep(timeSinceLastFrame);
    
    getObject()->graphics.render(timeSinceLastFrame);

    glutSwapBuffers();
}

void GameDriver::glutIdle(void)
{
    glutPostRedisplay();
}
