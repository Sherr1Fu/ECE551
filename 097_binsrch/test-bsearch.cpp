#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

extern int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
class Function1 : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned max_invocations;
  if (low < high) {
    max_invocations = log2(high - low) + 1;
  }
  else {
    max_invocations = 1;
  }

  CountedIntFn countFn(max_invocations, f, mesg);

  // Perform the binary search
  int result = binarySearchForZero(&countFn, low, high);

  // Check the answer
  if (result != expected_ans) {
    std::cerr << mesg << " failed: Expected " << expected_ans << ", got " << result
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main() {
  Function1 fun1;
  //CountedIntFn exampleFn(3, &fun1, "Example Test");
  check(&fun1, -1, 4, 0, "Example Test1");
  check(&fun1, 1, 4, 1, "Example Test2");
  check(&fun1, -11, -4, -5, "Example Test3");
  check(&fun1, 0, 4, 0, "Example Test4");
  check(&fun1, -2, 0, -1, "Example Test5");
  check(&fun1, -4, -4, -4, "Example Test6");
  return 0;
}
