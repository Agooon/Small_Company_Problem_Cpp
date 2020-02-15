#pragma once

// Simple class to generate random values
class CRandom
{
public:
	CRandom();
	CRandom(unsigned int seed);
	~CRandom();
	void setSeed(unsigned int newSeed);

	int iRandInt(int from, int to);
	unsigned int iRandUInt(unsigned int from, unsigned int to);
	double dRandDouble(double from, double to);

private:
	int seed;
	std::mt19937 generator;
	std::random_device device;
};

