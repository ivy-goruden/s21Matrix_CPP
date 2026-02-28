#include "test.h"
#include <cstdio>

START_TEST(test1) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c = a * b;
  int res = a.EqMatrix(c);
  ck_assert_int_eq(res, 1);
}
START_TEST(test2) {
  S21Matrix a, b;
  double newmatrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  b.setMatrix(new_matrix);
  S21Matrix c = a * b;
  double resmatrix[3][3] = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
  double **res_matrix = a.set_to_matrix(resmatrix);
  S21Matrix d;
  d.setMatrix(res_matrix);
  int res = c.EqMatrix(d);
  ck_assert_int_eq(res, 1);
}

START_TEST(test3) {
  S21Matrix a(2, 3);
  double newmatrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  S21Matrix b = a.Transpose();
  S21Matrix c = b * a;
  double resmatrix[3][3] = {{17, 22, 27}, {22, 29, 36}, {27, 36, 45}};
  double **res_matrix = a.set_to_matrix(resmatrix);
  S21Matrix d;
  d.setMatrix(res_matrix);
  int res = c.EqMatrix(d);
  ck_assert_int_eq(res, 1);
}

START_TEST(test4) {
  S21Matrix a;
  S21Matrix b;
  a.MulMatrix(b);
  int res = a.EqMatrix(b);
  ck_assert_int_eq(res, 1);
}
START_TEST(test5) {
  S21Matrix a, b;
  double newmatrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  b.setMatrix(new_matrix);
  a.MulMatrix(b);
  double resmatrix[3][3] = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
  double **res_matrix = a.set_to_matrix(resmatrix);
  S21Matrix d;
  d.setMatrix(res_matrix);
  int res = a.EqMatrix(d);
  ck_assert_int_eq(res, 1);
}

START_TEST(test6) {
  S21Matrix a(2, 3);
  double newmatrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  S21Matrix b = a.Transpose();
  b.MulMatrix(a);
  double resmatrix[3][3] = {{17, 22, 27}, {22, 29, 36}, {27, 36, 45}};
  double **res_matrix = a.set_to_matrix(resmatrix);
  S21Matrix d;
  d.setMatrix(res_matrix);
  int res = b.EqMatrix(d);
  ck_assert_int_eq(res, 1);
}
START_TEST(test7) {
  S21Matrix a(2, 3);
  double newmatrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  S21Matrix b = a.Transpose();
  b *= a;
  double resmatrix[3][3] = {{17, 22, 27}, {22, 29, 36}, {27, 36, 45}};
  double **res_matrix = a.set_to_matrix(resmatrix);
  S21Matrix d;
  d.setMatrix(res_matrix);
  int res = b.EqMatrix(d);
  ck_assert_int_eq(res, 1);
}

Suite *mul_matrix_suite(void) {
  Suite *s = suite_create("mul_matrix_suite");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test1);
  tcase_add_test(tc_core, test2);
  tcase_add_test(tc_core, test3);
  tcase_add_test(tc_core, test4);
  tcase_add_test(tc_core, test5);
  tcase_add_test(tc_core, test6);
  tcase_add_test(tc_core, test7);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_mul_matrix() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = mul_matrix_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
