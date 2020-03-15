#pragma once
#include "CSolution.h"
#include "CMscnProblem.h"
using namespace std;
class CConsoleMenu
{
public:
	CConsoleMenu() {
		FILE* listFile;
		listFile = fopen("INSTANCE_LIST.txt","r");
	    char sHelper[100];
		while (!feof(listFile)) {
			fscanf(listFile, "%s", sHelper);
			instancesNames.push_back(sHelper);
		}
		fclose(listFile);
	}
	~CConsoleMenu() {

	}

////////////////////////////////--- START MENU ---/////////////////////////////////////
	void vStartProgram() {
		int odp;
		while (1) {
			cout << " _________________________________________ " << endl;
			cout << "|------------- Choose option -------------|" << endl;
			cout << "|1. Instance menu                         |" << endl;
			cout << "|2. About program and author              |" << endl;
			cout << "|3. Exit                                  |" << endl;
			cout << "|_________________________________________|" << endl;
			cout << "Type: "; cin >> odp;
			system("CLS");

			switch (odp) {
			case 1: // Instance menu 
				vInstanceMenu();
				break;
			case 2: // Solution menu 
				vInfoAbout();
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
	CMscnProblem<double> actualInst;


	// -- 2 -- //
	void vInfoAbout() {
		cout << " ___________________________________________ " << endl;
		cout << "|-------- About program and Author ---------|" << endl;
		cout << "|___________________________________________|" << endl;
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
		system("CLS");
	}
	// --1-- //
////////////////////////////////--- INSTANCE MENU ---/////////////////////////////////////
	void vInstanceMenu() {
		int odp;
		while (1) {
			cout << " _________________________________________ " << endl;
			cout << "|------------- Instance MENU -------------|" << endl;
			cout << "|1. Show avaible instances                |" << endl;
			cout << "|2. Add instance from unregistered file   |" << endl;
			cout << "|3. Generate new instance                 |" << endl;
			cout << "|4. Delete instance                       |" << endl;
			cout << "|5. Solution MENU                         |" << endl;
			cout << "|6. Back                                  |" << endl;
			cout << "|_________________________________________|" << endl;
			cout << "Type: "; cin >> odp;
			system("CLS");

			switch (odp) {
			case 1: // Show avaible instances
				vShowAvalInst();
				system("CLS");
				break;
			case 2: // Add instance from unregistered file
				vAddInstFromFile();
				break;
			case 3: // Generate new instance 
				vGenerateNewInst();
				break;
			case 4: // Delete instance 
				vDeleteInst();
				break;
			case 5: // Solution MENU 
				vSolutionMenu();
				break;
			case 6: // Back
				return;
				break;
			default: cout << "Incorrect option!"<<endl;
			}
		}
	}
	// --1-- //
	void vShowAvalInst() {
		char odpCh[100];
		int odp;
		cout << " _________________________________________ " << endl;
		cout << "|--------------- Instances ---------------|" << endl;
		cout << "|_________________________________________|" << endl;
		for (int i = 0; i < instancesNames.size(); i++) {
			cout << i + 1 << ". " << instancesNames[i]<<endl;
		}
		// Until the input will be correct
		while(1){	
			cout << endl << "Choose number of instance that interest You(0 - Back): ";
			cin >> odpCh;
			odp = atoi(odpCh);
			if (odp == 0) return;
			if (odp > instancesNames.size()) {
				cout << "Incorect input! Too big number " << endl;
			}
			else if (odp < 0) {
				cout << "Incorect input! Too small number " << endl;
			}
			else break;
		}
		odp--;
		system("CLS");
		cout << " ______________"; for(size_t i = 0; i < instancesNames[odp].length()+4; i++) { cout << "_"; } cout << endl;

		cout << "|--- Instance: " << instancesNames[odp] << " ---|" << endl;

		cout << "|______________"; for(size_t i = 0; i < instancesNames[odp].length()+4; i++) { cout << "_"; }cout <<"|"<< endl;
		_sleep(100);
		actualInst.bReadFromFileInst((instancesNames[odp] + ".txt").c_str());
		actualInst.vShowInstance();
		readSolFromFileHelper(instancesNames[odp]);
		cout << "List of solutions and their quality." << endl;
		cout << "To see more information about them go to" << endl;

		for (int i = 0; i < lastSolutions.size(); i++) {
			cout<<lastSolutions[i].toString()<<endl;
		}
		cout <<endl<<endl<< "Press any key to go back.";
		_getch();
	}
	void readSolFromFileHelper(std::string instName) {
		FILE* listSolFile;

		listSolFile = fopen((instName + "_SOLUTIONS.txt").c_str(), "r");

		lastSolutions.clear();
		char sHelper[100];
		while (!feof(listSolFile)) {
			fgets(sHelper, 100, listSolFile);
			actualInst.bReadFromFileSol((instName + "_SOL_" + sHelper + ".txt").c_str());
			CSolution newSol(sHelper, actualInst.dGetQuality(actualInst.getSolution()), actualInst.getSolution());
			lastSolutions.push_back(newSol);
		}
		fclose(listSolFile);
	}
	// --2-- //
	void vAddInstFromFile() {
		cout << "Not implemented yet." << endl;
	}
	// --3-- //
	void vGenerateNewInst() {
		cout << "Not implemented yet." << endl;
	}
	// --4-- //
	void vDeleteInst() {
		cout << "Not implemented yet." << endl;
	}
	// --5-- //
	////////////////////////////////--- SOLUTION MENU ---/////////////////////////////////////
	void vSolutionMenu() {
		cout << "Not implemented yet." << endl;
	}


	// Variables used in program

	



	

};

