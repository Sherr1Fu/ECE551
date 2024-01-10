#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low > high)
    exit(EXIT_FAILURE);
  if (low == high)
    return low;
  /*if (f->invoke(high - 1) < 0)
    return high - 1;
  if (f->invoke(low) > 0)
  return low;*/
  while (low < high - 1) {
    int mid = (low + high) / 2;
    int result = f->invoke(mid);
    if (result > 0) {
      high = mid;
    }
    else if (result < 0) {
      low = mid;
    }
    else {
      return mid;
    }
  }
  return low;
}
