/*
 *  GraphicsInterface.h
 *  Final Project
 *
 *  Created by kevin calderone on 6/4/10.
 *
 */

#ifndef _GRAPHICSINTERFACE_H_
#define _GRAPHICSINTERFACE_H_

#include "GraphicsManager.h"
#include "AnimationManager.h"

#include "Objects.h"
class SpriteObject;
class SpriteGridObject;

class GraphicsInterface
{
public:
	GraphicsInterface();
	~GraphicsInterface();
	
	void render(double deltaTime);
		
	SpriteObject* newSpriteObject(std::string name);
	SpriteGridObject* newSpriteGridObject(std::string names[15][20],float z);
	TextObject* newTextObject(std::string text);
	
private:
	
	std::vector<Object*> objects;

	GraphicsManager graphics;
	AnimationManager animation;

};

#endif
