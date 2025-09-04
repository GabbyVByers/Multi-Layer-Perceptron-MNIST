
#include "perceptron.h"
#include "opengl.h"

int main()
{
	Perceptron perceptron;
	OpenGL OpenGL(1920, 1080, "Multilayer Perceptron");
	OpenGL.perceptron = &perceptron;
	OpenGL.enableVSYNC();

	while (OpenGL.isAlive())
	{
		OpenGL.processInput();
		OpenGL.clearScreen();
		OpenGL.renderSquares();
		OpenGL.swapBuffers();
	}

	return 0;
}

