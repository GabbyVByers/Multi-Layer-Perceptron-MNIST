
#include "perceptron.h"

void Perceptron::mapHandWrittenDigitToInputLayer(int imageIndex)
{
	HandWrittenDigit& digit = mnist_dataSet->handWrittenDigits[imageIndex];

	float* inputActivations = globalLayers[0];
	int numInputLayerNeurons = networkStructure[0];
	for (int neuronIndex = 0; neuronIndex < numInputLayerNeurons; neuronIndex++)
	{
		inputActivations[neuronIndex] = digit.pixels[neuronIndex];
	}
}

void Perceptron::forwardPropagation()
{

}

