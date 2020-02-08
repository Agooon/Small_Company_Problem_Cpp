#pragma once
#include "COptimizer.h"
template <typename T>
class CTrivMethod: public COptimizer<T>
{
public:
	CTrivMethod();
	~CTrivMethod();

	inline std::vector<T> getSolution(double time) { return this->generateSingleSol(); }
	inline std::vector<T> generateSingleSol();
	void setInstance(CProblem<T> *newInstance) { this->actualInstance = newInstance; }
};

template <>
std::vector<int> CTrivMethod<int>::generateSingleSol();
template <>
std::vector<double> CTrivMethod<double>::generateSingleSol();

template <typename T>
CTrivMethod<T>::CTrivMethod()
{
}

template <typename T>
CTrivMethod<T>::~CTrivMethod()
{
}
template <typename T>
std::vector<T> CTrivMethod<T>::generateSingleSol() {
	return std::vector<T>();
}
