#include "rand_story.h"
int main(int argc, char ** argv) {
  FILE * stream = NULL;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  catarray_t * cats = NULL;
  //int str = 0;
  category_t * used = NULL;
  size_t count = 0;

  if (argc != 3) {
    perror("Wrong input format");
    return EXIT_FAILURE;
  }
  //argv[1] words [2] story
  //read words
  stream = openfile(stream, argv[1]);
  cats = initcats(cats);
  cats = readwords(cats, stream);
  if (cats == NULL) {
    perror("something get wrong when reading file");
    freecats(cats);
    return EXIT_FAILURE;
  }
  closefile(stream);
  //printWords(cats);  //test

  //write story
  stream = openfile(stream, argv[2]);
  used = malloc(sizeof(*used));
  used->n_words = 0;
  used->name = "used";
  used->words = NULL;

  //char * name = NULL;
  category_t * findcat = NULL;
  int wordstart = 0;
  int wordcount = 0;
  while ((read = getline(&line, &len, stream)) != -1) {
    count = 0;  //calculate the number of '_'
    for (int i = 0; line[i] != '\n'; i++) {
      if (count % 2 == 0) {  //even number of '_'
        if (line[i] != '_') {
          printf("%c", line[i]);
        }
        else {
          count++;
          wordstart = i + 1;
          wordcount = 0;
        }
      }
      else {  //odd number of '_', the following is in the blank
        if (line[i] == '_') {
          count++;
          if (wordcount == 0) {
            perror("story blank format is wrong");
            free(line);
            freecat(used);
            freecats(cats);
            return EXIT_FAILURE;
          }
          char * name = malloc((wordcount + 1) * sizeof(*name));
          strncpy(name, line + wordstart, wordcount);
          name[wordcount] = '\0';
          int integer = ifint(name);
          //printf("\n%s,%d", name, integer);
          //printf("\n%zu", used->n_words);
          if (integer > 0 && integer <= used->n_words) {  //read from used
            free(name);
            name = used->words[used->n_words - integer];
            used = addnewname(used, name);
            printf("%s", name);
            name = NULL;
          }
          else if (integer > used->n_words) {
            perror("the number of previous used word is not enough\n");
            free(line);
            free(name);
            freecat(used);
            freecats(cats);
            return EXIT_FAILURE;
          }
          else {  //read from cats
            findcat = findcats(name, cats);
            if (findcat == NULL) {
              perror("can't find category in cats");
              free(line);
              free(name);
              freecat(used);
              freecats(cats);
              return EXIT_FAILURE;
            }
            const char * cat = chooseWord(name, cats);
            char * cat2 = malloc((strlen(cat) + 1) * sizeof(*cat2));
            strcpy(cat2, cat);
            used = addnewname(used, cat2);
            free(cat2);
            printf("%s", cat);
            free(name);
          }
        }
        else {
          wordcount++;
        }
      }
    }
    printf("\n");
    if (count % 2 != 0) {  //odd number of '_' in one line
      free(line);
      freecat(used);
      freecats(cats);
      perror("Unmatching underscore!");
      return EXIT_FAILURE;
    }
  }
  free(line);
  closefile(stream);
  freecats(cats);
  freecat(used);
  return EXIT_SUCCESS;
}
