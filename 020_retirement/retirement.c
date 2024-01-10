#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement(int startAge,         //in months
                double initial,       //initial savings in dollars
                retire_info working,  //info about working
                retire_info retired)  //info about being retired
{
  int age;
  int month;
  double balance = initial;
  for (int i = 0; i < working.months; i++) {
    age = (startAge + i) / 12;
    month = (startAge + i) - age * 12;

    printf("Age %3d month %2d you have $%.2f\n", age, month, balance);

    balance += balance * working.rate_of_return + working.contribution;
  }

  for (int i = 0; i < retired.months; i++) {
    age = (startAge + working.months + i) / 12;
    month = (startAge + working.months + i) - age * 12;

    printf("Age %3d month %2d you have $%.2f\n", age, month, balance);

    balance += balance * retired.rate_of_return + retired.contribution;
  }
}

int main() {
  retire_info working = {489, 1000, 0.045 / 12};
  retire_info retired = {384, -4000, 0.01 / 12};
  int startAge = 327;
  double initial = 21345;

  retirement(startAge, initial, working, retired);

  return 0;
}
