
#include "opengl.h"

int main()
{
	OpenGL OpenGL(1920, 1080, "Multilayer Perceptron");

	while (OpenGL.isAlive())
	{
		OpenGL.processInput();
		OpenGL.clearScreen();
		OpenGL.renderCircles();
		OpenGL.swapBuffers();
	}

	return 0;
}

