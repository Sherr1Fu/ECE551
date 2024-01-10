#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);
void run_check(int * array, size_t n, size_t expected_ans) {
  if (maxSeq(array, n) != expected_ans)
    exit(EXIT_FAILURE);
}
int main() {
  int array1[] = {0, 0, 0};
  int array2[] = {3, -1, 0};
  int array3[] = {0, 1, -3, 2};
  run_check(array1, 3, 1);
  run_check(array2, 3, 2);
  run_check(array3, 4, 2);
  run_check(NULL, 0, 0);
  return EXIT_SUCCESS;
}
