#include "pch.h"
#include "CSolution.h"

CSolution::CSolution()
{
}

CSolution::CSolution(const char* n, double qual, std::vector<double> sol)
{
	vSetName(n);
	vSetSolution(sol);
	vsetQuality(qual);
}

CSolution::~CSolution()
{
}
