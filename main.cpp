
#include "mnist_dataset.h"
#include "opengl.h"

int main()
{
	MNISTdataSet mnist_dataSet;
	OpenGL OpenGL(1920, 1080, "Multilayer Perceptron");
	OpenGL.mnist_dataSet = &mnist_dataSet;
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

