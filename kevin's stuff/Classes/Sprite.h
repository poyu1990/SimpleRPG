#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <cmath>
#include <string>

#include "MemoryAllocator.h"

struct SpriteDef
{
	SpriteDef(std::string n, short lowx, short lowy, short highx, short highy)
		: name(n),lx(lowx),ly(lowy),hx(highx),hy(highy) {};  

	std::string name;
	short lx, ly, hx, hy;  
};

class Sprite
{
public:
	Sprite(SpriteDef* def,MemoryChunk* data);
	~Sprite();
	
	void setPosition(float x, float y, float z, float r, float s);
	void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void getPosition(float& x, float& y, float& z, float& r, float& s);
	void getColor(unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a);
	
	void swapSprite(Sprite* other);
	
	float getWidth();
	float getHeight();
	
private:
	SpriteDef* spriteDef;

	// Vertex Packing:
	// float          x,y,z
	// unsigned char  r,g,b,a
	// short          u,v
	// 6 Vertexes
	MemoryChunk* renderData;

	float pos[3],angle,scale;
	unsigned char color[4];  
    
    void calculateUV();  
    void recalculateData();  
};

#endif // _SPRITE_H_
