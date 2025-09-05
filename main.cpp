
#include "perceptron.h"
#include "mnist_dataset.h"
#include "opengl.h"

int main()
{
	Perceptron perceptron;
	MNISTdataSet mnist_dataSet;
	OpenGL OpenGL(1920, 1080, "Multilayer Perceptron"); OpenGL.disableVSYNC();
	
	perceptron.mnist_dataSet = &mnist_dataSet;
	OpenGL.mnist_dataSet = &mnist_dataSet;
	OpenGL.perceptron = &perceptron;

	while (OpenGL.isAlive())
	{
		OpenGL.processInput();
		OpenGL.clearScreen();
		OpenGL.renderLines();
		OpenGL.renderCircles();
		//OpenGL.renderSquares();
		OpenGL.swapBuffers();
	}

	return 0;
}

