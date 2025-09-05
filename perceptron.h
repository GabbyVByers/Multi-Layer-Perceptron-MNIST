#pragma once

class Perceptron
{
public:

	float**  layers = nullptr;
	float**  biases = nullptr;
	float*** weights = nullptr;

	Perceptron()
	{
		layers = new float* [4];
		biases = new float* [3];
		weights = new float** [3];

		layers[0] = new float[784];
		layers[1] = new float[16];
		layers[2] = new float[16];
		layers[3] = new float[10];

		biases[0] = new float[16];
		biases[1] = new float[16];
		biases[2] = new float[10];

		weights[0] = new float* [784];
		weights[1] = new float* [16];
		weights[2] = new float* [16];

		for (int i = 0; i < 784; i++)
		{
			weights[0][i] = new float[16];
		}

		for (int i = 0; i < 16; i++)
		{
			weights[1][i] = new float[16];
		}

		for (int i = 0; i < 16; i++)
		{
			weights[2][i] = new float[10];
		}
	}

	~Perceptron()
	{
		for (int i = 0; i < 784; i++)
		{
			delete[] weights[0][i];
		}

		for (int i = 0; i < 16; i++)
		{
			delete[] weights[1][i];
		}

		for (int i = 0; i < 16; i++)
		{
			delete[] weights[2][i];
		}

		delete[] weights[0];
		delete[] weights[1];
		delete[] weights[2];

		delete[] biases[0];
		delete[] biases[1];
		delete[] biases[2];

		delete[] layers[0];
		delete[] layers[1];
		delete[] layers[2];
		delete[] layers[3];

		delete[] layers;
		delete[] biases;
		delete[] weights;
	}
};

