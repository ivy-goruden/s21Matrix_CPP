#include "test.h"

START_TEST(test1) {
  S21Matrix a;
  ck_assert_ptr_nonnull(&a);
  ck_assert_int_eq(a.getCols(), 3);
  ck_assert_int_eq(a.getRows(), 3);
}
END_TEST

START_TEST(test2) {
  S21Matrix a(4, 4);
  ck_assert_ptr_nonnull(&a);
  ck_assert_int_eq(a.getCols(), 4);
  ck_assert_int_eq(a.getRows(), 4);
}

START_TEST(test3) {
  S21Matrix a;
  double newmatrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double **new_matrix = a.set_to_matrix(newmatrix);
  a.setMatrix(new_matrix);
  a.setRows(4);
  a.setCols(4);
  S21Matrix b(4, 4);
  double resmatrix[4][4] = {
      {1, 2, 3, 0}, {4, 5, 6, 0}, {7, 8, 9, 0}, {0, 0, 0, 0}};
  double **res_matrix = b.set_to_matrix(resmatrix);
  b.setMatrix(res_matrix);
  bool res = a.EqMatrix(b);
  ck_assert_int_eq(res, true);
  ck_assert_ptr_nonnull(&a);
  ck_assert_int_eq(a.getCols(), 4);
  ck_assert_int_eq(a.getRows(), 4);
}

Suite *create_suite(void) {
  Suite *s = suite_create("create_suite");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test1);
  tcase_add_test(tc_core, test2);
  tcase_add_test(tc_core, test3);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_create() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = create_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
