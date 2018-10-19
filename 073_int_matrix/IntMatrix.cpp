#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(*rhs.rows[i]);
  }
}

IntMatrix::~IntMatrix() {
  if (rows != NULL) {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(*rhs.rows[i]);
    }
    if (rows != NULL) {
      for (int i = 0; i < numRows; i++) {
        delete rows[i];
      }
      delete[] rows;
    }
    rows = temp;
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
  assert(index < numRows && index >= 0);
  return *(rows[index]);
}
IntArray & IntMatrix::operator[](int index) {
  assert(index < numRows && index >= 0);
  return *(rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.getRows()) {
    return false;
  }
  if (numColumns != rhs.getColumns()) {
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
  assert(numRows == rhs.getRows() && numColumns == rhs.getColumns());
  IntMatrix addition(*this);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      addition[i][j] = addition[i][j] + rhs[i][j];
    }
  }
  return addition;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  if (rhs.getColumns() != 0) {
    for (int i = 0; i < rhs.getRows(); i++) {
      s << rhs[i];
      if (i != rhs.getRows() - 1) {
        s << ",\n";
      }
    }
  }
  s << " ]";
  return s;
}
