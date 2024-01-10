#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * Counts = createCounts();
  ssize_t read;
  char * line = NULL;
  size_t len = 0;
  //char ** Data;
  FILE * f;
  //int num = 0;
  char * value;
  char * newline;
  f = fopen(filename, "r");
  if (f == NULL) {
    perror("Failed to open countfile");
    exit(EXIT_FAILURE);
  }
  while ((read = getline(&line, &len, f)) != -1) {
    //Data = (char **)realloc(Data, (num + 1) * sizeof(char *));
    newline = malloc(strlen(line) * sizeof(char));
    int i = 0;
    while (line[i] != '\n') {
      newline[i] = line[i];
      i++;
    }
    newline[i] = '\0';
    value = lookupValue(kvPairs, newline);
    addCount(Counts, value);
    free(newline);
    newline = NULL;
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    perror("Failed to close the countfile!");
    exit(EXIT_FAILURE);
  }
  return Counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv;
  counts_t * c;
  char * outName;
  FILE * f;
  if (argc < 3) {
    perror("invalid input");
    return EXIT_FAILURE;
  }
  kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    c = countFile(argv[i], kv);
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)
    outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    f = fopen(outName, "w");
    if (f == NULL) {
      perror("Failed to open file f");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      perror("Failed to close the file f");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
    //free the memory for kv
  }
  freeKVs(kv);
  return EXIT_SUCCESS;
}
