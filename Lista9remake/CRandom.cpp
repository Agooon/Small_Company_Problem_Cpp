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

CRandom::CRandom(unsigned int seed)
{
	this->setSeed(seed);
}
void CRandom::setSeed(unsigned int newSeed) {
	seed = newSeed;
	generator.seed(seed);
}

int CRandom::iRandInt(int from, int to)
{
	if (from > to) return to;
	std::uniform_int_distribution<> distr(from, to);
	return distr(generator);
}

unsigned int CRandom::iRandUInt(unsigned int from, unsigned int to)
{
	if (from >= to-1) return to;
	std::uniform_int_distribution<> distr(from-INT_MAX, to-INT_MAX-1);
	return distr(generator)+INT_MAX;
}

double CRandom::dRandDouble(double from, double to)
{
	if (from > to) return to;
	std::uniform_real_distribution<> distr(from, to);
	return distr(generator);
}
