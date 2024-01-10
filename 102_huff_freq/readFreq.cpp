#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * frequencyArray = new uint64_t[257]();
  FILE * file = fopen(fname, "r");
  if (file == NULL) {
    std::cerr << "Failed to open file: " << fname << std::endl;
    exit(EXIT_FAILURE);
  }
  int c;
  while ((c = fgetc(file)) != EOF) {
    frequencyArray[c]++;
  }
  frequencyArray[256]++;
  if (fclose(file) != 0) {
    std::cerr << "Failed to close file: " << fname << std::endl;
    exit(EXIT_FAILURE);
  };
  return frequencyArray;
}
