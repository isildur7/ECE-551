#include <stdio.h>
#include <stdlib.h>

typedef struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
} retire_info_t;

double update_balance(double balance, retire_info_t phase) {
  // define returns per month dividing by 12 if balance is greater than 0
  double returns;
  if (balance > 0)
    returns = balance * phase.rate_of_return / 1200;
  else
    returns = 0;
  // add contribution and interest returns
  balance = balance + phase.contribution + returns;
  return balance;
}

void retirement(int startAge,           //age in months when saving starts
                double initial,         //intial savings in dollars
                retire_info_t working,  //info about working
                retire_info_t retired)  //infor after retired
{
  // set balance to initial amount of money
  double balance = initial;
  // time step = 1 month
  int ts;
  // print initial conditions
  printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, balance);
  // start calculations at startAge, run working calculations for months in working
  for (ts = startAge + 1; ts <= startAge + working.months; ++ts) {
    balance = update_balance(balance, working);
    printf("Age %3d month %2d you have $%.2lf\n", ts / 12, ts % 12, balance);
  }
  // now calculation for retirement
  for (; ts < startAge + working.months + retired.months; ++ts) {
    balance = update_balance(balance, retired);
    printf("Age %3d month %2d you have $%.2lf\n", ts / 12, ts % 12, balance);
  }
  return;
}

int main() {
  retire_info_t working, retired;

  working.months = 514;
  working.contribution = 1234;
  working.rate_of_return = 0.0056;

  retired.months = 205;
  retired.contribution = -6534;
  retired.rate_of_return = 0.00079;

  int Age = 240;
  double Savings = 0;

  retirement(Age, Savings, working, retired);
  return EXIT_SUCCESS;
}
