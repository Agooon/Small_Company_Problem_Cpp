#pragma once

#define default_size 5
#define err_noErr 0
#define err_wrong_size 1
#define err_wrong_index 1

template <typename T> class Matrix
{
public:
	Matrix();
	~Matrix();
	Matrix(int nheigth, int nlength);
	Matrix(int nheigth, int nlength, std::vector <T> &newMatrx);

	std::vector<T> getMatrix() { return matrx; }
	void setMatrix(int nheigth, int nlength, std::vector <T> &newMatrx);

	void resize(int nheigth, int nlength);
	int getLength() const { return length; }
	int getHeight() const { return heigth; }
	

	T getVal(int x, int y) const {
		if (x >= heigth || y >= length || x < 0 || y < 0) {
			return INT32_MIN;
		}
		return matrx[x*length + y];
	}
	void setVal(int x, int y, T value);

	int geterrCode() { return errCode; }
private:
	int length;
	int heigth;
	int errCode = 0;
	std::vector <T> matrx;
};

template <typename T>
Matrix<T>::Matrix()
{
	heigth = default_size;
	length = default_size;
	matrx.resize(default_size*default_size);
}

template <typename T>
Matrix<T>::~Matrix()
{

}

template<typename T>
Matrix<T>::Matrix(int nheigth,int nlength)
{
	length = nlength;
	heigth = nheigth;
	matrx.resize(length*heigth);
}

template<typename T>
Matrix<T>::Matrix(int nheigth, int nlength,std::vector<T>& newMatrx)
{
	length = nlength;
	heigth = nheigth;
	matrx.assign(newMatrx.begin(), newMatrx.end());
}

template<typename T>
void Matrix<T>::setMatrix(int nheigth, int nlength,std::vector<T> &newMatrx)
{
	errCode = 0;
	if (nlength < 0 || nheigth < 0) {
		errCode = err_wrong_size;
		return;
	}
	length = nlength;
	heigth = nheigth;
	matrx.assign(newMatrx.begin(), newMatrx.end());
}

template<typename T>
void Matrix<T>::resize(int nheigth,int nlength )
{
	errCode = 0;
	if ( nlength < 0 ||  nheigth < 0) {
		errCode = err_wrong_size;
		return;
	}
	length = nlength;
	heigth = nheigth;

	matrx.resize(nlength*nheigth);
}



template<typename T>
void Matrix<T>::setVal(int x, int y, T value)
{
	errCode = 0;
	if (x >= heigth || y >= length || x < 0 || y < 0) {
		errCode = err_wrong_index;
		return;
	}
	matrx[x*length + y] = value;
}

