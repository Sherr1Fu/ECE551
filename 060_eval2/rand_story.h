#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use
FILE * openfile(FILE * f, char * filename);
void closefile(FILE * f);
int ParseCommand4(int argc, char ** argv, char ** words, char ** story, int n);

catarray_t * initcats(catarray_t * cats);
category_t * initcat(category_t * cat, char * name);
category_t * findcats(char * category, catarray_t * cats);
void freecats(catarray_t * cats);
void freecat(category_t * cat);
void freewords(category_t * cat);
category_t * addnewcat(catarray_t * cats, char * name);
category_t * addnewname(category_t * cat, char * word);
int ParseLine(char * string);
catarray_t * readwords(catarray_t * cats, FILE * stream);
category_t * printstory(catarray_t * cats, FILE * stream, category_t * used, int n);
int ifint(char * string);
void deletename(catarray_t * cats, category_t * cat, char * name);
#endif
