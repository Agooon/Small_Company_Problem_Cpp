#pragma once
#include "COptimizer.h"
template<typename T>
class CMeanSolver: public COptimizer<T>
{
public:
	CMeanSolver();
	~CMeanSolver();

	inline std::vector<T> getSolution(double time) { return this->generateSingleSol(); }
	inline std::vector<T> generateSingleSol();
};


template<>
std::vector<int> CMeanSolver<int>::generateSingleSol();

template<>
std::vector<double> CMeanSolver<double>::generateSingleSol();

template<typename T>
CMeanSolver<T>::CMeanSolver()
{
}

template<typename T>
CMeanSolver<T>::~CMeanSolver()
{
}
template<typename T>
std::vector<T> CMeanSolver<T>::generateSingleSol() {
	return std::vector<T>();
}
