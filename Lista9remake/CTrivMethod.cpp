#include "pch.h"
#include "CTrivMethod.h"

//Specialized INT
template <>
std::vector<int> CTrivMethod<int>::generateSingleSol()
{
	std::vector<int> newSol;
	for (int i = 0; i < this->actualInstance->getLength(); i++) {
		newSol.push_back(i + 1);
	}
	this->actualSol = newSol;
	std::cout << std::endl << "Quality: " << this->actualInstance->dGetQuality(actualSol);
	return this->actualSol;
}

//Specialized DOUBLE
template <>
std::vector<double> CTrivMethod<double>::generateSingleSol()
{
	std::vector<double> newSol;
	for (int i = 0; i < this->actualInstance->getLength(); i++) {
		newSol.push_back(i + 1);
	}
	this->actualSol = newSol;
	std::cout << std::endl << "Quality: " << this->actualInstance->dGetQuality(actualSol);
	return this->actualSol;
}

template class CTrivMethod<double>;
template class CTrivMethod<int>;