#pragma once
#include "CRandom.h"
#include "Matrix.h"

// Abstract class for "problems"

template<typename T>
class CProblem
{
public:
	CProblem();
	CProblem(const char *name);
	~CProblem();

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

	size_t getLength() { return this->lengthOfSol; }
	int getErrCode() { return this->errCode; }
	std::vector< std::pair<T, T>> getMinMax() { return this->minmax; }

	void setName(const char *newName) { this->nameOfInst = newName; }
	std::string getName() { return nameOfInst; }
protected:
	std::string nameOfInst;
	std::vector< std::pair<T,T>> minmax; // Here every problem estimate some border values
	int errCode = 0;
	std::vector<T> pdSolution;
	size_t lengthOfSol=0;
};

template <typename T>
CProblem<T>::CProblem()
{
}
template <typename T>
CProblem<T>::CProblem(const char *name)
{
	this->bReadFromFileInst(name);
}

template <typename T>
CProblem<T>::~CProblem()
{
}