#include "pch.h"
#include "CRandom.h"
#include "Matrix.h"
#include "CMscnProblem.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"
#include "CTrivMethod.h"
#include "CMeanSolver.h"
#include "CConsoleMenu.h"
#pragma warning (disable: 4930)
using namespace std;

// To create a random Instance of problem with a random seed
void generateInstance(std::vector<CMscnProblem<double>*> &actualProblems);
void readProblemFile(std::vector<CMscnProblem<double>*> &actualProblems);
void readSolfromFile(std::vector<std::vector<std::vector<double>>> solutions, std::vector<CProblem<double>*>& actualProblems);


int main()
{
	CConsoleMenu menu1;
	menu1.vStartProgram();
	
}


void generateInstance(std::vector<CProblem<double>*> &actualProblems) {
	// Values needed to generate instance of problem
	int suppliers = 2, fabrics = 2, warehouses = 2, shops = 2;
	unsigned int seed = 1;
	double minGenVal = 1, maxGenVal = 500;
	CMscnProblem<double> * newProblem;
	// -- end of variables -- //

	cout << "-- Generating an instance --" << endl;
	cout << "Amount of suppliers(int): "; cin >> suppliers;
	cout << "Amount of fabrics(int): "; cin >> fabrics;
	cout << "Amount of warehouses(int): "; cin >> warehouses;
	cout << "Amount of shops(int): "; cin >> shops;
	cout << "Seed for a generator(unsigned int): "; cin >> seed;

	cout << "Minimum value for a random variable used for generation process(double): "; cin >> minGenVal;
	cout << "Maximum value for a random variable used for generation process(double): "; cin >> maxGenVal;

	cout << endl << "---------------------------" << endl;

	newProblem = new CMscnProblem<double>(suppliers, fabrics, warehouses, shops,
		seed, minGenVal, maxGenVal);
	newProblem->vShowInstance();
	actualProblems.push_back(newProblem);
}

void readProblemFile(std::vector<CProblem<double>*> &actualProblems)
{
	string name;
	bool tryagain;
	CMscnProblem<double>* newProblem;

	cout << "Type name of the file: (50 characters max)"; cin >> name;
	newProblem = new CMscnProblem<double>(name.c_str());
	while (!(newProblem->bReadFromFileInst(name.c_str())) ) {
		cout << "File doesn't exist!" << endl;
		cout << "Try again? (1=yes|0=no): "; cin >> tryagain;
		system("CLS");
		if (!tryagain) {
			return;
		}
		cout << "Type name of the file: "; cin >> name;
	}
	newProblem->vShowInstance();
	actualProblems.push_back(newProblem);
}
