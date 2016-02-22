/*
 *  Objects.cpp
 *  Final Project
 *
 *  Created by kevin calderone on 6/4/10.
 *
 */

#include "Objects.h"

Object::Object(GraphicsManager* g, AnimationManager* a)
	: graphics(g),animation(a) {
	
	
	
}

Object::~Object(){
	
	while(sprites.size()){
		animation->removeSprite( sprites.back() );
		delete sprites.back();
		sprites.pop_back();
	}
	
}

bool Object::isAnimating(){

	for(int i=0;i<sprites.size();++i)
		if( animation->isSpriteAnimating(sprites[i]) )
		   return 1;
		   
	return 0;
}

SpriteObject::SpriteObject(GraphicsManager* g, AnimationManager* a, std::string name)
	: Object(g,a) {
		
	sprites.push_back( graphics->newSprite(name) );
	
}

void SpriteObject::move(float x, float y, float sec){

	float tx,ty,z,r,s;
	
	sprites[0]->getPosition(tx,ty,z,r,s);
	changePosition(x,y,z,r,s,sec);
	
}

void SpriteObject::changePosition(float x, float y, float z, float r, float s, float sec){
	
	// instant change
	if( sec < 0.01 )
		sprites[0]->setPosition(x,y,z,r,s);		
	// animated change
	else	
		animation->changePosition(sprites[0],x,y,z,r,s,sec,0);		
}

void SpriteObject::changeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec){

	// instant change
	if( sec < 0.01 )
		sprites[0]->setColor(r,g,b,a);
	// animated change
	else
		animation->changeColor(sprites[0],r,g,b,a,sec,0);
}

void SpriteObject::changeSprite(std::string name){

	Sprite* spr = graphics->newSprite(name);
	
	if( spr == NULL )
		return;
	
	sprites[0]->swapSprite(spr);
	
    delete spr;
}

SpriteGridObject::SpriteGridObject(GraphicsManager* g, AnimationManager* a, std::string names[15][20], float z)
	: Object(g,a),depth(z) {
	
	changeSprites(names,1,0.0f);

}

void SpriteGridObject::changeSprites(std::string name[15][20],int dir, float sec){

	int moveX, moveY;
	
	switch( dir ){
		case 1:
			moveX = -800;
			moveY = 0;
			break;
		case 2:
			moveX = 800;
			moveY = 0;
			break;
		case 3:
			moveX = 0;
			moveY = -600;
			break;
		case 4:
			moveX = 0;
			moveY = 600;
			break;
		default:
			return;
	}
	
	while( sprites.size() ){
		float x,y,z,r,s;
		sprites.back()->getPosition(x,y,z,r,s);
		animation->changePosition(sprites.back(),x+moveX,y+moveY,z,r,s,sec,1);
		//animation->animatePhysics(sprites.back(),(rand()%500)-250,(rand()%200),0.0f,-800.0f,1.0f,1.0f,(rand()%40)-20,sec,1);
		sprites.pop_back();
	}
	
	for(int ty=0;ty<15;++ty)
		for(int tx=0;tx<20;++tx){
			
			if( name[ty][tx] == "none" )
				continue;
			
			Sprite* spr = graphics->newSprite( name[ty][tx] );
			
			
			spr->setPosition(-moveX+20+tx*40, -moveY+580-ty*40, depth, 0, 1.0f);
			animation->changePosition(spr,20+tx*40, 580-ty*40,depth,0,1.0f,sec,0);
			sprites.push_back( spr );
		}
		
}

TextObject::TextObject(GraphicsManager* g, AnimationManager* a, std::string text)
     : Object(g,a){

     changeText(text);                                        
                                        
}
       
void TextObject::move(float x, float y, float sec){
     	
    float tx,ty,z,r,s;	
     	
    sprites[0]->getPosition(tx,ty,x,r,s);
    changePosition(x,y,z,r,s,sec);
}
     
void TextObject::changePosition(float x, float y, float z, float r, float s, float sec){
     	    
    float bx,by,bs;
    float tx,ty,ts;
     	
   	sprites[0]->getPosition(bx,by,z,r,bs);
   	
    if( sec < 0.01 )
        for(int i=0;i<sprites.size();++i){
           sprites[i]->getPosition(tx,ty,z,r,ts);
           sprites[i]->setPosition(x+(tx-bx)*s/bs,y+(ty-by)*s/bs,z,r,s);
        }
	else
        for(int i=0;i<sprites.size();++i){
           sprites[i]->getPosition(tx,ty,z,r,ts);
           animation->changePosition(sprites[i],x+(tx-bx)*s/bs,y+(ty-by)*s/bs,z,r,s,sec,0);
        }
}

void TextObject::changeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec){
      
	if( sec < 0.01 )
        for(int i=0;i<sprites.size();++i)
           sprites[i]->setColor(r,g,b,a);
	else
        for(int i=0;i<sprites.size();++i)
           animation->changeColor(sprites[i],r,g,b,a,sec,0);
}

void TextObject::changeText(std::string text){
     
    float x=0.0f,y=0.0f,z=-0.1f,r=0.0f,s=0.5f;
	unsigned char re=255,gr=255,bl=255,al=255;
	
	float currentX = 0.0f;

    if( sprites.size() ){
        
        sprites[0]->getPosition(x,y,z,r,s);
		sprites[0]->getColor(re,gr,bl,al);
		
		currentX -= sprites[0]->getWidth()/2.0f;
         
    	while(sprites.size()){
    		animation->removeSprite( sprites.back() );
    		delete sprites.back();
    		sprites.pop_back();
    	}	
    }
	
	currentX += x;
	for(int i=0;i<text.length();++i){        
        
        std::string name;
        name += text[i];
        
        Sprite* spr = graphics->newSprite( name );  
        
        // not a recognized character, treat it is a space
        if( spr==NULL ){
            currentX += 30.0f*s;
            continue; 
        }
             
        currentX += s*spr->getWidth()/2.0f;  
          
        spr->setPosition(currentX,y,z,r,s); 
		spr->setColor(re,gr,bl,al);
          
        currentX += spr->getWidth()/2.0f + 6.0f*s;   
        
        sprites.push_back(spr); 
    } 
    
}
