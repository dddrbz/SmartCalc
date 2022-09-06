#include "credit.h"

double calc_annuity_payment(double sum, double term, double rate) {
  double payment;

  rate = rate / 12 / 100;
  payment = sum * (rate * pow(1 + rate, term) / (pow(1 + rate, term) - 1));
  return payment;
}

double calc_annuity_pay(double sum, double term, double rate) {
  return (calc_annuity_payment(sum, term, rate) * term);
}

double calc_annuity_overpayment(double sum, double term, double rate) {
  return (calc_annuity_pay(sum, term, rate) - sum);
}

double calc_differentiated_payment(double sum, double term, double rate,
                                   int num) {
  double payment = 0, base;

  rate = rate / 100;
  base = sum / term;
  for (int i = 0; i < num; ++i) {
    payment = base + sum * rate / 12;
    sum -= base;
  }
  return payment;
}

double calc_differentiated_pay(double sum, double term, double rate) {
  double pay = 0.0;

  for (int i = 1; i <= term; ++i) {
    pay += calc_differentiated_payment(sum, term, rate, i);
  }
  return pay;
}

double calc_differentiated_overpayment(double sum, double term, double rate) {
  return (calc_differentiated_pay(sum, term, rate) - sum);
}
