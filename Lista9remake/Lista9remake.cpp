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
	// Values needed to generate instance of problem
	int suppliers = 2, fabrics = 2, warehouses = 2, shops = 2;
	unsigned int seed = 1;
	double minGenVal=1, maxGenVal=500;
	// Values needed for optimizers | Time for both | crossP, diffW and amountOfPopulation for CDiffEvol
	int amountOfPopulation = 800;
	double time=30000, crossP=0.95, diffW=0.4;
	// Variables for problem class and optimizers
	CProblem<double>* actualProblem;
	COptimizer<double>* optimizer;
	std::vector<double> pdSolRand, pdSolEvol;
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
	
	actualProblem = new CMscnProblem<double>(suppliers, fabrics, warehouses, shops,
											seed, minGenVal, maxGenVal);
	actualProblem->vShowInstance();

	optimizer = new CRandomSearch<double>(actualProblem);
	cout << endl << "---------------------------" << endl;
	cout << "Time for a CRandomSearch in miliseconds(double): "; cin >> time;
	cout << "---------------------------";
	pdSolRand= optimizer->getSolution(time);
	actualProblem->vShowSolution();


	cout << endl << "---------------------------" << endl;
	cout << "Time for a CDiffEvol in miliseconds(double): "; cin >> time;
	cout << "CrossProb, propability of crossing genes, from 0.0 to 1.0(double): "; cin >> crossP;
	cout << "DiffWeight, the weight of the difference when genes are crossed(double): "; cin >> diffW;
	cout << endl << "---------------------------";


	optimizer = new CDiffEvol<double>(actualProblem, amountOfPopulation, crossP, diffW);
	pdSolEvol = optimizer->getSolution(time);




	cout << endl << endl << "------------------------------" << endl << endl;
	actualProblem->vShowInstance();

	cout << "Quality of RandomSearch: " << actualProblem->dGetQuality(pdSolRand)<<endl;
	actualProblem->vShowSolution();

	cout << "Quality of CDiffEvol: " << actualProblem->dGetQuality(pdSolEvol) << endl;
	actualProblem->vShowSolution();


	return 0;
}

// Here is my explanation of the program, and the problem that needs solving.
/*
	dostL - amount of suppliers | fabL - amount of fabrics
	magL - amount of warehouses | sklL - amount of shops
	xd - matrix of amount of raw materials transporting from supplier X to fabric Y
	xf - matrix of amount of products that are created and transported from fabric X to warehouse Y
	xm - matrix of amount of products that are stored and transported from warehouse X to shop Y
	
	cd - cost of buying and transportingvraw materials from supplier X to fabric Y
	cf - cost of creating and transporting products from fabric X to warehouse Y
	cm - cost of storing and transporting products from warehouse X to shop Y
*/

/*
		An objective of this program is to solve the problem with 4 main variables:
	Suppliers, fabrics, warehouses and shops.
	And we have 3 matrix: xd/xf/xm, which combined are going to be our solution.
	
		Our goal is to balance the values in each of the matrixes to get the best solution, 
	which is measured by function dGetQuality(std::vector pdSolution) in the class of CProblem.


		So now, whats the conditions, that our optimizers and dGetQuality() need to have "in mind"?
	1) The length of the solution should be: (4 + (dostL*fabL) + (fabL*magL) + (magL*sklL))
			(+4 becous of basic values that are put in front: dostL|fabL|magL|sklL)
	2) For each value in xd/xf/xm matrixes there is a min/max limit, which is placed in matrixes xdminmax/xfminmax/xmminmax.
	3) There are arrays of processing capacity for each supplier/fabric/warehouse/shops.
	4) Suppliers/fabrics/warehouses have maintenance costs, so sometimes is better to shutdown one, then use it a little.
	5) Shops have a value price of final product, the income is just: amountOfSoldproducts*price. Each shop can have different price.
	5) There is a cost of transporting/creating/storing the raw materials/products, the cost of it is placed in matrixes cd/cf/cm.
	6) Ofcourse each fabric can't produce more than it gets raw minerals from suppliers and 
		warehouse can't transport to shop more than it gets products from fabrics.
	

	This program contains 2 main optimizers: CRandomSearch and CDiffEvol, and 2 simple ones: CMeanSolver and CTrivMethod.
	CRandomSearch - just gets a random value between minimum and maximum for each. 
		If the solution is better then actual solution, actual solution gets replaced by new one, 
		till the end of time.
	
	CDiffEvol - have 3 main variables: amountOfPopulation, crossProb, diffWeight. Each of these have
		big impact on algorythm efficiency. At the start population is an array of random solutions,
		and each solution is modified by each loop of the algorithm by being mixed with other solutions
		and if new solution is better then old one, there is a replacement. (more explonation in the code of algorithm)
		
		
*/
