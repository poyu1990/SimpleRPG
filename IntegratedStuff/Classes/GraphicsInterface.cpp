/*
 *  GraphicsInterface.cpp
 *  Final Project
 *
 *  Created by kevin calderone on 6/4/10.
 *
 */

#include "GraphicsInterface.h"

GraphicsInterface::GraphicsInterface(){
	
}

GraphicsInterface::~GraphicsInterface(){

}

void GraphicsInterface::render(double deltaTime){

	animation.step(deltaTime);
	graphics.render();
	
}

SpriteObject* GraphicsInterface::newSpriteObject(std::string name){
	
	return new SpriteObject(&graphics,&animation,name);
	
}

SpriteGridObject* GraphicsInterface::newSpriteGridObject(std::string names[15][20], float z){
	
	return new SpriteGridObject(&graphics,&animation,names,z);
	
}

TextObject* GraphicsInterface::newTextObject(std::string text){
            
    return new TextObject(&graphics,&animation,text);            
            
}
