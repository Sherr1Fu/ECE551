#include "sunspots.h"

#include <errno.h>
#include <stdlib.h>
ss_monthly_t parseLine(char * line) {
  // WRITE ME
  ss_monthly_t ans;
  ans.year = 0;
  ans.month = 0;
  ans.num = 0;
  int i;
  char * ptr;
  //get year
  for (i = 0; i < 4; i++) {
    if (line[i] >= '0' && line[i] <= '9') {
      ans.year = ans.year * 10 + line[i] - '0';
    }
    else {
      fprintf(stderr, "Invalid key(%c) in year\n", line[i]);
      exit(EXIT_FAILURE);
    }
  }
  //examine '-'
  if (line[i] != '-') {
    fprintf(stderr, "Invalid connection key(%c)\n", line[i]);
    exit(EXIT_FAILURE);
  }
  //get month
  for (i = 5; i < 7; i++) {
    if (line[i] >= '0' && line[i] <= '9') {
      ans.month = ans.month * 10 + line[i] - '0';
    }
    else {
      fprintf(stderr, "Invalid key(%c) in month\n", line[i]);
      exit(EXIT_FAILURE);
    }
  }
  if (ans.month > 12 || ans.month < 1) {  //if month not in 1-12
    fprintf(stderr, "Invalid month(%d)\n", ans.month);
    exit(EXIT_FAILURE);
  }
  //examine ','
  if (line[i] != ',') {
    fprintf(stderr, "Invalid key(%c): must be ,\n", line[i]);
    exit(EXIT_FAILURE);
  }
  //get double num
  line = line + 8;
  errno = 0;  //flag for strtod
  ans.num = strtod(line, &ptr);
  if (errno != 0 || (ans.num == 0 && line == ptr)) {
    //fprintf(stderr, "strtod");
    perror("strtod");
    exit(EXIT_FAILURE);
  }

  if (*ptr != '\n') {
    fprintf(stderr, "Invalid key(%c) in num\n", *ptr);
    exit(EXIT_FAILURE);
  }
  return ans;
}

void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // WRITE ME
  if (w % 2 == 0 || w <= 0) {  //w must be positive odd integers
    fprintf(stderr, "Invalid window width(%d)\n", w);
    exit(EXIT_FAILURE);
  }
  double sum = 0;
  unsigned number = 0;
  for (int i = 0; i < n; i++) {
    sum = 0;
    number = 0;
    int j = i;
    for (j = (j < w / 2) ? 0 : (j - w / 2); j <= i + w / 2; j++) {
      if (j < n) {
        sum += data[j].num;
        number++;
      }
    }
    mean[i].num = sum / number;
    mean[i].month = data[i].month;
    mean[i].year = data[i].year;
  }
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  if (data == NULL || n == 0) {
    fprintf(stderr, "0 element when finding the largest value\n");
    exit(EXIT_FAILURE);
  }
  size_t i;
  double timestamp;
  double max = 0;

  for (i = 0; i < n; i++) {
    if (data == NULL) {
      fprintf(stderr, "There are only %lu elements, less than %lu\n", i, n);
      exit(EXIT_FAILURE);
    }
    if (data->num > max) {
      max = data->num;
      timestamp = data->year + data->month / 12.0;
    }
    data++;
  }
  return timestamp;
}

double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  if (n < 2) {
    fprintf(stderr, "data is not enough to calculate\n");
    exit(EXIT_FAILURE);
  }
  double * ptr;
  double sum = 0;
  double period = 0;
  ptr = timeStamps + 1;
  for (size_t i = 0; i < n - 1; i++) {
    if (ptr == NULL) {
      fprintf(stderr, "data is less than n\n");
      exit(EXIT_FAILURE);
    }
    sum += *ptr - *timeStamps;
    ptr++;
    timeStamps++;
  }
  period = sum / (n - 1);
  return period;
}
