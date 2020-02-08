#pragma once
#pragma warning(disable:4244)
#include "CRandom.h"
#include "CMscnProblem.h"
#include "COptimizer.h"
#include "MyInt.h"
#define amountOfConst 4

#define CrossProb 0.95
#define diffWeight 0.4

#define default_D 2
#define default_F 2
#define default_M 2
#define default_S 2
#define default_population 1000

#define MIN_VAL 0
template<typename T>
class CDiffEvol: public COptimizer<T>
{
public:
	CDiffEvol();
	CDiffEvol(CProblem<T> *newProblem, int amount);
	CDiffEvol(CProblem<T> *newProblem, int amount, double cross, double weight);
	
	~CDiffEvol();

	inline void setPopulation(int amount);

	inline std::vector<T> generateSol(int seed);
	inline std::vector<T> generateSingleSol() { return this->generateSol(this->device()); }

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
	int amountOfPopulation=default_population;
};

template<>
void CDiffEvol<int>::setPopulation(int amount);

template<>
void CDiffEvol<double>::setPopulation(int amount);

template<>
std::vector<int> CDiffEvol<int>::generateSol(int seed);

template<>
std::vector<double> CDiffEvol<double>::generateSol(int seed);


template<>
std::vector<int> CDiffEvol<int>::getSolution(double time);

template<>
std::vector<double> CDiffEvol<double>::getSolution(double time);


template<>
void CDiffEvol<MyInt>::setPopulation(int amount);

template<>
std::vector<MyInt> CDiffEvol<MyInt>::generateSol(int seed);


template<>
std::vector<MyInt> CDiffEvol<MyInt>::getSolution(double time);


template<typename T>
CDiffEvol<T>::CDiffEvol()
{
	//	generateInstance(default_D, default_F, default_M, default_S);
	//	setPopulation(default_population);
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
std::vector<T> CDiffEvol<T>::generateSol(int seed) {
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

}

