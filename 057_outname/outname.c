#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * outputName;
  char * str;
  outputName = malloc(sizeof(char) * (strlen(inputName) + strlen(".counts") + 1));
  strcpy(outputName, inputName);
  str = outputName + strlen(inputName);
  strcpy(str, ".counts");
  return outputName;
}
