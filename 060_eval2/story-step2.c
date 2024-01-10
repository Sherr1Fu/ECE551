#include "rand_story.h"

/*catarray_t * initcats(catarray_t * cats) {
  cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  return cats;
}
category_t * findcats(char * category, catarray_t * cats) {
  int i;
  for (i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, category) == 0) {
      return cats->arr + i;
    }
  }
  return NULL;
}

void freecats(catarray_t * cats) {
  for (int i = 0; i < cats->n; i++) {
    for (int j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].name);
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
}
category_t * addnewcat(catarray_t * cats, char * name) {
  cats->n++;
  cats->arr = realloc(cats->arr, cats->n * sizeof(*cats->arr));
  if (cats->arr == NULL) {
    return NULL;
  }
  cats->arr[cats->n - 1].name = malloc((strlen(name) + 1) * sizeof(char));
  strcpy(cats->arr[cats->n - 1].name, name);
  cats->arr[cats->n - 1].words = NULL;
  cats->arr[cats->n - 1].n_words = 0;
  return cats->arr + cats->n - 1;
}
category_t * addnewname(category_t * cat, char * word) {
  cat->words = realloc(cat->words, (cat->n_words + 1) * sizeof(*cat->words));
  if (cat->words == NULL) {
    return NULL;
  }
  cat->words[cat->n_words] = malloc((strlen(word) + 1) * sizeof(char));
  strcpy(cat->words[cat->n_words], word);
  cat->n_words++;
  return cat;
}
int ParseLine(char * string) {
  int i;
  int count = 0;  //count for ':'
  int str = 0;
  for (i = 0; string[i] != '\n'; i++) {
    if (string[i] == ':') {
      count++;
      if (count == 1) {
        str = i + 1;
      }
      else {
        return -1;
      }
    }
  }
  if (count == 0) {
    return -1;
  }
  if (str < 2) {
    return -1;
  }
  return str;
  }*/
int main(int argc, char ** argv) {
  FILE * stream = NULL;
  //char * line = NULL;
  //size_t len = 0;
  //ssize_t read;
  catarray_t * cats = NULL;
  //int str = 0;
  //category_t * cat = NULL;

  if (argc != 2) {
    perror("Wrong input format");
    return EXIT_FAILURE;
  }
  //open file
  //cats = initcats(cats);
  stream = openfile(stream, argv[1]);
  cats = initcats(cats);
  cats = readwords(cats, stream);
  //read lines
  /*  while ((read = getline(&line, &len, stream)) >= 0) {
    str = ParseLine(line);  //return the index of the name
    if (str == -1) {
      perror("invalid input format");
      freecats(cats);
      free(line);
      return EXIT_FAILURE;
    }
    //read name
    char * name = malloc(str * sizeof(char));
    strncpy(name, line, str - 1);
    name[str - 1] = '\0';
    //printf("%s\n", name);  //test
    //read word
    int WordLength = 0;
    while (line[str + WordLength] != '\n') {
      WordLength++;
    }
    if (WordLength == 0) {
      perror("invalid input format: word");
      freecats(cats);
      free(line);
      return EXIT_FAILURE;
    }
    char * word = malloc((WordLength + 1) * sizeof(char));
    strncpy(word, line + str, WordLength);
    word[WordLength] = '\0';
    //printf("%s\n", word);  //test

    cat = findcats(name, cats);  //find the str to category_t
    //add new cat
    if (cat == NULL) {
      cat = addnewcat(cats, name);
      if (cat == NULL) {
        perror("failed to add mew cat");
        freecats(cats);
        free(line);
        free(name);
        return EXIT_FAILURE;
      }
    }
    free(name);
    //add the word to the category cat points at;
    cat = addnewname(cat, word);
    if (cat == NULL) {
      perror("failed to add words to cat");
      freecats(cats);
      free(line);
      free(word);
      return EXIT_FAILURE;
    }
    free(word);
  }
  free(line);*/
  if (cats == NULL) {
    perror("something get wrong when reading file");
    //freecats(cats);
    closefile(stream);
    return EXIT_FAILURE;
  }
  closefile(stream);
  printWords(cats);
  freecats(cats);
  return EXIT_SUCCESS;
}
