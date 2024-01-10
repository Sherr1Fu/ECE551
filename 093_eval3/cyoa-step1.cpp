#include <stdio.h>

#include <iostream>

#include "cyoa-step12.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./cyoa-step1 storyfile\n";
    return EXIT_FAILURE;
  }
  story mystory;
  //string file0 = "/usr/local/ece551/cyoa/";
  string file = "/story.txt";
  string file2(argv[1]);
  string file3 = file2 + file;
  mystory.readstory(file3.c_str());
  mystory.printstory();
  //string str;
  //str = readfile(argv[1]);
  //std::cout << str;
  return EXIT_SUCCESS;
}
