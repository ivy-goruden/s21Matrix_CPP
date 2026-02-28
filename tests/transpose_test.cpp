#include "test.h"
#include <cstdio>

START_TEST(test1) {
  S21Matrix a;
  S21Matrix b = a.Transpose();
  int res = a.EqMatrix(b);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test2) {
  S21Matrix a;
  double newmatrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  S21Matrix b = a.Transpose();
  double resmatrix[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
  double **res_matrix = b.set_to_matrix(resmatrix);
  S21Matrix c;
  c.setMatrix(res_matrix);
  int res = b.EqMatrix(c);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test3) {
  S21Matrix a(2, 3);
  double newmatrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  S21Matrix b = a.Transpose();
  double resmatrix[3][2] = {{1, 4}, {2, 5}, {3, 6}};
  double **res_matrix = b.set_to_matrix(resmatrix);
  S21Matrix c(3, 2);
  c.setMatrix(res_matrix);
  int res = b.EqMatrix(c);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *transpose_suite(void) {
  Suite *s = suite_create("transpose_suite");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test1);
  tcase_add_test(tc_core, test2);
  tcase_add_test(tc_core, test3);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_transpose() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = transpose_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
