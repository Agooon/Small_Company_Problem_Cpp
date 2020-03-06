#pragma once
#pragma warning(disable: 4996)
#pragma warning(disable: 4244)
#pragma warning(disable: 6031)
#pragma warning(disable: 4477)
#include "CRandom.h"
#include "Matrix.h"
#include "CProblem.h"
#define NO_ERR 0;
#define PD_SOLUTION_ERR_NOT_EXIST 1
#define PD_SOLUTION_ERR_WRONG_SIZE 2
#define PD_SOLUTION_ERR_INFORMATION 3
#define PD_SOLUTION_ERR_NEGATIVE_VAL 4
#define WRONG_INDEX 5
#define WRONG_SIZE 6
#define FILE_POINTER_IS_NULL 7
#define WRONG_SOLUTION_FROM_FILE 8

#define amountOfConst 4
// For repearing  solution in dGetQuality
#define differenceRepair 1.03

// For generating close to reality problem
#define rand_multiplier1_5 1.5
#define rand_multiplier 2.0
#define rand_multiplier3 3
#define rand_multiplier4 4.0
#define rand_multiplier8 8.0
#define rand_multiplier12 12.0

// CMSCProblem is a class for a main problem of a task
// Short explanation of it is in "Lista9remake.cpp"

template<typename T>
class CMscnProblem: public CProblem<T>
{
public:
	CMscnProblem();
	~CMscnProblem();
	CMscnProblem(const CMscnProblem<T> &copyProblem);
	CMscnProblem(int d, int f, int m, int s, int seed, int min, int max);

////---- Getters for each val ----////

	int getDostL() { return this->dostL; }
	int getFabL()  { return this->fabL; }
	int getMagL()  { return this->magL; }
	int getSklL()  { return this->sklL; }

	Matrix<T> getCd() const { return this->cd; }
	Matrix<T> getCf() const { return this->cf; }
	Matrix<T> getCm() const { return this->cm; }

	std::vector<T> getUd() { return this->ud; }
	std::vector<T> getUf() { return this->uf; }
	std::vector<T> getUm() { return this->um; }
	std::vector<T> getp()  { return this->p; }

	std::vector<T> getSd() { return this->sd; }
	std::vector<T> getSf() { return this->sf; }
	std::vector<T> getSm() { return this->sm; }
	std::vector<T> getSs() { return this->ss; }

	Matrix<T> getXdminmax() const { return this->xdminmax; }
	Matrix<T> getXfminmax() const { return this->xfminmax; }
	Matrix<T> getXmminmax() const { return this->xmminmax; }


	Matrix<T> getXd() const { return this->xd; }
	Matrix<T> getXf() const { return this->xf; }
	Matrix<T> getXm() const { return this->xm; }
	void vSaveSolution();
	void vSaveSolution(std::vector<T> &pdSol);
	std::vector<T> getSolution() { return this->pdSolution; }

////---- Setting values inside of vectors/matrixs ----////

	bool bsetCd(int indX, int  indY, T value);
	bool bsetCf(int indX, int  indY, T value);
	bool bsetCm(int indX, int  indY, T value);

	bool bsetSd(int indX, T value);
	bool bsetSf(int indX, T value);
	bool bsetSm(int indX, T value);
	bool bsetSs(int indX, T value);

	bool bsetUd(int indX, T value);
	bool bsetUf(int indX, T value);
	bool bsetUm(int indX, T value);
	bool bsetP(int indX, T value);

////---- Changing amout of vectors and matrixs ----////

	bool bsetDostL(int value);
	bool bsetFabL (int value);
	bool bsetMagL (int value);
	bool bsetSklL (int value);

////---- Other functions ----////

	// Functions from abstract class
	bool bConstraintsSatisfied(std::vector<T> pdSol);
	double dGetQuality(std::vector<T> &pdSol);

	bool bReadFromFileInst(const char *name);
	bool bSaveToFileInst(const char *name);

	bool bReadFromFileSol(const char *name);
	bool bSaveToFileSol(const char *name);

	// Functions for generating random problem
	void vsetBasics(int d, int f, int m, int s);
	void vGenerateInstance(int d, int f, int m, int s, int iInstanceSeed, double minVal, double maxVal);

	void vsetInstance(const CMscnProblem<T> &newInstance);

////--- Functions for checking the status of the problem/solution ----////

	void vShowInstance();
	void vShowSolution();

////////////////////////////////////////////////////////////////

	int geterrCode() { return this->errCode; }
private:

	// Functions for dGetQuality for repearing the solution
	inline void vRepairMinmax(std::vector<T> &pdSol);
	inline void vRepairLimits(std::vector<T> &pdSol);

	// Functions for bConstraintsSatisfied to check the if solution is correct
	inline bool checkBasicCorrectness(std::vector<T> pdSol);
	inline bool bCheckMinMax(std::vector<T> pdSol);
	inline bool helperCheckMinMax(int index, Matrix<T> minmaxS, T value);
	inline bool bCheckOverload();

	CRandom myGenerator;
	inline void vsetMinmax();
// amount of suppliers/fabrics/warehouses/shops
	int dostL = 0; // dostL - amount of suppliers 
	int fabL = 0; // fabL - amount of fabrics
	int magL = 0; // magL - amount of warehouses
	int sklL = 0; // sklL - amount of shops

//////------- Data of The Problem -------//////

//-- Costs of production/transportation raw materials/products on each stage --//

	Matrix<T> cd; // cost of buying and transportingvraw materials from supplier X to fabric Y
	Matrix<T> cf; // cost of creating and transporting products from fabric X to warehouse Y
	Matrix<T> cm; // cost of storing and transporting products from warehouse X to shop Y

	// In the task maintaining shops/selling products was for free

//-- Processing capacity of suppliers/fabrics/warehouses/shops --//

	std::vector<T> sd;// array of processing capacity of suppliers
	std::vector<T> sf;// array of processing capacity of fabrics
	std::vector<T> sm;// array of processing capacity of warehouses
	std::vector<T> ss;// array of processing capacity of shops

//-- Maintenance costs suppliers/fabrics/warehouses and income of shops --//

	std::vector<T> ud;// array of maintenance costs of suppliers
	std::vector<T> uf;// array of maintenance costs of fabrics
	std::vector<T> um;// array of maintenance costs of warehouses
	std::vector<T> p;// array of incomes of shops	// maintenance costs of the shop=0

//-- Minimum and maximum amounts of xd/xf/xm --//
	// xd/xf/xm are parts of the solution
	// xd - matrix of amount of raw materials transporting from supplier X to fabric Y
	// xf - matrix of amount of products that are created and transported from fabric X to warehouse Y
	// xm - matrix of amount of products that are stored and transported from warehouse X to shop Y

	// xdminmax -  a matrix of heigth dostL*fabL and length 2 (to store minimum and maximum for each value in xd matrix)
	// xfminmax/xmminmax - are similar to above just the heigth is diffent, depending of amount of fabrics/warehouses/shops

	Matrix<T> xdminmax;// explained above
	Matrix<T> xfminmax;// explained above
	Matrix<T> xmminmax;// explained above

	Matrix<T> xd;// explained above
	Matrix<T> xf;// explained above
	Matrix<T> xm;// explained above

};

// Specialized functions

//Specialized INT
template<>
bool CMscnProblem<int>::checkBasicCorrectness(std::vector<int> pdSol);

template<>
double CMscnProblem<int>::dGetQuality(std::vector<int> &pdSol);

template<>
void CMscnProblem<int>::vRepairMinmax(std::vector<int>& pdSol);

template<>
void CMscnProblem<int>::vRepairLimits(std::vector<int> &pdSol);

template<>
bool CMscnProblem<int>::helperCheckMinMax(int index, Matrix<int> minmaxS, int value);

template<>
bool CMscnProblem<int>::bCheckMinMax(std::vector<int> pdSol);

template<>
bool CMscnProblem<int>::bCheckOverload();

template<>
bool CMscnProblem<int>::bReadFromFileInst(const char * name);

template<>
bool CMscnProblem<int>::bReadFromFileSol(const char * name);

template<>
void CMscnProblem<int>::vGenerateInstance(int d, int f, int m, int s, int iInstanceSeed, double minVal, double maxVal);

//Specialized DOUBLE
template<>
bool CMscnProblem<double>::checkBasicCorrectness(std::vector<double> pdSol);

template<>
double CMscnProblem<double>::dGetQuality(std::vector<double> &pdSol);

template<>
void CMscnProblem<double>::vRepairMinmax(std::vector<double>& pdSol);

template<>
void CMscnProblem<double>::vRepairLimits(std::vector<double> &pdSol);

template<>
bool CMscnProblem<double>::helperCheckMinMax(int index, Matrix<double> minmaxS, double value);

template<>
bool CMscnProblem<double>::bCheckMinMax(std::vector<double> pdSol);

template<>
bool CMscnProblem<double>::bCheckOverload();

template<>
bool CMscnProblem<double>::bReadFromFileInst(const char * name);

template<>
bool CMscnProblem<double>::bReadFromFileSol(const char * name);

template<>
void CMscnProblem<double>::vGenerateInstance(int d, int f, int m, int s, int iInstanceSeed, double minVal, double maxVal);


// Functions for every type
template<typename T>
CMscnProblem<T>::CMscnProblem()
{
}

template<typename T>
CMscnProblem<T>::~CMscnProblem()
{
}

template<typename T>
CMscnProblem<T>::CMscnProblem(const CMscnProblem<T> & copyProblem)
{
	this->vsetInstance(copyProblem);
}

template<typename T>
CMscnProblem<T>::CMscnProblem(int d, int f, int m, int s, int seed, int min, int max)
{
	this->vGenerateInstance(d, f, m, s,seed, min, max);
}

template<typename T>
void CMscnProblem<T>::vSaveSolution()
{
	//basic values
	this->pdSolution.push_back(this->dostL); this->pdSolution.push_back(this->fabL);
	this->pdSolution.push_back(this->magL);  this->pdSolution.push_back(this->sklL);
	//xd
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			this->pdSolution.push_back(this->xd.getVal(i, j));
		}
	}
	//xf
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			this->pdSolution.push_back(this->xf.getVal(i, j));
		}
	}
	//xm
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			this->pdSolution.push_back(this->xm.getVal(i, j));
		}
	}
}

template<typename T>
void CMscnProblem<T>::vSaveSolution(std::vector<T>& pdSol)
{
	int index = 4;
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			this->xd.setVal(i, j, pdSol[index++]);
		}
	}
	//xf
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			this->xf.setVal(i, j, pdSol[index++]);
		}
	}
	//xm
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			this->xm.setVal(i, j, pdSol[index++]);
		}
	}
	this->vSaveSolution();
}

template<typename T>
bool CMscnProblem<T>::bsetCd(int indX, int indY, T value)
{
	if (indX >= this->dostL || indY >= this->fabL || indX < 0 || indY < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->cd.setVal(indX, indY, value);
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetCf(int indX, int indY, T value)
{
	if (indX >= this->fabL || indY >= this->magL || indX < 0 || indY < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->cf.setVal(indX, indY, value);
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetCm(int indX, int indY, T value)
{
	if (indX >= this->magL || indY >= this->sklL || indX < 0 || indY < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->cm.setVal(indX, indY, value);
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetSd(int indX, T value)
{
	if (indX >= this->dostL || indX < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->sd[indX] = value;
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetSf(int indX, T value)
{
	if (indX >= this->fabL || indX < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->sf[indX] = value;
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetSm(int indX, T value)
{
	if (indX >= this->magL || indX < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->sm[indX] = value;
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetSs(int indX, T value)
{
	if (indX >= this->sklL || indX < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->ss[indX] = value;
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetUd(int indX, T value)
{
	if (indX >= this->dostL || indX < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->ud[indX] = value;
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetUf(int indX, T value)
{
	if (indX >= this->fabL || indX < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->uf[indX] = value;
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetUm(int indX, T value)
{
	if (indX >= this->magL || indX < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->um[indX] = value;
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetP(int indX, T value)
{
	if (indX >= this->sklL || indX < 0) {
		this->errCode = WRONG_INDEX;
		return false;
	}
	this->p[indX] = value;
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetDostL(int value)
{
	if (value < 1 || value == this->dostL) {
		this->errCode = WRONG_SIZE;
		return false;
	}
	this->dostL = value;
	this->cd.resize(this->dostL, this->fabL);

	this->sd.resize(this->dostL);
	this->ud.resize(this->dostL);

	this->xd.resize(this->dostL, this->fabL);
	this->xdminmax.resize(this->dostL*this->fabL, 2);

	this->lengthOfSol = amountOfConst + (this->dostL*this->fabL) + (this->fabL * this->magL) + (this->magL*this->sklL);
	this->minmax.resize(this->lengthOfSol);
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetFabL(int value)
{
	if (value < 1 || value == this->fabL) {
		this->errCode = WRONG_SIZE;
		return false;
	}
	this->fabL = value;
	this->cd.resize(this->dostL, this->fabL);
	this->cf.resize(this->fabL, this->magL);

	this->sf.resize(this->fabL);
	this->uf.resize(this->fabL);

	this->xd.resize(this->dostL, this->fabL);
	this->xdminmax.resize(this->dostL*this->fabL, 2);

	this->xf.resize(this->fabL, this->magL);
	this->xfminmax.resize(this->fabL*this->magL, 2);

	this->lengthOfSol = amountOfConst + (this->dostL*this->fabL) + (this->fabL *this->magL) + (this->magL*this->sklL);
	this->minmax.resize(this->lengthOfSol);
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetMagL(int value)
{
	if (value < 1 || value == this->magL) {
		this->errCode = WRONG_SIZE;
		return false;
	}
	this->magL = value;
	this->cf.resize(this->fabL, this->magL);
	this->cm.resize(this->magL, this->sklL);

	this->sm.resize(this->magL);
	this->um.resize(this->magL);

	this->xf.resize(this->fabL, this->magL);
	this->xfminmax.resize(this->fabL*this->magL, 2);
	this->xm.resize(this->magL, this->sklL);
	this->xmminmax.resize(this->magL*this->sklL, 2);

	this->lengthOfSol = amountOfConst + (this->dostL*this->fabL) + (this->fabL * this->magL) + (this->magL*this->sklL);
	this->minmax.resize(this->lengthOfSol);
	return true;
}

template<typename T>
bool CMscnProblem<T>::bsetSklL(int value)
{
	if (value < 1 || value == this->sklL) {
		this->errCode = WRONG_SIZE;
		return false;
	}
	this->sklL = value;
	this->cm.resize(this->magL, this->sklL);

	this->ss.resize(this->sklL);
	this->p.resize(this->sklL);

	this->xm.resize(this->magL, this->sklL);
	this->xmminmax.resize(this->magL*this->sklL, 2);
	this->lengthOfSol = amountOfConst + (this->dostL*this->fabL) + (this->fabL *this->magL) + (this->magL*this->sklL);
	this->minmax.resize(this->lengthOfSol);
	return true;
}

template<typename T>
bool CMscnProblem<T>::checkBasicCorrectness(std::vector<T> pdSol)
{
	return false;
}

template<typename T>
double CMscnProblem<T>::dGetQuality(std::vector<T> &pdSol) {
	return 0;
}

template<typename T>
bool CMscnProblem<T>::helperCheckMinMax(int index, Matrix<T> minmaxS, T value)
{
	return false;
}

template<typename T>
bool CMscnProblem<T>::bCheckMinMax(std::vector<T> pdSol) {
	return false;
}

template<typename T>
bool CMscnProblem<T>::bCheckOverload() {
	return false;
}

template<typename T>
bool CMscnProblem<T>::bConstraintsSatisfied(std::vector<T> pdSol)
{
	if (!this->checkBasicCorrectness(pdSol)) {
		return false;
	}
	if (!this->bCheckMinMax(pdSol)) {
		return false;
	}
	if (!this->bCheckOverload()) {
		return false;
	}
	this->pdSolution.assign(pdSol.begin(), pdSol.end());
	return true;
}

template<typename T>
bool CMscnProblem<T>::bReadFromFileInst(const char * name) {
	return false;
}

template<typename T>
bool CMscnProblem<T>::bSaveToFileInst(const char * name)
{
	FILE *newFile;
	newFile = fopen(name, "w");
	std::string line;

	line = "D " + std::to_string(this->dostL) + "\n";
	fprintf(newFile, line.c_str());
	line = "F " + std::to_string(this->fabL) + "\n";
	fprintf(newFile, line.c_str());
	line = "M " + std::to_string(this->magL) + "\n";
	fprintf(newFile, line.c_str());
	line = "S " + std::to_string(this->sklL) + "\n";
	fprintf(newFile, line.c_str());

	// sd sf sm ss
	line = "\nsd \n";
	fprintf(newFile, line.c_str());
	line = "";
	for (int i = 0; i < this->dostL; i++) {
		line += std::to_string(this->sd[i]) + " ";
	}
	fprintf(newFile, line.c_str());
	line = "\nsf \n";
	fprintf(newFile, line.c_str());
	line = "";
	for (int i = 0; i < this->fabL; i++) {
		line += std::to_string(this->sf[i]) + " ";
	}
	fprintf(newFile, line.c_str());
	line = "\nsm \n";
	fprintf(newFile, line.c_str());
	line = "";
	for (int i = 0; i < this->magL; i++) {
		line += std::to_string(this->sm[i]) + " ";
	}
	fprintf(newFile, line.c_str());
	line = "\nss \n";
	fprintf(newFile, line.c_str());
	line = "";
	for (int i = 0; i < this->sklL; i++) {
		line += std::to_string(this->ss[i]) + " ";
	}
	fprintf(newFile, line.c_str());


	//cd cf cm
	line = "\n\ncd \n";
	fprintf(newFile, line.c_str());
	for (int i = 0; i < this->dostL; i++) {
		line = "";
		for (int j = 0; j < this->fabL; j++) {
			line += std::to_string(this->cd.getVal(i, j)) + " ";
		}
		line += " \n";
		fprintf(newFile, line.c_str());
	}

	line = "\ncf \n";
	fprintf(newFile, line.c_str());
	for (int i = 0; i < this->fabL; i++) {
		line = "";
		for (int j = 0; j < this->magL; j++) {
			line += std::to_string(this->cf.getVal(i, j)) + " ";
		}
		line += " \n";
		fprintf(newFile, line.c_str());
	}
	line = "\ncm \n";
	fprintf(newFile, line.c_str());
	for (int i = 0; i < this->magL; i++) {
		line = "";
		for (int j = 0; j < this->sklL; j++) {
			line += std::to_string(this->cm.getVal(i, j)) + " ";
		}
		line += " \n";
		fprintf(newFile, line.c_str());
	}


	//ud uf um p
	line = "\n\nud \n";
	fprintf(newFile, line.c_str());
	line = "";
	for (int i = 0; i < this->dostL; i++) {
		line += std::to_string(this->ud[i]) + " ";
	}
	fprintf(newFile, line.c_str());
	line = "\nuf \n";
	fprintf(newFile, line.c_str());
	line = "";
	for (int i = 0; i < this->fabL; i++) {
		line += std::to_string(this->uf[i]) + " ";
	}
	fprintf(newFile, line.c_str());
	line = "\num \n";
	fprintf(newFile, line.c_str());
	line = "";
	for (int i = 0; i < this->magL; i++) {
		line += std::to_string(this->um[i]) + " ";
	}
	fprintf(newFile, line.c_str());
	line = "\np \n";
	fprintf(newFile, line.c_str());
	line = "";
	for (int i = 0; i < this->sklL; i++) {
		line += std::to_string(this->p[i]) + " ";
	}
	fprintf(newFile, line.c_str());


	//xdminmax xfminmax xmminmax
	line = "\n\nxdminmax \n";
	fprintf(newFile, line.c_str());
	for (int i = 0; i < this->dostL *this->fabL; i++) {
		line = "";
		for (int j = 0; j < 2; j++) {
			line += std::to_string(this->xdminmax.getVal(i, j)) + " ";
		}
		line += " \n";
		fprintf(newFile, line.c_str());
	}

	line = "xfminmax \n";
	fprintf(newFile, line.c_str());
	for (int i = 0; i < (this->fabL*this->magL); i++) {
		line = "";
		for (int j = 0; j < 2; j++) {
			line += std::to_string(this->xfminmax.getVal(i, j)) + " ";
		}
		line += " \n";
		fprintf(newFile, line.c_str());
	}
	line = "xmminmax \n";
	fprintf(newFile, line.c_str());
	for (int i = 0; i < this->magL*this->sklL; i++) {
		line = "";
		for (int j = 0; j < 2; j++) {
			line += std::to_string(this->xmminmax.getVal(i, j)) + " ";
		}
		line += " \n";
		fprintf(newFile, line.c_str());
	}

	fclose(newFile);

	return true;
}

template<typename T>
bool CMscnProblem<T>::bReadFromFileSol(const char * name) {
	return false;
}

template<typename T>
bool CMscnProblem<T>::bSaveToFileSol(const char * name)
{
	FILE *newFile;
	newFile = fopen(name, "w");
	std::string line;

	line = "D " + std::to_string(this->dostL) + "\n";
	fprintf(newFile, line.c_str());
	line = "F " + std::to_string(this->fabL) + "\n";
	fprintf(newFile, line.c_str());
	line = "M " + std::to_string(this->magL) + "\n";
	fprintf(newFile, line.c_str());
	line = "S " + std::to_string(this->sklL) + "\n";
	fprintf(newFile, line.c_str());

	line = "\nxd \n";
	fprintf(newFile, line.c_str());
	for (int i = 0; i < this->dostL; i++) {
		line = "";
		for (int j = 0; j < this->fabL; j++) {
			line += std::to_string(this->xd.getVal(i, j)) + " ";
		}
		line += " \n";
		fprintf(newFile, line.c_str());
	}
	line = "\nxf \n";
	fprintf(newFile, line.c_str());
	for (int i = 0; i < this->fabL; i++) {
		line = "";
		for (int j = 0; j < this->magL; j++) {
			line += std::to_string(this->xf.getVal(i, j)) + " ";
		}
		line += " \n";
		fprintf(newFile, line.c_str());
	}
	line = "\nxm \n";
	fprintf(newFile, line.c_str());
	for (int i = 0; i < this->magL; i++) {
		line = "";
		for (int j = 0; j < this->sklL; j++) {
			line += std::to_string(this->xm.getVal(i, j)) + " ";
		}
		line += " \n";
		fprintf(newFile, line.c_str());
	}
	return true;
}

template<typename T>
void CMscnProblem<T>::vsetBasics(int d, int f, int m, int s) {
	this->bsetDostL(d);
	this->bsetFabL(f);
	this->bsetMagL(m);
	this->bsetSklL(s);
}

template<typename T>
void CMscnProblem<T>::vGenerateInstance(int d, int f, int m, int s, int iInstanceSeed, double minVal, double maxVal) {

}

template<typename T>
void CMscnProblem<T>::vsetInstance(const CMscnProblem<T> &newInstance)
{
	this->lengthOfSol = newInstance.lengthOfSol;
	this->bsetDostL(newInstance.dostL);
	this->bsetFabL(newInstance.fabL);
	this->bsetMagL(newInstance.magL);
	this->bsetSklL(newInstance.sklL);

	this->sd.assign(newInstance.sd.begin(), newInstance.sd.end());
	this->sf.assign(newInstance.sf.begin(), newInstance.sf.end());
	this->sm.assign(newInstance.sm.begin(), newInstance.sm.end());
	this->ss.assign(newInstance.ss.begin(), newInstance.ss.end());

	this->ud.assign(newInstance.ud.begin(), newInstance.ud.end());
	this->uf.assign(newInstance.uf.begin(), newInstance.uf.end());
	this->um.assign(newInstance.um.begin(), newInstance.um.end());
	this->p.assign(newInstance.p.begin(), newInstance.p.end());

	// cd cf cm
	for (int i = 0; i < dostL; i++) {
		for (int j = 0; j < fabL; j++) {
			this->cd.setVal(i, j, newInstance.cd.getVal(i, j));
		}
	}
	for (int i = 0; i < fabL; i++) {
		for (int j = 0; j < magL; j++) {
			this->cf.setVal(i, j, newInstance.cf.getVal(i, j));
		}
	}
	for (int i = 0; i < magL; i++) {
		for (int j = 0; j < sklL; j++) {
			this->cm.setVal(i, j, newInstance.cm.getVal(i, j));
		}
	}
	//minmax xd xf xm
	for (int i = 0; i < dostL*fabL; i++) {
		for (int j = 0; j < 2; j++) {
			this->xdminmax.setVal(i, j, newInstance.xdminmax.getVal(i, j));
		}
	}
	for (int i = 0; i < fabL*magL; i++) {
		for (int j = 0; j < 2; j++) {
			this->xfminmax.setVal(i, j, newInstance.xfminmax.getVal(i, j));
		}
	}
	for (int i = 0; i < magL*sklL; i++) {
		for (int j = 0; j < 2; j++) {
			this->xmminmax.setVal(i, j, newInstance.xmminmax.getVal(i, j));
		}
	}
	this->vsetMinmax();
}

template<typename T>
void CMscnProblem<T>::vShowInstance()
{
	std::cout << std::endl << "--------------" << std::endl;
	std::cout << "---Instance---" << std::endl;

	std::cout << "Dostawcy: " << this->dostL << std::endl;
	std::cout << "Fabryki: " << this->fabL << std::endl;
	std::cout << "Magazyny: " << this->magL << std::endl;
	std::cout << "Sklepy: " << this->sklL << std::endl;

	// sd - sf - sm - ss
	std::cout << "sd: " << std::endl;
	for (int i = 0; i < this->dostL; i++) {
		std::cout << this->sd[i] << "; ";
	}
	std::cout << std::endl << "sf: " << std::endl;
	for (int i = 0; i < this->fabL; i++) {
		std::cout << this->sf[i] << "; ";
	}
	std::cout << std::endl << "sm: " << std::endl;
	for (int i = 0; i < this->magL; i++) {
		std::cout << this->sm[i] << "; ";
	}
	std::cout << std::endl << "ss: " << std::endl;
	for (int i = 0; i < this->sklL; i++) {
		std::cout << this->ss[i] << "; ";
	}
	// cd - cf - cm
	std::cout << std::endl << "cd: " << std::endl;
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			std::cout << this->cd.getVal(i, j) << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << "cf: " << std::endl;
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			std::cout << this->cf.getVal(i, j) << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << "cm: " << std::endl;
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			std::cout << this->cm.getVal(i, j) << "; ";
		}
		std::cout << std::endl;
	}
	// ud - uf - um - p
	std::cout << "ud: " << std::endl;
	for (int i = 0; i < this->dostL; i++) {
		std::cout << this->ud[i] << "; ";
	}
	std::cout << std::endl << "uf: " << std::endl;
	for (int i = 0; i < this->fabL; i++) {
		std::cout << this->uf[i] << "; ";
	}
	std::cout << std::endl << "um: " << std::endl;
	for (int i = 0; i < this->magL; i++) {
		std::cout << this->um[i] << "; ";
	}
	std::cout << std::endl << "p: " << std::endl;
	for (int i = 0; i < this->sklL; i++) {
		std::cout << this->p[i] << "; ";
	}
	// xdminmax - xfminmax - xmminmax
	std::cout << std::endl << "xdminmax: " << std::endl;
	for (int i = 0; i < this->dostL*this->fabL; i++) {
		for (int j = 0; j < 2; j++) {
			std::cout << this->xdminmax.getVal(i, j) << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << "xfminmax: " << std::endl;
	for (int i = 0; i < this->fabL*this->magL; i++) {
		for (int j = 0; j < 2; j++) {
			std::cout << this->xfminmax.getVal(i, j) << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << "xmminmax: " << std::endl;
	for (int i = 0; i < this->magL*this->sklL; i++) {
		for (int j = 0; j < 2; j++) {
			std::cout << this->xmminmax.getVal(i, j) << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "--------------" << std::endl;
}

template<typename T>
void CMscnProblem<T>::vShowSolution()
{
	std::cout << std::endl << "--------------" << std::endl;
	std::cout << "---Solution---" << std::endl;
	std::cout << "Dostawcy: " << this->dostL << std::endl;
	std::cout << "Fabryki: " << this->fabL << std::endl;
	std::cout << "Magazyny: " << this->magL << std::endl;
	std::cout << "Sklepy: " << this->sklL << std::endl;


	// xd - xf - xm
	std::cout << "xd: " << std::endl;
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			std::cout << this->xd.getVal(i, j) << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << "xf: " << std::endl;
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			std::cout << this->xf.getVal(i, j) << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << "xm: " << std::endl;
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			std::cout << this->xm.getVal(i, j) << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << "--------------" << std::endl;
}

template<typename T>
void CMscnProblem<T>::vsetMinmax()
{
	this->lengthOfSol = (amountOfConst + this->dostL *this->fabL + this->fabL * this->magL + this->magL * this->sklL);
	this->minmax.resize(this->lengthOfSol);
	this->minmax[0].first = this->dostL; this->minmax[0].second = this->dostL;
	this->minmax[1].first = this->fabL;  this->minmax[1].second = this->fabL;
	this->minmax[2].first = this->magL;  this->minmax[2].second = this->magL;
	this->minmax[3].first = this->sklL;  this->minmax[3].second = this->sklL;
	int index = 4;
	for (int i = 0; i < this->dostL*this->fabL; i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) this->minmax[index].first = this->getXdminmax().getVal(i, j);
			else this->minmax[index++].second = this->getXdminmax().getVal(i, j);
		}
	}
	for (int i = 0; i < this->fabL*this->magL; i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) this->minmax[index].first = this->getXfminmax().getVal(i, j);
			else this->minmax[index++].second = this->getXfminmax().getVal(i, j);
		}
	}
	for (int i = 0; i < this->magL*this->sklL; i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) this->minmax[index].first = this->getXmminmax().getVal(i, j);
			else this->minmax[index++].second = this->getXmminmax().getVal(i, j);
		}
	}
}


