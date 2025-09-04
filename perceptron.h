#pragma once

#include <cassert>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

struct ImageFileHeader
{
	unsigned int magicNumber = 0;
	unsigned int numImages = 0;
	unsigned int numRows = 0;
	unsigned int numColumns = 0;

	void reverseByteOrdering()
	{

	}
};

struct HandWrittenDigit
{
	int digit = -1;
	unsigned char* pixels = nullptr;
};

class Perceptron
{
public:

	std::vector<HandWrittenDigit> handWrittenDigits;

	Perceptron()
	{
		std::ifstream digits("train-images.idx3-ubyte", std::ios::binary | std::ios::ate);
		size_t sizeDigits = digits.tellg(); digits.seekg(0, std::ios::beg);

		ImageFileHeader imageFileHeader;
		digits.read(reinterpret_cast<char*>(&imageFileHeader), sizeof(ImageFileHeader));

		std::cout << "Magic Number: " << imageFileHeader.magicNumber << "\n";
		std::cout << "Num Images  : " << imageFileHeader.numImages << "\n";
		std::cout << "Num Rows    : " << imageFileHeader.numRows << "\n";
		std::cout << "Num Columns : " << imageFileHeader.numColumns << "\n";
	}
};

