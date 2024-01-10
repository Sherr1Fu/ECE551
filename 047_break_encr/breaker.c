#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/*void encrypt(FILE * f, int key) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      c += key;
      c %= 26;
      c += 'a';
    }
    printf("%c", c);
  }
  }*/
void decrypt(FILE * f) {
  int c;
  int letter[26] = {0};
  int max = 0;
  int max_index = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      letter[tolower(c) - 'a']++;
    }
  }
  for (int i = 0; i < 26; i++) {
    if (letter[i] > max) {
      max = letter[i];
      max_index = i;
    }
  }
  if (max_index >= 'e' - 'a') {
    printf("%d\n", max_index + 'a' - 'e');
  }
  else
    printf("%d\n", max_index + 26 + 'a' - 'e');
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  //int key = atoi(argv[1]);
  /*if (key == 0) {
    fprintf(stderr, "Invalid key (%s): must be a non-zero integer\n", argv[1]);
    return EXIT_FAILURE;
    }*/
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  //encrypt(f, key);
  decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
