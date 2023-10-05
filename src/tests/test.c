#include "unit.h"

START_TEST(polish1) {
  double res1 = get_answer("2+2*2", 0);
  double res2 = 2 + 2 * 2;
  ck_assert_double_eq_tol(res1, res2, 10e-7);
}
END_TEST

START_TEST(polish2) {
  double res1 = get_answer("cos(3)", 0);
  double res2 = cos(3);
  ck_assert_double_eq_tol(res1, res2, 10e-7);
}
END_TEST

START_TEST(polish3) {
  double res1 = get_answer("sin(+x)*asin(1)*atan(2)*tan(1)", 0);
  double res2 = sin(+0) * asin(1) * atan(2) * tan(1);
  ck_assert_double_eq_tol(res1, res2, 10e-7);
}
END_TEST

START_TEST(polish4) {
  double res1 = get_answer("0+0", 0);
  double res2 = 0 + 0;
  ck_assert_double_eq_tol(res1, res2, 10e-7);
}
END_TEST

START_TEST(polish5) {
  double res1 = get_answer("+sqrt(4)^3-log(4)", 0);
  double res2 = +pow(sqrt(4), 3) - log10(4);
  ck_assert_double_eq_tol(res1, res2, 10e-7);
}
END_TEST

Suite *suite_polish() {
  Suite *s = suite_create("polish");
  TCase *temp = tcase_create("polish");

  suite_add_tcase(s, temp);

  tcase_add_test(temp, polish1);
  tcase_add_test(temp, polish2);
  tcase_add_test(temp, polish3);
  tcase_add_test(temp, polish4);
  tcase_add_test(temp, polish5);

  return s;
}