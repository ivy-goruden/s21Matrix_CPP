#include "test.h"

START_TEST(test1) {
  S21Matrix a;
  try {
    a.InverseMatrix();
    ck_assert_int_eq(0, 1);
  } catch (const std::invalid_argument) {
    ck_assert_int_eq(1, 1);
  }
}
START_TEST(test2) {
  S21Matrix a;
  double newmatrix[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  S21Matrix b = a.InverseMatrix();
  double resmatrix[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  double **res_matrix = a.set_to_matrix(resmatrix);
  S21Matrix d;
  d.setMatrix(res_matrix);
  int res = b.EqMatrix(d);
  b.print();
  ck_assert_int_eq(res, 1);
}

Suite *inverse_suite(void) {
  Suite *s = suite_create("inverse_suite");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test1);
  tcase_add_test(tc_core, test2);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_inverse() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = inverse_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
