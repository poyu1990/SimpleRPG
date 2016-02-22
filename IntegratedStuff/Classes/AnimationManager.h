/*
 *  AnimationManager.h
 *  Final Project
 *
 *  Created by kevin calderone on 6/4/10.
 *
 */

#ifndef _ANINIMATIONMANAGER_H_
#define _ANINIMATIONMANAGER_H_

#include "Sprite.h"
#include "Animator.h"

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();
	
	void step(float deltaTime);
	void removeSprite(Sprite* spr);
	
	void changePosition(Sprite* spr,float x, float y, float z, float r, float s, float sec, bool kill);
	void changeColor(Sprite* spr, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec, bool kill);
	void animatePhysics(Sprite* spr, float vx, float vy, float ax, float ay, float rx, float ry, float spin, float sec, bool kill);
	
	bool isSpriteAnimating(Sprite* spr);
	
private:
	
	std::vector<Animator*> animators;

};

#endif
