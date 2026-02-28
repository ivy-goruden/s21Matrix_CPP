
#include "s21_matrix.h"

#include <cstddef>
#include <stdexcept>
// создает матрицу rows на cols(либо 3 на 3)
S21Matrix::S21Matrix(int newrows, int newcols) {
  rows = newrows;
  cols = newcols;
  matrix = (double **)malloc(rows * sizeof(double *));
  if (!matrix) {
    free(matrix);
    throw std::bad_alloc();
  }
  for (int i = 0; i < rows; i++) {
    matrix[i] = (double *)malloc(cols * sizeof(double));
    if (!matrix[i]) {
      for (int x = 0; x <= 1; x++) {
        free(matrix[x]);
      }
      throw std::bad_alloc();
    }
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = 0;
    }
  }
}
void S21Matrix::change_matrix_size(int newrows, int newcols) {
  if (newrows < rows) {
    for (int i = newrows; i < rows; i++) {
      free(matrix[i]);
    }
  }
  matrix = (double **)realloc(matrix, newrows * sizeof(double *));
  if (!matrix) {
    free(matrix);
    throw std::bad_alloc();
  }
  rows = newrows;
  cols = newcols;
  for (int i = 0; i < rows; i++) {
    matrix[i] = (double *)realloc(matrix[i], cols * sizeof(double));
    for (int x = 0; x < cols; x++) {
      if (!matrix[i][x]) {
        matrix[i][x] = 0;
      }
    }
  }
}
// освобождает память, выделенную под матрицу
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void S21Matrix::print() {
  for (int i = 0; i < rows; i++) {
    printf("[");
    for (int x = 0; x < cols; x++) {
      printf("%f, ", matrix[i][x]);
    }
    printf("]\n");
  }
}
// copy
S21Matrix::S21Matrix(const S21Matrix &other) {
  change_matrix_size(other.rows, other.cols);
  for (int i = 0; i < other.rows; i++) {
    for (int x = 0; x < other.cols; x++) {
      matrix[i][x] = other.matrix[i][x];
    }
  }
}
// move
S21Matrix::S21Matrix(S21Matrix &&other) {
  change_matrix_size(other.rows, other.cols);
  for (int i = 0; i < other.rows; i++) {
    memmove(matrix[i], other.matrix[i], sizeof(double *) * other.cols);
  }

  // чистим rvalue
  other.matrix = nullptr;
  other.rows = 0;
  other.cols = 0;
}

int S21Matrix::getRows() { return rows; }
// get cols
int S21Matrix::getCols() { return cols; }
double **S21Matrix::getMatrix() { return matrix; }

void S21Matrix::setRows(int newrows) { change_matrix_size(newrows, cols); }
// get cols
void S21Matrix::setCols(int newcols) { change_matrix_size(rows, newcols); }
void S21Matrix::setMatrix(double **newmatrix) {
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      matrix[i][x] = newmatrix[i][x];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows != other.rows || cols != other.cols) {
    return false;
  }
  double tolerance = 1e-7;
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      if (matrix[i][x] - other.matrix[i][x] > tolerance) {
        return false;
      }
    }
  }
  return true;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }
void S21Matrix::operator+=(const S21Matrix &other) { return SumMatrix(other); }
void S21Matrix::operator-=(const S21Matrix &other) { return SubMatrix(other); }
void S21Matrix::operator*=(const S21Matrix &other) { return MulMatrix(other); }
void S21Matrix::operator*=(const double num) { return MulNumber(num); }
double S21Matrix::operator()(int i, int j) {
  if (i >= rows || j >= cols) {
    throw std::out_of_range("Out of range");
  }
  return matrix[i][j];
}

void S21Matrix::operator=(const S21Matrix &other) {
  change_matrix_size(other.rows, other.cols);
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      matrix[i][x] = other.matrix[i][x];
    }
  }
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Matrixes must be of one size");
  }
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      matrix[i][x] = matrix[i][x] + other.matrix[i][x];
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Matrices must be of one size");
  }
  S21Matrix result(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      result.matrix[i][x] = matrix[i][x] + other.matrix[i][x];
    }
  }
  return result;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Matrixes must be of one size");
  }
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      matrix[i][x] = matrix[i][x] - other.matrix[i][x];
    }
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Matrixes must be of one size");
  }
  S21Matrix result(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      result.matrix[i][x] = matrix[i][x] - other.matrix[i][x];
    }
  }
  return result;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      matrix[i][x] = matrix[i][x] * num;
    }
  }
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      result.matrix[i][x] = matrix[i][x] * num;
    }
  }
  return result;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols != other.rows) {
    throw std::invalid_argument(
        "Matrix A columns must be equal to matrix B rows");
  }
  double **res_matrix = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++) {
    res_matrix[i] = (double *)malloc(other.cols * sizeof(double));
  }
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < other.cols; x++) {
      double res = 0;
      for (int j = 0; j < cols; j++) {
        res += matrix[i][j] * other.matrix[j][x];
      }
      res_matrix[i][x] = res;
    }
  }
  cols = other.cols;
  setMatrix(res_matrix);
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  if (cols != other.rows) {
    throw std::invalid_argument(
        "Matrix A columns must be equal to matrix B rows");
  }
  S21Matrix res(rows, other.cols);
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < other.cols; x++) {
      double resn = 0;
      for (int j = 0; j < cols; j++) {
        resn += matrix[i][j] * other.matrix[j][x];
      }
      res.matrix[i][x] = resn;
    }
  }
  return res;
}
S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols, rows);
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      res.matrix[x][i] = (matrix[i][x]);
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (rows != cols) {
    throw std::invalid_argument("The matrix must be rectangular");
  }
  if (rows == 1) {
    return matrix[0][0];
  }
  if (rows == 2) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  }

  S21Matrix b(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < cols; x++) {
      b.matrix[i][x] = matrix[i][x];
    }
  }
  double **mat = b.matrix;
  double det = 1;
  // columns
  for (int i = 0; i < rows - 1; i++) {
    int max_row = i;
    // rows
    for (int x = i + 1; x < rows; x++) {
      if (fabs(mat[x][i]) > fabs(mat[max_row][i])) {
        max_row = x;
      }
    }
    if (fabs(mat[max_row][i]) < 0.00001) {
      throw std::invalid_argument("No determinant for this matrix");
    }
    // change rows
    if (max_row != i) {
      det *= -1;
      double *prev_mat = mat[i];
      double *now_mat = mat[max_row];
      mat[i] = now_mat;
      mat[max_row] = prev_mat;
    }
    for (int j = i + 1; j < rows; j++) {
      double factor = mat[j][i] / mat[i][i];
      for (int k = 0; k < rows; k++) {
        mat[j][k] -= mat[i][k] * factor;
      }
    }
  }
  for (int i = 0; i < rows; i++) {
    det *= mat[i][i];
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols != rows) {
    throw std::invalid_argument("The matrix must be rectangular");
  }
  S21Matrix result(rows, cols);
  if (rows == 1) {
    result.matrix[0][0] = 1;
  }
  for (int i = 0; i < rows; i++) {
    for (int x = 0; x < rows; x++) {
      result.matrix[i][x] = get_matrix_minor(i, x) * (pow(-1, (i + x)));
    }
  }
  return result;
}

double S21Matrix::get_matrix_minor(int row, int column) {
  if (row >= rows || column >= cols) {
    throw std::invalid_argument("Coordinate must be beyound matrix bounds");
  }
  if (cols == 1 && rows == 1) {
    return 1.0;
  }
  S21Matrix mat(rows - 1, cols - 1);
  int indexA = -1;
  for (int i = 0; i < rows; i++) {
    if (i == row) {
      continue;
    }
    indexA++;
    int indexB = -1;
    for (int x = 0; x < rows; x++) {
      if (x == column) {
        continue;
      }
      indexB++;
      mat.matrix[indexA][indexB] = matrix[i][x];
    }
  }
  double minor = mat.Determinant();
  return minor;
}

S21Matrix S21Matrix::InverseMatrix() {
  double res;
  res = Determinant();
  if ((int)res == 0) {
    throw std::invalid_argument("Determinan't mustn't be 0");
  }
  res = 1 / res;
  S21Matrix b = CalcComplements();
  S21Matrix c = b.Transpose();
  S21Matrix result = c * res;
  return result;
}