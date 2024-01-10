#include "rand_story.h"

FILE * openfile(FILE * f, char * filename) {
  f = fopen(filename, "r");
  if (f == NULL) {
    perror("input file open failed");
    exit(EXIT_FAILURE);
  }
  return f;
}

void closefile(FILE * f) {
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
}

int ParseCommand4(int argc, char ** argv, char ** words, char ** story, int n) {
  if (argc != 3 && argc != 4) {
    perror("Wrong input format");
    return -1;
  }
  if (argc == 4) {
    n = strcmp(argv[1], "-n");
    if (n != 0) {
      perror("Wrong input format: 4 input");
      return -1;
    }
    *words = argv[2];
    *story = argv[3];
  }
  else {
    *words = argv[1];
    *story = argv[2];
  }
  return n;
}
catarray_t * initcats(catarray_t * cats) {
  cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  return cats;
}
category_t * initcat(category_t * cat, char * name) {
  cat = malloc(sizeof(*cat));
  cat->name = name;
  cat->words = NULL;
  cat->n_words = 0;
  return cat;
}
category_t * findcats(char * category, catarray_t * cats) {
  int i;
  for (i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, category) == 0 && cats->arr[i].n_words != 0) {
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
void freecat(category_t * cat) {
  for (int i = 0; i < cat->n_words; i++) {
    free(cat->words[i]);
  }
  //free(cat->name);
  free(cat->words);
  free(cat);
}

void freewords(category_t * cat) {
  for (int i = 0; i < cat->n_words; i++) {
    free(cat->words[i]);
  }
  free(cat->words);
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
        return str;
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
}
catarray_t * readwords(catarray_t * cats, FILE * stream) {
  //FILE * stream = NULL;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  //catarray_t * cats = NULL;
  int str = 0;
  category_t * cat = NULL;
  while ((read = getline(&line, &len, stream)) >= 0) {
    str = ParseLine(line);  //return the index of the name
    if (str == -1) {
      perror("invalid input format");
      free(line);
      freecats(cats);
      return NULL;
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
    /*if (WordLength == 0) {
      perror("invalid input format: word");
      freecats(cats);
      free(name);
      free(line);
      return NULL;
      }*/
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
        free(line);
        free(name);
        free(word);
        freecats(cats);
        return NULL;
      }
    }
    free(name);
    //add the word to the category cat points at;
    cat = addnewname(cat, word);
    if (cat == NULL) {
      perror("failed to add words to cat");
      free(line);
      free(word);
      freecats(cats);
      return NULL;
    }
    free(word);
  }
  free(line);
  return cats;
}

category_t * printstory(catarray_t * cats, FILE * stream, category_t * used, int n) {
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  category_t * findcat = NULL;
  while ((read = getline(&line, &len, stream)) != -1) {
    int wordstart = 0;
    int wordcount = 0;
    size_t count = 0;  //calculate the number of '_'
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
          if (wordcount == 0) {  //blank has no name
            perror("story blank format is wrong");
            free(line);
            freecat(used);
            return NULL;
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
            return NULL;
          }
          else {  //read from cats
            findcat = findcats(name, cats);
            if (findcat == NULL) {
              perror("can't find category in cats");
              free(line);
              free(name);
              freecat(used);
              return NULL;
            }
            const char * cat = chooseWord(name, cats);
            char * cat2 = malloc((strlen(cat) + 1) * sizeof(*cat2));
            strcpy(cat2, cat);
            used = addnewname(used, cat2);
            printf("%s", cat);
            if (n == 0) {  //-n exists
              deletename(cats, findcat, cat2);
            }
            free(cat2);
            free(name);
            name = NULL;
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
      //freecats(cats);
      perror("Unmatching underscore!");
      return NULL;
    }
  }
  free(line);
  return used;
}

int ifint(char * string) {
  int num;
  char * endptr;
  num = strtol(string, &endptr, 10);
  if (*endptr != '\0') {  //not int
    num = 0;
  }
  return num;
}

void deletename(catarray_t * cats, category_t * cat, char * name) {
  char ** newwords = NULL;
  if (cat->n_words <= 1) {
    free(cat->words[0]);
    free(cat->words);
    cat->words = NULL;
    cat->n_words = 0;
    return;
  }
  newwords = malloc((cat->n_words - 1) * sizeof(char *));
  int count = 0;
  for (int i = 0; i < cat->n_words; i++) {
    if (strcmp(cat->words[i], name) != 0) {  //save
      newwords[count] = malloc((strlen(cat->words[i]) + 1) * sizeof(char));
      strcpy(newwords[count], cat->words[i]);
      count++;
    }
  }
  freewords(cat);
  cat->words = newwords;
  cat->n_words--;
}
