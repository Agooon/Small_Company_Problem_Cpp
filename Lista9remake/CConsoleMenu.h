#pragma once
#include "CSolution.h"
#include "CMscnProblem.h"
#include "CDiffEvol.h"
#include "CRandomSearch.h"
#define FRAME_LENGTH 44

#pragma warning(disable: 26451)
using namespace std;
class CConsoleMenu
{
public:
	// Starts by reading changes in INSTANCE_LIST.txt
	CConsoleMenu() {
		FILE* fListFile;
		fListFile = fopen("INSTANCE_LIST.txt","r");
		char sHelper[101];
		while (!feof(fListFile)) {
			fscanf(fListFile, "%100s", sHelper);
			instancesNames.push_back(sHelper);
		}
		fclose(fListFile);
	}
	~CConsoleMenu() {

	}

////////////////////////////////------------------------------- START MENU  ------------------------------------/////////////////////////////////////

	void vStartProgram() {
		char sAnsw[10];
		while (1) {
			vPrintStringInFrame("Choose option",1,0);
			cout << "|1. Instance menu                          |" << endl;
			cout << "|2. About program and author               |" << endl;
			cout << "|0. Exit                                   |" << endl;
			cout << "|__________________________________________|" << endl;
			cout << "Answer: "; cin >> sAnsw;
			system("CLS");

			switch (atoi(sAnsw)) {
			case 1: // Instance menu 
				vMENUinstanceMenu();
				break;
			case 2: // About program and author 
				vMENUinfoAbout();
				system("CLS");
				break;
			case 0: // End
				cout << "Always test Your code!";
				return;
			default: cout << "Incorrect option!"<<endl;
			}
		}
	}
private:
	std::vector<std::string> instancesNames; // changes if user adds/deletes instance
	std::vector<CSolution> lastSolutions; // changes when reading from file
	CMscnProblem<double> actualInst; // CMscProblem class to operate instances and solutions


	// -- 2 -- // START MENU - About program and author 
	void vMENUinfoAbout() {
		vPrintStringInFrame("About program and Author",1,1);

		cout << "Author: Adam Sierakowski" << endl;
		cout << "GitHub: github.com/Agooon" << endl;
		cout << "E-mail: adam.sierakowski.kontakt@gmail.com" << endl<<endl;

		cout << "I am a young programist that wanted to expand" << endl;
		cout << "this  project  from  studies, all  of UI  and" << endl;
		cout << "managment of memory is my own idea. I decided" << endl;
		cout << "to make this project  just a bit more usefull" << endl;
		cout << "and show off it's capabilities to people that" << endl;
		cout << "aren't familiar with optimization algorithms." << endl<<endl;

		cout << "Program is about solving a problem of company" << endl;
		cout << "that have 4 main variables:" << endl;
		cout << "Suppliers, fabrics, warehouses and shops." << endl;
		cout << "The goal is to balance the values in xd/xf/xm" << endl;
		cout << "matrixes  which combined  are going to be our" << endl;
		cout << "solution. Optimization algorithms are helping" << endl;
		cout << "to find the best possible solution." << endl;
		cout << "Detailed explanation in Readme.txt file." << endl<<endl;

		vWaitForPressAnyKey();
	}

////////////////////////////////----------------------------- INSTANCE MENU  -----------------------------------/////////////////////////////////////

	// --1-- // START MENU - Instance MENU
	void vMENUinstanceMenu() {
		char sAnsw[10];
		while (1) {
		//	cout << " __________________________________________ " << endl;
		//	cout << "|-------------- Instance MENU -------------|" << endl;
			vPrintStringInFrame("Instance MENU",1,0);
			cout << "|1. Show avaible instances                 |" << endl;
			cout << "|2. Add instance from unregistered file    |" << endl;
			cout << "|3. Generate new instance                  |" << endl;
			cout << "|4. Delete instance                        |" << endl;
			cout << "|5. Solution MENU                          |" << endl;
			cout << "|0. Back                                   |" << endl;
			cout << "|__________________________________________|" << endl;
			cout << "Answer: "; cin >> sAnsw;
			system("CLS");

			switch (atoi(sAnsw)) {
			case 1: // Show avaible instances
				vMENUshowAvalInst();
				system("CLS");
				break;
			case 2: // Add instance from unregistered file
				vMENUaddInstFromFile();
				system("CLS");
				break;
			case 3: // Generate new instance 
				vMENUgenerateNewInst();
				system("CLS");
				break;
			case 4: // Delete instance 
				vMENUdeleteInst();
				system("CLS");
				break;
			case 5: // Solution MENU 
				vMENUsolutionMenu();
				system("CLS");
				break;
			case 0: // Back
				return;
			default: cout << "Incorrect option!"<<endl;
			}
		}
	}
	
	// --1-- // INSTANCE MENU - Show avaible instances
	void vMENUshowAvalInst() {
		vPrintStringInFrame("Instances",1,1);
		vPrintInstances();

		int iAnsw = iChooseInstance();
		if (iAnsw == 0) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}
		iAnsw--; // Vector starts at 0 index
		system("CLS");
		vPrintStringInFrame(instancesNames[iAnsw].c_str(),1,1);

		vSetInstance(iAnsw); 
		actualInst.vShowInstance();

		vReadSolsFromFile(instancesNames[iAnsw]);

		vPrintLastSolutions();
		cout <<endl<< "To see more information about them go to 'Solution MENU'" << endl;

		vWaitForPressAnyKey();
	}
	// --2-- // INSTANCE MENU - Add instance from unregistered file
	void vMENUaddInstFromFile() {
		std::string sFileName;
		vPrintStringInFrame("Add instance from file",1,1);

		cout << "Enter the file name (without .txt, like 'Myfile'): " << endl;
		cout << "Answer: "; cin >> sFileName;

		// Checking if file exist
		if (actualInst.bReadFromFileInst((sFileName + ".txt").c_str()) == NULL) {
			cout << "File doesn't exist!";
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}
		if (bInstFileExist(sFileName)) {
			cout << "File is already in database!";
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}
		vAddInstance(sFileName);

		vWaitForPressAnyKey();
	}
	// --3-- // INSTANCE MENU - Generate new instance
	void vMENUgenerateNewInst() {
		// Values needed to generate instance of problem
		bool bAnsw;
		std::string sNameOfInst;
		size_t iSuppliers, iFabrics, iWarehouses, iShops;
		unsigned int iSeed;
		double dMinGenVal, dMaxGenVal;
		// -- end of variables -- //	
		while (1) {
			vPrintStringInFrame("Generating an instance of Problem",1,1);
			cout << "Name of new instance (without whites): "; cin >> sNameOfInst;
			if (bInstFileExist(sNameOfInst)) {
				system("CLS");
				cout << "This instance name is already taken!" << endl;
			}
			else break; // If name is unique -> end the loop
		}

		cout << "Amount of suppliers(int,val<0): "; cin >> iSuppliers;
		cout << "Amount of fabrics(int,val<0): "; cin >> iFabrics;
		cout << "Amount of warehouses(int,val<0): "; cin >> iWarehouses;
		cout << "Amount of shops(int,val<0): "; cin >> iShops;

		cout << "Set your own seed for generator - 1"  << endl << "Set random seed for generator - 0" << endl;
		cout << "Answer: "; cin >> bAnsw;

		if (bAnsw) { cout << "Seed for a generator(int,val<0): "; cin >> iSeed; }
		else {
			std::random_device device;
			iSeed = device();
		}
		cout << "Minimum value for a random constant value used for generation(double): "; cin >> dMinGenVal;
		cout << "Maximum value for a random constant value used for generation(double): "; cin >> dMaxGenVal;

		cout << endl << "Do you want to generate this instance?" << endl;
		cout << "Yes - 1 | No - 0" << endl;
		cout << "Answer: "; cin >> bAnsw;

		if (!bAnsw) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}

		actualInst.vGenerateInstance(iSuppliers, iFabrics, iWarehouses, iShops, iSeed, dMinGenVal, dMaxGenVal);
		actualInst.vShowInstance();

		cout << endl << "Do you want to save this instance?" << endl;
		cout << "Yes - 1 | No - 0" << endl;
		cout << "Answer: "; cin >> bAnsw;
		if (bAnsw) {
			actualInst.bSaveToFileInst((sNameOfInst + ".txt").c_str());
			vAddInstance(sNameOfInst);
		}
		
		vWaitForPressAnyKey();
	}
	// --4-- // INSTANCE MENU - Delete instance
	void vMENUdeleteInst() {
		char sAnsw2[10], sAnsw3[10];

		vPrintStringInFrame("Delete instance",1,1);
		cout << "List of instances: " << endl;
		vPrintInstances();

		int iAnsw = iChooseInstance();
		if (iAnsw == 0) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}
		iAnsw--; // Vector starts at 0 index

		system("CLS");
		vPrintStringInFrame(instancesNames[iAnsw].c_str(),1, 1);

		cout << "Show instance and it's solutions| Yes - 1 | No - 0"<<endl;
		cout << "Answer: "; cin >> sAnsw2;
		if (atoi(sAnsw2)) { // If user wants to see informations about instance before deleting
			vSetInstance(iAnsw);
			actualInst.vShowInstance();
			vReadSolsFromFile(instancesNames[iAnsw]);
			cout << "List of solutions and their quality." << endl;
			cout << "To see more information about them go to 'Solution MENU'" << endl;
			vPrintLastSolutions();
		}
		
		cout << endl << "Are You sure to delete this instance? | Yes - 1 | No - 0" << endl;
		cout << "Answer: "; cin >> sAnsw3;
		if (!atoi(sAnsw3)) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}

		// If solutions hadn't been read before
		if (!atoi(sAnsw2)) {
			vSetInstance(iAnsw);
			vReadSolsFromFile(instancesNames[iAnsw]);
		}
		
		// Deleting files
		
		// Solution files
		for (int i = 0; i < lastSolutions.size(); i++) {
			std::remove((instancesNames[iAnsw] + "_SOL_" + lastSolutions[i].sGetName() + ".txt").c_str());
			cout << endl << "Deleted: " << instancesNames[iAnsw] + "_SOL_"+lastSolutions[i].sGetName() + ".txt";
		}
		
		// File with names of solutions and Instance file
		std::remove((instancesNames[iAnsw] + "_SOLUTIONS.txt").c_str());
		cout << endl << "Deleted: " << instancesNames[iAnsw]+ "_SOLUTIONS.txt";
		std::remove((instancesNames[iAnsw] + ".txt").c_str());
		cout << endl << "Deleted: " << instancesNames[iAnsw];
		
		// Updating INSTANCE_LIST.txt
		lastSolutions.clear();
		instancesNames.erase(instancesNames.begin()+ iAnsw);
		vUpdateInstanceList();

		vWaitForPressAnyKey();
	}
	
////////////////////////////////----------------------------- SOLUTION MENU ------------------------------------/////////////////////////////////////

	// --5-- // INSTANCE MENU - Solution MENU
	void vMENUsolutionMenu() {
		char sAnsw[10];
		while (1) {
			vPrintStringInFrame("Solution MENU",1, 0);
			cout << "|1. Choose instance                        |" << endl;
			cout << "|2. Avaible algorithms                     |" << endl;
			cout << "|0. Back                                   |" << endl;
			cout << "|__________________________________________|" << endl;
			cout << "Answer: "; cin >> sAnsw;
			system("CLS");

			switch (atoi(sAnsw)) {
			case 1: // Choose instance
				vChooseInstance();
				break;
			case 2: // Avaible algorithms 
				vAvaibleAlgorithmsInfo();
				system("CLS");
				break;
			case 0: // Back 
				return;
			default: cout << "Incorrect option!" << endl;
			}
		}
	}
	// --2-- // SOLUTION MENU - Avaible algorithms
	void vAvaibleAlgorithmsInfo() {
		vPrintStringInFrame("Avaible Algorithms",1, 1); cout << endl;

		vPrintStringInFrame("CRandomSearch",1, 1);
		cout << "It's a simple algorithm that is searching for" << endl;
		cout << "a solution in a  given time.  At the start it" << endl;
		cout << "randomize starting solution and with the same" << endl;
		cout << "condtions randomizes next one, if the new one" << endl;
		cout << "is  better,  it  replaced  the  old  one.  It" << endl;
		cout << "repeats until time tuns out."<<endl;

		vPrintStringInFrame("CDiffEvol",1,1);
		cout << "It's a evolution algorithms that starts  with" << endl;
		cout << "a limited population of random solutions that" << endl;
		cout << "are randomize  like in a  CRandomSearch. Then" << endl;
		cout << "each solution  has a  chance to change  value" << endl;
		cout << "based on other solution values at this index." << endl;
		cout << "If the new solution has greater quality  than" << endl;
		cout << "previous one, it  replaced it, if it's  worse" << endl;
		cout << "the original solution doesn't change. You can" << endl;
		cout << "see the improvemnt of solutions in CDiffEvol," << endl;
		cout << "if You enable  the option  'Watch population'" << endl;
		cout << "before activating this algorithm.";

		vWaitForPressAnyKey();
		return;
	}


////////////////////////////////-------------------------- Specific Instance MENU ------------------------------/////////////////////////////////////

	// --1-- // SOLUTION MENU - Choose instance
	void vChooseInstance() {
		vPrintStringInFrame("Choose Instance",1,1);
		vPrintInstances();

		int iAnsw = iChooseInstance();
		if (iAnsw == 0) {
			vWaitForPressAnyKey();
			return;
		}
		iAnsw--;
		vSetInstance(iAnsw);

		system("CLS");
		vReadSolsFromFile(actualInst.getName());
		vSpecificInstanceMENU();
	}

	void vSpecificInstanceMENU() {
		char sAnsw[10];
		while (1) {
			vPrintStringInFrame(actualInst.getName().c_str(),1,0);
			cout << "|1. Show Instance                          |" << endl;
			cout << "|2. Show Solutions                         |" << endl;
			cout << "|3. Read Solution from file                |" << endl;
			cout << "|4. Generate new Solution                  |" << endl;
			cout << "|5. Delete chosen Solutions                |" << endl;
			cout << "|0. Back                                   |" << endl;
			cout << "|__________________________________________|" << endl;
			cout << "Answer: "; cin >> sAnsw;
			system("CLS");

			switch (atoi(sAnsw)) {
			case 1: // Show Instance
				vMENUshowChosenInst();
				system("CLS");
				break;
			case 2: // Show Solutions
				vMENUshowSolutionsOfChosenInst();
				system("CLS");
				break;
			case 3: // Read Solution from file
				vMENUreadSolFromFile();
				system("CLS");
				break;
			case 4: // Generate new Solution
				vMENUgenerateNewSol();
				system("CLS");
				break;
			case 5: // Delete chosen Solutions
				vMENUdeleteChosenSols();
				system("CLS");
				break;
			case 0: // Back
				return;
			default: cout << "Incorrect option!" << endl;
			}
		}
	}
	// --1-- // Specific Instance MENU - Show Instance
	void vMENUshowChosenInst() {
		vPrintStringInFrame(actualInst.getName().c_str(),1, 1);
		
		vReadSolsFromFile(actualInst.getName());
		actualInst.vShowInstance();
		vPrintLastSolutions();

		vWaitForPressAnyKey();	
	}
	// --2-- // Specific Instance MENU - Show Solutions
	void vMENUshowSolutionsOfChosenInst() {
		char bAnsw2[10];
		int iAnsw;
		while (1) {
			vReadSolsFromFile(actualInst.getName());
			vPrintLastSolutions();
			iAnsw = iChooseSolution();
			if (iAnsw == 0) {
				vWaitForPressAnyKey();
				return;
			}
			iAnsw--;
			system("CLS");
			vPrintStringInFrame(("Solution "+std::to_string(iAnsw +1)+" of "+actualInst.getName()).c_str(),1,0);
			vPrintStringInFrame((lastSolutions[iAnsw].toString()).c_str(), 0, 1);
			actualInst.vSaveSolution(lastSolutions[iAnsw].getSolution());
			actualInst.vShowSolution();

			cout << "Do You want to see other solution? | 1 - Yes | 0 - No" << endl;
			cout << "Answer: "; cin >> bAnsw2;
			if (!atoi(bAnsw2)) {
				vWaitForPressAnyKey();
				return;
			}
			system("CLS");
		}
	}
	// --3-- // Specific Instance MENU- Read Solution from file
	void vMENUreadSolFromFile() {
		std::string nameOfFile;
		char sAnsw[10];
		while (1) {
			vPrintStringInFrame("Read Solution from file", 1, 1);
			cout << "Write the name of file (without .txt, like 'MySol')" << endl;
			cout << "Answer:"; cin >> nameOfFile;

			if (bSolFileExist(nameOfFile)) {
				cout << "This solution is already in database" << endl;
				cout << "Do you want to try again? | Yes - 1 | No - 0" << endl;
				cout << "Answer"; cin >> sAnsw;
				if (!atoi(sAnsw)) {
					vWaitForPressAnyKey();
					return;
				}
			}
			else if (fopen((nameOfFile + ".txt").c_str(), "r") == NULL) {
				cout << "File " << nameOfFile << ".txt doesn't exist!" << endl;
				cout << "Do you want to try again? | Yes - 1 | No - 0" << endl;
				cout << "Answer"; cin >> sAnsw;
				if (!atoi(sAnsw)) {
					vWaitForPressAnyKey();
					return;
				}
			}
			else break; // correct fileName
			system("CLS");
		}
		
		if (!actualInst.bReadFromFileSol((nameOfFile + ".txt").c_str()) ) {
			cout << "File doesn't have correct format for this instance." << endl;
			vWaitForPressAnyKey();
			return;
		}
		
		if (!actualInst.bConstraintsSatisfied(actualInst.getSolution())) {
			cout << "Solution have incorrect values, only correct solutions can be saved." << endl;
			cout << "Program can automaticly repair it, it may lower the quality of it." << endl;
			cout << "Do You want to repair solution automaticly? | 1 - Yes | 0 - No" << endl;
			cout << "Answer: "; cin >> sAnsw;

			if (!atoi(sAnsw)) {
				vWaitForPressAnyKey();
				return;
			}
		}
		system("CLS");
		vPrintStringInFrame(nameOfFile.c_str(),1,1);
		actualInst.vShowSolution();
		cout << "Quality of " << nameOfFile << " | " << actualInst.dGetQuality(actualInst.getSolution()) << endl;

		cout << endl << "Do you want to save " << nameOfFile << "? | 1 - Yes | 2 - No" << endl;
		cout << "Answer: "; cin >> sAnsw;

		if (atoi(sAnsw)) {
			vAddSolution(nameOfFile);
			cout <<actualInst.getName()<<"_SOL_"<< nameOfFile << ".txt is saved in database!";
		}

		vWaitForPressAnyKey();
	}
	// --4-- // Specific Instance MENU - Generate new Solution
	void vMENUgenerateNewSol() {
		char sAnsw[10];
		while (1) {
			vPrintStringInFrame("Generating new Solution", 1, 1);
			vPrintStringInFrame("Choose algorithm", 0, 1);
			vPrintAvaibleAlgorithms();
			cout << "|------------ 0. Back          ------------|" << endl;
			cout << "|__________________________________________|" << endl;
			cout << "Answer: "; cin >> sAnsw;
			system("CLS");
			switch (atoi(sAnsw)) {

			case 1:
				vCRandomSearch();
				system("CLS");
				break;
			case 2:
				vCDiffEvol();
				system("CLS");
				break;
			case 0:
				return;

			default: cout << "Incorrect option!" << endl;
			}
		}
		
	}
	// --5-- // Specific Instance MENU - Delete chosen Solutions
	void vMENUdeleteChosenSols() {
		vPrintStringInFrame(actualInst.getName().c_str(), 1, 1);

		vReadSolsFromFile(actualInst.getName());
		vPrintLastSolutions();

		char sAnsw2[10];
		int iAnsw = iChooseSolution();
		if (iAnsw == 0) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}
		iAnsw--; // Vector starts at 0 index

		cout << endl << "Are You sure to delete this instance? | Yes - 1 | No - 0" << endl;
		cout << "Answer: "; cin >> sAnsw2;
		if (!atoi(sAnsw2)) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}

		// Solution file	
		std::remove((actualInst.getName() + "_SOL_" + lastSolutions[iAnsw].sGetName() + ".txt").c_str());
		cout << endl << "Deleted: " << actualInst.getName() + "_SOL_" + lastSolutions[iAnsw].sGetName()+".txt";
		lastSolutions.erase(lastSolutions.begin()+iAnsw);

		vUpdateSolutionList();

		vWaitForPressAnyKey();
	}


////////////////////////////////-------------------------- Optimization Algorithms -----------------------------/////////////////////////////////////
	void vCRandomSearch() {
		// Basic variables for each algorithm
		char sAnsw[51];
		double dTime;
		std::vector <double> sol;

		vPrintStringInFrame("CRandomSearch",1,1);
		cout << "Enter a time in which the algorithm will run (Miliseconds, like '2500')" << endl;
		cout << "Answer: "; cin >> dTime;

		cout << "Do You want to see the process of choosing solution? | 1 - Yes | 0 - No" << endl;
		cout << "It's a bit slower, becouse program use console output." << endl;
		cout << "Answer: "; cin >> sAnsw;
		CRandomSearch<double> cRandSearch;
		
		cRandSearch.setInstance(actualInst);
		if (atoi(sAnsw)) {
			sol=cRandSearch.getSolutionShow(dTime);
		}
		else {
			sol=cRandSearch.getSolution(dTime);
		}
		double quality = actualInst.dGetQuality(sol);
		actualInst.vShowSolution();
		cout << endl << "Quality of newSolution: " << quality << endl;

		cout << endl << "Do You want to save this solution? | 1- Yes | 0 - No" << endl;
		cout << "Answer: "; cin >> sAnsw;

		if (atoi(sAnsw)) {
			cout << "Give a name of solution without whitespaces, max 50 characters (like 'MyNewSol')" << endl;
			while (1) { // Until name will be new
				cout << "Answer: "; cin >> sAnsw;
				if (!bSolFileExist(sAnsw)) {
					vAddSolution(sAnsw);
					return;
				}
				cout << "Name already taken!" << endl;
			}	
		}
	}
	
	void vCDiffEvol() {
		// Basic variables for each algorithm
		char sAnsw[51];
		std::vector <double> sol;
		double dTime;
		// Additional variables for CDiffEvol
		int iAmountOfPopulation;
		double dCrossProb, dDiffWeight;

		vPrintStringInFrame("CDiffEvol", 1, 1);

		cout << "Enter a time in which the algorithm will run (Miliseconds, like '2500')" << endl;
		cout << "Answer: "; cin >> dTime;
		cout << "Enter amount of population" << endl;
		cout << "Answer: "; cin >> iAmountOfPopulation;
		cout << "Enter probability of crossing genes beetwen population(double, from 0 to 1, best one around 0.95)" << endl;
		cout << "Answer: "; cin >> dCrossProb;
		cout << "Enter difference ratio of value when genes are crossed(double, from 0 to 1, best one around 0.4)" << endl;
		cout << "Answer: "; cin >> dDiffWeight;


		cout << "Do You want to see the process of choosing solution? | 1 - Yes | 0 - No" << endl;
		cout << "It's a bit slower, becouse program use console output." << endl;
		cout << "Answer: "; cin >> sAnsw;
		CDiffEvol<double> cDiffEvol(actualInst,iAmountOfPopulation,dCrossProb,dDiffWeight);
		

		if (atoi(sAnsw)) {
			sol=cDiffEvol.getSolutionShow(dTime);
		}
		else {
			sol=cDiffEvol.getSolution(dTime);
		}
		double quality = actualInst.dGetQuality(sol);
		actualInst.vShowSolution();

		cout << endl << "Quality of newSolution: " << quality << endl;

		cout << endl << "Do You want to save this solution? | 1- Yes | 0 - No" << endl;
		cout << "Answer: "; cin >> sAnsw;

		if (atoi(sAnsw)) {
			cout << "Give a name of solution without whitespaces, max 50 characters (like 'MyNewSol')" << endl;
			while (1) { // Until name will be new
				cout << "Answer: "; cin >> sAnsw;
				if (!bSolFileExist(sAnsw)) {
					vAddSolution(sAnsw);
					return;
				}
				cout << "Name already taken!" << endl;
			}
		}
	}

////////////////////////////////--------------------- Functions used in multiple options -----------------------/////////////////////////////////////

	// Prints string in frame, depends on a size of the string // max size of string is 42
	void vPrintStringInFrame(const char *str,bool upperLine, bool lowerLine) {
		size_t length = strlen(str);
		bool odd = (length % 2);
		if (upperLine)cout << " __________________________________________ " << endl;
		cout << "|"; for (size_t i = 0; i < ((FRAME_LENGTH- length+ odd)/2)-3; i++) { cout << "-"; }
		
		cout << "- " << str << " -";

		for (size_t i = 0; i < ((FRAME_LENGTH-length)/2)-3; i++) { cout << "-"; } cout << "|"<<endl;
		if(lowerLine)cout << "|__________________________________________|" << endl;
	}
	// Prints avaible instances
	void vPrintInstances() {
		for (int i = 0; i < instancesNames.size(); i++) {
			cout << i + 1 << ". " << instancesNames[i] << endl;
		}
	}
	// Waits for user to press any key
	void vWaitForPressAnyKey() {
		cout << endl << endl << "Press any key to go back.";
		_getch();
	}
	// Prints solutions from instance that is now being read
	void vPrintLastSolutions() {
		
		vPrintStringInFrame(("Solutions of "+actualInst.getName()).c_str(),1,0);
		vPrintStringInFrame("And their quality", 0, 0);
		cout << "|__________________________________________|" << endl;
		cout << endl;
		for (int i = 0; i < lastSolutions.size(); i++) {
			cout <<i+1<<". "<< lastSolutions[i].toString() << endl;
		}
	}
	// Prints avaible algorithms
	void vPrintAvaibleAlgorithms() {
		vPrintStringInFrame("1. CRandomSearch", 0, 0);
		vPrintStringInFrame("2. CDiffEvol    ", 0, 0);
	}
	// Reads solutions from instance that is now being read
	void vReadSolsFromFile(std::string instName) {
		FILE* listSolFile;
		listSolFile = fopen((instName + "_SOLUTIONS.txt").c_str(), "r");
		lastSolutions.clear();
		fseek(listSolFile,0, SEEK_END);

		if (ftell(listSolFile) == 0) {
			fclose(listSolFile);
			return;
		}

		char sHelper[101];
		rewind(listSolFile);
		while (!feof(listSolFile)) {
			fscanf(listSolFile, "%s" , sHelper);
			actualInst.bReadFromFileSol((instName + "_SOL_" + sHelper + ".txt").c_str());

			actualInst.dGetQuality(actualInst.getSolution());

			CSolution newSol(sHelper, actualInst.dGetQuality(actualInst.getSolution()), actualInst.getSolution());
			lastSolutions.push_back(newSol);
		}
		fclose(listSolFile);
	}
	// Adds created/added from file instance to database
	void vAddInstance(std::string fileName) {
		FILE* actualFile;
		actualFile = fopen("INSTANCE_LIST.txt", "r");
		fseek(actualFile, 0, SEEK_END);
		int size = ftell(actualFile);
		fclose(actualFile);

		actualFile = fopen("INSTANCE_LIST.txt", "a");
		if (size != 0) fprintf(actualFile, "\n");
		
		
		fprintf(actualFile, fileName.c_str());
		instancesNames.push_back(fileName);
		fclose(actualFile);

		if (actualFile = fopen((fileName + "_SOLUTIONS.txt").c_str(), "r")) {
			fclose(actualFile);
			return;
		}
		else {
			actualFile = fopen((fileName + "_SOLUTIONS.txt").c_str(), "w");
			fclose(actualFile);
		}
	}
	// Adds created/added form file solution to database
	void vAddSolution(std::string fileName) {
		
		FILE* actualFile;
		actualFile = fopen((actualInst.getName()+"_SOLUTIONS.txt").c_str(),"r");
		fseek(actualFile, 0, SEEK_END);
		int size = ftell(actualFile);
		fclose(actualFile);

		actualFile = fopen((actualInst.getName() + "_SOLUTIONS.txt").c_str(), "a");
		if (size != 0) fprintf(actualFile, "\n");


		fprintf(actualFile, fileName.c_str());
		fclose(actualFile);
		
		CSolution newSol(fileName.c_str(),actualInst.dGetQuality(actualInst.getSolution()), actualInst.getSolution());
		lastSolutions.push_back(newSol);
		actualInst.bSaveToFileSol((actualInst.getName() + "_SOL_" + fileName + ".txt").c_str());
	}
	// Checking if instance file is already in database
	bool bInstFileExist(std::string fileName) {
		for (size_t i = 0; i < instancesNames.size(); i++) {
			if (instancesNames[i] == fileName) 
				return true;
		}
		return false;
	}
	// Checking if solution file is already in database
	bool bSolFileExist(std::string fileName) {
		for (size_t i = 0; i < lastSolutions.size(); i++) {
			if (lastSolutions[i].sGetName() == fileName)
				return true;
		}
		return false;
	}
	// returns chosen number of instance
	int iChooseInstance() {
		char odpCh[100];
		int odp;
		while (1) {
			cout << endl << "Choose number of instance that interest You(0 - Back): "<<endl;
			cout << "Answer: "; cin >> odpCh;
			odp = atoi(odpCh);
			if (odp == 0) return odp;
			if (odp > instancesNames.size()) {
				cout << "Incorect input! Too big number " << endl;
			}
			else if (odp < 0) {
				cout << "Incorect input! Too small number " << endl;
			}
			else return odp; // if chosen correctly
		}
	}
	// returns chosen number of solution
	int iChooseSolution() {
		char answCh[100];
		int answ;
		while (1) {
			cout << endl << "Choose number of solution that interest You(0 - Back): " << endl;
			cout << "Answer: "; cin >> answCh;
			answ = atoi(answCh);
			if (answ > lastSolutions.size()) {
				cout << "Incorect input! Too big number " << endl;
			}
			else if (answ < 0) {
				cout << "Incorect input! Too small number " << endl;
			}
			else return answ; // if chosen correctly
		}
	}
	// Sets CMscnProblem object on instance with given index
	void vSetInstance(int index) {
		actualInst.bReadFromFileInst((instancesNames[index] + ".txt").c_str());
	}
	// After deleting new instance it updates instancesNames
	void vUpdateInstanceList() {
		FILE* listFile;
		listFile = fopen("INSTANCE_LIST.txt", "w");
		char sHelper[101];
		fprintf(listFile, instancesNames[0].c_str());
		for (int i = 1; i < instancesNames.size(); i++) {
			fprintf(listFile, "\n");
			fprintf(listFile, instancesNames[i].c_str());
		}
		fclose(listFile);
	}
	// After deletingnew solutions it updates lastSolutions
	void vUpdateSolutionList() {
		FILE* listFile;
		listFile = fopen((actualInst.getName() + "_SOLUTIONS.txt").c_str(), "w");
		char sHelper[101];
		fprintf(listFile, lastSolutions[0].sGetName().c_str());
		for (int i = 1; i < lastSolutions.size(); i++) {
			fprintf(listFile, "\n");
			fprintf(listFile, lastSolutions[i].sGetName().c_str());
		}
		fclose(listFile);
	}

};

