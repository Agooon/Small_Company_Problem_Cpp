#include "pch.h"
#include "CDiffEvol.h"
// The task was to make template class that can take integers.
// CDiffEvol works for integer type, it wasn't nessesary to optimize functionality for this type.
// And as you would expect, it works really bad.

//Specialized INT
template<>
void CDiffEvol<int>::setPopulation(int amount)
{
	this->population.clear();
	this->amountOfPopulation = amount;
	myGenerator.setSeed(this->device());
	std::vector <int> newSol;
	for (int i = 0; i < amount; i++) {
		newSol = this->generateSingleSol(myGenerator.iRandUInt(0, UINT_MAX));
		this->actualInstance->dGetQuality(newSol);
		this->population.push_back(newSol);
	}
}

template<>
std::vector<int> CDiffEvol<int>::generateSingleSol(unsigned int seed)
{
	this->myGenerator.setSeed(seed);
	std::vector<int> newSol;
	for (int i = 0; i < this->actualInstance->getLength(); i++) {
		newSol.push_back(this->myGenerator.iRandInt(this->actualInstance->getMinMax()[i].first, this->actualInstance->getMinMax()[i].second));
	}
	return newSol;
}

template<>
std::vector<int> CDiffEvol<int>::getSolution(double time)
{
	std::cout << std::endl << "---------------" << std::endl;
	this->myGenerator.setSeed(this->device());
	std::vector<int> baseInd, addInd0, addInd1, indNew;
	int indexBase, indexAdd0, indexAdd1;
	size_t genotypeSize =(size_t) this->population[0].size();
	indNew.resize(genotypeSize);

	this->timer.vsetD_secs(0);
	this->timer.queryPerfStart();
	this->timer.queryPerfFreq();
	while (timer.dgetD_secs() < time / 1000) {
		std::cout << std::endl << "Quality of the first solution from population: " << this->actualInstance->dGetQuality(population[0]);
		// I put here the "std::cout" to show how algorithm improves the population. // To improve the algorithm you can comment it out.
		for (int i = 0; i < this->amountOfPopulation; i++) {
			indexBase = this->myGenerator.iRandInt(0, this->amountOfPopulation - 1);
			indexAdd0 = this->myGenerator.iRandInt(0, this->amountOfPopulation - 1);
			indexAdd1 = this->myGenerator.iRandInt(0, this->amountOfPopulation - 1);

			if (bindividualsAreDifferent(i, indexBase, indexAdd0, indexAdd1)) {
				baseInd = this->population[indexBase];
				addInd0 = this->population[indexAdd0];
				addInd1 = this->population[indexAdd1];
				for (size_t geneOffset = 0; geneOffset < genotypeSize; geneOffset++) {
					if (this->myGenerator.dRandDouble(0, 1) < crossProb) {
						indNew[geneOffset] = baseInd[geneOffset]
							+ diffweight * (addInd0[geneOffset] - (__int64)addInd1[geneOffset]);
					}
					else {
						indNew[geneOffset] = this->population[i][geneOffset];
					}
				}
				if (this->actualInstance->bConstraintsSatisfied(indNew) &&
					this->actualInstance->dGetQuality(indNew) >= this->actualInstance->dGetQuality(population[i])) {
					this->population[i] = indNew;
				}
			}
		}
		this->timer.queryPerfEnd();
		this->timer.vsetD_secs(this->timer.getliEnd(), this->timer.getliStart(), this->timer.getliFreq());
	}
	this->actualSol = this->population[0];
	for (int i = 1; i < this->amountOfPopulation; i++) {
		if (this->actualInstance->dGetQuality(actualSol) < this->actualInstance->dGetQuality(population[i])) {
			this->actualSol = this->population[i];
		}

	}
	std::cout << std::endl << "Quality of the first solution from population: " << this->actualInstance->dGetQuality(this->population[0]);
	std::cout << std::endl << "The best solution from population: " << this->actualInstance->dGetQuality(this->actualSol) << std::endl;

	return this->actualSol;
}

//Specialized DOUBLE
template<>
void CDiffEvol<double>::setPopulation(int amount)
{
	this->population.clear();
	this->amountOfPopulation = amount;
	myGenerator.setSeed(this->device());
	std::vector <double> newSol;
	for (int i = 0; i < amount; i++) {
		newSol = this->generateSingleSol(myGenerator.iRandUInt(0, UINT_MAX));
		this->actualInstance->dGetQuality(newSol);
		this->population.push_back(newSol);
	}
}

template<>
std::vector<double> CDiffEvol<double>::generateSingleSol(unsigned int seed)
{
	this->myGenerator.setSeed(seed);
	std::vector<double> newSol;
	for (int i = 0; i < this->actualInstance->getLength(); i++) {
		newSol.push_back(this->myGenerator.dRandDouble(this->actualInstance->getMinMax()[i].first, this->actualInstance->getMinMax()[i].second));
	}
	return newSol;
}

template<>
std::vector<double> CDiffEvol<double>::getSolution(double time)
{
	std::cout << std::endl << "---------------" << std::endl;
	this->myGenerator.setSeed(this->device());
	std::vector<double> baseInd, addInd0, addInd1, indNew;
	int indexBase, indexAdd0, indexAdd1;
	size_t genotypeSize = this->population[0].size();
	indNew.resize(genotypeSize);

	this->timer.vsetD_secs(0);
	this->timer.queryPerfStart();
	this->timer.queryPerfFreq();
	while (timer.dgetD_secs() < time / 1000) {
		std::cout << std::endl << "Quality of the first solution from population: " << this->actualInstance->dGetQuality(population[0]);
		// I put here the "std::cout" to show how algorithm improves the population. // To improve the algorithm you can comment it out.
		for (int i = 0; i < this->amountOfPopulation; i++) {
			indexBase = this->myGenerator.iRandInt(0, this->amountOfPopulation - 1);
			indexAdd0 = this->myGenerator.iRandInt(0, this->amountOfPopulation - 1);
			indexAdd1 = this->myGenerator.iRandInt(0, this->amountOfPopulation - 1);

			if (this->bindividualsAreDifferent(i, indexBase, indexAdd0, indexAdd1)) {
				baseInd = this->population[indexBase];
				addInd0 = this->population[indexAdd0];
				addInd1 = this->population[indexAdd1];
				for (size_t geneOffset = 0; geneOffset < genotypeSize; geneOffset++) {
					if (this->myGenerator.dRandDouble(0, 1) < crossProb) {
						indNew[geneOffset] = baseInd[geneOffset]
							+ diffweight * (addInd0[geneOffset] - addInd1[geneOffset]);
					}
					else {
						indNew[geneOffset] = this->population[i][geneOffset];
					}
				}
				if (this->actualInstance->bConstraintsSatisfied(indNew) &&
					this->actualInstance->dGetQuality(indNew) >= this->actualInstance->dGetQuality(population[i])) {
					this->population[i] = indNew;
				}
			}
		}
		this->timer.queryPerfEnd();
		this->timer.vsetD_secs(this->timer.getliEnd(), this->timer.getliStart(), this->timer.getliFreq());
	}
	this->actualSol = this->population[0];
	for (int i = 1; i < this->amountOfPopulation; i++) {
		if (this->actualInstance->dGetQuality(actualSol) < this->actualInstance->dGetQuality(population[i])) {
			this->actualSol = this->population[i];
		}

	}
	std::cout << std::endl << "Quality of the first solution from population: " << this->actualInstance->dGetQuality(this->population[0]);
	std::cout << std::endl << "The best solution from population: " << this->actualInstance->dGetQuality(this->actualSol) << std::endl;

	return this->actualSol;
}

template class CDiffEvol<double>;
template class CDiffEvol<int>;