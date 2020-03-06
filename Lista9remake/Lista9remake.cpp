#include "pch.h"
#include "CRandom.h"
#include "Matrix.h"
#include "CMscnProblem.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"
#include "CTrivMethod.h"
#include "CMeanSolver.h"
#pragma warning (disable: 4930)
using namespace std;

// To create a random Instance of problem with a random seed
void generateInstance(std::vector<CProblem<double>*> &actualProblems);
void readProblemFile(std::vector<CProblem<double>*> &actualProblems);
void readSolfromFile(std::vector<std::vector<std::vector<double>>> solutions, std::vector<CProblem<double>*>& actualProblems);


int main()
{
	int end = false;
	int odp;
	std::vector<CProblem<double>*> actualProblems;
	// For each problem, there could be multiple solutions
	std::vector<std::vector<std::vector<double>>> solutions;

	while (!end) {
		cout << endl;
		cout << " _________________________________________ " << endl;
		cout << "|------------- Choose option -------------|" << endl;
		cout << "|1. Generate instance of problem          |" << endl;
		cout << "|2. Read problem from file                |" << endl;
		cout << "|3. Read solution from file               |" << endl;
		cout << "|4. Use RandomSearch to solve problem     |" << endl;
		cout << "|5. Use CDiffEvol to solve the problem    |" << endl;
		cout << "|6. Save last solution to file            |" << endl;
		cout << "|7. Save last 2 solutions to files        |" << endl;
		cout << "|8. Save last instance of problem to file |" << endl;
		cout << "|9. Show instance of problem and solutions|" << endl;
		cout << "|0. Exit                                  |" << endl;
		cout << "|_________________________________________|" << endl;
		cout << "Type: "; cin >> odp;
		system("CLS");

		switch (odp) {
		case 1:
			generateInstance(actualProblems);
			break;
		case 2:
			readProblemFile(actualProblems);
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		case 5:
			
			break;
		case 6:
			
			break;
		case 7:
			
			break;
		case 8:

			break;
		case 9:
			
			break;
		case 0:
			cout << "Bye, Bye!";
			end = true;
			break;
		default: cout << "Incorrect option!";
		}	
	}
	return 0;
}


void generateInstance(std::vector<CProblem<double>*> &actualProblems) {
	// Values needed to generate instance of problem
	int suppliers = 2, fabrics = 2, warehouses = 2, shops = 2;
	unsigned int seed = 1;
	double minGenVal = 1, maxGenVal = 500;
	CProblem<double> * newProblem;
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
	char* name;
	bool tryagain;
	CProblem<double>* newProblem;
	cout << "Type name of the file: "; cin >> name;
	while (!(newProblem->bReadFromFileInst(name)) ) {
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
