#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans)
    exit(EXIT_FAILURE);
};

int main() {
  run_check(2, 5, 32);
  run_check(-2, 3, -8);
  run_check(0, 0, 1);
  return EXIT_SUCCESS;
}
