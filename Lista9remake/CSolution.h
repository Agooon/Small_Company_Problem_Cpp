#pragma once
class CSolution
{
public:
	CSolution();
	CSolution(const char *n, double qual, std::vector<double> sol);
	~CSolution();

	void vSetName(const char* newName) { name = newName; }
	std::string sGetName() { return name; }

	void vSetSolution(std::vector<double> newSol) { this->solution = newSol; }
	std::vector<double> getSolution() { return this->solution; }
	
	void vsetQuality(double newQuality) { quality = newQuality; }
	double dGetQuality() { return this->quality; }

	std::string toString() {
		return name + " "+ std::to_string(this->quality);
	}
private:
	std::string name="Default_Name";
	std::vector<double> solution;
	double quality=0;
};

