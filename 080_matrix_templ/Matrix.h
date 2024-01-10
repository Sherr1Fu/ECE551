#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(0){};
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(r, std::vector<T>(c)){};
  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows){};
  //~Matrix();
  Matrix & operator=(const Matrix & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;
};

/*template<typename T>
Matrix<T>::~Matrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
  }*/
template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  if (this != &rhs) {
    /*for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    rows = new Matrix<T> *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      rows[i] = new Matrix<T>(*rhs.rows[i]);
      }*/
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
  }
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}
template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}
template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(index >= 0);
  assert(index < numRows);
  //std::cout << "abc";
  //const std::vector<T> & ref = *rows[index];
  //std::cout << "after[]";
  return rows[index];
}
template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index >= 0);
  assert(index < numRows);
  //std::cout << "abc";
  //std::vector<T> & ref = *rows[index];
  //std::cout << "after[]";
  return rows[index];
}
template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (numRows != rhs.numRows) {
    return false;
  }
  if (numColumns != rhs.numColumns) {
    return false;
  }
  if (rows != rhs.rows) {
    return false;
  }
  return true;
}
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  Matrix<T> ans(getRows(), getColumns());
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      //(*rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
      ans[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return ans;
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  std::string rowdelim;
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rowdelim << "{";
    rowdelim = ",\n";
    std::string coldelim;
    for (int j = 0; j < rhs.getColumns(); j++) {
      s << coldelim << rhs[i][j];
      coldelim = ", ";
    }
    s << "}";
  }
  s << " ]";
  return s;
}
#endif
