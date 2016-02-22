/*
 *  Animator.h
 *  Final Project
 *
 *  Created by kevin calderone on 6/4/10.
 *
 */

#include "Sprite.h"

class AnimationManager;

class Animator
{
public:
	Animator(Sprite* spr,float time,bool kill);
	virtual ~Animator();
	
	virtual bool step(float deltaTime) = 0;
	
	Sprite* getSprite(){return sprite;}
	
protected:
    friend class AnimationManager;
    
	float finishTime;
	float currentTime;
	
	Sprite* sprite;
	bool killOnFinish;
};

class MoveAnimator : public Animator
{
public:
	MoveAnimator(Sprite* spr,float x, float y, float z, float r, float s, float sec, bool kill);
	
    bool step(float deltaTime);
	
protected:
	
	float startPos[3];
	float startAngle;
	float startScale;
	
	float endPos[3];
	float endAngle;
	float endScale;

};

class ColorAnimator : public Animator
{
public:
	ColorAnimator(Sprite* spr, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec, bool kill);
	
	bool step(float deltaTime);
	
private:

	unsigned char startColor[4];
	unsigned char endColor[4];
	
};

class PhysicsAnimator : public Animator
{
public:
    PhysicsAnimator(Sprite* spr, float vx, float vy, float ax, float ay, float rx, float ry, float spin,float sec, bool kill);
    
    bool step(float deltaTIme); 
    
private:
    
    float vel[2];
    float acc[2]; 
    float res[2]; 
    
    float rot;    
};

