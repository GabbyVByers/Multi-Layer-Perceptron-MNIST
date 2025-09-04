#pragma once

#include <cassert>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

inline unsigned int returnReversedBytes(unsigned int value)
{
	return ((value & 0x000000FF) << 24) |
		   ((value & 0x0000FF00) << 8)  |
		   ((value & 0x00FF0000) >> 8)  |
		   ((value & 0xFF000000) >> 24);
}

struct ImageFileHeader
{
	unsigned int magicNumber = 0;
	unsigned int numImages = 0;
	unsigned int numRows = 0;
	unsigned int numColumns = 0;
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
		
		imageFileHeader.magicNumber = returnReversedBytes(imageFileHeader.magicNumber);
		imageFileHeader.numImages   = returnReversedBytes(imageFileHeader.numImages);
		imageFileHeader.numRows     = returnReversedBytes(imageFileHeader.numRows);
		imageFileHeader.numColumns  = returnReversedBytes(imageFileHeader.numColumns);

		std::cout << "Magic Number: " << imageFileHeader.magicNumber << "\n";
		std::cout << "Num Images  : " << imageFileHeader.numImages << "\n";
		std::cout << "Num Rows    : " << imageFileHeader.numRows << "\n";
		std::cout << "Num Columns : " << imageFileHeader.numColumns << "\n";

		handWrittenDigits.clear();
		handWrittenDigits.reserve(imageFileHeader.numImages);
		for (int i = 0; i < imageFileHeader.numImages; i++)
		{
			HandWrittenDigit digit;
			digit.pixels = new unsigned char[784]; // Every image is exactly 28x28 and contains exactly 784 pixels.
			digits.read(reinterpret_cast<char*>(digit.pixels), sizeof(unsigned char) * 784);
			handWrittenDigits.push_back(digit);
		}
	}

	~Perceptron()
	{
		for (auto& digit : handWrittenDigits)
		{
			delete[] digit.pixels;
		}
	}
};

