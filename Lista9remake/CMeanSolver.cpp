#include "pch.h"
#include "CMeanSolver.h"

template<>
std::vector<int> CMeanSolver<int>::generateSingleSol()
{
	std::vector<int> newSol;
	for (int i = 0; i < this->actualInstance->getLength(); i++) {
		newSol.push_back((this->actualInstance->getMinMax()[i].first + this->actualInstance->getMinMax()[i].second) / 2);
	}
	this->actualSol = newSol;
	std::cout << std::endl << "Quality: " << this->actualInstance->dGetQuality(actualSol);
	return this->actualSol;
}

template<>
std::vector<double> CMeanSolver<double>::generateSingleSol()
{
	std::vector<double> newSol;
	for (int i = 0; i < this->actualInstance->getLength(); i++) {
		newSol.push_back((this->actualInstance->getMinMax()[i].first + this->actualInstance->getMinMax()[i].second) / 2);
	}
	this->actualSol = newSol;
	std::cout << std::endl << "Quality: " << this->actualInstance->dGetQuality(actualSol);
	return this->actualSol;
}

template class CMeanSolver<double>;
template class CMeanSolver<int>;