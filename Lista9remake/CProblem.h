#pragma once
#include "CRandom.h"
#include "Matrix.h"

// Abstract class for "problems"

template<typename T>
class CProblem
{
public:
	inline CProblem();
	inline ~CProblem();

	// Every problem/solution should be put in some kind of file
	// so this methods are nessesary
	virtual bool bReadFromFileInst(const char *name)=0;
	virtual bool bSaveToFileInst(const char *name)=0;

	virtual bool bReadFromFileSol(const char *name)=0;
	virtual bool bSaveToFileSol(const char *name)=0;

	// dGetQuality - gives back the "score" of solution to this problem.
	// bConstraintsSatisfied - checks if solution is correct (check min/max values, etc.)
	virtual double dGetQuality(std::vector<T> &pdSol) = 0;
	virtual bool bConstraintsSatisfied(std::vector<T> pdSol) = 0;

	// Just for showing results/problems during the program
	virtual void vShowInstance()=0;
	virtual void vShowSolution()=0;

	virtual int getLength() { return this->lengthOfSol; }
	virtual int getErrCode() { return this->errCode; }
	virtual std::vector< std::pair<T, T>> getMinMax() { return this->minmax; }
protected:
	std::vector< std::pair<T,T>> minmax; // Here every problem estimate some border values
	int errCode = 0;
	std::vector<T> pdSolution;
	int lengthOfSol;
};

template <typename T>
CProblem<T>::CProblem()
{
}

template <typename T>
CProblem<T>::~CProblem()
{
}