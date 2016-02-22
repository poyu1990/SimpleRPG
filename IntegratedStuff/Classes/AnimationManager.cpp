/*
 *  AnimationManager.cpp
 *  Final Project
 *
 *  Created by kevin calderone on 6/4/10.
 *
 */

#include "AnimationManager.h"

AnimationManager::AnimationManager(){
	
}

AnimationManager::~AnimationManager(){
	
	while(animators.size()){
		delete animators.back();
		animators.pop_back();
	}
	
}

void AnimationManager::step(float deltaTime){

	for(int i=0;i<animators.size();++i)
		if( animators[i]->step(deltaTime) ){
            
            if( animators[i]->killOnFinish ){
                
                // remove any other animators on this sprite
                for(int j=0;j<animators.size();++j)
                    if( animators[j]->getSprite() == animators[i]->getSprite() && i!=j ){
                    
                        delete animators[j];
                        animators.erase(animators.begin()+j);
                        
                        if(j<i)
                            i--;
                        j--;    
                    }
                                
                delete animators[i]->sprite;
            }
                
			delete animators[i];
			animators.erase(animators.begin()+i);
			i--;
		}
	
}

void AnimationManager::removeSprite(Sprite* spr){

	for(int i=0;i<animators.size();++i)
		if( animators[i]->getSprite() == spr ){
			delete animators[i];
			animators.erase(animators.begin()+i);
			i--;
		}
		
}

bool AnimationManager::isSpriteAnimating(Sprite* spr){

	for(int i=0;i<animators.size();++i)
		if( animators[i]->getSprite() == spr )
			return 1;
		
	return 0;
}

void AnimationManager::changePosition(Sprite* spr,float x, float y, float z, float r, float s, float sec, bool kill){
	
	animators.push_back( new MoveAnimator(spr,x,y,z,r,s,sec,kill) );
	
}

void AnimationManager::changeColor(Sprite* spr, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float sec, bool kill){

	animators.push_back( new ColorAnimator(spr,r,g,b,a,sec,kill) );
	
}

void AnimationManager::animatePhysics(Sprite* spr, float vx, float vy, float ax, float ay, float rx, float ry, float spin, float sec, bool kill){

    animators.push_back( new PhysicsAnimator(spr,vx,vy,ax,ay,rx,ry,spin,sec,kill) );
     
}

