#pragma once
#include "CRandom.h"
#include "Matrix.h"
#include "CMscnProblem.h"
#include "COptimizer.h"
#define MIN_VAL 0

#define amountOfConst 4
template<typename T>
class CRandomSearch: public COptimizer<T>
{
public:
	CRandomSearch();
	CRandomSearch(CProblem<T> *newInstance);
	~CRandomSearch();

	std::vector<T> getSolution(double time);
	std::vector<T> getSolutionShow(double time);

	std::vector<T> generateSingleSol(unsigned int seed);
	void setInstance(CProblem<T> *newInstance);
	void setInstance(CMscnProblem<T> &newInstance);
	CProblem<T> *getInstance() { return this->actualInstance ; }
	

	void vshowActualInstance();
	void vshowActualSol();
private:	
};

// Specialized functions
template<>
std::vector<int> CRandomSearch<int>::getSolution(double time);

template<>
std::vector<int> CRandomSearch<int>::getSolutionShow(double time);

template<>
std::vector<int> CRandomSearch<int>::generateSingleSol(unsigned int seed);

template<>
std::vector<double> CRandomSearch<double>::getSolution(double time);

template<>
std::vector<double> CRandomSearch<double>::getSolutionShow(double time);

template<>
std::vector<double> CRandomSearch<double>::generateSingleSol(unsigned int seed);

// Functions for every type
template<typename T>
CRandomSearch<T>::CRandomSearch()
{
}

template<typename T>
CRandomSearch<T>::CRandomSearch(CProblem<T> *newInstance)
{
	this->actualInstance = newInstance;
}

template<typename T>
CRandomSearch<T>::~CRandomSearch()
{
}

template<typename T>
std::vector<T> CRandomSearch<T>::getSolution(double time) {
	return this->generateSingleSol();
}

template<typename T>
std::vector<T> CRandomSearch<T>::generateSingleSol(unsigned int seed) {
	return std::vector<T>();
}

template<typename T>
void CRandomSearch<T>::setInstance(CProblem<T> *newInstance)
{
	this->actualInstance = newInstance;
}

template<typename T>
void CRandomSearch<T>::setInstance(CMscnProblem<T> &newInstance)
{
	this->actualInstance = new CMscnProblem<T>(newInstance);
}

template<typename T>
void CRandomSearch<T>::vshowActualInstance()
{
	this->actualInstance->vShowInstance();
}
template<typename T>
void CRandomSearch<T>::vshowActualSol()
{
	this->actualInstance->vShowSolution();
}