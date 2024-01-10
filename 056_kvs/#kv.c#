#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * kvfill(kvarray_t * array, char * line, size_t len) {
  int i, j, t;
  for (i = 0; i < len; i++) {
    if (line[i] == '=') {
      break;
    }
  }
  if (i == len) {
    freeKVs(array);
    free(line);
    perror("missing \"=\"");
    exit(EXIT_FAILURE);
  }
  for (t = i + 1; t < len; t++) {
    if (line[t] == '\n') {
      break;
    }
  }
  t = t - i - 1;
  array->kvpair[array->length].key = malloc((i + 1) * sizeof(char));
  array->kvpair[array->length].value = malloc((t + 1) * sizeof(char));
  for (j = 0; j < i; j++) {
    array->kvpair[array->length].key[j] = line[j];
  }
  array->kvpair[array->length].key[j] = '\0';
  for (j = 0; j < t; j++) {
    array->kvpair[array->length].value[j] = line[j + i + 1];
  }
  array->kvpair[array->length].value[j] = '\0';
  return array;
}
kvarray_t * readFile(FILE * f, kvarray_t * array) {
  ssize_t read;
  char * line = NULL;
  size_t len = 0;
  if (array == NULL) {
    array = malloc(sizeof(kvarray_t));
    array->kvpair = NULL;
    array->length = 0;
  }
  while ((read = getline(&line, &len, f)) != -1) {
    array->kvpair =
        (kvpair_t *)realloc(array->kvpair, (array->length + 1) * sizeof(kvpair_t));
    //array->length++;
    if (array->kvpair == NULL) {
      free(array);
      free(line);
      perror("Failed to realloc memory");
      exit(EXIT_FAILURE);
    }
    //fill the kvpair
    array = kvfill(array, line, len);
    free(line);
    line = NULL;
    array->length++;
  }
  free(line);
  return array;
}
kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * array = NULL;
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Failed to open file");
    exit(EXIT_FAILURE);
  }
  array = readFile(f, array);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  return array;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    free(pairs->kvpair[i].key);
    free(pairs->kvpair[i].value);
  }
  free(pairs->kvpair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpair[i].key, pairs->kvpair[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  //char * target = NULL;
  for (int i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->kvpair[i].key, key) == 0) {
      return pairs->kvpair[i].value;
    }
  }
  return NULL;
}
