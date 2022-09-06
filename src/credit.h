#ifndef SRC_CREDIT_H_
#define SRC_CREDIT_H_

#include <math.h>

double calc_annuity_payment(double sum, double term, double rate);
double calc_annuity_pay(double sum, double term, double rate);
double calc_annuity_overpayment(double sum, double term, double rate);
double calc_differentiated_payment(double sum, double term, double rate,
                                   int num);
double calc_differentiated_pay(double sum, double term, double rate);
double calc_differentiated_overpayment(double sum, double term, double rate);

#endif  // SRC_CREDIT_H_
