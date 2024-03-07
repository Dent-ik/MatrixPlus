#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <cmath>
#include <iostream>

class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void RemoveMatrix();
  void Copy(const Matrix& other);
  void CreateMatrix(int rows, int columns);

  void GetMatrix(int row, int col, const Matrix& tmp);
  Matrix DelElement(const int col, const int row) const;

 public:
  Matrix();
  Matrix(int rows, int columns);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  int getRows() const noexcept { return rows_; }
  int getCols() const noexcept { return cols_; }
  double** getMatrix() { return matrix_; };

  bool EqMatrix(const Matrix& other);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix Transpose();
  double Determinant();
  Matrix CalcComplements();
  Matrix InverseMatrix();

  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(double number);
  Matrix operator*(const Matrix& other);
  bool operator==(const Matrix& other);
  Matrix& operator=(const Matrix& other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  double& operator()(int i, int j);
  Matrix& operator*=(double number);
};

#endif  // SRC_MATRIX_H_