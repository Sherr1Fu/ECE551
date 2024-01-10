#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(FILE * f) {
  char c;
  int i, j;
  char matrix[10][11];
  for (i = 9; i >= 0; i--) {
    for (j = 0; j < 10; j++) {
      if ((matrix[j][i] = fgetc(f)) == EOF) {
        fprintf(stderr, "Insufficient input\n");
        exit(EXIT_FAILURE);
      }
      if (matrix[j][i] == '\n') {
        fprintf(stderr, "Insufficient input in a line");
        exit(EXIT_FAILURE);
      }
    }
    if ((matrix[i][j] = fgetc(f)) == EOF) {
      fprintf(stderr, "Insufficient input\n");
      exit(EXIT_FAILURE);
    }
    if (matrix[i][j] != '\n') {
      fprintf(stderr, "Exceeded input in a line");
      exit(EXIT_FAILURE);
    }
  }
  if ((c = fgetc(f)) != EOF) {
    fprintf(stderr, "Exceeded input lines");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 11; j++) {
      printf("%c", matrix[i][j]);
    }
  }
  /*if ((c = fgetc(f)) != EOF) {
    fprintf(stderr, "Exceeded input lines");
    exit(EXIT_FAILURE);
  }
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      c += key;
      c %= 26;
      c += 'a';
    }
    printf("%c", c);
    }*/
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid Command\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotate(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
