#pragma once
#include "COptimizer.h"
// Simple class, was a modification on checking exercise with 
// creating an abstract class COptimizer
template<typename T>
class CMeanSolver: public COptimizer<T>
{
public:
	CMeanSolver();
	~CMeanSolver();

	inline std::vector<T> getSolution(double time) { return this->generateSingleSol(); }
	inline std::vector<T> generateSingleSol();
};

// Specialized finctions

//Specialized INT
template<>
std::vector<int> CMeanSolver<int>::generateSingleSol();

//Specialized DOUBLE
template<>
std::vector<double> CMeanSolver<double>::generateSingleSol();

// Functions for every type

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
