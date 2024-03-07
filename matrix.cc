#include "matrix.h"

Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}
Matrix::Matrix(int rows, int columns) {
  this->CreateMatrix(rows, columns);
}
Matrix::Matrix(const Matrix& other) { this->Copy(other); }
Matrix::Matrix(Matrix&& other) {
  this->Copy(other);
  other.RemoveMatrix();
}
Matrix::~Matrix() {
  if (this->matrix_ != nullptr) {
    this->RemoveMatrix();
  }
}
void Matrix::CreateMatrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}
void Matrix::RemoveMatrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  if (rows_ > 0) delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}
void Matrix::GetMatrix(int row, int col, const Matrix& tmp) {
  int m_row = 0;
  int m_col = 0;
  for (int i = 0; i < this->rows_; i++) {
    if (i == row) {
      continue;
    }
    m_col = 0;
    for (int j = 0; j < this->cols_; j++) {
      if (j == col) {
        continue;
      }
      tmp.matrix_[m_row][m_col] = this->matrix_[i][j];
      m_col++;
    }
    m_row++;
  }
}
Matrix Matrix::DelElement(int col, int row) const {
  Matrix result(this->rows_ - 1, this->cols_ - 1);
  int result_i = 0;
  int result_j = 0;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (j != col && i != row) {
        result.matrix_[result_i][result_j] = this->matrix_[i][j];
        result_j++;
      }
    }
    if (i != row) {
      result_i++;
    }
    result_j = 0;
  }

  return result;
}

void Matrix::Copy(const Matrix& other) {
  this->CreateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
bool Matrix::EqMatrix(const Matrix& other) {
  bool res = true;
  if (other.cols_ != this->cols_ || other.rows_ != this->rows_) {
    return false;
    throw std::length_error("Matrix incorect cols or rows");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::abs(other.matrix_[i][j] - this->matrix_[i][j] > 1e-7)) {
        return false;
      }
    }
  }

  return res;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (other.cols_ != this->cols_ || other.rows_ != this->rows_) {
    throw std::length_error("Matrix incorect cols or rows");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  if (other.cols_ != this->cols_ || other.rows_ != this->rows_) {
    throw std::length_error("Matrix incorect cols or rows");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] = this->matrix_[i][j] * num;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.getRows()) {
    throw std::length_error("Matrix incorect cols or rows");
  }

  Matrix result{this->rows_, other.cols_};

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.rows_; j++) {
      for (int k = 0; k < other.cols_; k++) {
        result.matrix_[i][j] =
            result.matrix_[i][j] + this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

Matrix Matrix::Transpose() {
  Matrix transp(cols_, rows_);
  for (int i = 0; i < transp.rows_; i++) {
    for (int j = 0; j < transp.cols_; j++) {
      transp.matrix_[i][j] = matrix_[j][i];
    }
  }
  return transp;
}
double Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::length_error("Matrix incorect cols or rows");
  }

  double result = 0;
  double pow = -1.0;

  if (rows_ == 1)
    result = matrix_[0][0];
  else if (rows_ == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else {
    for (int j = 0; j < cols_; j++) {
      pow *= -1.0;
      result +=
          pow * this->matrix_[0][j] * this->DelElement(j, 0).Determinant();
    }
  }

  return result;
}

Matrix Matrix::CalcComplements() {
  if (this->rows_ != this->cols_) {
    throw std::length_error("Matrix incorect cols or rows");
  }
  Matrix result(this->rows_, this->cols_);
  Matrix minor(this->rows_ - 1, this->cols_ - 1);
  double determinant = 0.0;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->GetMatrix(i, j, minor);
      determinant = minor.Determinant();
      result.matrix_[i][j] = pow(-1, i + j) * determinant;
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  double det = this->Determinant();

  if (det == 0) {
    throw std::length_error("Matrix incorect cols or rows");
  }

  Matrix result = this->CalcComplements().Transpose();

  result.MulNumber(1.0 / det);

  return result;
}

double& Matrix::operator()(int i, int j) {
  if (i > this->rows_ || j > this->cols_ || i < 0 || j < 0) {
    throw std::length_error("Matrix incorect cols or rows");
  }
  return this->matrix_[i][j];
}

Matrix Matrix::operator+(const Matrix& other) {
  this->SumMatrix(other);
  Matrix temp = *this;
  return temp;
}

Matrix& Matrix::operator=(const Matrix& other) {
  this->RemoveMatrix();
  this->Copy(other);
  return *this;
}
bool Matrix::operator==(const Matrix& other) {
  bool temp = this->EqMatrix(other);
  return temp;
}

Matrix Matrix::operator-(const Matrix& other) {
  this->SubMatrix(other);
  Matrix temp = *this;
  return temp;
}

Matrix Matrix::operator*(const Matrix& other) {
  this->MulMatrix(other);
  Matrix temp = *this;
  return temp;
}

Matrix Matrix::operator*(double number) {
  Matrix temp{*this};
  temp.MulNumber(number);
  return temp;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  this->MulMatrix(other);
  Matrix temp = *this;
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  this->SumMatrix(other);
  Matrix temp = *this;
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  this->SubMatrix(other);
  Matrix temp = *this;
  return *this;
}

Matrix& Matrix::operator*=(double number) {
  this->MulNumber(number);
  Matrix temp = *this;
  return *this;
}
