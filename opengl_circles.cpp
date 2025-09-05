
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

	float stride = 0.5f;
	float spacing = 0.07f;
	float outer = 0.03f;
	float inner = outer - 0.003f;

	std::vector<CircleVertex> circleVertices;

	float currColumnPos = ((float)(perceptron->numLayers - 1) / 2.0f) * (-1.0f * stride);
	for (int layer = 0; layer < perceptron->numLayers; layer++)
	{
		int numNeuronsToDraw = -1;
		if (layer == 0) { numNeuronsToDraw = 23; }
		else { numNeuronsToDraw = perceptron->networkStructure[layer]; }

		float currRowPos = ((float)(numNeuronsToDraw - 1) / 2.0f) * (-1.0f * spacing);
		for (int i = 0; i < numNeuronsToDraw; i++)
		{
			CircleVertex outerCircle = { currColumnPos, currRowPos, 1.0f, 1.0f, 1.0f, outer };
			CircleVertex innerCircle = { currColumnPos, currRowPos, 0.0f, 0.0f, 0.0f, inner };
			circleVertices.push_back(outerCircle);
			circleVertices.push_back(innerCircle);
			currRowPos += spacing;
		}
		currColumnPos += stride;
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(CircleVertex) * circleVertices.size(), &circleVertices[0], GL_STATIC_DRAW);
	int width, height; glfwGetFramebufferSize(window, &width, &height);
	glUniform2f(glGetUniformLocation(circleShaderProgram, "uScreenDimensions"), (float)width, (float)height);
	glDrawArrays(GL_POINTS, 0, (GLsizei)circleVertices.size());
}

