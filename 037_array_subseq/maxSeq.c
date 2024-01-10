#include <stddef.h>
size_t maxSeq(int * array, size_t n) {
  size_t maxseq = 1;
  size_t maxseq2 = 1;
  int * p = array;
  if (n == 0)
    return 0;
  for (size_t i = 0; i < n - 1; i++) {
    if (*(p + i) < *(p + i + 1))
      maxseq2++;
    else {
      if (maxseq2 > maxseq)
        maxseq = maxseq2;
      maxseq2 = 1;
    }
  }
  if (maxseq2 > maxseq)
    maxseq = maxseq2;
  return maxseq;
}
