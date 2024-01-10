#include "cyoa-step4.hpp"

#include <stdio.h>

#include <iostream>

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
  try {
    mystory.readstory(file3.c_str());
  }
  catch (const std::exception & e) {
    cerr << "ReadStory Error: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  try {
    mystory.playstory();
  }
  catch (const std::exception & e) {
    cerr << "PlayStory Error: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  /*if (mystory.verifystory() == EXIT_SUCCESS) {
    //mystory.playstory();
    mystory.findways();
  }
  else {
    return EXIT_FAILURE;
    }*/
  //string str;
  //str = readfile(argv[1]);
  //std::cout << str;
  return EXIT_SUCCESS;
}
