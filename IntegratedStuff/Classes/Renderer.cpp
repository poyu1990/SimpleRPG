#include "Renderer.h"

Renderer::Renderer(std::string textureFile){
     
     renderData = new MemoryAllocator(1000);        
     
     texture = new BMPTexture(textureFile + ".bmp");
     loadSpriteDefs(textureFile + ".txt");    
}
                   
Renderer::~Renderer(){
      
      while(spriteDefs.size()){
           delete spriteDefs.back();
           spriteDefs.pop_back();   
      }
      
      delete renderData;
      delete texture;
                    
}

void Renderer::render(){
     
	unsigned int numSprites = renderData->usedMemory()/120;
	
	if( numSprites == 0 )
		return;	
	
	texture->apply();
	
	renderData->defrag();
	
	float* data = (float*)(renderData->getDataBegin());
	
    glVertexPointer(	3,		GL_FLOAT,			20,	          &data[0]);
    glColorPointer(		4,		GL_UNSIGNED_BYTE,	20,	          &data[3]);
    glTexCoordPointer(	2,		GL_SHORT,			20,	          &data[4]);
		
    glDrawArrays (GL_TRIANGLES, 0, numSprites*6);
	
}

Sprite* Renderer::createSprite(std::string name){

    SpriteDef* spriteDef = NULL;
    Sprite* sprite = NULL;

    for(int i=0;i<spriteDefs.size();++i)
       if( spriteDefs[i]->name == name ){
           spriteDef = spriteDefs[i];
           break;
       }  
      
    if( spriteDef != NULL )
        sprite = new Sprite(spriteDef,renderData->newBlock( 6*(12+4+4) ));
         
    return sprite;
}

void Renderer::loadSpriteDefs(std::string file){
     
  std::ifstream is;
  is.open (file.c_str(), std::ios::binary );

  if( !is.is_open() )
      printf("Error loading SpriteDefs for texture %s\n",file.c_str());
  else{

       std::string name;
       short lx,ly,hx,hy;
       
       while( is.good() ){
           is >> name >> lx >> ly >> hx >> hy;
		   
		   // flip y-coordinates since textures are stored upside-down
		   int temp = ly;
		   ly = texture->getHeight() - hy;
		   hy = texture->getHeight() - temp;
		   
           spriteDefs.push_back( new SpriteDef(name,lx,ly,hx,hy) );
       }
       
       is.close();

   } 
     
}
