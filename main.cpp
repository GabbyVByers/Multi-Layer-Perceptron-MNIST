
#include "perceptron.h"
#include "mnist_dataset.h"
#include "opengl.h"

int main()
{
	{
		Perceptron perceptron;
	}
	
	Perceptron perceptron;
	MNISTdataSet mnist_dataSet;
	OpenGL OpenGL(1920, 1080, "Multilayer Perceptron");
	OpenGL.perceptron = &perceptron;
	OpenGL.mnist_dataSet = &mnist_dataSet;
	OpenGL.disableVSYNC();

	while (OpenGL.isAlive())
	{
		OpenGL.processInput();
		OpenGL.clearScreen();
		OpenGL.renderCircles();
		//OpenGL.renderSquares();
		OpenGL.swapBuffers();
	}

	return 0;
}

