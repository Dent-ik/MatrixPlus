#include <gtest/gtest.h>

#include "../matrix.h"

TEST(test, DefaultConstructor1) {
  Matrix mat;
  ASSERT_EQ(mat.getRows(), 0);
  ASSERT_EQ(mat.getCols(), 0);
  ASSERT_EQ(mat.getMatrix(), nullptr);
}

TEST(MatrixTest, ParamConstructor1) {
  ASSERT_NO_THROW(Matrix matrix(5, 5));
}

TEST(MatrixTest, CopyConstructor) {
  Matrix a(5, 5);
  Matrix b(a);
  ASSERT_EQ(a.getRows(), b.getRows());
  ASSERT_EQ(a.getCols(), b.getCols());
  ASSERT_NO_THROW(Matrix b(a));
}

TEST(MatrixTest, CopyConstructor1) {
  Matrix A(3, 4);
  Matrix B(A);
  EXPECT_EQ(3, B.getRows());
  EXPECT_EQ(4, B.getCols());
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, constructor_move) {
  Matrix A(5, 5);
  Matrix B(std::move(A));
  EXPECT_EQ(5, B.getRows());
  EXPECT_EQ(5, B.getCols());
  EXPECT_EQ(0, A.getRows());
  EXPECT_EQ(0, A.getCols());
}

TEST(MatrixTest, EqMatrix1) {
  Matrix a;
  Matrix b;

  bool result1 = a.EqMatrix(b);
  bool result2 = b.EqMatrix(a);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(result2 = result1);
}

TEST(MatrixTest, EqMatrix2) {
  Matrix a(2, 1);
  Matrix b(1, 1);

  bool result1 = a.EqMatrix(b);
  bool result2 = b.EqMatrix(a);
  EXPECT_FALSE(result1);
  EXPECT_FALSE(result2);
  EXPECT_FALSE(result2 = result1);
}
TEST(MatrixTest, EqMatrix3) {
  Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;

  Matrix matrix(3, 3);
  matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
  matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
  matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;

  EXPECT_FALSE(A.EqMatrix(matrix));
}
TEST(MatrixTest, EqMatrix4) {
  Matrix A(3, 3);
  A(0, 0) = 5555555555, 5, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;

  Matrix matrix(3, 3);
  matrix(0, 0) = 5555555555, 4, matrix(0, 1) = 8, matrix(0, 2) = 3;
  matrix(1, 0) = 5, matrix(1, 1) = 9, matrix(1, 2) = 1;
  matrix(2, 0) = 9, matrix(2, 1) = 4, matrix(2, 2) = 2;

  EXPECT_TRUE(A.EqMatrix(matrix));
}

TEST(MatrixTest, SumMatrix1) {
  Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  Matrix matrix(3, 3);
  matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
  matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
  matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;
  A.SumMatrix(A);
  ASSERT_EQ(true, A.EqMatrix(matrix));
}

TEST(MatrixTest, SumMatrix2) {
  Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  Matrix matrix(3, 4);
  matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
  matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
  matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;

  ASSERT_ANY_THROW(A.SumMatrix(matrix););
}

TEST(Matrix, SumMatrixTest3) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  expected(0, 0) = 6;
  expected(0, 1) = 8;
  expected(1, 0) = 10;
  expected(1, 1) = 12;

  a.SumMatrix(b);
  EXPECT_TRUE(a == expected);
}

TEST(MatrixTest, SumMatrixTest4) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  expected(0, 0) = 6;
  expected(0, 1) = 8;
  expected(1, 0) = 10;
  expected(1, 1) = 12;

  a += b;
  EXPECT_TRUE(a == expected);
}

TEST(MatrixTest, SubMatrix1) {
  Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  Matrix matrix(3, 3);
  matrix(0, 0) = 0, matrix(0, 1) = 0, matrix(0, 2) = 0;
  matrix(1, 0) = 0, matrix(1, 1) = 0, matrix(1, 2) = 0;
  matrix(2, 0) = 0, matrix(2, 1) = 0, matrix(2, 2) = 0;
  A.SubMatrix(A);
  ASSERT_EQ(true, A.EqMatrix(matrix));
}

TEST(MatrixTest, MulMatrix1) {
  Matrix A(3, 3);
  Matrix B(1, 1);

  EXPECT_THROW(A.MulMatrix(B), std::length_error);
}

TEST(MatrixTest, SubMatrix2) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  Matrix expected(2, 2);

  a(0, 0) = 4;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 6;

  b(0, 0) = 2;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 3;

  expected(0, 0) = 2;
  expected(0, 1) = 2;
  expected(1, 0) = 3;
  expected(1, 1) = 3;

  a.SubMatrix(b);
  EXPECT_TRUE(a == expected);
}

TEST(MatrixTest, MulNumber1) {
  const double num = 2;
  Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  Matrix matrix(3, 3);
  matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
  matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
  matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;
  A.MulNumber(num);
  EXPECT_TRUE(A == matrix);
}

TEST(Matrix, MulNumber2) {
  const double num = 5;
  Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  Matrix matrix(3, 3);
  matrix(0, 0) = 35, matrix(0, 1) = 40, matrix(0, 2) = 15;
  matrix(1, 0) = 25, matrix(1, 1) = 45, matrix(1, 2) = 5;
  matrix(2, 0) = 45, matrix(2, 1) = 20, matrix(2, 2) = 10;
  A.MulNumber(num);
  EXPECT_TRUE(A == matrix);
}

TEST(MatrixTest, MulNumber3) {
  Matrix a(2, 2);
  Matrix expected(2, 2);
  const double num = 3;
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  expected(0, 0) = 3;
  expected(0, 1) = 6;
  expected(1, 0) = 9;
  expected(1, 1) = 12;

  a.MulNumber(num);
  EXPECT_TRUE(a == expected);
}

TEST(MatrixTest, MulMatrix2) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  expected(0, 0) = 19;
  expected(0, 1) = 22;
  expected(1, 0) = 43;
  expected(1, 1) = 50;

  a.MulMatrix(b);

  EXPECT_TRUE(a == expected);
}

TEST(MatrixTest, Determinant1) {
  Matrix test_matrix(2, 3);
  Matrix matrix_before = test_matrix;

  EXPECT_ANY_THROW(test_matrix.Determinant());
  EXPECT_TRUE(test_matrix == matrix_before);
}
TEST(MatrixTest, Determinant2) {
  Matrix A(1, 2);
  EXPECT_THROW(A.Determinant(), std::length_error);
}

TEST(MatrixTest, Determinant3) {
  Matrix A(3, 3);
  A(0, 0) = 0, A(0, 1) = 1, A(0, 2) = 2;
  A(1, 0) = 3, A(1, 1) = 4, A(1, 2) = 5;
  A(2, 0) = 6, A(2, 1) = 0, A(2, 2) = 7;

  double res = A.Determinant();
  EXPECT_TRUE(-39.0 == res);
}

TEST(MatrixTest, Determinant4) {
  Matrix A(3, 3);
  A(0, 0) = 6, A(0, 1) = 0, A(0, 2) = 7;
  A(1, 0) = 3, A(1, 1) = 4, A(1, 2) = 5;
  A(2, 0) = 0, A(2, 1) = 1, A(2, 2) = 2;

  double res = A.Determinant();
  EXPECT_TRUE(39.0 == res);
}

TEST(MatrixTest, Determinant5) {
  Matrix A(1, 1);

  double res = A.Determinant();
  EXPECT_TRUE(0.0 == res);
}

TEST(MatrixTest, Determinant6) {
  Matrix A(1, 2);
  EXPECT_THROW(A.Determinant(), std::length_error);
}

TEST(MatrixTest, CalcComplements1) {
  Matrix A(3, 2);
  EXPECT_THROW(A.CalcComplements(), std::length_error);
}

TEST(MatrixTest, CalcComplements2) {
  Matrix A(2, 3);
  Matrix B(3, 3);

  EXPECT_THROW(A.SubMatrix(B), std::length_error);
}

TEST(MatrixTest, CalcComplements3) {
  Matrix m1(3, 3);
  Matrix m2(3, 3);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 0;
  m1(1, 1) = 4;
  m1(1, 2) = 2;
  m1(2, 0) = 5;
  m1(2, 1) = 2;
  m1(2, 2) = 1;

  m2(0, 0) = 0;
  m2(0, 1) = 10;
  m2(0, 2) = -20;
  m2(1, 0) = 4;
  m2(1, 1) = -14;
  m2(1, 2) = 8;
  m2(2, 0) = -8;
  m2(2, 1) = -2;
  m2(2, 2) = 4;

  bool res = m1.CalcComplements() == m2;

  EXPECT_EQ(res, true);
}

TEST(MatrixTest, OperatorSum) {
  Matrix A(3, 4);
  Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;
  A = B + B;
  EXPECT_EQ(1, A == B);
};

TEST(MatrixTest, OperatorSub) {
  Matrix A(3, 4);
  Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;
  A = B - B;
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, OperatorMUl) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 1;

  B(1, 0) = 1;
  B(1, 1) = 1;
  A = B * B;
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, OperatorMulNumber) {
  Matrix A(2, 2);
  Matrix res(2, 2);
  double num = 5;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 25;
  res(1, 1) = 30;

  A = A * num;
  EXPECT_TRUE(A == res);
}

TEST(MatrixTest, OperatorMulNumberEq) {
  Matrix A(2, 2);
  Matrix res(2, 2);
  double num = 5;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 25;
  res(1, 1) = 30;

  A *= num;
  EXPECT_TRUE(A == res);
}

TEST(MatrixTest, operator_error) {
  Matrix B(2, 2);
  EXPECT_THROW((B(0, 5) = 2), std::length_error);
}

TEST(MatrixTest, operator_error1) {
  Matrix B(3, 3);
  EXPECT_THROW((B(4, 1) = 1), std::length_error);
}

TEST(MatrixTest, OperatorSubReq1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix res(2, 2);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  res(0, 0) = 2;
  res(0, 1) = 4;
  res(1, 0) = 10;
  res(1, 1) = 12;

  A += B;
  EXPECT_TRUE(A == res);
}

TEST(MatrixTest, OperatorSub1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix res(2, 2);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  res(0, 0) = 0;
  res(0, 1) = 0;
  res(1, 0) = 0;
  res(1, 1) = 0;

  A -= B;
  EXPECT_TRUE(A == res);
}
TEST(MatrixTest, OperatorMul1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix res(2, 2);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  res(0, 0) = 1;
  res(0, 1) = 4;
  res(1, 0) = 25;
  res(1, 1) = 36;

  A *= B;
  EXPECT_TRUE(A == res);
}

TEST(MatrixTest, OperatorSumNumber1) {
  Matrix A(2, 2);
  Matrix res(2, 2);
  double num = 5;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 25;
  res(1, 1) = 30;

  A *= num;
  EXPECT_TRUE(A == res);
}

TEST(MatrixTest, InverseMatrix1) {
  Matrix A(1, 2);
  EXPECT_THROW(A.InverseMatrix(), std::length_error);
}

TEST(MatrixTest, InverseMatrix3) {
  Matrix A(1, 1);
  EXPECT_THROW(A.InverseMatrix(), std::length_error);
}

TEST(MatrixTest, Inverse2) {
  Matrix A(2, 2);
  Matrix res(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  res(0, 0) = -2;
  res(0, 1) = 1;
  res(1, 0) = 1.5;
  res(1, 1) = -0.5;

  EXPECT_TRUE(A.InverseMatrix() == res);
}

TEST(MatrixTest, Transpose1) {
  Matrix A(3, 2);
  Matrix B(2, 3);
  EXPECT_TRUE(A.Transpose() == B);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
