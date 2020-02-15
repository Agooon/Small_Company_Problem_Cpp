#pragma once
#pragma warning(disable:4244)
#include "CRandom.h"
#include "CMscnProblem.h"
#include "COptimizer.h"
#define amountOfConst 4

#define CrossProb 0.95
#define diffWeight 0.4


#define default_population 1000

#define MIN_VAL 0
template<typename T>
class CDiffEvol: public COptimizer<T>
{
public:
	CDiffEvol();
	CDiffEvol(CProblem<T>* newProblem);
	CDiffEvol(CProblem<T> *newProblem, int amount);
	CDiffEvol(CProblem<T> *newProblem, int amount, double cross, double weight);
	
	~CDiffEvol();

	inline void setPopulation(int amount);

	inline std::vector<T> generateSingleSol(unsigned int seed);

	inline void setInstance(CProblem<T> *newProblem) { this->actualInstance = newProblem; }
	inline CProblem<T>* getInstance() { return this->actualInstance; }

	inline bool bindividualsAreDifferent(int ind, int baseInd, int addInd0, int addInd1);

	inline std::vector<T> getSolution(double time);

	void vsetWeight(double weight) { this->diffweight = weight; }
	void vsetCross(double cross) { this->crossProb = cross; }
	void vshowActualInstance();
	void vshowActualSol();
private:
	double crossProb = CrossProb;
	double diffweight = diffWeight;
	std::vector<std::vector<T>> population;
	int amountOfPopulation=0;
};

// Specialized functions

//Specialized INT
template<>
void CDiffEvol<int>::setPopulation(int amount);

template<>
std::vector<int> CDiffEvol<int>::generateSingleSol(unsigned int seed);

template<>
std::vector<int> CDiffEvol<int>::getSolution(double time);

//Specialized DOUBLE
template<>
void CDiffEvol<double>::setPopulation(int amount);

template<>
std::vector<double> CDiffEvol<double>::generateSingleSol(unsigned int seed);

template<>
std::vector<double> CDiffEvol<double>::getSolution(double time);

// Functions for every type
template<typename T>
CDiffEvol<T>::CDiffEvol()
{
}

template<typename T>
CDiffEvol<T>::CDiffEvol(CProblem<T>* newProblem)
{
	this->setInstance(newProblem);
	this->setPopulation(default_population);
	this->amountOfPopulation = default_population;
}

template<typename T>
CDiffEvol<T>::CDiffEvol(CProblem<T> *newProblem, int amount)
{
	this->setInstance(newProblem);
	this->setPopulation(amount);
	this->amountOfPopulation = amount;
}

template<typename T>
CDiffEvol<T>::CDiffEvol(CProblem<T> *newProblem, int amount, double cross, double weight)
{
	this->setInstance(newProblem);
	this->setPopulation(amount);
	this->amountOfPopulation = amount;
	this->crossProb = cross;
	this->diffweight = weight;
}

template<typename T>
CDiffEvol<T>::~CDiffEvol()
{
}

template<typename T>
std::vector<T> CDiffEvol<T>::generateSingleSol(unsigned int seed) {
	// No implementation for types other then int/double
	return std::vector<T>();
}

template<typename T>
bool CDiffEvol<T>::bindividualsAreDifferent(int ind, int baseInd, int addInd0, int addInd1)
{
	return (ind != baseInd && ind != addInd0 && ind != addInd1 &&
			baseInd != addInd0 && baseInd != addInd1 &&
			addInd0 != addInd1);
}

template<typename T>
void CDiffEvol<T>::vshowActualInstance()
{
	this->actualInstance->vShowInstance();
}

template<typename T>
void CDiffEvol<T>::vshowActualSol()
{
	this->actualInstance->vShowSolution();
}

template<typename T>
void CDiffEvol<T>::setPopulation(int amount)
{
	// No implementation for types other then int/double
}

