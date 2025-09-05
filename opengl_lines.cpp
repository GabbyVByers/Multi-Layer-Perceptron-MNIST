
#include "opengl.h"
#include "sigmoid.h"

struct LineVertex
{
	float x, y;
	float r, g, b;
};

void OpenGL::initLineRendering()
{
	glGenVertexArrays(1, &lineVAO);
	glGenBuffers(1, &lineVBO);

	glBindVertexArray(lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	std::string vert = loadSourceFile("glsl_line.vert");
	std::string frag = loadSourceFile("glsl_line.frag");
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

	lineShaderProgram = glCreateProgram();
	glAttachShader(lineShaderProgram, vertexShader);
	glAttachShader(lineShaderProgram, fragmentShader);
	glLinkProgram(lineShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glEnable(GL_PROGRAM_POINT_SIZE);
}

void OpenGL::renderLines()
{
	glBindVertexArray(lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glUseProgram(lineShaderProgram);

	std::vector<LineVertex> lineVertices;

	for (int layer = 0; layer < perceptron->numLayers - 1; layer++)
	{
		int numNeurons = -1;
		if (layer == 0) { numNeurons = 23; }
		else { numNeurons = perceptron->networkStructure[layer]; }
		for (int neuron = 0; neuron < numNeurons; neuron++)
		{
			Vec2f position = neuronScreenPosition(layer, neuron);
			if ((layer == 0) && ((neuron == 10) || (neuron == 11) || (neuron == 12)))
			{
				continue;
			}
	
			int nextLayer = layer + 1;
			int numNextNeurons = perceptron->networkStructure[nextLayer];
			for (int nextNeuron = 0; nextNeuron < numNextNeurons; nextNeuron++)
			{
				Vec2f nextPosition = neuronScreenPosition(nextLayer, nextNeuron);
				float weight = perceptron->globalWeights[layer][nextNeuron][neuron];
				float sig = sigmoid(weight);
				LineVertex start = { position.x, position.y, 1.0f - sig, sig, 0.0f };
				LineVertex end = { nextPosition.x, nextPosition.y, 1.0f - sig, sig, 0.0f };
				lineVertices.push_back(start);
				lineVertices.push_back(end);
			}
		}
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(LineVertex) * lineVertices.size(), &lineVertices[0], GL_STATIC_DRAW);
	int width, height; glfwGetFramebufferSize(window, &width, &height);
	glUniform2f(glGetUniformLocation(lineShaderProgram, "uScreenDimensions"), (float)width, (float)height);
	glDrawArrays(GL_LINES, 0, (GLsizei)lineVertices.size());
}

