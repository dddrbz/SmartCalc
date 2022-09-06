#include <check.h>

#include "ch_stack.h"
#include "count.h"
#include "credit.h"

START_TEST(ch_stack_01) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('1', &head);
  ck_assert_int_eq(head->value, '1');
  free_stack_ch(&head);
}
END_TEST

START_TEST(ch_stack_02) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('c', &head);
  ck_assert_int_eq(head->value, 'c');
  free_stack_ch(&head);
}
END_TEST

START_TEST(ch_stack_03) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('\0', &head);
  ck_assert_int_eq(head->value, '\0');
  free_stack_ch(&head);
}
END_TEST

START_TEST(ch_stack_04) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('\n', &head);
  ck_assert_int_eq(head->value, '\n');
  free_stack_ch(&head);
}
END_TEST

START_TEST(ch_stack_05) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('+', &head);
  ck_assert_int_eq(head->value, '+');
  free_stack_ch(&head);
}
END_TEST

START_TEST(ch_stack_06) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('+', &head);
  ck_assert_int_eq(get_value_from_stack_ch(&head), '+');
  free_stack_ch(&head);
}
END_TEST

START_TEST(ch_stack_07) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('1', &head);
  ck_assert_int_eq(get_value_from_stack_ch(&head), '1');
  free_stack_ch(&head);
}
END_TEST

START_TEST(ch_stack_08) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('c', &head);
  ck_assert_int_eq(get_value_from_stack_ch(&head), 'c');
  free_stack_ch(&head);
}
END_TEST

START_TEST(ch_stack_09) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('\0', &head);
  ck_assert_int_eq(get_value_from_stack_ch(&head), '\0');
  free_stack_ch(&head);
}
END_TEST

START_TEST(ch_stack_10) {
  stack_ch *head = NULL;

  add_value_to_stack_ch('\n', &head);
  ck_assert_int_eq(get_value_from_stack_ch(&head), '\n');
  free_stack_ch(&head);
}
END_TEST

START_TEST(db_stack_01) {
  stack_db *head = NULL;

  add_value_to_stack_db(1, &head);
  ck_assert_double_eq(head->value, 1);
  free_stack_db(&head);
}
END_TEST

START_TEST(db_stack_02) {
  stack_db *head = NULL;

  add_value_to_stack_db(12.22, &head);
  ck_assert_double_eq(head->value, 12.22);
  free_stack_db(&head);
}
END_TEST

START_TEST(db_stack_03) {
  stack_db *head = NULL;

  add_value_to_stack_db(0, &head);
  ck_assert_double_eq(head->value, 0);
  free_stack_db(&head);
}
END_TEST

START_TEST(db_stack_04) {
  stack_db *head = NULL;

  add_value_to_stack_db(-4.1, &head);
  ck_assert_double_eq(head->value, -4.1);
  free_stack_db(&head);
}
END_TEST

START_TEST(db_stack_05) {
  stack_db *head = NULL;

  add_value_to_stack_db(0.000001, &head);
  ck_assert_double_eq(head->value, 0.000001);
  free_stack_db(&head);
}
END_TEST

START_TEST(db_stack_06) {
  stack_db *head = NULL;

  add_value_to_stack_db(1, &head);
  ck_assert_int_eq(get_value_from_stack_db(&head), 1);
  free_stack_db(&head);
}
END_TEST

START_TEST(db_stack_07) {
  stack_db *head = NULL;

  add_value_to_stack_db(1.22, &head);
  ck_assert_int_eq(get_value_from_stack_db(&head), 1.22);
  free_stack_db(&head);
}
END_TEST

START_TEST(db_stack_08) {
  stack_db *head = NULL;

  add_value_to_stack_db(0.00001, &head);
  ck_assert_int_eq(get_value_from_stack_db(&head), 0.00001);
  free_stack_db(&head);
}
END_TEST

START_TEST(db_stack_09) {
  stack_db *head = NULL;

  add_value_to_stack_db(-4.2, &head);
  ck_assert_int_eq(get_value_from_stack_db(&head), -4.2);
  free_stack_db(&head);
}
END_TEST

START_TEST(db_stack_10) {
  stack_db *head = NULL;

  add_value_to_stack_db(0, &head);
  ck_assert_int_eq(get_value_from_stack_db(&head), 0);
  free_stack_db(&head);
}
END_TEST

START_TEST(notation_01) {
  char str[] = "2+4";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "2|4|+");
}
END_TEST

START_TEST(notation_02) {
  char str[] = "2+4+cos(4)";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "2|4|+4|cos+");
}
END_TEST

START_TEST(notation_03) {
  char str[] = "(2+4)+cos(4)";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "2|4|+4|cos+");
}
END_TEST

START_TEST(notation_04) {
  char str[] = "(2+4)cos(4)";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(notation_05) {
  char str[] = "+(2+4)+cos(4)";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "2|4|+4|cos+");
}
END_TEST

START_TEST(notation_06) {
  char str[] = "-(2+4)+cos(4)";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "2|4|+~4|cos+");
}
END_TEST

START_TEST(notation_07) {
  char str[] = "-(2+4)+cos(4)-2.2";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "2|4|+~4|cos+2.2|-");
}
END_TEST

START_TEST(notation_08) {
  char str[] = "-(2+--4)+cos(4)-2.2";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "2|4|+~4|cos+2.2|-");
}
END_TEST

START_TEST(notation_09) {
  char str[] = "-(2+--4)+cos(4)-2.2mod4";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "2|4|+~4|cos+2.2|4|%-");
}
END_TEST

START_TEST(notation_10) {
  char *str = NULL;
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(notation_11) {
  char str[] = "-(2*--4)/cos(4^x^2)-2.2mod4";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "2|4|*~4|x|^2|^cos/2.2|4|%-");
}
END_TEST

START_TEST(notation_12) {
  char str[] = "--4";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "4|");
}
END_TEST

START_TEST(notation_13) {
  char str[] = "---4";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "4|~");
}
END_TEST

START_TEST(notation_14) {
  char str[] = "-(-(-4))";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "4|~~~");
}
END_TEST

START_TEST(notation_15) {
  char str[] = "(45+1";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(notation_16) {
  char str[] = "45+1)";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(notation_17) {
  char str[] = "++4";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "4|");
}
END_TEST

START_TEST(notation_18) {
  char str[] = "45.5.5";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(notation_19) {
  char str[] = "46---6";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "46|6|-");
}
END_TEST

START_TEST(notation_20) {
  char str[] = "45+9)";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(notation_21) {
  char str[] = "*(55-7)";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(notation_22) {
  char str[] = "hello";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(notation_23) {
  char str[] = "3*/2";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(notation_24) {
  char str[] = "*";
  char result[50] = {0};

  translate_notation(str, result);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(count_01) {
  char str[] = "2+6";
  char result[50] = {0};
  double result_num = 8, test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, result_num);
}
END_TEST

START_TEST(count_02) {
  char str[] = "2+6+x";
  char result[50] = {0};
  double result_num = 8, test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, result_num);
}
END_TEST

START_TEST(count_03) {
  char str[] = "cos(4)";
  char result[50] = {0};
  double test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, cos(4));
}
END_TEST

START_TEST(count_04) {
  char str[] = "sin(4)";
  char result[50] = {0};
  double test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, sin(4));
}
END_TEST

START_TEST(count_05) {
  char str[] = "tan(4)";
  char result[50] = {0};
  double test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, tan(4));
}
END_TEST

START_TEST(count_06) {
  char str[] = "acos(1)";
  char result[50] = {0};
  double test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, acos(1));
}
END_TEST

START_TEST(count_07) {
  char str[] = "asin(1)";
  char result[50] = {0};
  double test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, asin(1));
}
END_TEST

START_TEST(count_08) {
  char str[] = "atan(1)";
  char result[50] = {0};
  double test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, atan(1));
}
END_TEST

START_TEST(count_09) {
  char str[] = "sqrt(4)";
  char result[50] = {0};
  double test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, sqrt(4));
}
END_TEST

START_TEST(count_10) {
  char str[] = "ln(4)";
  char result[50] = {0};
  double test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, log(4));
}
END_TEST

START_TEST(count_11) {
  char str[] = "log(4)";
  char result[50] = {0};
  double test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, log10(4));
}
END_TEST

START_TEST(count_12) {
  char str[] = "(2+6)/2*2%-2-6^2";
  char result[50] = {0};
  double result_num = -36, test_num;

  translate_notation(str, result);
  calculate_expression(result, &test_num, 0);
  ck_assert_double_eq(test_num, result_num);
}
END_TEST

START_TEST(count_13) { ck_assert_int_eq(check_x_string("1.6"), TRUE); }
END_TEST

START_TEST(count_14) { ck_assert_int_eq(check_x_string("1..6"), FALSE); }
END_TEST

START_TEST(count_15) { ck_assert_int_eq(check_x_string("78956"), TRUE); }
END_TEST

START_TEST(count_16) { ck_assert_int_eq(check_x_string("g"), FALSE); }
END_TEST

START_TEST(count_17) { ck_assert_int_eq(check_x_string("-1.6"), TRUE); }
END_TEST

START_TEST(credit_01) {
  double res = calc_annuity_overpayment(1000000, 20, 10);
  res = round(res * 100) / 100;
  ck_assert_double_eq_tol(89798.40, res, 1e-02);
}
END_TEST

START_TEST(credit_02) {
  double res = calc_annuity_overpayment(1000000, 22, 10);
  res = round(res * 100) / 100;
  ck_assert_double_eq_tol(98615.33, res, 1e-02);
}
END_TEST

START_TEST(credit_03) {
  double res = calc_differentiated_overpayment(1000000, 20, 10);
  res = round(res * 100) / 100;
  ck_assert_double_eq_tol(87500, res, 1e-02);
}
END_TEST

START_TEST(credit_04) {
  double res = calc_differentiated_overpayment(100000, 22, 10);
  res = round(res * 100) / 100;
  ck_assert_double_eq_tol(9583.33, res, 1e-02);
}
END_TEST

Suite *ch_stack_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("ch_stack_test");
  tc_core = tcase_create("ch_stack_test");

  tcase_add_test(tc_core, ch_stack_01);
  tcase_add_test(tc_core, ch_stack_02);
  tcase_add_test(tc_core, ch_stack_03);
  tcase_add_test(tc_core, ch_stack_04);
  tcase_add_test(tc_core, ch_stack_05);
  tcase_add_test(tc_core, ch_stack_06);
  tcase_add_test(tc_core, ch_stack_07);
  tcase_add_test(tc_core, ch_stack_08);
  tcase_add_test(tc_core, ch_stack_09);
  tcase_add_test(tc_core, ch_stack_10);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *db_stack_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("db_stack_test");
  tc_core = tcase_create("db_stack_test");

  tcase_add_test(tc_core, db_stack_01);
  tcase_add_test(tc_core, db_stack_02);
  tcase_add_test(tc_core, db_stack_03);
  tcase_add_test(tc_core, db_stack_04);
  tcase_add_test(tc_core, db_stack_05);
  tcase_add_test(tc_core, db_stack_06);
  tcase_add_test(tc_core, db_stack_07);
  tcase_add_test(tc_core, db_stack_08);
  tcase_add_test(tc_core, db_stack_09);
  tcase_add_test(tc_core, db_stack_10);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *notation_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("notation_test");
  tc_core = tcase_create("notation_test");

  tcase_add_test(tc_core, notation_01);
  tcase_add_test(tc_core, notation_02);
  tcase_add_test(tc_core, notation_03);
  tcase_add_test(tc_core, notation_04);
  tcase_add_test(tc_core, notation_05);
  tcase_add_test(tc_core, notation_06);
  tcase_add_test(tc_core, notation_07);
  tcase_add_test(tc_core, notation_08);
  tcase_add_test(tc_core, notation_09);
  tcase_add_test(tc_core, notation_10);
  tcase_add_test(tc_core, notation_11);
  tcase_add_test(tc_core, notation_12);
  tcase_add_test(tc_core, notation_13);
  tcase_add_test(tc_core, notation_14);
  tcase_add_test(tc_core, notation_15);
  tcase_add_test(tc_core, notation_16);
  tcase_add_test(tc_core, notation_17);
  tcase_add_test(tc_core, notation_18);
  tcase_add_test(tc_core, notation_19);
  tcase_add_test(tc_core, notation_20);
  tcase_add_test(tc_core, notation_21);
  tcase_add_test(tc_core, notation_22);
  tcase_add_test(tc_core, notation_23);
  tcase_add_test(tc_core, notation_24);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *count_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("count_test");
  tc_core = tcase_create("count_test");

  tcase_add_test(tc_core, count_01);
  tcase_add_test(tc_core, count_02);
  tcase_add_test(tc_core, count_03);
  tcase_add_test(tc_core, count_04);
  tcase_add_test(tc_core, count_05);
  tcase_add_test(tc_core, count_06);
  tcase_add_test(tc_core, count_07);
  tcase_add_test(tc_core, count_08);
  tcase_add_test(tc_core, count_09);
  tcase_add_test(tc_core, count_10);
  tcase_add_test(tc_core, count_11);
  tcase_add_test(tc_core, count_12);
  tcase_add_test(tc_core, count_13);
  tcase_add_test(tc_core, count_14);
  tcase_add_test(tc_core, count_15);
  tcase_add_test(tc_core, count_16);
  tcase_add_test(tc_core, count_17);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *credit_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("credit_test");
  tc_core = tcase_create("credit_test");

  tcase_add_test(tc_core, credit_01);
  tcase_add_test(tc_core, credit_02);
  tcase_add_test(tc_core, credit_03);
  tcase_add_test(tc_core, credit_04);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = ch_stack_test();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  no_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  s = db_stack_test();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  no_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  s = notation_test();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  no_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  s = count_test();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  no_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  s = credit_test();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  no_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
