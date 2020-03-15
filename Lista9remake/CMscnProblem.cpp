#include "pch.h"
#include "CMscnProblem.h"
#pragma warning(disable: 4267)
#pragma warning(disable: 6031)
//Specialized INT
template<>
bool CMscnProblem<int>::checkBasicCorrectness(std::vector<int> pdSol)
{
	if (pdSol.empty()) {
		this->errCode = PD_SOLUTION_ERR_NOT_EXIST;
		return false;
	}
	//Czy ma wartoœci ujemne
	for (size_t i = 0; i < pdSol.size(); i++) {
		if (pdSol[i] < 0) {
			this->errCode = PD_SOLUTION_ERR_NEGATIVE_VAL;
			return false;
		}
	}
	//Czy zgadza sie z instancj¹
	if (pdSol[0] != this->dostL || pdSol[1] != this->fabL ||
		pdSol[2] != this->magL || pdSol[3] != this->sklL) {
		this->errCode = PD_SOLUTION_ERR_INFORMATION;
		return false;
	}

	if (pdSol.size() != (4 + (this->dostL*this->fabL) + (this->fabL*this->magL) + (this->magL*this->sklL))) {
		this->errCode = PD_SOLUTION_ERR_WRONG_SIZE;
		return false;
	}
	return true;
}

template<>
double CMscnProblem<int>::dGetQuality(std::vector<int> &pdSol) {
	this->vSaveSolution(pdSol);
	//Podstawowa naprawa limitów minmax i limitu produkcyjnych


	if (!this->bConstraintsSatisfied(pdSol)) {
		this->vRepairMinmax(pdSol);
		this->vRepairLimits(pdSol);
	}

	int kosztTransportu = 0;
	int kosztUmow = 0;
	int przychod = 0;

	bool used;
	//xd
	for (int i = 0; i < this->dostL; i++) {
		used = false;
		for (int j = 0; j < this->fabL; j++) {
			if (this->xd.getVal(i, j) != 0) used = true;
			kosztTransportu += this->xd.getVal(i, j) * this->cd.getVal(i, j);
		}
		kosztUmow += used * this->ud[i];
	}

	//xf
	for (int i = 0; i < this->fabL; i++) {
		used = false;
		for (int j = 0; j < this->magL; j++) {
			if (this->xf.getVal(i, j) != 0) used = true;
			kosztTransportu += this->xf.getVal(i, j) * this->cf.getVal(i, j);
		}
		kosztUmow += used * this->uf[i];
	}

	//xm
	for (int i = 0; i < this->magL; i++) {
		used = false;
		for (int j = 0; j < this->sklL; j++) {
			przychod += this->p[j] * this->xm.getVal(i, j);
			if (this->xm.getVal(i, j) != 0) used = true;
			kosztTransportu += this->xm.getVal(i, j) *this->cm.getVal(i, j);
		}
		kosztUmow += used * this->um[i];
	}
	this->pdSolution.assign(pdSol.begin(), pdSol.end());
	const __int64 quality = (__int64)przychod - kosztUmow - kosztTransportu;
	return quality;
}

template<>
void CMscnProblem<int>::vRepairMinmax(std::vector<int>& pdSol)
{
	for (int i = 0; i < this->lengthOfSol; i++) {
		if (pdSol[i] < this->minmax[i].first) pdSol[i] = this->minmax[i].first;
		else if (pdSol[i] > this->minmax[i].second) pdSol[i] = this->minmax[i].second;
	}
}

template<>
void CMscnProblem<int>::vRepairLimits(std::vector<int> &pdSol)
{
	std::vector <int> suma;

	//Ograniczenie dostawców do ich maksymalnych mo¿liwoœci
	suma.clear();
	suma.resize(this->dostL);
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			suma[i] += this->xd.getVal(i, j);
		}
		//Je¿eli przekracza mozliwosci to naprawiamy
		while (suma[i] > this->getSd()[i]) {
			suma[i] = 0;
			for (int j = 0; j < this->fabL; j++) {
				this->xd.setVal(i, j, this->xd.getVal(i, j) / differenceRepair);
				suma[i] += this->xd.getVal(i, j);
			}
		}
	}
	//Ograniczenie fabryk do ich maksymalnych mo¿liwoœci
	suma.clear();
	suma.resize(this->fabL);
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			suma[i] += this->xf.getVal(i, j);
		}
		//Je¿eli przekracza mozliwosci to naprawiamy
		while (suma[i] > this->getSf()[i]) {
			suma[i] = 0;
			for (int j = 0; j < this->magL; j++) {
				this->xf.setVal(i, j, this->xf.getVal(i, j) / differenceRepair);
				suma[i] += this->xf.getVal(i, j);
			}
		}
	}
	//Ograniczenie magazynów do ich maksymalnych mo¿liwoœci
	suma.clear();
	suma.resize(this->magL);
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			suma[i] += this->xm.getVal(i, j);
		}
		//Je¿eli przekracza mozliwosci to naprawiamy
		while (suma[i] > this->getSm()[i]) {
			suma[i] = 0;
			for (int j = 0; j < this->sklL; j++) {
				this->xm.setVal(i, j, this->xm.getVal(i, j) / differenceRepair);
				suma[i] += this->xm.getVal(i, j);
			}
		}
	}
	//Ograniczenie sklepów do ich maksymalnych mo¿liwoœci
	suma.clear();
	suma.resize(this->sklL);
	for (int i = 0; i < this->sklL; i++) {
		for (int j = 0; j < this->magL; j++) {
			suma[i] += this->xm.getVal(j, i);
		}
		//Je¿eli przekracza mozliwosci to naprawiamy
		while (suma[i] > this->getSs()[i]) {
			suma[i] = 0;
			for (int j = 0; j < this->magL; j++) {
				this->xm.setVal(j, i, this->xm.getVal(j, i) / differenceRepair);
				suma[i] += this->xm.getVal(j, i);
			}
		}
	}
	//naprawianie produkowania wiêcej ni¿ siê dosta³o

	//Czy fabryki produkuj¹ wiêcej ni¿ mog¹
	int valIn;
	int valOut;
	for (int i = 0; i < this->fabL; i++) {
		do {
			valIn = 0;
			valOut = 0;
			for (int j = 0; j < this->dostL; j++) {
				valIn += this->xd.getVal(j, i); //surowce do fabryki
			}
			for (int j = 0; j < this->magL; j++) {
				valOut += this->xf.getVal(i, j); //produkty z fabryki
			}
			if (valIn < valOut) {
				valIn = 0;
				valOut = 0;
				for (int j = 0; j < this->dostL; j++) {
					valIn += this->xd.getVal(j, i); //surowce do fabryki
				}
				for (int j = 0; j < this->magL; j++) {
					this->xf.setVal(i, j, this->xf.getVal(i, j) / differenceRepair);
					valOut += this->xf.getVal(i, j); //produkty z fabryki
				}
			}
		} while (valIn < valOut);
	}
	//Czy magazyny daj¹ wiêcej ni¿ maj¹
	for (int i = 0; i < this->magL; i++) {
		do {
			valIn = 0;
			valOut = 0;

			for (int j = 0; j < this->fabL; j++) {
				valIn += this->xf.getVal(j, i); //produkty do magazynu
			}
			for (int j = 0; j < this->sklL; j++) {
				valOut += this->xm.getVal(i, j); //produkty z magazynu
			}
			//przekazuje wiêcej ni¿ mo¿e
			if (valIn < valOut) {
				valIn = 0;
				valOut = 0;
				for (int j = 0; j < this->fabL; j++) {
					valIn += this->xf.getVal(j, i); //produkty do magazynu
				}
				for (int j = 0; j < this->sklL; j++) {
					xm.setVal(i, j, this->xm.getVal(i, j) / differenceRepair);
					valOut += this->xm.getVal(i, j); //produkty z magazynu
				}
			}
		} while (valIn < valOut);
	}

}

template<>
bool CMscnProblem<int>::helperCheckMinMax(int index, Matrix<int> minmaxS, int value)
{
	return (minmaxS.getVal(index, 0) <= value && minmaxS.getVal(index, 1) >= value);
}

template<>
bool CMscnProblem<int>::bCheckMinMax(std::vector<int> pdSol)
{
	int index = 4;
	int ind = 0;
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			if (!this->helperCheckMinMax(ind++, this->xdminmax, pdSol[index++])) {
				return false;
			}
		}
	}
	//xf
	ind = 0;
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			if (!this->helperCheckMinMax(ind++, this->xfminmax, pdSol[index++])) {
				return false;
			}
		}
	}
	//xm
	ind = 0;
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			if (!this->helperCheckMinMax(ind++, this->xmminmax, pdSol[index++])) {
				return false;
			}
		}
	}
	return true;
}

template<>
bool CMscnProblem<int>::bCheckOverload()
{
	int sum;
	//Sprawdzanie przeci¹¿enia dostawców
	for (int i = 0; i < this->dostL; i++) {
		sum = 0;
		for (int j = 0; j < this->fabL; j++) {
			sum += this->xd.getVal(i, j);
		}
		if (sum > this->sd[i]) {
			return false;
		}
	}
	//Sprawdzanie przeci¹¿enia fabryk
	for (int i = 0; i < this->fabL; i++) {
		sum = 0;
		for (int j = 0; j < this->magL; j++) {
			sum += this->xf.getVal(i, j);
		}
		if (sum > this->sf[i]) {
			return false;
		}
	}
	//Sprawdzanie przeci¹¿enia magazynów
	for (int i = 0; i < magL; i++) {
		sum = 0;
		for (int j = 0; j < this->sklL; j++) {
			sum += this->xm.getVal(i, j);
		}
		if (sum > this->sm[i]) {
			return false;
		}
	}
	//Sprawdzanie przeci¹¿enia sklepów
	for (int i = 0; i < this->sklL; i++) {
		sum = 0;
		for (int j = 0; j < this->magL; j++) {
			sum += this->xm.getVal(j, i);
		}
		if (sum > this->ss[i]) {
			return false;
		}
	}

	int valIn;
	int valOut;
	for (int i = 0; i < this->fabL; i++) {
		valIn = 0;
		valOut = 0;

		for (int j = 0; j < this->dostL; j++) {
			valIn += this->xd.getVal(j, i); //surowce do fabryki
		}
		for (int j = 0; j < this->magL; j++) {
			valOut += this->xf.getVal(i, j); //produkty z fabryki
		}
		if (valIn < valOut) return false; //tworzy wiêcej ni¿ mo¿e
	}
	for (int i = 0; i < this->magL; i++) {
		valIn = 0;
		valOut = 0;

		for (int j = 0; j < this->fabL; j++) {
			valIn += this->xf.getVal(j, i); //produkty do magazynu
		}
		for (int j = 0; j < this->sklL; j++) {
			valOut += this->xm.getVal(i, j); //produkty z magazynu
		}
		if (valIn < valOut) return false; //przekazuje wiêcej ni¿ mo¿e
	}
	return true;
}

template<>
bool CMscnProblem<int>::bReadFromFileInst(const char * name)
{
	FILE *newFile;
	newFile = fopen(name, "r+");
	if (newFile == NULL) { std::cout << "xdd"; }
	char *helperC;
	helperC = new char[10];

	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &this->dostL);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &this->fabL);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &this->magL);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &this->sklL);

	//Moce produkcyjne/przerobowe
	//sd
	double helper;
	this->sd.resize(this->dostL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL; i++) {
		fscanf(newFile, "%lf", &helper);
		this->sd[i] = (int)helper;
	}
	//sf
	this->sf.resize(this->fabL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->fabL; i++) {
		fscanf(newFile, "%lf", &helper);
		this->sf[i] = (int)helper;
	}
	this->sm.resize(this->magL);
	//sm
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL; i++) {
		fscanf(newFile, "%lf", &helper);
		this->sm[i] = (int)helper;
	}
	this->ss.resize(this->sklL);
	//ss
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->sklL; i++) {
		fscanf(newFile, "%lf", &helper);
		this->ss[i] = (int)helper;
	}

	//Koszty transpotu surowca/produktu

	//cd
	this->cd.resize(this->dostL, this->fabL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->cd.setVal(i, j, (int)helper);
		}
	}
	//cf
	this->cf.resize(this->fabL, this->magL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->cf.setVal(i, j, (int)helper);
		}
	}
	//cm
	this->cm.resize(this->magL, this->sklL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->cm.setVal(i, j, (int)helper);
		}
	}

	//Op³aty za umowy oraz przychod z sprzedazy produktu w sklepie
	//ud
	this->ud.resize(this->dostL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL; i++) {
		fscanf(newFile, "%lf", &helper);
		this->ud[i] = (int)helper;
	}
	//uf
	this->uf.resize(this->fabL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < fabL; i++) {
		fscanf(newFile, "%lf", &helper);
		this->uf[i] = (int)helper;
	}
	//um
	this->um.resize(this->magL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL; i++) {
		fscanf(newFile, "%lf", &helper);
		this->um[i] = (int)helper;
	}
	//p
	this->p.resize(this->sklL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->sklL; i++) {
		fscanf(newFile, "%lf", &helper);
		this->p[i] = (int)helper;
	}

	//MINMAX
	//xdminmax
	this->xdminmax.resize(this->dostL*this->fabL, 2);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL*this->fabL; i++) {
		for (int j = 0; j < 2; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xdminmax.setVal(i, j, (int)helper);
		}
	}
	//xfminmax
	this->xfminmax.resize(this->fabL*this->magL, 2);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->fabL*this->magL; i++) {
		for (int j = 0; j < 2; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xfminmax.setVal(i, j, (int)helper);
		}
	}
	//xmminmax
	this->xmminmax.resize(this->magL*this->sklL, 2);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL*this->sklL; i++) {
		for (int j = 0; j < 2; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xmminmax.setVal(i, j, (int)helper);
		}
	}
	fclose(newFile);

	this->vsetMinmax();
	return true;
}

template<>
bool CMscnProblem<int>::bReadFromFileSol(const char * name)
{
	this->errCode = 0;
	FILE *newFile;
	newFile = fopen(name, "r");
	size_t d, f, m, s;

	char *helperC;
	helperC = new char[10];

	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &d);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &f);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &m);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &s);

	if (d != this->dostL || f != this->fabL || m != this->magL || s != this->sklL) {
		this->errCode = WRONG_SOLUTION_FROM_FILE;
		fclose(newFile);
		return false;
	}
	this->pdSolution.push_back(d); this->pdSolution.push_back(f);
	this->pdSolution.push_back(m); this->pdSolution.push_back(s);

	double helper;
	//xd
	this->xd.resize(this->dostL, this->fabL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xd.setVal(i, j, (int)helper);
			this->pdSolution.push_back((int)helper);
		}
	}
	//xf
	this->xf.resize(this->fabL, this->magL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xf.setVal(i, j, (int)helper);
			this->pdSolution.push_back((int)helper);
		}
	}
	//xm
	this->xm.resize(this->magL, this->sklL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xm.setVal(i, j, (int)helper);
			this->pdSolution.push_back((int)helper);
		}
	}
	fclose(newFile);
	this->vSaveSolution();
	return true;
}

template<>
void CMscnProblem<int>::vGenerateInstance(size_t d, size_t f, size_t m, size_t s, int iInstanceSeed, double minVal, double maxVal) {
	vsetBasics(d, f, m, s);
	this->myGenerator.setSeed(iInstanceSeed);
	this->lengthOfSol = ((size_t)amountOfConst + d * f + f * m + m * s);

	int sredniaS = this->myGenerator.iRandInt(minVal, maxVal);
	std::cout << std::endl << "Srednia wylosowana na seed(" << iInstanceSeed << "): " << sredniaS;

	//Losowanie wartoœci instancji problemu
	//sd
	for (int i = 0; i < this->dostL; i++) {
		this->bsetSd(i, this->myGenerator.iRandInt(sredniaS, sredniaS*rand_multiplier));
	}
	//sf
	for (int i = 0; i < this->fabL; i++) {
		this->bsetSf(i, this->myGenerator.iRandInt(sredniaS, sredniaS * rand_multiplier));
	}
	//sm
	for (int i = 0; i < this->magL; i++) {
		this->bsetSm(i, this->myGenerator.iRandInt(sredniaS, sredniaS * rand_multiplier));
	}
	//ss
	for (int i = 0; i < this->sklL; i++) {
		this->bsetSs(i, this->myGenerator.iRandInt(sredniaS, sredniaS * rand_multiplier));
	}

	//Koszty utrzymania


	//ud
	for (int i = 0; i < this->dostL; i++) {
		this->bsetUd(i, this->myGenerator.iRandInt(sredniaS*rand_multiplier8, sredniaS*rand_multiplier12));
	}
	//uf
	for (int i = 0; i < this->fabL; i++) {
		this->bsetUf(i, this->myGenerator.iRandInt(sredniaS*rand_multiplier8, sredniaS*rand_multiplier12));
	}
	//um
	for (int i = 0; i < this->magL; i++) {
		this->bsetUm(i, this->myGenerator.iRandInt(sredniaS*rand_multiplier8, sredniaS*rand_multiplier12));
	}

	//koszty transportu/produkcji

	//cd
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			this->bsetCd(i, j, this->myGenerator.iRandInt(sredniaS / rand_multiplier3, sredniaS / rand_multiplier));
		}
	}
	//cf
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			this->bsetCf(i, j, this->myGenerator.iRandInt(sredniaS / rand_multiplier3, sredniaS / rand_multiplier));
		}
	}
	//cm
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			this->bsetCm(i, j, this->myGenerator.iRandInt(sredniaS / rand_multiplier3, sredniaS / rand_multiplier));
		}
	}


	//p
	for (int i = 0; i < this->sklL; i++) {
		this->bsetP(i, this->myGenerator.iRandInt(sredniaS*rand_multiplier1_5, sredniaS*rand_multiplier));
	}

	//MINMAX

	//xdminmax

	for (int i = 0; i < (this->dostL*this->fabL); i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) this->xdminmax.setVal(i, j, 0);
			else this->xdminmax.setVal(i, j, (sredniaS * rand_multiplier4));
		}
	}

	//xfminmax
	for (int i = 0; i < (this->magL*this->fabL); i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) this->xfminmax.setVal(i, j, 0);
			else this->xfminmax.setVal(i, j, (sredniaS * rand_multiplier4));
		}
	}
	//xmminmax

	for (int i = 0; i < (this->magL*this->sklL); i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) this->xmminmax.setVal(i, j, 0);
			else this->xmminmax.setVal(i, j, (sredniaS * rand_multiplier4));
		}
	}
	this->vsetMinmax();
}

//Specialized DOUBLE
template<>
bool CMscnProblem<double>::checkBasicCorrectness(std::vector<double> pdSol)
{
	if (pdSol.empty()) {
		this->errCode = PD_SOLUTION_ERR_NOT_EXIST;
		return false;
	}
	//Czy ma wartoœci ujemne
	for (size_t i = 0; i < pdSol.size(); i++) {
		if (pdSol[i] < 0) {
			this->errCode = PD_SOLUTION_ERR_NEGATIVE_VAL;
			return false;
		}
	}
	//Czy zgadza sie z instancj¹
	if (pdSol[0] != this->dostL || pdSol[1] != this->fabL ||
		pdSol[2] != this->magL || pdSol[3] != this->sklL) {
		this->errCode = PD_SOLUTION_ERR_INFORMATION;
		return false;
	}

	if (pdSol.size() != (4 + (this->dostL*this->fabL) + (this->fabL*this->magL) + (this->magL*this->sklL))) {
		this->errCode = PD_SOLUTION_ERR_WRONG_SIZE;
		return false;
	}
	return true;
}

template<>
double CMscnProblem<double>::dGetQuality(std::vector<double> &pdSol)
{
	this->vSaveSolution(pdSol);
	//Podstawowa naprawa limitów minmax i limitu produkcyjnych


	if (!this->bConstraintsSatisfied(pdSol)) {
		this->vRepairMinmax(pdSol);
		this->vRepairLimits(pdSol);
	}

	double kosztTransportu = 0;
	double kosztUmow = 0;
	double przychod = 0;

	bool used;
	//xd
	for (int i = 0; i < this->dostL; i++) {
		used = false;
		for (int j = 0; j < this->fabL; j++) {
			if (this->xd.getVal(i, j) != 0) used = true;
			kosztTransportu += this->xd.getVal(i, j) *this->cd.getVal(i, j);
		}
		kosztUmow += used * this->ud[i];
	}

	//xf
	for (int i = 0; i < this->fabL; i++) {
		used = false;
		for (int j = 0; j < this->magL; j++) {
			if (this->xf.getVal(i, j) != 0) used = true;
			kosztTransportu += this->xf.getVal(i, j) * this->cf.getVal(i, j);
		}
		kosztUmow += used * this->uf[i];
	}

	//xm
	for (int i = 0; i < this->magL; i++) {
		used = false;
		for (int j = 0; j < this->sklL; j++) {
			przychod += this->p[j] * this->xm.getVal(i, j);
			if (this->xm.getVal(i, j) != 0) used = true;
			kosztTransportu += this->xm.getVal(i, j) * this->cm.getVal(i, j);
		}
		kosztUmow += used * this->um[i];
	}
	this->pdSolution.assign(pdSol.begin(), pdSol.end());
	return przychod - kosztUmow - kosztTransportu;
}

template<>
void CMscnProblem<double>::vRepairMinmax(std::vector<double>& pdSol)
{
	for (int i = 0; i < this->lengthOfSol; i++) {
		if (pdSol[i] < this->minmax[i].first) pdSol[i] = this->minmax[i].first;
		else if (pdSol[i] > this->minmax[i].second) pdSol[i] = this->minmax[i].second;
	}
}

template<>
void CMscnProblem<double>::vRepairLimits(std::vector<double> &pdSol)
{
	std::vector <double> suma;

	//Ograniczenie dostawców do ich maksymalnych mo¿liwoœci
	suma.clear();
	suma.resize(this->dostL);
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			suma[i] += this->xd.getVal(i, j);
		}
		//Je¿eli przekracza mozliwosci to naprawiamy
		while (suma[i] > this->getSd()[i]) {
			suma[i] = 0;
			for (int j = 0; j < this->fabL; j++) {
				this->xd.setVal(i, j, this->xd.getVal(i, j) / differenceRepair);
				suma[i] += this->xd.getVal(i, j);
			}
		}
	}
	//Ograniczenie fabryk do ich maksymalnych mo¿liwoœci
	suma.clear();
	suma.resize(this->fabL);
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			suma[i] += this->xf.getVal(i, j);
		}
		//Je¿eli przekracza mozliwosci to naprawiamy
		while (suma[i] > this->getSf()[i]) {
			suma[i] = 0;
			for (int j = 0; j < this->magL; j++) {
				xf.setVal(i, j, this->xf.getVal(i, j) / differenceRepair);
				suma[i] += this->xf.getVal(i, j);
			}
		}
	}
	//Ograniczenie magazynów do ich maksymalnych mo¿liwoœci
	suma.clear();
	suma.resize(this->magL);
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			suma[i] += this->xm.getVal(i, j);
		}
		//Je¿eli przekracza mozliwosci to naprawiamy
		while (suma[i] > this->getSm()[i]) {
			suma[i] = 0;
			for (int j = 0; j < this->sklL; j++) {
				this->xm.setVal(i, j, this->xm.getVal(i, j) / differenceRepair);
				suma[i] += this->xm.getVal(i, j);
			}
		}
	}
	//Ograniczenie sklepów do ich maksymalnych mo¿liwoœci
	suma.clear();
	suma.resize(this->sklL);
	for (int i = 0; i < this->sklL; i++) {
		for (int j = 0; j < this->magL; j++) {
			suma[i] += this->xm.getVal(j, i);
		}
		//Je¿eli przekracza mozliwosci to naprawiamy
		while (suma[i] > this->getSs()[i]) {
			suma[i] = 0;
			for (int j = 0; j < this->magL; j++) {
				this->xm.setVal(j, i, this->xm.getVal(j, i) / differenceRepair);
				suma[i] += this->xm.getVal(j, i);
			}
		}
	}
	//naprawianie produkowania wiêcej ni¿ siê dosta³o

	//Czy fabryki produkuj¹ wiêcej ni¿ mog¹
	double valIn;
	double valOut;
	for (int i = 0; i < this->fabL; i++) {
		do {
			valIn = 0;
			valOut = 0;
			for (int j = 0; j < this->dostL; j++) {
				valIn += this->xd.getVal(j, i); //surowce do fabryki
			}
			for (int j = 0; j < this->magL; j++) {
				valOut += this->xf.getVal(i, j); //produkty z fabryki
			}
			if (valIn < valOut) {
				valIn = 0;
				valOut = 0;
				for (int j = 0; j < this->dostL; j++) {
					valIn += this->xd.getVal(j, i); //surowce do fabryki
				}
				for (int j = 0; j < this->magL; j++) {
					xf.setVal(i, j, this->xf.getVal(i, j) / differenceRepair);
					valOut += this->xf.getVal(i, j); //produkty z fabryki
				}
			}
		} while (valIn < valOut);
	}
	//Czy magazyny daj¹ wiêcej ni¿ maj¹
	for (int i = 0; i < this->magL; i++) {
		do {
			valIn = 0;
			valOut = 0;

			for (int j = 0; j < this->fabL; j++) {
				valIn += this->xf.getVal(j, i); //produkty do magazynu
			}
			for (int j = 0; j < this->sklL; j++) {
				valOut += this->xm.getVal(i, j); //produkty z magazynu
			}
			//przekazuje wiêcej ni¿ mo¿e
			if (valIn < valOut) {
				valIn = 0;
				valOut = 0;
				for (int j = 0; j < this->fabL; j++) {
					valIn += this->xf.getVal(j, i); //produkty do magazynu
				}
				for (int j = 0; j < this->sklL; j++) {
					xm.setVal(i, j, this->xm.getVal(i, j) / differenceRepair);
					valOut += this->xm.getVal(i, j); //produkty z magazynu
				}
			}
		} while (valIn < valOut);
	}

}

template<>
bool CMscnProblem<double>::helperCheckMinMax(int index, Matrix<double> minmaxS, double value)
{
	return (minmaxS.getVal(index, 0) <= value && minmaxS.getVal(index, 1) >= value);
}

template<>
bool CMscnProblem<double>::bCheckMinMax(std::vector<double> pdSol)
{
	int index = 4;
	int ind = 0;
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			if (!this->helperCheckMinMax(ind++, this->xdminmax, pdSol[index++])) {
				return false;
			}
		}
	}
	//xf
	ind = 0;
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			if (!this->helperCheckMinMax(ind++, this->xfminmax, pdSol[index++])) {
				return false;
			}
		}
	}
	//xm
	ind = 0;
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			if (!this->helperCheckMinMax(ind++, this->xmminmax, pdSol[index++])) {
				return false;
			}
		}
	}
	return true;
}

template<>
bool CMscnProblem<double>::bCheckOverload()
{
	double sum;
	//Sprawdzanie przeci¹¿enia dostawców
	for (int i = 0; i < this->dostL; i++) {
		sum = 0;
		for (int j = 0; j < this->fabL; j++) {
			sum += this->xd.getVal(i, j);
		}
		if (sum > this->sd[i]) {
			return false;
		}
	}
	//Sprawdzanie przeci¹¿enia fabryk
	for (int i = 0; i < this->fabL; i++) {
		sum = 0;
		for (int j = 0; j < this->magL; j++) {
			sum += this->xf.getVal(i, j);
		}
		if (sum > this->sf[i]) {
			return false;
		}
	}
	//Sprawdzanie przeci¹¿enia magazynów
	for (int i = 0; i < this->magL; i++) {
		sum = 0;
		for (int j = 0; j < this->sklL; j++) {
			sum += this->xm.getVal(i, j);
		}
		if (sum > this->sm[i]) {
			return false;
		}
	}
	//Sprawdzanie przeci¹¿enia sklepów
	for (int i = 0; i < this->sklL; i++) {
		sum = 0;
		for (int j = 0; j < this->magL; j++) {
			sum += this->xm.getVal(j, i);
		}
		if (sum > this->ss[i]) {
			return false;
		}
	}

	double valIn;
	double valOut;
	for (int i = 0; i < this->fabL; i++) {
		valIn = 0;
		valOut = 0;

		for (int j = 0; j < this->dostL; j++) {
			valIn += this->xd.getVal(j, i); //surowce do fabryki
		}
		for (int j = 0; j < this->magL; j++) {
			valOut += this->xf.getVal(i, j); //produkty z fabryki
		}
		if (valIn < valOut) return false; //tworzy wiêcej ni¿ mo¿e
	}
	for (int i = 0; i < this->magL; i++) {
		valIn = 0;
		valOut = 0;

		for (int j = 0; j < this->fabL; j++) {
			valIn += this->xf.getVal(j, i); //produkty do magazynu
		}
		for (int j = 0; j < this->sklL; j++) {
			valOut += this->xm.getVal(i, j); //produkty z magazynu
		}
		if (valIn < valOut) return false; //przekazuje wiêcej ni¿ mo¿e
	}
	return true;
}

template<>
bool CMscnProblem<double>::bReadFromFileInst(const char * name)
{
	FILE *newFile;
	newFile = fopen(name, "r+");
	if (newFile == NULL) return false;
	char *helperC;
	helperC = new char[10];

	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &this->dostL);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &this->fabL);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &this->magL);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &this->sklL);

	//Moce produkcyjne/przerobowe
	//sd
	this->sd.resize(this->dostL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL; i++) {
		fscanf(newFile, "%lf", &this->sd[i]);
	}
	//sf
	this->sf.resize(this->fabL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->fabL; i++) {
		fscanf(newFile, "%lf", &this->sf[i]);
	}
	this->sm.resize(this->magL);
	//sm
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL; i++) {
		fscanf(newFile, "%lf", &this->sm[i]);
	}
	this->ss.resize(this->sklL);
	//ss
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->sklL; i++) {
		fscanf(newFile, "%lf", &this->ss[i]);
	}

	//Koszty transpotu surowca/produktu
	double helper;
	//cd
	this->cd.resize(this->dostL, this->fabL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->cd.setVal(i, j, helper);
		}
	}
	//cf
	this->cf.resize(this->fabL, this->magL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->cf.setVal(i, j, helper);
		}
	}
	//cm
	this->cm.resize(this->magL, this->sklL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->cm.setVal(i, j, helper);
		}
	}

	//Op³aty za umowy oraz przychod z sprzedazy produktu w sklepie
	//ud
	this->ud.resize(this->dostL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL; i++) {
		fscanf(newFile, "%lf", &this->ud[i]);
	}
	//uf
	this->uf.resize(this->fabL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->fabL; i++) {
		fscanf(newFile, "%lf", &this->uf[i]);
	}
	//um
	this->um.resize(this->magL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL; i++) {
		fscanf(newFile, "%lf", &this->um[i]);
	}
	//p
	this->p.resize(this->sklL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < sklL; i++) {
		fscanf(newFile, "%lf", &this->p[i]);
	}

	//MINMAX
	//xdminmax
	this->xdminmax.resize(this->dostL*this->fabL, 2);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL*this->fabL; i++) {
		for (int j = 0; j < 2; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xdminmax.setVal(i, j, helper);
		}
	}
	//xfminmax
	this->xfminmax.resize(this->fabL*this->magL, 2);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->fabL*this->magL; i++) {
		for (int j = 0; j < 2; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xfminmax.setVal(i, j, helper);
		}
	}
	//xmminmax
	this->xmminmax.resize(this->magL*this->sklL, 2);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL*this->sklL; i++) {
		for (int j = 0; j < 2; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xmminmax.setVal(i, j, helper);
		}
	}
	fclose(newFile);

	this->vsetMinmax();
	return true;
}

template<>
bool CMscnProblem<double>::bReadFromFileSol(const char * name)
{
	this->errCode = 0;
	FILE *newFile;
	newFile = fopen(name, "r");
	size_t d, f, m, s;

	char *helperC;
	helperC = new char[10];

	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &d);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &f);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &m);
	fscanf(newFile, "%s", helperC); fscanf(newFile, "%zu", &s);

	if (d != this->dostL || f != this->fabL || m != this->magL || s != this->sklL) {
		this->errCode = WRONG_SOLUTION_FROM_FILE;
		fclose(newFile);
		return false;
	}
	this->pdSolution.push_back(d); this->pdSolution.push_back(f);
	this->pdSolution.push_back(m); this->pdSolution.push_back(s);

	double helper;
	//xd
	this->xd.resize(dostL, fabL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xd.setVal(i, j, helper);
			this->pdSolution.push_back(helper);
		}
	}
	//xf
	this->xf.resize(fabL, magL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xf.setVal(i, j, helper);
			this->pdSolution.push_back(helper);
		}
	}
	//xm
	this->xm.resize(magL, sklL);
	fscanf(newFile, "%s", helperC);
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			fscanf(newFile, "%lf", &helper);
			this->xm.setVal(i, j, helper);
			this->pdSolution.push_back(helper);
		}
	}
	fclose(newFile);
	this->vSaveSolution();
	return true;
}

template<>
void CMscnProblem<double>::vGenerateInstance(size_t d, size_t f, size_t m, size_t s, int iInstanceSeed, double minVal, double maxVal) {
	this->vsetBasics(d, f, m, s);
	this->myGenerator.setSeed(iInstanceSeed);
	this->lengthOfSol = (amountOfConst + d * f + f * m + m * s);

	double sredniaS = this->myGenerator.dRandDouble(minVal, maxVal);
	std::cout << std::endl << "Srednia wylosowana na seed(" << iInstanceSeed << "): " << sredniaS;

	//Losowanie wartoœci instancji problemu
	//sd
	for (int i = 0; i < this->dostL; i++) {
		this->bsetSd(i, this->myGenerator.dRandDouble(sredniaS, sredniaS*rand_multiplier));
	}
	//sf
	for (int i = 0; i < this->fabL; i++) {
		this->bsetSf(i, this->myGenerator.dRandDouble(sredniaS, sredniaS * rand_multiplier));
	}
	//sm
	for (int i = 0; i < this->magL; i++) {
		this->bsetSm(i, this->myGenerator.dRandDouble(sredniaS, sredniaS * rand_multiplier));
	}
	//ss
	for (int i = 0; i < this->sklL; i++) {
		this->bsetSs(i, this->myGenerator.dRandDouble(sredniaS, sredniaS * rand_multiplier));
	}

	//Koszty utrzymania


	//ud
	for (int i = 0; i < this->dostL; i++) {
		this->bsetUd(i, this->myGenerator.dRandDouble(sredniaS*rand_multiplier8, sredniaS*rand_multiplier12));
	}
	//uf
	for (int i = 0; i < this->fabL; i++) {
		this->bsetUf(i, this->myGenerator.dRandDouble(sredniaS*rand_multiplier8, sredniaS*rand_multiplier12));
	}
	//um
	for (int i = 0; i < this->magL; i++) {
		this->bsetUm(i, this->myGenerator.dRandDouble(sredniaS*rand_multiplier8, sredniaS*rand_multiplier12));
	}

	//koszty transportu/produkcji

	//cd
	for (int i = 0; i < this->dostL; i++) {
		for (int j = 0; j < this->fabL; j++) {
			this->bsetCd(i, j, this->myGenerator.dRandDouble(sredniaS / rand_multiplier3, sredniaS / rand_multiplier));
		}
	}
	//cf
	for (int i = 0; i < this->fabL; i++) {
		for (int j = 0; j < this->magL; j++) {
			this->bsetCf(i, j, this->myGenerator.dRandDouble(sredniaS / rand_multiplier3, sredniaS / rand_multiplier));
		}
	}
	//cm
	for (int i = 0; i < this->magL; i++) {
		for (int j = 0; j < this->sklL; j++) {
			this->bsetCm(i, j, this->myGenerator.dRandDouble(sredniaS / rand_multiplier3, sredniaS / rand_multiplier));
		}
	}


	//p
	for (int i = 0; i < this->sklL; i++) {
		this->bsetP(i, this->myGenerator.dRandDouble(sredniaS*rand_multiplier1_5, sredniaS*rand_multiplier));
	}

	//MINMAX

	//xdminmax

	for (int i = 0; i < (this->dostL*this->fabL); i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) this->xdminmax.setVal(i, j, 0);
			else this->xdminmax.setVal(i, j, (sredniaS * rand_multiplier4));
		}
	}

	//xfminmax
	for (int i = 0; i < (this->magL*this->fabL); i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) this->xfminmax.setVal(i, j, 0);
			else this->xfminmax.setVal(i, j, (sredniaS * rand_multiplier4));
		}
	}
	//xmminmax

	for (int i = 0; i < (this->magL*this->sklL); i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) this->xmminmax.setVal(i, j, 0);
			else this->xmminmax.setVal(i, j, (sredniaS * rand_multiplier4));
		}
	}
	this->vsetMinmax();
}


template class CMscnProblem<double>;
template class CMscnProblem<int>;
