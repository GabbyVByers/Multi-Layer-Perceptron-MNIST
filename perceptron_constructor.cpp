
#include "perceptron.h"

Perceptron::Perceptron()
{
	mallocPerceptron();
	initPerceptronWithRandomWeightsAndBiases();
}

Perceptron::~Perceptron()
{
	freePerceptron();
}

void Perceptron::mallocPerceptron()
{
	numLayers = networkStructure.size();

	globalLayers = new float* [numLayers];
	for (int i = 0; i < numLayers; i++)
	{
		globalLayers[i] = new float[networkStructure[i]];
	}

	globalBiases = new float* [numLayers - 1];
	for (int i = 0; i < numLayers - 1; i++)
	{
		globalBiases[i] = new float[networkStructure[i + 1]];
	}

	globalWeights = new float** [numLayers - 1];
	for (int layer = 0; layer < numLayers - 1; layer++)
	{
		int numPrevNeurons = networkStructure[layer];
		int numCurrNeurons = networkStructure[layer + 1];

		globalWeights[layer] = new float* [numCurrNeurons];
		for (int i = 0; i < numCurrNeurons; i++)
		{
			globalWeights[layer][i] = new float[numPrevNeurons];
		}
	}
}

void Perceptron::freePerceptron()
{
	for (int i = 0; i < numLayers; i++)
	{
		delete[] globalLayers[i];
	}
	delete[] globalLayers;

	for (int i = 0; i < numLayers - 1; i++)
	{
		delete[] globalBiases[i];
	}
	delete[] globalBiases;

	for (int layer = 0; layer < numLayers - 1; layer++)
	{
		int numPrevNeurons = networkStructure[layer];
		int numCurrNeurons = networkStructure[layer + 1];

		for (int i = 0; i < numCurrNeurons; i++)
		{
			delete[] globalWeights[layer][i];
		}
		delete[] globalWeights[layer];
	}
	delete[] globalWeights;
}

void Perceptron::initPerceptronWithRandomWeightsAndBiases()
{
	for (int layer = 0; layer < numLayers - 1; layer++)
	{
		float** weights = globalWeights[layer];
		int numPrevNeurons = networkStructure[layer];
		int numCurrNeurons = networkStructure[layer + 1];

		for (int i = 0; i < numCurrNeurons; i++)
		{
			for (int j = 0; j < numPrevNeurons; j++)
			{
				weights[i][j] = randf();
			}
		}
	}

	for (int layer = 0; layer < numLayers - 1; layer++)
	{
		float* biases = globalBiases[layer];
		int numBiases = networkStructure[layer + 1];
		for (int i = 0; i < numBiases; i++)
		{
			biases[i] = randf();
		}
	}
}

