#include <stdlib.h>
#include "OpenGL.h"

#include "GameDriver.h"

int main(int argc, char *argv[])
{
    glutInitWindowSize(800,600);
    glutInitWindowPosition(40,40);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
    glutCreateWindow("Awesome game Gamma");
	
    glutReshapeFunc(GameDriver::glutResize);
    glutDisplayFunc(GameDriver::glutDisplay);
    glutKeyboardFunc(GameDriver::glutInput);
    glutSpecialFunc(GameDriver::glutSpecialInput);
    glutIdleFunc(GameDriver::glutIdle);
	
	//glutFullScreen();
	
    glClearColor(1,1,1,1);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);
	
	// Enable vsync
	
#if defined WIN32
    typedef void (APIENTRY *PFNWGLEXTSWAPCONTROLPROC) (int);
    typedef int (*PFNWGLEXTGETSWAPINTERVALPROC) (void);
	PFNWGLEXTSWAPCONTROLPROC wglSwapIntervalEXT = NULL;
	
	char* extensions = (char*)glGetString(GL_EXTENSIONS);
    if (strstr(extensions,"WGL_EXT_swap_control"))
    {
        wglSwapIntervalEXT = (PFNWGLEXTSWAPCONTROLPROC)
        wglGetProcAddress("wglSwapIntervalEXT");
        //exit(0);
        wglSwapIntervalEXT(1);
    }
    
#else  // OSX 10.6
	
	int swap_interval = 1;
	CGLContextObj cgl_context = CGLGetCurrentContext();
	CGLSetParameter(cgl_context, kCGLCPSwapInterval, &swap_interval);
	
#endif
	
	
    glutMainLoop();
	
    return EXIT_SUCCESS;
}
