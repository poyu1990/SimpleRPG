#include <string>
#include <fstream>

#include "OpenGL.h"

class BMPTexture
{
public:
	BMPTexture(std::string fileName);
	~BMPTexture(); 

	void apply();

	int getWidth(){return width;}
    int getHeight(){return height;}   
	
private:
     
	void loadTexture(char* data);
        
	std::string file;
     
	GLuint texture;
	unsigned int width;
	unsigned int height;
  
};
