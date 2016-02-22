#include "GraphicsManager.h"

GraphicsManager::GraphicsManager() {
    
    loadTextures("textureList.txt");
                                                                    
}
                                   
GraphicsManager::~GraphicsManager() {

    while(renderers.size()){
         delete renderers.back();
         renderers.pop_back();                        
    }
                                        
}

Sprite* GraphicsManager::newSprite(std::string name){
        
    Sprite* sprite = NULL;

    for(int i=0;i<renderers.size();++i)
        if( sprite = renderers[i]->createSprite(name) ) 
            break;   
   
    if( sprite == NULL )
        printf("Error: Sprite not found");

    return sprite;   
}

void GraphicsManager::render() {
     
     for(int i=0;i<renderers.size();++i)
        renderers[i]->render();
   
}

void GraphicsManager::loadTextures(std::string file){

  std::ifstream is;
  is.open (file.c_str(), std::ios::binary );

  if( !is.is_open() )
      printf("Error loading Texture List");
  else{
       std::string texture;
       
       while( is.good() ){
            is >> texture;           
            renderers.push_back( new Renderer(texture) );      
       }

       is.close();

   }           

     
}
