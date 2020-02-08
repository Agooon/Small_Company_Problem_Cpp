
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

int main()
{
	int time, population,seed;
	double weigth, cross;
	cout << "Podaj czas: ";
	cin >> time;

	cout<<endl << "Podaj populajce: ";
	cin >> population;

	cout << endl << "Podaj weigth: ";
	cin >> weigth;

	cout << endl << "Podaj cross: ";
	cin >> cross;

	cout << endl << "Podaj seed: ";
	cin >> seed;


	cout << endl << "-------------" << endl;
	//CProblem<double> *myproblem;
	//myproblem = new CMscnProblem<double>();

	//cout<<myproblem->bReadFromFileInst("SuperPlik2.txt");
	CMscnProblem<double> *myproblem;
	myproblem = new CMscnProblem<double>();
	myproblem->vGenerateInstance(1,1,1,1,seed);
	myproblem->vShowInstance();

	COptimizer<double> *optimizer;

/*	optimizer = new CRandomSearch<double>();
	optimizer->setInstance(myproblem);
	optimizer->getSolution(time);
	myproblem->vShowSolution();
	*/

	optimizer = new CDiffEvol<double>(myproblem,population,cross, weigth);

	optimizer->getSolution(time);
	myproblem->vShowInstance();
	myproblem->vShowSolution();


	delete myproblem;
	return 0;
}

