#include <stdio.h>
#include <stdlib.h>

typedef struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
} retire_info_t;

double update_balance(double balance, retire_info_t phase) {
  // define returns per month dividing by 100 if balance is greater than 0
  double returns = 0;
  if (balance > 0)
    returns = balance * phase.rate_of_return;
  // add contribution and interest returns
  balance = balance + phase.contribution + returns;
  return balance;
}

void retirement(int startAge,           //age in months when saving starts
                double initial,         //intial savings in dollars
                retire_info_t working,  //info about working
                retire_info_t retired)  //info after retired
{
  // set balance to initial amount of money
  double current_balance = initial;
  // time step = 1 month
  int ts;
  // print initial conditions
  printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, current_balance);

  for (ts = startAge + 1; ts < startAge + working.months + retired.months; ts++) {
    // start calculations at startAge, run working calculations for months in working
    if (ts <= startAge + working.months)
      current_balance = update_balance(current_balance, working);
    // now calculation for retirement
    else
      current_balance = update_balance(current_balance, retired);

    printf("Age %3d month %2d you have $%.2lf\n", ts / 12, ts % 12, current_balance);
  }
  return;
}

int main() {
  retire_info_t working, retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  int Age = 327;
  double Savings = 21345;

  retirement(Age, Savings, working, retired);
  return EXIT_SUCCESS;
}
