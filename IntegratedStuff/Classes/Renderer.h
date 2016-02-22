#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <string>
#include <vector>

#include "OpenGL.h"
#include "MemoryAllocator.h"
#include "Sprite.h"
#include "BMPTexture.h"

class Renderer
{
public:
    Renderer(std::string texture);
    ~Renderer();
       
    Sprite* createSprite(std::string name);
       
    void render();

private:     
    
    std::vector<SpriteDef*> spriteDefs;
    
    BMPTexture* texture;
    MemoryAllocator* renderData;
    
    void loadSpriteDefs(std::string file);
    
};

#endif //_RENDERER_H_
