#pragma once
#include "CRandom.h"
#include "Matrix.h"

template<typename T>
class CProblem
{
public:
	inline CProblem();
	inline ~CProblem();

	virtual bool bReadFromFileInst(const char *name)=0;
	virtual bool bSaveToFileInst(const char *name)=0;

	virtual bool bReadFromFileSol(const char *name)=0;
	virtual bool bSaveToFileSol(const char *name)=0;

	virtual double dGetQuality(std::vector<T> &pdSol) = 0;
	virtual bool bConstraintsSatisfied(std::vector<T> pdSol) = 0;

	virtual void vShowInstance()=0;
	virtual void vShowSolution()=0;


	virtual int getLength() { return this->lengthOfSol; }
	virtual int getErrCode() { return this->errCode; }
	virtual std::vector< std::pair<T, T>> getMinMax() { return this->minmax; }
protected:
	std::vector< std::pair<T,T>> minmax;
	CRandom myGenerator;
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