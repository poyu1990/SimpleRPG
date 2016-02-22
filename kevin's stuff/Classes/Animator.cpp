/*
 *  Animator.cpp
 *  Final Project
 *
 *  Created by kevin calderone on 6/4/10.
 *
 */

#include "Animator.h"

Animator::Animator(Sprite* spr,float time,bool kill)
: sprite(spr),finishTime(time),currentTime(0.0f),killOnFinish(kill){
	
}

Animator::~Animator(){
	
}

MoveAnimator::MoveAnimator(Sprite* spr,float x, float y, float z, float r, float s, float sec, bool kill)
: Animator(spr,sec,kill) {

	spr->getPosition(startPos[0],startPos[1],startPos[2],startAngle,startScale);
	
	endPos[0] = x;
	endPos[1] = y;
	endPos[2] = z;

	endAngle = r;
	endScale = s;
		
}

bool MoveAnimator::step(float deltaTime){
		
	currentTime += deltaTime;
	
	if( currentTime > finishTime ){

        sprite->setPosition(endPos[0], endPos[1], endPos[2], endAngle, endScale);
		    
		return 1;
	}
	
	float x = startPos[0] + (endPos[0]-startPos[0])*currentTime/finishTime;
	float y = startPos[1] + (endPos[1]-startPos[1])*currentTime/finishTime;
	float z = startPos[2] + (endPos[2]-startPos[2])*currentTime/finishTime;

	float r = startAngle + (endAngle-startAngle)*currentTime/finishTime;
	float s = startScale + (endScale-startScale)*currentTime/finishTime;
	
	sprite->setPosition(x,y,z,r,s);
	
	return 0;
}

ColorAnimator::ColorAnimator(Sprite* spr, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec, bool kill)	
	: Animator(spr, sec, kill) {

	spr->getColor(startColor[0],startColor[1],startColor[2],startColor[3]);
	
	endColor[0] = r;
	endColor[1] = g;
	endColor[2] = b;
	endColor[3] = a;
	
}

bool ColorAnimator::step(float deltaTime){
	
	currentTime += deltaTime;
	
	if( currentTime > finishTime ){
        
        sprite->setColor(endColor[0],endColor[1],endColor[2],endColor[3]);
		    
		return 1;
	}
	
	float r = startColor[0] + (endColor[0]-startColor[0])*currentTime/finishTime;
	float g = startColor[1] + (endColor[1]-startColor[1])*currentTime/finishTime;
	float b = startColor[2] + (endColor[2]-startColor[2])*currentTime/finishTime;
	float a = startColor[3] + (endColor[3]-startColor[3])*currentTime/finishTime;
	
	sprite->setColor((unsigned int)r,(unsigned int)g,(unsigned int)b,(unsigned int)a);
	
	return 0;	
}

PhysicsAnimator::PhysicsAnimator(Sprite* spr, float vx, float vy, float ax, float ay, float rx, float ry, float spin, float sec, bool kill)
    : Animator(spr,sec,kill) {

    vel[0] = vx;
    vel[1] = vy;
    
    acc[0] = ax;
    acc[1] = ay;
    
    res[0] = rx;
    res[1] = ry;
    
    rot = spin;
    
}
    
bool PhysicsAnimator::step(float deltaTime){
     
	 bool done = 0;
     
	 currentTime += deltaTime;
     
     if( currentTime > finishTime ){
         deltaTime -= currentTime - finishTime;
         currentTime = finishTime;
		 done = 1;
     }
         
     float x,y,z,r,s;
     sprite->getPosition(x,y,z,r,s);
     
     x += vel[0]*deltaTime + 0.5f*acc[0]*deltaTime*deltaTime;
     y += + vel[1]*deltaTime + 0.5f*acc[1]*deltaTime*deltaTime;   
     
     vel[0] += acc[0]*deltaTime;
     vel[1] += acc[1]*deltaTime;
     
     vel[0] *= res[0];
     vel[1] *= res[1];
     
     r += rot;
     
     sprite->setPosition(x,y,z,r,s);  
	
     return done;
}

