
#include "perceptron.h"
#include "opengl.h"

int main()
{
	Perceptron preceptron;

	OpenGL OpenGL(1920, 1080, "Multilayer Perceptron");
	OpenGL.disableVSYNC();

	while (OpenGL.isAlive())
	{
		OpenGL.processInput();
		OpenGL.clearScreen();
		OpenGL.renderCircles();
		OpenGL.swapBuffers();
	}

	return 0;
}

