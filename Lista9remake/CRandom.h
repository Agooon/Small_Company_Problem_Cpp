#pragma once

// Simple class to generate random values
class CRandom
{
public:
	CRandom();
	~CRandom();
	void setSeed(int newSeed);

	int iRandInt(int from, int to);
	double dRandDouble(double from, double to);

private:
	int seed;
	std::mt19937 generator;
	std::random_device device;
};

