#include "IntMatrix.h"

IntMatrix::IntMatrix() {
  numRows = 0;
  numColumns = 0;
  rows = NULL;
}
IntMatrix::IntMatrix(int r, int c) {
  numRows = r;
  numColumns = c;
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(*rhs.rows[i]);
    //std::cout << rows[i]->size();
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    rows = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      rows[i] = new IntArray(*rhs.rows[i]);
    }
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0);
  assert(index < numRows);
  //std::cout << "abc";
  const IntArray & ref = *rows[index];
  //std::cout << "after[]";
  return ref;
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0);
  assert(index < numRows);
  //std::cout << "abc";
  IntArray & ref = *rows[index];
  //std::cout << "after[]";
  return ref;
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows) {
    return false;
  }
  if (numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if (*rows[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
      //rows[i][j] = rows[i][j] + rhs.rows[i][j];
    }
  }
  return *this;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  s << "[ ";
  int i;
  for (i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  s << rhs[i];
  s << " ]";
  return s;
}
