/*
 *  Objects.h
 *  Final Project
 *
 *  Created by kevin calderone on 6/4/10.
 *
 */

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "GraphicsManager.h"
#include "AnimationManager.h"

class Object
{
public:
	Object(GraphicsManager* g, AnimationManager* a);
	virtual ~Object();

	virtual void move(float x, float y, float sec) = 0;
	virtual void changePosition(float x, float y, float z, float r, float s, float sec) = 0;
	virtual void changeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec) = 0;
	
	bool isAnimating();
	
protected:

	std::vector<Sprite*> sprites;
	
	GraphicsManager* graphics;
	AnimationManager* animation;
};

class SpriteObject : public Object
{
public:
	SpriteObject(GraphicsManager* g, AnimationManager* a, std::string name);

	void move(float x, float y, float sec);
	void changePosition(float x, float y, float z, float r, float s, float sec);
	void changeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec);

	void changeSprite(std::string name);
private:
};

class SpriteGridObject : Object
{
public:
	SpriteGridObject(GraphicsManager* g, AnimationManager* a, std::string name[15][20], float z);
	
	void move(float x, float y, float sec){};
	void changePosition(float x, float y, float z, float r, float s, float sec){};
	void changeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec){};
	
	void changeSprites(std::string name[15][20],int dir, float sec);
private:	
	float depth;
};

class TextObject : public Object
{
public:
    TextObject(GraphicsManager* g, AnimationManager* a, std::string text);   
       
 	void move(float x, float y, float sec);
	void changePosition(float x, float y, float z, float r, float s, float sec);
	void changeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec);  
    
    void changeText(std::string text); 
       
private:      
      
};

#endif
