#include "test.h"

START_TEST(test1) {
  S21Matrix a;
  S21Matrix b;
  S21Matrix c = a + b;
  int res = c.EqMatrix(a);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test2) {
  S21Matrix a(4, 4);
  S21Matrix b;
  try {
    S21Matrix c = a + b;
    (void)c; // suppress unused warning
    ck_assert_int_eq(0, 1);
  } catch (const std::invalid_argument &) {
    ck_assert_int_eq(1, 1);
  }
}
END_TEST

START_TEST(test3) {
  S21Matrix a;
  double newmatrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  S21Matrix b;
  double newmatrix2[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  double **new_matrix2 = b.set_to_matrix(newmatrix2);
  b.setMatrix(new_matrix2);
  S21Matrix c = a + b;
  double resmatrix[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
  double **res_matrix = b.set_to_matrix(resmatrix);
  S21Matrix d;
  d.setMatrix(res_matrix);
  bool res = c.EqMatrix(d);
  ck_assert_int_eq(res, true);
}
END_TEST

START_TEST(test4) {
  S21Matrix a;
  S21Matrix b;
  a.SumMatrix(b);
  int res = a.EqMatrix(a);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test5) {
  S21Matrix a(4, 4);
  S21Matrix b;
  try {
    a.SumMatrix(b);
    ck_assert_int_eq(0, 1);
  } catch (const std::invalid_argument &) {
    ck_assert_int_eq(1, 1);
  }
}
END_TEST

START_TEST(test6) {
  S21Matrix a;
  double newmatrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  S21Matrix b;
  double newmatrix2[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  double **new_matrix2 = b.set_to_matrix(newmatrix2);
  b.setMatrix(new_matrix2);
  a.SumMatrix(b);
  double resmatrix[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
  double **res_matrix = b.set_to_matrix(resmatrix);
  S21Matrix c;
  c.setMatrix(res_matrix);
  bool res = a.EqMatrix(c);
  ck_assert_int_eq(res, true);
}
START_TEST(test7) {
  S21Matrix a;
  double newmatrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  S21Matrix b;
  double newmatrix2[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  double **new_matrix2 = b.set_to_matrix(newmatrix2);
  b.setMatrix(new_matrix2);
  a += b;
  double resmatrix[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
  double **res_matrix = b.set_to_matrix(resmatrix);
  S21Matrix c;
  c.setMatrix(res_matrix);
  bool res = a.EqMatrix(c);
  ck_assert_int_eq(res, true);
}
END_TEST

Suite *sum_suite(void) {
  Suite *s = suite_create("sum_suite");

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
int main_sum() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = sum_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
