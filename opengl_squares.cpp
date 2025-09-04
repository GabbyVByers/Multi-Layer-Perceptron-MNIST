
#include "opengl.h"
#include "random.h"

struct SquareVertex
{
	float x, y;
	float r, g, b;
	float radius;
};

void OpenGL::initSquareRendering()
{
	glGenVertexArrays(1, &squareVAO);
	glGenBuffers(1, &squareVBO);

	glBindVertexArray(squareVAO);
	glBindBuffer(GL_ARRAY_BUFFER, squareVBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SquareVertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SquareVertex), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(SquareVertex), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	std::string vert = loadSourceFile("glsl_square.vert");
	std::string frag = loadSourceFile("glsl_square.frag");
	const char* vertShaderSource = vert.c_str();
	const char* fragShaderSource = frag.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertShaderSource, nullptr);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragShaderSource, nullptr);
	glCompileShader(fragmentShader);

	squareShaderProgram = glCreateProgram();
	glAttachShader(squareShaderProgram, vertexShader);
	glAttachShader(squareShaderProgram, fragmentShader);
	glLinkProgram(squareShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glEnable(GL_PROGRAM_POINT_SIZE);
}

void OpenGL::renderSquares()
{
	glBindVertexArray(squareVAO);
	glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
	glUseProgram(squareShaderProgram);

	static int count = 0;
	count++;
	count %= perceptron->handWrittenDigits.size();

	std::vector<SquareVertex> squareVertices;
	float scale = 0.05f;
	for (int i = 0; i < 784; i++)
	{
		int x = i % 28;
		int y = i / 28;
		SquareVertex square =
		{
			(float)(x *  scale) - 0.5f,
			(float)(y * -scale) + 0.5f,
			(float)perceptron->handWrittenDigits[count].pixels[i] / 255.0f,
			(float)perceptron->handWrittenDigits[count].pixels[i] / 255.0f,
			(float)perceptron->handWrittenDigits[count].pixels[i] / 255.0f,
			scale * 0.5f
		};
		squareVertices.push_back(square);
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(SquareVertex) * squareVertices.size(), &squareVertices[0], GL_STATIC_DRAW);
	int width, height; glfwGetFramebufferSize(window, &width, &height);
	glUniform2f(glGetUniformLocation(squareShaderProgram, "uScreenDimensions"), (float)width, (float)height);
	glDrawArrays(GL_POINTS, 0, (GLsizei)squareVertices.size());
}

 