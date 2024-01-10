#ifndef __STORY_STEP1__
#define __STORY_STEP1__
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class option {
 private:
  size_t destpage;
  string optiontext;

 public:
  option(size_t dest, string o) : destpage(dest), optiontext(o){};
  string & getoption() { return optiontext; };
};

class page {
 protected:
  size_t number;
  char type;
  string text;
  //vector<option> options;
 public:
  virtual ~page(){};
  page(size_t n, char t, string & s) : number(n), type(t), text(s){};
  size_t getnumber() { return number; }
  char gettype() { return type; }
  virtual void printpage() = 0;
  virtual void addoption(size_t dest, string & op) = 0;
};

class story {
 private:
  vector<page *> pages;
  void parseline(string & s, string & path);
  ssize_t existedpage(size_t num);

 public:
  ~story() {
    for (size_t i = 0; i < pages.size(); i++) {
      delete pages[i];
    }
  }
  int readstory(const char * filename);
  virtual void printstory();
};

class Npage : public page {
 private:
  vector<option *> options;

 public:
  Npage(size_t n, char t, string & s) : page(n, t, s){};
  virtual ~Npage() {
    for (size_t i = 0; i < options.size(); i++) {
      delete options[i];
    }
  };
  virtual void printpage();
  void printoptions() {
    for (size_t i = 0; i < options.size(); i++) {
      cout << " " << (i + 1) << ". " << options[i]->getoption() << endl;
    }
  };
  void addoption(size_t dest, string & op) {
    //class option newOption(dest, op);
    //cout << newOption.getoption() << endl;
    options.push_back(new option(dest, op));
    //cout << options[options.size() - 1]->getoption() << endl;
  };
};
class Wpage : public page {
 public:
  virtual ~Wpage(){};
  virtual void printpage();
  Wpage(size_t n, char t, string & s) : page(n, t, s){};
  virtual void addoption(size_t dest, string & op){};
};
class Lpage : public page {
 public:
  virtual ~Lpage(){};
  Lpage(size_t n, char t, string & s) : page(n, t, s){};
  virtual void printpage();
  virtual void addoption(size_t dest, string & op){};
};
string readfile(const char * filename) {
  ifstream infile(filename);
  //infile.open(filename);
  if (!infile.is_open()) {
    cerr << "Unable to open file:" << filename << endl;
    return "";
  }
  stringstream filetext;
  char ch;
  while (infile.get(ch)) {
    filetext.put(ch);
  }
  infile.close();
  return filetext.str();
}

string replaceFileName(const string & filePath, const string & newFileName) {
  size_t lastSlashPos = filePath.find_last_of('/');
  if (lastSlashPos != string::npos) {
    return filePath.substr(0, lastSlashPos + 1) + newFileName;
  }
  else {
    return newFileName;
  }
}

void story::printstory() {
  for (size_t i = 0; i < pages.size(); i++) {
    cout << "Page " << pages[i]->getnumber() << endl;
    cout << "==========" << endl;
    pages[i]->printpage();
  }
}
int story::readstory(const char * filename) {
  ifstream infile(filename);
  string s;
  if (!infile.is_open()) {
    cerr << "Unable to open file:" << filename << endl;
    return EXIT_FAILURE;
  }
  string path(filename);
  while (getline(infile, s)) {
    //cout << s << endl;  /////
    if (s.empty()) {
      continue;
    }
    parseline(s, path);
  }
  infile.close();
  return EXIT_SUCCESS;
}
ssize_t story::existedpage(size_t num) {
  for (size_t i = 0; i < pages.size(); i++) {
    if (num == pages[i]->getnumber()) {
      return i;
    }
  }
  return -1;
}
void story::parseline(string & s, string & path) {
  //page or choice
  istringstream line(s);
  size_t number, destpage;
  char at, type, colon;
  string filename, text;
  string pagefilename;
  line >> number >> at >> type >> colon >> filename;
  //page  0@N:page0.txt
  //ifpage
  if (at == '@' && (type == 'N' || type == 'W' || type == 'L') && colon == ':') {
    pagefilename = replaceFileName(path, filename);
    text = readfile(pagefilename.c_str());
    page * Newpage;
    if (type == 'N') {
      Newpage = new Npage(number, type, text);
    }
    else if (type == 'W') {
      Newpage = new Wpage(number, type, text);
    }
    else if (type == 'L') {
      Newpage = new Lpage(number, type, text);
    }
    if (existedpage(number) == -1) {
      pages.push_back(Newpage);
      //  cout << "addpage successfully" << endl;
    }
    else {
      //throw"two page have the same number";
      cerr << "two page have the same number" << endl;
    }
    return;
  }
  istringstream line2(s);
  line2 >> number >> at >> destpage >> colon;
  //ifchoice 0:1:Give the dragon a cookie.
  getline(line2, text);
  if (at == ':' && colon == ':') {
    ssize_t index = existedpage(number);
    if (index >= 0) {
      if (pages[index]->gettype() == 'N') {
        pages[index]->addoption(destpage, text);
        //cout << text << endl;
        //cout << "addoption successfully" << endl;
        return;
      }
    }
    cerr << "page " << number << " is not existed" << endl;
  }
}

/*void Npage::printoptions() {
  for (size_t i = 0; i < options.size(); i++) {
    //cout << " " << (i + 1) << ". " << options[i]->getoption() << endl;
    cout << options[i]->getoption() << endl;
  }
  }*/

void Npage::printpage() {
  cout << text << endl;
  //cout << endl;
  cout << "What would you like to do?" << endl;
  cout << endl;
  printoptions();
}
void Wpage::printpage() {
  cout << text << endl;
  //cout << endl;
  cout << "Congratulations! You have won. Hooray!" << endl;
}
void Lpage::printpage() {
  cout << text << endl;
  //cout << endl;
  cout << "Sorry, you have lost. Better luck next time!" << endl;
}
#endif
