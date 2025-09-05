#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "perceptron.h"
#include "mnist_dataset.h"

class OpenGL
{
public:

	Perceptron* perceptron = nullptr;
	MNISTdataSet* mnist_dataSet = nullptr;
	
	GLFWwindow* window = nullptr;

	unsigned int squareShaderProgram;
	unsigned int squareVAO;
	unsigned int squareVBO;

	unsigned int circleShaderProgram;
	unsigned int circleVAO;
	unsigned int circleVBO;

	unsigned int lineShaderProgram;
	unsigned int lineVAO;
	unsigned int lineVBO;

	// Utilities
	OpenGL(int initWidth, int initHeight, std::string title);
	~OpenGL();
	bool isAlive();
	void disableVSYNC();
	void enableVSYNC();
	void clearScreen();
	void swapBuffers();
	std::string loadSourceFile(std::string filePath);

	// Square Rendering
	void initSquareRendering();
	void renderSquares();

	// Circle Rendering
	void initCircleRendering();
	void renderCircles();

	// Line Rendering
	//void initLineRendering();
	//void renderLines();

	// GUI
	//void initImGui() const;
	//void renderGUI();

	// User Input
	void processInput();
};

