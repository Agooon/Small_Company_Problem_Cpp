#pragma once

#define default_size 5
#define err_noErr 0
#define err_wrong_size 1
#define err_wrong_index 1

// Simple class for using handy use of Matrixs

template <typename T> class Matrix
{
public:
	Matrix();
	~Matrix();
	Matrix(size_t nheigth, size_t nlength);
	Matrix(size_t nheigth, size_t nlength, std::vector <T> &newMatrx);

	std::vector<T> getMatrix() { return matrx; }
	void setMatrix(size_t nheigth, size_t nlength, std::vector <T> &newMatrx);

	void resize(size_t nheigth, size_t nlength);
	size_t getLength() const { return length; }
	size_t getHeight() const { return heigth; }
	

	T getVal(size_t x, size_t y) const {
		if (x >= heigth || y >= length || x < 0 || y < 0) {
			return NULL;
		}
		return matrx[x*length + y];
	}
	void setVal(size_t x, size_t y, T value);

	int geterrCode() { return errCode; }
private:
	size_t length;
	size_t heigth;
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
Matrix<T>::Matrix(size_t nheigth, size_t nlength)
{
	length = nlength;
	heigth = nheigth;
	matrx.resize(length*heigth);
}

template<typename T>
Matrix<T>::Matrix(size_t nheigth, size_t nlength,std::vector<T>& newMatrx)
{
	length = nlength;
	heigth = nheigth;
	matrx.assign(newMatrx.begin(), newMatrx.end());
}

template<typename T>
void Matrix<T>::setMatrix(size_t nheigth, size_t nlength,std::vector<T> &newMatrx)
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
void Matrix<T>::resize(size_t nheigth, size_t nlength )
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
void Matrix<T>::setVal(size_t x, size_t y, T value)
{
	errCode = 0;
	if (x >= heigth || y >= length || x < 0 || y < 0) {
		errCode = err_wrong_index;
		return;
	}
	matrx[x*length + y] = value;
}

