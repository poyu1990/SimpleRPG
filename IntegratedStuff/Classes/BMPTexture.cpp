#include "BMPTexture.h"

BMPTexture::BMPTexture(std::string fileName)
  : file(fileName),texture(0) {
       
  std::ifstream is;
  is.open (file.c_str(), std::ios::binary );

  if( !is.is_open() )
      printf("Error loading Texture");
  else{
       int length;
       char * data;
       
       is.seekg (0, std::ios::end);
       length = is.tellg();
       is.seekg (0, std::ios::beg);

       data = new char [length];

       is.read (data,length);
       is.close();

       loadTexture(data);
	  
	  delete [] data;
   }                       

}
                                   
BMPTexture::~BMPTexture(){
   
   glDeleteTextures(1,&texture);
   
}
 
void BMPTexture::loadTexture(char* data){
 
	unsigned int dataBegin = *((unsigned int*)(data+10)); 

	width = *((unsigned int*)(data+18));
	height = *((unsigned int*)(data+22));

	glGenTextures(1, &texture); 

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, &data[dataBegin]);
	
}
 
void BMPTexture::apply(){

	glMatrixMode(GL_TEXTURE);
	
	glLoadIdentity();
	glScalef(1.0f/width,1.0f/height,1.0f);
	
	glBindTexture(GL_TEXTURE_2D, texture);
     
}
