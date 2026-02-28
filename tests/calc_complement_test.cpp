#include "test.h"

START_TEST(test1) {
  S21Matrix a;
  S21Matrix b = a.CalcComplements();
  double resmatrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  double **res_matrix = a.set_to_matrix(resmatrix);
  S21Matrix c;
  c.setMatrix(res_matrix);
  int res = b.EqMatrix(c);
  ck_assert_int_eq(res, 1);
}
START_TEST(test2) {
  S21Matrix a, b;
  double newmatrix[3][3] = {{1, 2, 3}, {0, 4, 5}, {1, 0, 6}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  b = a.CalcComplements();
  double resmatrix[3][3] = {{24, 5, -4}, {-12, 3, 2}, {-2, -5, 4}};
  double **res_matrix = a.set_to_matrix(resmatrix);
  S21Matrix d;
  d.setMatrix(res_matrix);
  int res = b.EqMatrix(d);
  ck_assert_int_eq(res, 1);
}

START_TEST(test3) {
  S21Matrix a(2, 3);
  double newmatrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  try {
    a.CalcComplements();
    ck_assert_int_eq(0, 1);
  } catch (const std::invalid_argument) {
    ck_assert_int_eq(1, 1);
  }
}

Suite *calc_complements_suite(void) {
  Suite *s = suite_create("calc_complements_suite");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test1);
  tcase_add_test(tc_core, test2);
  tcase_add_test(tc_core, test3);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_calc_complements() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = calc_complements_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
