
#include "opengl.h"
#include "random.h"

struct CircleVertex
{
	float x, y;
	float r, g, b;
	float radius;
};

void OpenGL::initCircleRendering()
{
	glGenVertexArrays(1, &circleVAO);
	glGenBuffers(1, &circleVBO);

	glBindVertexArray(circleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, circleVBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(CircleVertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CircleVertex), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(CircleVertex), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	std::string vert = loadSourceFile("glsl_circle.vert");
	std::string frag = loadSourceFile("glsl_circle.frag");
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

	circleShaderProgram = glCreateProgram();
	glAttachShader(circleShaderProgram, vertexShader);
	glAttachShader(circleShaderProgram, fragmentShader);
	glLinkProgram(circleShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glEnable(GL_PROGRAM_POINT_SIZE);
}

void OpenGL::renderCircles()
{
	glBindVertexArray(circleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
	glUseProgram(circleShaderProgram);

	std::vector<CircleVertex> circleVertices;
	for (int i = 0; i < 20; i++)
	{
		CircleVertex vert =
		{
			randomFloat(-1.0f, 1.0f), // x
			randomFloat(-1.0f, 1.0f), // y
			randomFloat( 0.0f, 1.0f), // r
			randomFloat( 0.0f, 1.0f), // g
			randomFloat( 0.0f, 1.0f), // b
			randomFloat( 0.0f, 0.2f), // rad
		};
		circleVertices.push_back(vert);
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(CircleVertex) * circleVertices.size(), &circleVertices[0], GL_STATIC_DRAW);
	int width, height; glfwGetFramebufferSize(window, &width, &height);
	glUniform2f(glGetUniformLocation(circleShaderProgram, "uScreenDimensions"), (float)width, (float)height);
	glDrawArrays(GL_POINTS, 0, (GLsizei)circleVertices.size());
}

