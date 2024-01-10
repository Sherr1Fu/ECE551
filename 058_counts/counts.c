#include "counts.h"

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  if (counts == NULL) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }
  counts->values = NULL;
  counts->size = 0;
  counts->unknowns = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknowns++;
    return;
  }
  for (int i = 0; i < c->size; i++) {
    if (strcmp(c->values[i].value, name) == 0) {
      c->values[i].count++;
      return;
    }
  }
  c->values = realloc(c->values, (c->size + 1) * sizeof(one_count_t));
  if (c->values == NULL) {
    free(c);
    perror("Failed to realloc memory");
    exit(EXIT_FAILURE);
  }
  c->values[c->size].value = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(c->values[c->size].value, name);
  c->values[c->size].count = 1;
  c->size++;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->values[i].value, c->values[i].count);
  }
  if (c->unknowns != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknowns);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    free(c->values[i].value);
  }
  free(c->values);
  free(c);
}
