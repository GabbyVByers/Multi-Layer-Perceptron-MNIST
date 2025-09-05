#pragma once

#include <vector>

class Perceptron
{
public:

	float**  layers  = nullptr;
	float**  biases  = nullptr;
	float*** weights = nullptr;

	int numLayers = -1;
	const std::vector<int> networkStructure = { 784, 16, 16, 10 };

	Perceptron()
	{
		numLayers = networkStructure.size();

		layers = new float* [numLayers];
		for (int i = 0; i < numLayers; i++)
		{
			layers[i] = new float[networkStructure[i]];
		}

		biases = new float* [numLayers - 1];
		for (int i = 0; i < numLayers - 1; i++)
		{
			biases[i] = new float[networkStructure[i + 1]];
		}

		weights = new float** [numLayers - 1];
		for (int i = 0; i < numLayers - 1; i++)
		{
			weights[i] = new float* [networkStructure[i]];
			for (int j = 0; j < networkStructure[i]; i++)
			{
				weights[i][j] = new float[networkStructure[i + 1]];
			}
		}
	}

	~Perceptron()
	{
		
	}
};

