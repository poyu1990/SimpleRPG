#include "Sprite.h"
 
Sprite::Sprite(SpriteDef* def,MemoryChunk* data)
  : spriteDef(def),renderData(data) {
                   
    setPosition(0.0f,0.0f,0.0f,0,1.0f);
    setColor(255,255,255,255);
    calculateUV();
}

Sprite::~Sprite(){      
 
   delete renderData;                    
}

void Sprite::swapSprite(Sprite* other){
     
     MemoryChunk* tempData = renderData;
     renderData = other->renderData;
     other->renderData = tempData;
     
     SpriteDef* tempDef = spriteDef;
     spriteDef = other->spriteDef;
     other->spriteDef = tempDef;
     
     recalculateData();
}

void Sprite::setPosition(float x, float y, float z, float r, float s){
     
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    
    angle = r;
    scale = s; 
    
    float w = (spriteDef->hx - spriteDef->lx)*scale/2.0f;   
    float h = (spriteDef->hy - spriteDef->ly)*scale/2.0f;   
      
    float* posData = (float*)renderData->getDataBegin();
    
    float si = sin(angle*3.141592f/180.0f), co = cos(angle*3.141592f/180.0f);  
    //x = x cos - y sin
    //y = x sin + y cos
    
    posData[0] = x + (-w)*co - (-h)*si;
    posData[1] = y + (-w)*si + (-h)*co;
    posData[2] = z;

    posData[5] = posData[15] = x + (w)*co - (-h)*si;
    posData[6] = posData[16] = y + (w)*si + (-h)*co;
    posData[7] = posData[17] = z;
    
    posData[10] = posData[20]= x + (-w)*co - (h)*si;
    posData[11] = posData[21] = y + (-w)*si + (h)*co;
    posData[12] = posData[22] = z;
    
    posData[25] = x + (w)*co - (h)*si;
    posData[26] = y + (w)*si + (h)*co;
    posData[27] = z;        
 }

void Sprite::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
     
     color[0] = r;
     color[1] = g;
     color[2] = b;
     color[3] = a;
     
     unsigned char* data = (unsigned char*)renderData->getDataBegin();
     
     data[12]=data[32]=data[52]=data[72]=data[92]=data[112]=r;
     data[13]=data[33]=data[53]=data[73]=data[93]=data[113]=g;
     data[14]=data[34]=data[54]=data[74]=data[94]=data[114]=b;
     data[15]=data[35]=data[55]=data[75]=data[95]=data[115]=a; 
}

void Sprite::getPosition(float& x, float& y, float& z, float& r, float& s){

	x = pos[0];
	y = pos[1];
	z = pos[2];
	
	r = angle;
	s = scale;
}

void Sprite::getColor(unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a){
	
	r = color[0];
	g = color[1];
	b = color[2];
	a = color[3];
}

float Sprite::getWidth(){
      return scale*(spriteDef->hx-spriteDef->lx);      
}
      
float Sprite::getHeight(){
      return scale*(spriteDef->hy-spriteDef->ly);        
}

void Sprite::calculateUV(){
        
    short* uvData = (short*)renderData->getDataBegin();
    
    uvData[8]=spriteDef->lx;                  
    uvData[9]=spriteDef->ly;
    
    uvData[18]=uvData[38]=spriteDef->hx;                  
    uvData[19]=uvData[39]=spriteDef->ly;
    
    uvData[28]=uvData[48]=spriteDef->lx;                  
    uvData[29]=uvData[49]=spriteDef->hy;
    
    uvData[58]=spriteDef->hx;                  
    uvData[59]=spriteDef->hy; 
}

void Sprite::recalculateData(){
        
     setPosition(pos[0],pos[1],pos[2],angle,scale);
     setColor(color[0],color[1],color[2],color[3]);   
     calculateUV();           
}
