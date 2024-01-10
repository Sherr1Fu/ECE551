#include "rand_story.h"

int main(int argc, char ** argv) {
  FILE * stream = NULL;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  size_t count = 0;
  //char ** lines = NULL;

  if (argc != 2) {
    perror("Wrong input format");
    exit(EXIT_FAILURE);
  }
  else {  //open file
    stream = openfile(stream, argv[1]);
    while ((read = getline(&line, &len, stream)) != -1) {
      count = 0;  //calculate the number of '_'
      for (int i = 0; line[i] != '\n'; i++) {
        if (count % 2 == 0) {  //even number of '_'
          if (line[i] != '_') {
            printf("%c", line[i]);
          }
          else {
            count++;
          }
        }
        else {  //odd number of '_', the following is in the blank
          if (line[i] == '_') {
            count++;
            const char * cat = chooseWord("verb", NULL);
            printf("%s", cat);
          }
        }
      }
      printf("\n");
      if (count % 2 != 0) {  //odd number of '_' in one line
        free(line);
        perror("Unmatching underscore!");
        return EXIT_FAILURE;
      }
    }
    free(line);
    closefile(stream);
  }
  return EXIT_SUCCESS;
}
