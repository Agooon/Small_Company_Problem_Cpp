#include "pch.h"
#include "CRandomSearch.h"
#pragma warning(disable: 4244)

//Specialized INT
template<>
std::vector<int> CRandomSearch<int>::getSolution(double time)
{
	this->myGenerator.setSeed(this->device());

	std::vector<int> newSol;
	this->actualSol.clear();
	this->timer.vsetD_secs(0);
	this->timer.queryPerfStart();
	this->timer.queryPerfFreq();
	while (timer.dgetD_secs() < time / 1000) {
		newSol = this->generateSingleSol(myGenerator.iRandUInt(0, UINT_MAX));

		// There is no solution yet
		if (actualSol.empty()) {
			this->actualInstance->dGetQuality(newSol);

			this->actualSol.assign(newSol.begin(), newSol.end());
		}
		// There is a solution, but new one is better
		else if (this->actualInstance->dGetQuality(newSol) > this->actualInstance->dGetQuality(actualSol)) {
				actualSol.assign(newSol.begin(), newSol.end());
			}
		
		this->timer.queryPerfEnd();
		this->timer.vsetD_secs(this->timer.getliEnd(), this->timer.getliStart(), this->timer.getliFreq());
	}//while(clock()<end)

	return this->actualSol;
}

template<>
std::vector<int> CRandomSearch<int>::getSolutionShow(double time)
{
	this->myGenerator.setSeed(this->device());

	std::vector<int> newSol;
	this->actualSol.clear();
	this->timer.vsetD_secs(0);
	this->timer.queryPerfStart();
	this->timer.queryPerfFreq();
	while (timer.dgetD_secs() < time / 1000) {
		newSol = this->generateSingleSol(myGenerator.iRandUInt(0, UINT_MAX));

		// There is no solution yet
		if (actualSol.empty()) {
			this->actualInstance->dGetQuality(newSol);

			this->actualSol.assign(newSol.begin(), newSol.end());
		}

		// There is a solution, but new one is better
		else if (this->actualInstance->dGetQuality(newSol) > this->actualInstance->dGetQuality(actualSol)) {
				actualSol.assign(newSol.begin(), newSol.end());

				std::cout << std::endl << "Quality of new better solution: " << this->actualInstance->dGetQuality(actualSol) << std::endl;
			 }
	
		this->timer.queryPerfEnd();
		this->timer.vsetD_secs(this->timer.getliEnd(), this->timer.getliStart(), this->timer.getliFreq());
	}//while(clock()<end)

	return this->actualSol;
}

template<>
std::vector<int> CRandomSearch<int>::generateSingleSol(unsigned int seed)
{
	this->myGenerator.setSeed(seed);
	std::vector<int> newSol;
	newSol.resize(0);
	for (int i = 0; i < this->actualInstance->getLength(); i++) {
		newSol.push_back(this->myGenerator.dRandDouble(this->actualInstance->getMinMax()[i].first, this->actualInstance->getMinMax()[i].second));
	}
	return newSol;
}

//Specialized DOUBLE
template<>
std::vector<double> CRandomSearch<double>::getSolution(double time)
{
	this->myGenerator.setSeed(this->device());

	std::vector<double> newSol;
	this->actualSol.clear();
	this->timer.vsetD_secs(0);
	this->timer.queryPerfStart();
	this->timer.queryPerfFreq();
	while (timer.dgetD_secs() < time / 1000) {
		newSol = this->generateSingleSol(myGenerator.iRandUInt(0, UINT_MAX));

		// There is no solution yet
		if (actualSol.empty()) {
			this->actualInstance->dGetQuality(newSol);

			this->actualSol.assign(newSol.begin(), newSol.end());
		}

		// There is a solution, but new one is better
		else if (this->actualInstance->dGetQuality(newSol) > this->actualInstance->dGetQuality(actualSol)) {
				this->actualSol.assign(newSol.begin(), newSol.end());
			}
		
		this->timer.queryPerfEnd();
		this->timer.vsetD_secs(this->timer.getliEnd(), this->timer.getliStart(), this->timer.getliFreq());
	}//while(clock()<end)

	return this->actualSol;
}

template<>
std::vector<double> CRandomSearch<double>::getSolutionShow(double time)
{
	this->myGenerator.setSeed(this->device());

	std::vector<double> newSol;
	this->actualSol.clear();
	this->timer.vsetD_secs(0);
	this->timer.queryPerfStart();
	this->timer.queryPerfFreq();
	while (timer.dgetD_secs() < time / 1000) {
		newSol = this->generateSingleSol(myGenerator.iRandUInt(0, UINT_MAX));

		// There is no solution yet
		if (actualSol.empty()) {
			this->actualInstance->dGetQuality(newSol);

			this->actualSol.assign(newSol.begin(), newSol.end());
		}

		// There is a solution, but new one is better
		else if (this->actualInstance->dGetQuality(newSol) > this->actualInstance->dGetQuality(actualSol)) {
			this->actualSol.assign(newSol.begin(), newSol.end());
			std::cout << std::endl << "Quality of new better solution: " << this->actualInstance->dGetQuality(actualSol) << std::endl;
		}

		this->timer.queryPerfEnd();
		this->timer.vsetD_secs(this->timer.getliEnd(), this->timer.getliStart(), this->timer.getliFreq());
	}//while(clock()<end)

	return this->actualSol;
}

template<>
std::vector<double> CRandomSearch<double>::generateSingleSol(unsigned int seed)
{
	this->myGenerator.setSeed(seed);
	std::vector<double> newSol;
	for (int i = 0; i < this->actualInstance->getLength(); i++) {
		newSol.push_back(this->myGenerator.dRandDouble(this->actualInstance->getMinMax()[i].first, this->actualInstance->getMinMax()[i].second));
	}
	return newSol;
}

template class CRandomSearch<double>;
template class CRandomSearch<int>;
