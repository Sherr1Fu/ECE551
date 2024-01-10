#include "rand_story.h"
int main(int argc, char ** argv) {
  int n = 1;  //-n n=0 activate
  char * words = NULL;
  char * story = NULL;
  //parse command
  n = ParseCommand4(argc, argv, &words, &story, n);
  if (n == -1) {
    perror("Wrong command format\n");
    return EXIT_FAILURE;
  }

  FILE * stream = NULL;
  //char * line = NULL;
  //size_t len = 0;
  //ssize_t read;
  catarray_t * cats = NULL;
  category_t * used = NULL;
  //  size_t count = 0;

  //read words
  stream = openfile(stream, words);
  cats = initcats(cats);
  cats = readwords(cats, stream);
  closefile(stream);
  if (cats == NULL) {
    perror("something get wrong when reading words from file");
    //freecats(cats);
    return EXIT_FAILURE;
  }
  //closefile(stream);
  //printWords(cats);  //test

  //write story
  stream = openfile(stream, story);
  used = initcat(used, "used");
  used = printstory(cats, stream, used, n);
  if (used == NULL) {
    perror("something get wrong when printing story\n");
    closefile(stream);
    freecats(cats);
    return EXIT_FAILURE;
  }
  closefile(stream);
  freecats(cats);
  freecat(used);
  return EXIT_SUCCESS;
}
