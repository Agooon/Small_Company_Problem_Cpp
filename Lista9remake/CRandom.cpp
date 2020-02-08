#include "pch.h"
#include "CRandom.h"

CRandom::CRandom()
{
	seed = device();
	generator.seed(seed);
}

CRandom::~CRandom()
{
}
void CRandom::setSeed(int newSeed) {
	seed = newSeed;
	generator.seed(seed);
}

int CRandom::iRandInt(int from, int to)
{
	if (from > to) return to;
	std::uniform_int_distribution<int> distr(from, to);
	return distr(generator);
}

double CRandom::dRandDouble(double from, double to)
{
	if (from > to) return to;
	std::uniform_real_distribution<double> distr(from, to);
	return distr(generator);
}
