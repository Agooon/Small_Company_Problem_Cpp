#pragma once
#include "CSolution.h"
#include "CMscnProblem.h"
#include "CRandom.h"
#define FRAME_LENGTH 44

#pragma warning(disable: 26451)
using namespace std;
class CConsoleMenu
{
public:
	// Starts by reading changes in INSTANCE_LIST.txt
	CConsoleMenu() {
		FILE* listFile;
		listFile = fopen("INSTANCE_LIST.txt","r");
		char sHelper[101];
		while (!feof(listFile)) {
			fscanf(listFile, "%100s", sHelper);
			instancesNames.push_back(sHelper);
		}
		fclose(listFile);
	}
	~CConsoleMenu() {

	}

////////////////////////////////--------------------------------------------------------------------------------/////////////////////////////////////
////////////////////////////////------------------------------- START MENU  ------------------------------------/////////////////////////////////////
///////////////////////////////---------------------------------------------------------------------------------/////////////////////////////////////

	void vStartProgram() {
		int odp;
		while (1) {
			vPrintStringInFrame("Choose option",0);
			cout << "|1. Instance menu                          |" << endl;
			cout << "|2. About program and author               |" << endl;
			cout << "|3. Exit                                   |" << endl;
			cout << "|__________________________________________|" << endl;
			cout << "Answer: "; cin >> odp;
			system("CLS");

			switch (odp) {
			case 1: // Instance menu 
				vMENUInstanceMenu();
				break;
			case 2: // About program and author 
				vMENUInfoAbout();
				system("CLS");
				break;
			case 3: // End
				cout << "Bye, Bye!";
				return;
				break;
			default: cout << "Incorrect option!"<<endl;
			}
		}
	}
private:
	std::vector<std::string> instancesNames; // changes if user adds/deletes instance
	std::vector<CSolution> lastSolutions; // changes when reading from file
	CMscnProblem<double> actualInst; // CMscProblem class to operate instances and solutions


	// -- 2 -- // START MENU - About program and author 
	void vMENUInfoAbout() {
		vPrintStringInFrame("About program and Author",1);

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

		cout << "Press any key to go back.";
		_getch();
	}

////////////////////////////////--------------------------------------------------------------------------------/////////////////////////////////////
////////////////////////////////----------------------------- INSTANCE MENU  -----------------------------------/////////////////////////////////////
///////////////////////////////---------------------------------------------------------------------------------/////////////////////////////////////

	// --1-- // START MENU - Instance MENU
	void vMENUInstanceMenu() {
		int odp;
		while (1) {
		//	cout << " __________________________________________ " << endl;
		//	cout << "|-------------- Instance MENU -------------|" << endl;
			vPrintStringInFrame("Instance MENU",0);
			cout << "|1. Show avaible instances                 |" << endl;
			cout << "|2. Add instance from unregistered file    |" << endl;
			cout << "|3. Generate new instance                  |" << endl;
			cout << "|4. Delete instance                        |" << endl;
			cout << "|5. Solution MENU                          |" << endl;
			cout << "|6. Back                                   |" << endl;
			cout << "|__________________________________________|" << endl;
			cout << "Answer: "; cin >> odp;
			system("CLS");

			switch (odp) {
			case 1: // Show avaible instances
				vMENUShowAvalInst();
				system("CLS");
				break;
			case 2: // Add instance from unregistered file
				vMENUAddInstFromFile();
				system("CLS");
				break;
			case 3: // Generate new instance 
				vMENUGenerateNewInst();
				system("CLS");
				break;
			case 4: // Delete instance 
				vMENUDeleteInst();
				system("CLS");
				break;
			case 5: // Solution MENU 
				vMENUSolutionMenu();
				system("CLS");
				break;
			case 6: // Back
				return;
				break;
			default: cout << "Incorrect option!"<<endl;
			}
		}
	}
	// --1-- // INSTANCE MENU - Show avaible instances
	void vMENUShowAvalInst() {
		vPrintStringInFrame("Instances",1);
		vPrintInstances();

		int odp = iChooseInstance();
		if (odp == 0) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}
		odp--; // Vector starts at 0 index

		system("CLS");
		vPrintStringInFrame(instancesNames[odp].c_str(),1);
		
		actualInst.bReadFromFileInst((instancesNames[odp] + ".txt").c_str());
		actualInst.vShowInstance();
		vReadSolFromFile(instancesNames[odp]);
		cout << "List of solutions and their quality." << endl;
		cout << "To see more information about them go to 'Solution MENU'" << endl;
		vPrintLastSolutions();

		cout <<endl<<endl<< "Press any key to go back.";
		_getch();
	}
	
	// --2-- // INSTANCE MENU - Add instance from unregistered file
	void vMENUAddInstFromFile() {
		std::string fileName;
		vPrintStringInFrame("Add instance from file",1);

		cout << "Enter the file name (without .txt, like 'Myfile'): " << endl;
		cout << "Answer: "; cin >> fileName;

		// Checking if file exist
		if (actualInst.bReadFromFileInst((fileName + ".txt").c_str()) == NULL) {
			cout << "File doesn't exist!";
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}
		if (bInstFileExist(fileName)) {
			cout << "File is already in database!";
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}
		vAddInstance(fileName);

		cout << endl << endl << "Press any key to go back.";
		_getch();
	}
	// --3-- // INSTANCE MENU - Generate new instance
	void vMENUGenerateNewInst() {
		// Values needed to generate instance of problem
		bool odp;
		std::string nameOfInst;
		size_t suppliers, fabrics, warehouses, shops;
		unsigned int seed = 1;
		double minGenVal = 1, maxGenVal = 500;
		// -- end of variables -- //	
		while (1) {
			vPrintStringInFrame("Generating an instance of Problem",1);
			cout << "Name of new instance (without whites): "; cin >> nameOfInst;
			if (bInstFileExist(nameOfInst)) {
				system("CLS");
				cout << "This instance name is already taken!" << endl;
			}
			else break; // If name is unique -> end the loop
		}

		cout << "Amount of suppliers(int,val<0): "; cin >> suppliers;
		cout << "Amount of fabrics(int,val<0): "; cin >> fabrics;
		cout << "Amount of warehouses(int,val<0): "; cin >> warehouses;
		cout << "Amount of shops(int,val<0): "; cin >> shops;

		cout << "Set your own seed for generator - 1"  << endl << "Set random seed for generator - 0" << endl;
		cout << "Answer: "; cin >> odp;

		if (odp) { cout << "Seed for a generator(int,val<0): "; cin >> seed; }
		else {
			std::random_device device;
			seed = device();
		}
		cout << "Minimum value for a random constant value used for generation(double): "; cin >> minGenVal;
		cout << "Maximum value for a random constant value used for generation(double): "; cin >> maxGenVal;

		cout << endl << "Do you want to generate this instance?" << endl;
		cout << "Yes - 1 | No - 0" << endl;
		cout << "Answer: "; cin >> odp;

		if (!odp) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}

		actualInst.vGenerateInstance(suppliers, fabrics, warehouses, shops, seed, minGenVal, maxGenVal);
		actualInst.vShowInstance();

		cout << endl << "Do you want to save this instance?" << endl;
		cout << "Yes - 1 | No - 0" << endl;
		cout << "Answer: "; cin >> odp;
		if (odp ) {
			actualInst.bSaveToFileInst((nameOfInst + ".txt").c_str());
			vAddInstance(nameOfInst);
		}
		cout << endl << endl << "Press any key to go back.";
		_getch();
	}
	// --4-- // INSTANCE MENU - Delete instance
	void vMENUDeleteInst() {
		int odp;
		bool odp2,odp3;
		vPrintStringInFrame("Delete instance",1);
		cout << "List of instances: " << endl;
		vPrintInstances();
		odp = iChooseInstance();
		if (odp == 0) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}
		odp--; // Vector starts at 0 index

		system("CLS");
		vPrintStringInFrame(instancesNames[odp].c_str(), 1);

		cout << "Show instance and it's solutions| Yes - 1 | No - 0"<<endl;
		cout << "Answer: "; cin >> odp2;
		if (odp2) {
			actualInst.bReadFromFileInst((instancesNames[odp] + ".txt").c_str());
			actualInst.vShowInstance();
			vReadSolFromFile(instancesNames[odp]);
			cout << "List of solutions and their quality." << endl;
			cout << "To see more information about them go to 'Solution MENU'" << endl;
			vPrintLastSolutions();
		}
		
		cout << endl << "Are You sure to delete this instance? | Yes - 1 | No - 0" << endl;
		cout << "Answer: "; cin >> odp3;
		if (!odp3) {
			cout << endl << endl << "Press any key to go back.";
			_getch();
			return;
		}

		// If solutions hadn't been read before
		if (!odp2) {
			actualInst.bReadFromFileInst((instancesNames[odp] + ".txt").c_str());
			actualInst.bReadFromFileInst((instancesNames[odp] + ".txt").c_str());
			vReadSolFromFile(instancesNames[odp]);
		}
		
		// Deleting files
		
		for (int i = 0; i < lastSolutions.size(); i++) {
			std::remove((instancesNames[odp] + "_SOL_" + lastSolutions[i].sGetName() + ".txt").c_str());
			cout << endl << "Deleted: " << instancesNames[odp] + "_SOL_"+lastSolutions[i].sGetName();
		}
			
		std::remove((instancesNames[odp] + "_SOLUTIONS.txt").c_str());
		cout << endl << "Deleted: " << instancesNames[odp]+ "_SOLUTIONS.txt";
		std::remove((instancesNames[odp] + ".txt").c_str());
		cout << endl << "Deleted: " << instancesNames[odp];
		
		// Updating INSTANCE_LIST.txt
		lastSolutions.clear();
		instancesNames.erase(instancesNames.begin()+odp);
		vUpdateInstanceList();

		cout << endl << endl << "Press any key to go back.";
		_getch();
	}
	

////////////////////////////////--------------------------------------------------------------------------------/////////////////////////////////////
////////////////////////////////----------------------------- SOLUTION MENU ------------------------------------/////////////////////////////////////
///////////////////////////////---------------------------------------------------------------------------------/////////////////////////////////////
	// --5-- // INSTANCE MENU - Solution MENU
	void vMENUSolutionMenu() {
		int odp;
		while (1) {
			vPrintStringInFrame("Solution MENU", 0);
			cout << "|1. Choose instance                        |" << endl;
			cout << "|2. Avaible algorithms                     |" << endl;
			cout << "|3. Back                                   |" << endl;
			cout << "|__________________________________________|" << endl;
			cout << "Answer: "; cin >> odp;
			system("CLS");

			switch (odp) {
			case 1: // Choose instance
				vChooseAlgorithm();
				break;
			case 2: // Avaible algorithms 
				vAvaibleAlgorithmsInfo();
				system("CLS");
				break;
			case 3: // Back 
				return;
				break;
			default: cout << "Incorrect option!" << endl;
			}
		}
	}
	// --2-- // SOLUTION MENU - Avaible algorithms
	void vAvaibleAlgorithmsInfo() {
		vPrintStringInFrame("Avaible Algorithms", 1); cout << endl;

		vPrintStringInFrame("CRandomSearch", 1);
		cout << "It's a simple algorithm that is searching for" << endl;
		cout << "a solution in a  given time.  At the start it" << endl;
		cout << "randomize starting solution and with the same" << endl;
		cout << "condtions randomizes next one, if the new one" << endl;
		cout << "is  better,  it  replaced  the  old  one.  It" << endl;
		cout << "repeats until time tuns out."<<endl;

		vPrintStringInFrame("CDiffEvol",1);
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
		cout << endl << endl << "Press any key to go back.";
		_getch();
		return;
	}

////////////////////////////////--------------------------------------------------------------------------------/////////////////////////////////////
////////////////////////////////-------------------------- Specific Instance MENU ------------------------------/////////////////////////////////////
///////////////////////////////---------------------------------------------------------------------------------/////////////////////////////////////
	// --1-- // SOLUTION MENU - Choose instance
	void vChooseAlgorithm() {
		cout << "Not implemented yet.";

		cout << endl << endl << "Press any key to go back.";
		_getch();
		system("CLS");
	}



////////////////////////////////--------------------------------------------------------------------------------/////////////////////////////////////
////////////////////////////////--------------------- Functions used in multiple options -----------------------/////////////////////////////////////
///////////////////////////////---------------------------------------------------------------------------------/////////////////////////////////////
	// 
	void vPrintStringInFrame(const char *str, bool lowerLine) {
		size_t length = strlen(str);
		bool odd = (length % 2);
		cout << " __________________________________________ " << endl;
		cout << "|"; for (size_t i = 0; i < ((FRAME_LENGTH- length+ odd)/2)-2; i++) { cout << "-"; }
		
		cout << " " << str << " ";

		for (size_t i = 0; i < ((FRAME_LENGTH-length)/2)-2; i++) { cout << "-"; } cout << "|"<<endl;
		if(lowerLine)cout << "|__________________________________________|" << endl;
	}

	// Prints avaible instances
	void vPrintInstances() {
		for (int i = 0; i < instancesNames.size(); i++) {
			cout << i + 1 << ". " << instancesNames[i] << endl;
		}
	}
	// Prints solutions from instance that is now being read
	void vPrintLastSolutions() {
		for (int i = 0; i < lastSolutions.size(); i++) {
			cout << lastSolutions[i].toString() << endl;
		}
	}
	// Reads solutions from instance that is now being read
	void vReadSolFromFile(std::string instName) {
		FILE* listSolFile;
		listSolFile = fopen((instName + "_SOLUTIONS.txt").c_str(), "r");
		
		fseek(listSolFile,0, SEEK_END);

		if (ftell(listSolFile) == 0) {
			fclose(listSolFile);
			lastSolutions.clear();
			return;
		}

		lastSolutions.clear();
		char sHelper[100];
		rewind(listSolFile);
		while (!feof(listSolFile)) {
			fgets(sHelper, 100, listSolFile);
			actualInst.bReadFromFileSol((instName + "_SOL_" + sHelper + ".txt").c_str());
			CSolution newSol(sHelper, actualInst.dGetQuality(actualInst.getSolution()), actualInst.getSolution());
			lastSolutions.push_back(newSol);
		}
		fclose(listSolFile);
	}
	// Adds created/added from file instance to database
	void vAddInstance(std::string fileName) {
		FILE* actualFile;
		actualFile = fopen("INSTANCE_LIST.txt", "a");
		fprintf(actualFile, "\n");
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
	// Checking if file is already in database
	bool bInstFileExist(std::string fileName) {
		for (int i = 0; i < instancesNames.size(); i++) {
			if (instancesNames[i] == fileName) 
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

};

