#include "GameDriver.h"

GameDriver::GameDriver() {
isBattle = false;
	player = graphics.newSpriteObject("player_down");
px = 500;
	py = 100;
	player->changePosition(px,py, -0.5, 0, 1.0f,0.0f);
	
	
	//enemy = graphics.newSpriteObject("enemy_left");
	ex = 380;
	ey = 380;
	//enemy->changePosition(ex,ey, -0.5, 0, 1.0f,0.0f);
	
    sign = graphics.newSpriteObject("sign");
	sign->changePosition(300,9990, -0.5, 0, 1.0f,0.0f);
	
	std::string tileNames[15][20];

	for(int i=0;i<15;++i)
		for(int j=0;j<20;++j)
			tileNames[i][j] = "none";
	
	batMap = graphics.newSpriteGridObject( tileNames, -0.3f );
	
	loadLevelFile("level1.txt",tileNames);
	loadCollisionFile("level1_collide.txt");
	currentMap = 1;
	
	map = graphics.newSpriteGridObject( tileNames, -0.9f );
	
	for(int i=0;i<4;++i){
		menuWords[i] = NULL;
		atkWords[i] = NULL;
	}
	for(int i=0;i<6;++i)	
		interfaceWords[i] = NULL;

	you = new Character(100, 3, 9, 9, 5, 5, 5, "You", &graphics);
	you->addAttk(0, 31);
    you->addAttk(1, 30);
    you->addAttk(2, 29);
    
	loadMap(1,0);
	
}

GameDriver::~GameDriver() {

	delete you;
	delete map;
	delete player;
	delete batMap;
	delete sign;
	
	if (enemyGuy)
	delete enemyGuy;
	
	if( enemy )
		delete enemy;
	
	for(int i=0;i<5;++i)	
		if( interfaceWords[i] )
			delete interfaceWords[i];
	
	for(int i=0;i<4;++i){
		if( menuWords[i] )
			delete menuWords[i];	
		if( atkWords[i] )
			delete atkWords[i];
	}
}

void GameDriver::gameStep(double timeSinceLastFrame){
	 
	
}

void GameDriver::movePlayer(int x, int y){
	
	if( player->isAnimating() )
		return;
	
	if( !walkable[ 16-((py+y)+20)/40 ][ ((px+x)+20)/40 ] )
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
    if(enemyGuy && currentMap != 2)
    {
		enemyGuy->getCol(ex, ey);
		if( abs(px-ex) + abs(py-ey) < 60 )
			startBattle(*you, *enemyGuy);
    }
    if(currentMap == 2 && !isBattle)
    {
		
		for(int r = 0; r < 4; r++)
		{
			enemies[r]->getCol(ex, ey);
			if( abs(px-ex) + abs(py-ey) < 60 )
			{
				enemyGuy = enemies[r];
				startBattle(*you, *enemyGuy);
				break;
			}
		}
    }
    if(currentMap == 1)
    {
		if( abs(px-300) + abs(py-470) < 51 )
			startMessage("Press C if you are in trouble!");
	}
	
}


void GameDriver::loadMap(int dir,float sec){
	
	float yOffset = 0.0f;
	
	if( enemyGuy && currentMap!=2)
		delete enemyGuy;
	
	if( dir==3 && currentMap!=4 ){
		currentMap++;
		yOffset = 600;
	}
	else if( dir==4 && currentMap!=1 ){
		currentMap--;
		yOffset = -600;
	}
	
	if( currentMap == 2 ){
		enemyGuy = new Character(50, 3, 2, 2, 5, 1, 5, "Crossbow Bandit", &graphics, 9001, 390, "player_up");
	}
	
	std::stringstream lvl;
	lvl << "level" << currentMap << ".txt";
	
	std::string tileNames[15][20];
	
	loadLevelFile(lvl.str(),tileNames);
	
	std::stringstream col;
	col << "level" << currentMap << "_collide.txt";
	
	loadCollisionFile(col.str());
	
	map->changeSprites(tileNames,dir,sec);
	for(int r = 0; r < 4; r++)
	{
		if(enemies[r] != NULL)
			enemies[r]->pic->changePosition(380, 9390, -0.5f, 0, 1.0f, sec);
	}
	if(!isBattle)
	{
    	sign->changePosition(300,9990, -0.5, 0, 1.0f,0.0f);
    	switch(currentMap)
    	{
			case 1:
				enemyGuy = new Character(50, 3, 2, 2, 5, 1, 5, "Crossbow Bandit", &graphics, 380, 390, "enemy_left");
				enemyGuy->addAttk(0, 29);
				enemyGuy->addAttk(1, 30);
				enemyGuy->addAttk(2, 29);
				enemyGuy->gainExp(25);
				
				sign->changePosition(300,470+yOffset, -0.5, 0, 1.0f,0.0f);
				sign->changePosition(300, 470, -0.5f, 0, 1.0f, sec);
				
				enemyGuy->pic->changePosition(380, 390+yOffset, -0.5f, 0, 1.0f, 0.0f);
				enemyGuy->pic->changePosition(380, 390, -0.5f, 0, 1.0f, sec);				
				
				break;
			case 2:
				/*
				 enemyGuy = new Character(111, 3, 5, 5, 5, 5, 5, "Hedge Person", &graphics, 280, 390, "googly");
				 enemyGuy->addAttk(0, 29);
				 enemyGuy->addAttk(1, 30);
				 enemyGuy->addAttk(2, 29);
				 enemyGuy->gainExp(30);
				 */
				// Multiple enemies
				
				for(int r = 0; r < 4; r++)
				{
                    int inX = 140, inY = 390;
					enemies[r] = new Character(111, 3, 5, 5, 5, 5, 5, "Hedge Person", &graphics, 200, 9390, "googly");
					enemies[r]->addAttk(0, 29);
					enemies[r]->addAttk(1, 30);
					enemies[r]->addAttk(2, 29);
					enemies[r]->gainExp(30);
					switch(r)
					{
							
						case 0:
							
							break;
							
						case 1:
							inX = 440;
							inY = 300;
							break;
						case 2:
							inX = 340;
							inY = 100;
							break;
						case 3:
							inX = 700;
							inY = 390;
							break;
							
					}
					enemies[r]->pic->changePosition(inX, inY+yOffset, -0.5f, 0, 1.0f, 0.0f);
					enemies[r]->pic->changePosition(inX, inY, -0.5f, 0, 1.0f, sec);
					enemies[r]->setCol(inX, inY);
					
				}
				
				// End multiple enemies
				
				/*
				 enemyGuy->pic->changePosition(280, 390+yOffset, -0.5f, 0, 1.0f, 0.0f);
				 enemyGuy->pic->changePosition(280, 390, -0.5f, 0, 1.0f, sec);			
				 */
				break;
			case 3:
				enemyGuy = new Character(200, 3, 5, 5, 5, 6, 5, "Gate Guard", &graphics, 155, 500, "gateman");
				enemyGuy->addAttk(0, 29);
				enemyGuy->addAttk(1, 30);
				enemyGuy->addAttk(2, 29);
				enemyGuy->gainExp(50);
				
				enemyGuy->pic->changePosition(155, 500+yOffset, -0.5f, 0, 1.0f, 0.0f);
				enemyGuy->pic->changePosition(155, 500, -0.5f, 0, 1.0f, sec);		
				
				break;
			case 4:
				enemyGuy = new Character(999, 7, 7, 7, 7, 7, 7, "Mr End", &graphics, 380, 390, "sign");
				enemyGuy->addAttk(0, 29);
				enemyGuy->addAttk(1, 30);
				enemyGuy->addAttk(2, 29);
				enemyGuy->gainExp(77);
				
				enemyGuy->pic->changePosition(380, 390+yOffset, -0.5f, 0, 1.0f, 0.0f);
				enemyGuy->pic->changePosition(380, 390, -0.5f, 0, 1.0f, sec);		
				break;
        }
    }
    
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

void GameDriver::loadCollisionFile(std::string name){
	
	std::ifstream is;
	is.open (name.c_str(), std::ios::binary );
	
	if( !is.is_open() )
		printf("Error loading level file");
	else{
		
		for(int y=0;y<17;++y)
			for(int x=0;x<22;++x)
				is >> walkable[y][x];
		
		is.close();
		
	}    
}

void GameDriver::startBattle(Character& you, Character& them){
     
     isBattle = true;
    stringstream batText;
	interfaceWords[0] = graphics.newTextObject("Battle Menu");
    interfaceWords[0]->changePosition(345.0f,100,-0.1f,0,0.25f,0.0f);
	
	interfaceWords[1] = graphics.newTextObject(you.getName());
    interfaceWords[1]->changePosition(590.0f,100,-0.1f,0,0.25f,0.0f);
    batText<<you.getAttr(5)<<"/"<<you.getAttr(8);
	interfaceWords[2] = graphics.newTextObject(batText.str());
    interfaceWords[2]->changePosition(620.0f,80,-0.1f,0,0.25f,0.0f);
    batText.clear();
    batText.str("");
    
	interfaceWords[3] = graphics.newTextObject(them.getName());
    interfaceWords[3]->changePosition(590.0f,40,-0.1f,0,0.25f,0.0f);
    batText<<them.getAttr(5)<<"/"<<them.getAttr(8);
	interfaceWords[4] = graphics.newTextObject(batText.str());
    interfaceWords[4]->changePosition(620.0f,20,-0.1f,0,0.25f,0.0f);
    batText.clear();
    batText.str("");

	menuWords[0] = graphics.newTextObject("Fight");
    menuWords[0]->changePosition(60.0f,60,-0.1f,0,0.25f,0.0f);
    menuWords[0]->changeColor(255,0,0,255,0.0f);	
    menuWords[1] = graphics.newTextObject("Item");
    menuWords[1]->changePosition(55.0f,40,-0.1f,0,0.25f,0.0f);
    menuWords[2] = graphics.newTextObject("Run");
    menuWords[2]->changePosition(60.0f,20,-0.1f,0,0.25f,0.0f);
	
	cursorPos = 0;
	cursorLevel = 0;
	
	std::string batNames[15][20];

	loadLevelFile("bat.txt",batNames);
	
	batMap->changeSprites(batNames,4,0.0f);
	
    glutKeyboardFunc(GameDriver::glutBattleInput);
	glutSpecialFunc(GameDriver::glutSpecialBattleInput);
	
}

void GameDriver::endBattle(){
	isBattle = false;
	for(int i=0;i<6;++i)
		if(interfaceWords[i] && i!=5){
			delete interfaceWords[i];
			interfaceWords[i] = NULL;	
		}

	for(int i=0;i<4;++i){
		if(menuWords[i]){
			delete menuWords[i];
			menuWords[i] = NULL;	
		}
		if(atkWords[i]){
			delete atkWords[i];
			atkWords[i] = NULL;	
		}
	}
	
	std::string tileNames[15][20];
	
	for(int i=0;i<15;++i)
		for(int j=0;j<20;++j)
			tileNames[i][j] = "none";
	
	batMap->changeSprites(tileNames,3,0.0f);

    //glutKeyboardFunc(GameDriver::glutInput);
    //glutSpecialFunc(GameDriver::glutSpecialInput);
	
    //enemy->~Object();
    //ex = 9999;
	//ey = 9999;
	enemyGuy->setCol(9999, 0);
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
case 'c':
                getObject()->you->addAttk(3, 28);
                break;
           case 'C':
                getObject()->you->addAttk(3, 28);
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

void GameDriver::dispHP(Character& you, Character& them)
{
     
     
     stringstream batText;
    batText<<you.getAttr(5)<<"/"<<you.getAttr(8);
    delete interfaceWords[2];
	interfaceWords[2] = graphics.newTextObject(batText.str());
    interfaceWords[2]->changePosition(630.0f,80,-0.1f,0,0.25f,0.0f);
    batText.clear();
    batText.str("");
    delete interfaceWords[4];
    batText<<them.getAttr(5)<<"/"<<them.getAttr(8);
	interfaceWords[4] = graphics.newTextObject(batText.str());
    interfaceWords[4]->changePosition(630.0f,20,-0.1f,0,0.25f,0.0f);
    batText.clear();
    batText.str("");     
     
     }

void GameDriver::glutBattleInput(unsigned char key, int x, int y)
{
     static int curRate = 6;
    switch (key)
    {
           case (int)'c':
                getObject()->you->addAttk(3, 28);
                break;
           case (int)'C':
                getObject()->you->addAttk(3, 28);
                break;
		case 13 :  // enter
			if( getObject()->cursorLevel == 0){
				if( getObject()->cursorPos == 0 ){ // fight
					
					getObject()->menuWords[0]->changeColor(255, 255, 255, 255, 0.0f);
					
					for(int i=0;i<4;++i){
						if(!getObject()->you->getAttk(i))
							break;
						getObject()->atkWords[i] = getObject()->graphics.newTextObject(getObject()->battle.atkL.nameData(getObject()->you->getAttk(i)));
						getObject()->atkWords[i]->changePosition(260.0f,60-(i*20),-0.1f,0,0.25f,0.0f);
					}
					
					getObject()->atkWords[0]->changeColor(255, 0, 0, 255, 0.0f);
					getObject()->cursorLevel = 1;
					getObject()->isItem = 0;
					
				}
				else if( getObject()->cursorPos == 1){
			
					for(int i=0;i<32;i++)
						getObject()->names[i] = "";
					
					getObject()->you->getItem()->inventory(getObject()->names,getObject()->counts);
					
					if( getObject()->names[0] == ""){
						getObject()->startMessage("You do not have any items.");
						return;
					}
					
					getObject()->menuWords[1]->changeColor(255, 255, 255, 255, 0.0f);
					
					
					std::stringstream ss;
					for(int i=0;i<4;++i){
						if(getObject()->names[i]=="")
							continue;
						ss.clear();
						ss.str("");
						ss << getObject()->names[i] + " x" << getObject()->counts[i];
						getObject()->atkWords[i] = getObject()->graphics.newTextObject( ss.str() );
						getObject()->atkWords[i]->changePosition(260.0f,60-(i*20),-0.1f,0,0.25f,0.0f);
					}
					
					getObject()->atkWords[0]->changeColor(255, 0, 0, 255, 0.0f);
					getObject()->cursorLevel = 1;
					getObject()->cursorPos = 0;
					getObject()->isItem  = 1;
					
				}
				else if( getObject()->cursorPos == 2 ){  // run
					getObject()->endBattle();
					getObject()->startMessage("Ran away!");
				}
			}
			else if( getObject()->cursorLevel == 1 ){  // select move
			
				if(getObject()->isItem){
					
					HealItem hItem;
					int index = hItem.lookup( getObject()->names[ getObject()->cursorPos ] );
					int heal = hItem.use( index );
					getObject()->you->increaseHP( heal );
					getObject()->you->getItem()->itemUse(index);
					
					std::stringstream ss;
					
					ss << "You healed " << heal << " HP.";
					
					getObject()->dispHP(*(getObject()->you), *(getObject()->enemyGuy));
					getObject()->startMessage(ss.str());
					
					
					getObject()->cursorPos = 0;
					getObject()->cursorLevel = 0;
					getObject()->menuWords[0]->changeColor(255, 0, 0, 255, 0.0f);
					
					for(int i=0;i<4;++i)
						if( getObject()->atkWords[i] ){
							delete getObject()->atkWords[i];
							getObject()->atkWords[i] = NULL;
						}
				}
				else{

					getObject()->menuWords[0]->changeColor(255, 0, 0, 255, 0.0f);

					switch(getObject()->attackTarget(*(getObject()->you), *(getObject()->enemyGuy), (*(getObject()->you)).getAttk(getObject()->cursorPos)))
					{
					case 1:
						curRate -= 3;
					case 2:
						curRate -= 1;
					case 3:
						curRate -= 2;                          
					}
					if(getObject()->isBattle && curRate<1)
					{
						   curRate = -6;
						   while(curRate<0)
						   {
								switch(getObject()->attackTarget(*(getObject()->enemyGuy), *(getObject()->you), (*(getObject()->enemyGuy)).getAttk(0)))
								{
									   case 1:
											curRate += 3;
									   case 2:
											curRate += 1;
									   case 3:
											curRate += 2;                          
								}
								
							}
							curRate = 6;
					}
						   

					getObject()->cursorPos = 0;
					getObject()->cursorLevel = 0;

					//getObject()->menuWords[0]->changeColor(255, 0, 0, 255, 0.0f);

					for(int i=0;i<4;++i)
					if( getObject()->atkWords[i] ){
						delete getObject()->atkWords[i];
						getObject()->atkWords[i] = NULL;
					}

				
				}
				
			}
			break;
		case 127: // backspace
			if( getObject()->cursorLevel == 1 ){  // back menu level
				getObject()->cursorPos = 0;
				getObject()->cursorLevel = 0;
				
				getObject()->menuWords[0]->changeColor(255, 0, 0, 255, 0.0f);

				for(int i=0;i<4;++i)
					if( getObject()->atkWords[i] ){
						delete getObject()->atkWords[i];
						getObject()->atkWords[i] = NULL;
					}
					
			}
			
			break;
		case 27 :
		case 'Q':
		case 'q': 
			exit(0);                   
			break;
			
		default:
			break;
    }
	
}




void GameDriver::glutSpecialBattleInput(int key, int x, int y)
{
	int numEntries = 0;
	
	if( getObject()->cursorLevel == 0 ){  // attack/run
		for(int i=0;i<4;++i)
			if( getObject()->menuWords[i] )
				numEntries++;
	}
	else if( getObject()->cursorLevel == 1 ){  // moves
		for(int i=0;i<4;++i)
			if( getObject()->atkWords[i] )
				numEntries++;
	}
	
    switch (key)
    {
	case GLUT_KEY_LEFT:
			
		break;
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_UP:
			getObject()->cursorPos -= 1;
		break;
	case GLUT_KEY_DOWN:
			getObject()->cursorPos += 1;
		break;
    default:
        break;
    }
	
	if( getObject()->cursorPos < 0 )
		getObject()->cursorPos += numEntries;
	else if( getObject()->cursorPos >= numEntries )
		getObject()->cursorPos -= numEntries;
	
	
	if( getObject()->cursorLevel == 0 ){
	
		for(int i=0;i<numEntries;++i)
			if( i == getObject()->cursorPos )
				getObject()->menuWords[i]->changeColor(255,0,0,255,0.0f);
			else
				getObject()->menuWords[i]->changeColor(255,255,255,255,0.0f);
			
	}
	else if(getObject()->cursorLevel == 1){
		
		for(int i=0;i<numEntries;++i)
			if( i == getObject()->cursorPos )
				getObject()->atkWords[i]->changeColor(255,0,0,255,0.0f);
			else
				getObject()->atkWords[i]->changeColor(255,255,255,255,0.0f);
		
	}

}


void GameDriver::glutMessageInput(unsigned char key, int x, int y)
{
     if(key == 13)
     {
            if(getObject()->isBattle)
            getObject()->endMessage(1);
            else
            getObject()->endMessage();
            //Do something to close the message/scroll it
     }
     if((key == 'c')||(key== 'C'))
     {
             
                getObject()->you->addAttk(3, 28);
     }
	
}

void GameDriver::glutSpecialMessageInput(int key, int x, int y)
{ //Does nothing so they don't get any fancy ideas about walking away from messages
}


int GameDriver::attackTarget(Character& attacker, Character &target, int attkNum)
{
    stringstream info;
     if(getObject()->battle.attackRoll((atkL.data(2, attkNum) + attacker.getAttr(atkL.data(1, attkNum))), target.getAttr(7)))
       {
           info<<attacker.getName()<<" hit with "<<atkL.nameData(attkNum)<<" for "
           <<atkL.data(3, attkNum)*(attacker.getAttr(atkL.data(4, attkNum)))<<" damage!"<<endl;
           target.damage(atkL.data(3, attkNum)*(attacker.getAttr(atkL.data(4, attkNum))));
           //getObject()->menuWords[0]->changeColor(0, 255, 0, 255, 0.0f);
           dispHP(*you, *enemyGuy);
           
           
           
       }
       else
       {
           info<<attacker.getName()<<" missed with "<<atkL.nameData(attkNum)<<"!"<<endl;
           //getObject()->menuWords[0]->changeColor(0, 0, 255, 255, 0.0f);
       }
       /*
       delete interfaceWords[5];
       interfaceWords[5] = graphics.newTextObject(info.str());
       interfaceWords[5]->changePosition(180.0f,148,-0.1f,0,0.25f,0.0f);
       */
       startMessage(info.str());
       info.clear();
       info.str("");
       
       if((attacker.getAttr(5)==0)||(target.getAttr(5)==0))
         {
          endBattle();
          if((*you).getAttr(5)==0)
          {
               info<<(*you).getName()<<" lost!";
               //loadMap(1,0);
			  
			   restartGame();
			  
			    startMessage(info.str());
          }
          else
          {
               info<<(*you).getName()<<" won!";
			  
			   startMessage(info.str());
			  
			  if( currentMap == 4 ){
				  startMessage("You won the game!"); 
				  startMessage("Credits:");
				  startMessage("Kevin Calderone");
				  startMessage("Maxwell Taylor");
				  startMessage("Benson Chen");
				  startMessage("Ben Ritter");
				  startMessage("Thank you for playing!");
				  startMessage("quit");
			  }
			  
			  if (you->gainExp(enemyGuy->getAttr(9)) )
				  startMessage("You leveled up!");
			  
               isBattle = 0;
          }
                                    
          info.clear();
       info.str("");
         }
       return atkL.data(5, attkNum);
     
}

void GameDriver::startMessage(std::string message)
{
	messageQueue.push(message);
	if(messageQueue.size()==1){
		delete interfaceWords[5];
		interfaceWords[5] = graphics.newTextObject(messageQueue.front());
		interfaceWords[5]->changePosition(180.0f,148,-0.1f,0,0.25f,1.0f);
		glutKeyboardFunc(GameDriver::glutMessageInput);
		glutSpecialFunc(GameDriver::glutSpecialMessageInput);
	}
}

void GameDriver::endMessage(int inputType)
{
	messageQueue.pop();

	if(messageQueue.size()==0){
		 delete interfaceWords[5];
		 interfaceWords[5] = graphics.newTextObject("");
		 glutKeyboardFunc(GameDriver::glutBattleInput);
		 glutSpecialFunc(GameDriver::glutSpecialBattleInput);
		 if(inputType ==0)
		 {
		   glutKeyboardFunc(GameDriver::glutInput);
		   glutSpecialFunc(GameDriver::glutSpecialInput);
		 }
	}
	else {
		if( messageQueue.front()== "quit" )
			exit(1);
		
		delete interfaceWords[5];
		interfaceWords[5] = graphics.newTextObject(messageQueue.front());
		interfaceWords[5]->changePosition(180.0f,148,-0.1f,0,0.25f,1.0f);
	}

}

void GameDriver::restartGame(){

	delete you;
	delete player;
	
	isBattle = false;
	player = graphics.newSpriteObject("player_down");
	px = 500;
	py = 100;
	player->changePosition(px,py, -0.5, 0, 1.0f,0.0f);
	
	std::string tileNames[15][20];
	
	loadLevelFile("level1.txt",tileNames);
	loadCollisionFile("level1_collide.txt");
	currentMap = 1;
	
	map->changeSprites(tileNames,4,0.0f);
	
	you = new Character(100, 3, 9, 9, 5, 5, 5, "You", &graphics);
	you->addAttk(0, 31);
    you->addAttk(1, 30);
    you->addAttk(2, 29);
	
	while( messageQueue.size() )
		endMessage(1);
	
	startMessage("You Died!");
    
	loadMap(1,0);

	
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
