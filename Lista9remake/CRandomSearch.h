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
	~CRandomSearch();

	inline std::vector<T> getSolution(double time);

	inline std::vector<T> generateSingleSol();
	inline void setInstance(CProblem<T> *newInstance);
	inline CProblem<T> *getInstance() { return this->actualInstance ; }
	

	void vshowActualInstance();
	void vshowActualSol();
private:	
};

template<>
std::vector<int> CRandomSearch<int>::getSolution(double time);

template<>
std::vector<double> CRandomSearch<double>::getSolution(double time);

template<>
std::vector<int> CRandomSearch<int>::generateSingleSol();

template<>
std::vector<double> CRandomSearch<double>::generateSingleSol();


template<typename T>
CRandomSearch<T>::CRandomSearch()
{
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
std::vector<T> CRandomSearch<T>::generateSingleSol() {
	return std::vector<T>();
}

template<typename T>
void CRandomSearch<T>::setInstance(CProblem<T> *newInstance)
{
	this->actualInstance = newInstance;
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