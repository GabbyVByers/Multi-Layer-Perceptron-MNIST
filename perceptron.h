#pragma once

#include "random.h"
#include <vector>

inline float randf()
{
	return randomFloat(-1.0f, 1.0f);
}

class Perceptron
{
public:

	float**  globalLayers  = nullptr;
	float**  globalBiases  = nullptr;
	float*** globalWeights = nullptr;

	int numLayers = -1;
	const std::vector<int> networkStructure = { 784, 16, 16, 10 };

	Perceptron();
	~Perceptron();

	void mallocPerceptron();
	void initPerceptronWithRandomWeightsAndBiases();
	void freePerceptron();
};

