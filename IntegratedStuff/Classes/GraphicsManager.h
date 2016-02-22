#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include <vector>
#include <string>

#include "OpenGL.h"

class Sprite;
class SpriteDef;

#include "Renderer.h"

class GraphicsManager
{
public:
     GraphicsManager();
     ~GraphicsManager();
       
     void render();
     
     Sprite* newSprite(std::string name);
       
private: 
         
     std::vector<Renderer*> renderers;
      
     void loadTextures(std::string file);  
};


#endif // _GRAPHICSMANAGER_H_
