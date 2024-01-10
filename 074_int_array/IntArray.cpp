#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  data = NULL;
  numElements = 0;
}
IntArray::IntArray(int n) {
  data = new int[n];
  numElements = n;
}

IntArray::IntArray(const IntArray & rhs) {
  numElements = rhs.numElements;
  data = new int[rhs.numElements];
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    delete[] data;
    data = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      data[i] = rhs.data[i];
    }
    numElements = rhs.numElements;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index >= 0);
  assert(index < numElements);
  const int & ref = data[index];
  return ref;
}
int & IntArray::operator[](int index) {
  assert(index >= 0);
  assert(index < numElements);
  int & ref = data[index];
  return ref;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() == 0) {
    s << "{}";
    return s;
  }
  if (rhs.size() == 1) {
    s << "{" << rhs[0] << "}";
    return s;
  }
  s << "{";
  int i;
  for (i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[i] << "}";

  return s;
}
