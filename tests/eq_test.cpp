#include "test.h"

START_TEST(test1) {
  S21Matrix a;
  S21Matrix b;
  int res = a.EqMatrix(b);
  ck_assert_int_eq(res, 1);
}
START_TEST(test2) {
  S21Matrix a;
  S21Matrix b;
  a.setRows(4);
  int res = a.EqMatrix(b);
  ck_assert_int_eq(res, 0);
}

Suite *eq_suite(void) {
  Suite *s = suite_create("eq_suite");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test1);
  tcase_add_test(tc_core, test2);
  suite_add_tcase(s, tc_core);
  return s;
}

// Запуск тестов
int main_eq() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = eq_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
