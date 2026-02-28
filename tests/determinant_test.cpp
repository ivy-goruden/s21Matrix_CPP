#include "test.h"

START_TEST(test1) {
  S21Matrix a;
  try {
    a.Determinant();
    ck_assert_double_eq(1, 0);
  } catch (const std::invalid_argument) {
    ck_assert_double_eq(1, 1);
  }
}
START_TEST(test2) {
  S21Matrix a(1, 1);
  double newmatrix[1][1] = {{8}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  double det = a.Determinant();
  ck_assert_double_eq(det, 8);
}
START_TEST(test3) {
  S21Matrix a(2, 2);
  double newmatrix[2][2] = {{8, 5}, {4, 5}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  double det = a.Determinant();
  ck_assert_double_eq(det, 20);
}

Suite *determinant_suite(void) {
  Suite *s = suite_create("determinant_suite");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test1);
  tcase_add_test(tc_core, test2);
  tcase_add_test(tc_core, test3);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_determinant() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = determinant_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
