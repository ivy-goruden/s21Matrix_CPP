#ifndef HEADER_MATRIX
#define HEADER_MATRIX

#include <math.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>
#include <stdexcept>

class S21Matrix {
private:
  int rows;
  int cols;
  double **matrix;

public:
  S21Matrix(int newrows = 3,
            int newcols = 3); // создает матрицу rows на cols(меняет размер уже
                              // созданной)
  void change_matrix_size(int newrows, int newcols); // изменяет размер матрицы
  ~S21Matrix(); // освобождает память, выделенную под матрицу
  void print(); // выводит содержимое матрицы в консоль
  S21Matrix(const S21Matrix &other);  // copy
  S21Matrix(S21Matrix &&other);       // move
  int getRows();                      // get rows
  int getCols();                      // get cols
  double **getMatrix();               // get matrix
  void setRows(int newrows);          // set rows
  void setCols(int newcols);          // set cols
  void setMatrix(double **newmatrix); // set matrix
  bool EqMatrix(const S21Matrix &other);
  bool operator==(const S21Matrix &other); // lvalue
  void operator=(const S21Matrix &other);  // lvalue
  template <size_t R, size_t C>
  double **set_to_matrix(const double (&arr)[R][C]);
  void SumMatrix(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other); // lvalue
  void SubMatrix(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other); // lvalue
  void MulNumber(const double num);
  S21Matrix operator*(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(const double num);
  double operator()(int i, int j);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double get_matrix_minor(int row, int column);
  double Determinant();
  S21Matrix InverseMatrix();
};

template <size_t R, size_t C>
double **S21Matrix::set_to_matrix(const double (&arr)[R][C]) {
  double **new_matrix = static_cast<double **>(malloc(R * sizeof(double *)));
  if (!new_matrix) {
    throw std::bad_alloc();
  }

  for (size_t i = 0; i < R; ++i) {
    new_matrix[i] = static_cast<double *>(malloc(C * sizeof(double)));
    if (!new_matrix[i]) {
      for (size_t x = 0; x < i; ++x) {
        free(new_matrix[x]);
      }
      free(new_matrix);
      throw std::bad_alloc();
    }
    for (size_t j = 0; j < C; ++j) {
      new_matrix[i][j] = arr[i][j];
    }
  }
  return new_matrix;
}
#endif
