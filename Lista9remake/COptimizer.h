#pragma once
#include "CRandom.h"
#include "CProblem.h"
#include "CTimer.h"
#pragma warning(disable:4244)

// Abstract class for optimizers

template<typename T>
class COptimizer
{
public:
	COptimizer();
	~COptimizer();

	virtual std::vector<T> getSolution(double time)=0;
	virtual std::vector<T> generateSingleSol()=0;
	virtual void setInstance(CProblem<T> *newInstance) { actualInstance = newInstance; }
	CProblem<T> *getInstance() { return actualInstance; }
protected:
	CTimer timer;
	int errCode = 0;
	std::vector<T> actualSol;
	CProblem<T> *actualInstance;

	// Most of optimizers would like to use random values, some don't need it
	// I leave it here, becouse in both optimizers that work, random numbers are needed
	std::random_device device; 
	CRandom myGenerator;
};

template <typename T>
COptimizer<T>::COptimizer()
{
}

template <typename T>
COptimizer<T>::~COptimizer()
{
}