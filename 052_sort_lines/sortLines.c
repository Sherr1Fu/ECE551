#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void printData(char ** data, size_t count) {
  for (int i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
  free(data);
}
void freeall(char ** data, size_t count) {
  for (int i = 0; i < count; i++) {
    free(data[i]);
  }
  free(data);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  FILE * stream;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  char ** lines = NULL;
  size_t count = 0;

  if (argc == 1) {  //no argument
    while ((read = getline(&line, &len, stdin)) != -1) {
      lines = (char **)realloc(lines, (count + 1) * sizeof(char *));
      if (lines == NULL) {
        free(line);
        perror("Failed to realloc memory");
        exit(EXIT_FAILURE);
      }
      lines[count] = malloc(len);
      strcpy(lines[count], line);
      //free(line);
      count++;
    }
    sortData(lines, count);
    printData(lines, count);
    free(line);
  }
  else {  //have arguments
    for (int i = 1; i < argc; i++) {
      stream = fopen(argv[i], "r");
      if (stream == NULL) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
      }
      while ((read = getline(&line, &len, stream)) != -1) {
        lines = (char **)realloc(lines, (count + 1) * sizeof(char *));
        if (lines == NULL) {
          free(line);
          perror("Failed to realloc memory");
          exit(EXIT_FAILURE);
        }
        lines[count] = malloc(len);
        strcpy(lines[count], line);
        //free(line);
        count++;
      }
      if (fclose(stream) != 0) {
        perror("Failed to close the input file!");
        free(line);
        freeall(lines, count);
        return EXIT_FAILURE;
      }
      sortData(lines, count);
      printData(lines, count);
      lines = NULL;
      free(line);
      line = NULL;
      count = 0;
    }
  }
  //free(line);
  //sortData(lines, count);
  //printData(lines, count);
  return EXIT_SUCCESS;
}
