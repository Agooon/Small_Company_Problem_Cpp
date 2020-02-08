#pragma once
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
	std::default_random_engine generator;
	std::random_device device;
};

