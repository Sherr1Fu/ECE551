#ifndef __STORY_STEP4__
#define __STORY_STEP4__
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class option {
 private:
  size_t destpage;
  string optiontext;
  string var;
  long int value;
  bool isval;
  bool isreveal;  //the option is revealed or not
  string s;       // unavailable

 public:
  option(size_t dest, string o, string v, long int val, bool is) :
      destpage(dest), optiontext(o), var(v), value(val), isval(is), s("<UNAVAILABLE>"){};
  string & getoption(map<string, long int> storyvar) {
    if (isval == false) {
      isreveal = true;
      return optiontext;
    }
    else {
      std::map<std::string, long int>::const_iterator it2 = storyvar.find(var);
      if (it2 == storyvar.end()) {
        throw std::runtime_error("Option variable not existed in story");
      }
      if (value == storyvar[var]) {
        isreveal = true;
        return optiontext;
      }
      else {
        isreveal = false;
        //s = "<UNAVAILABLE>";
        return s;
      }
    }
  };
  size_t getdest() const { return destpage; };
  bool getreveal() const { return isreveal; };
};

class page {
 protected:
  size_t number;
  char type;
  string text;
  vector<option> options;
  map<string, long int> pagevarmap;

 public:
  ~page(){};
  page(size_t n, char t, string & s) : number(n), type(t), text(s){};
  void addpagevar(string & var, long int value) {
    std::map<std::string, long int>::iterator it = pagevarmap.find(var);
    if (it != pagevarmap.end()) {
      //if var has existed
      throw std::runtime_error("Same variable already set for this page");
    }
    else {
      pagevarmap[var] = value;
    }
  }
  size_t getnumber() const { return number; };
  char gettype() const { return type; };
  size_t getopnum() const { return options.size(); };
  size_t selectoption(size_t i) const { return options[i].getdest(); };
  bool isoptionreveal(size_t i) const { return options[i].getreveal(); };
  void setvariable(map<string, long int> & map) {
    std::map<std::string, long int>::const_iterator it = pagevarmap.begin();
    while (it != pagevarmap.end()) {
      std::map<std::string, long int>::const_iterator it2 = map.find(it->first);
      if (it2 == map.end()) {
        throw std::runtime_error("Variable not existed");
      }
      map[it->first] = it->second;
      it++;
    }
  };
  void printpage(map<string, long int> & map) {
    cout << text << endl;
    if (type == 'N') {
      cout << "What would you like to do?" << endl;
      cout << endl;
      printoptions(map);
    }
    else if (type == 'W') {
      cout << "Congratulations! You have won. Hooray!" << endl;
    }
    else if (type == 'L') {
      cout << "Sorry, you have lost. Better luck next time!" << endl;
    }
    else {
      cerr << "page type is not valid" << endl;
    }
  };
  void printoptions(map<string, long int> & map) {
    for (size_t i = 0; i < options.size(); i++) {
      cout << " " << (i + 1) << ". " << options[i].getoption(map) << endl;
    }
  };
  void addoption(size_t dest, string & op) {
    ////wait for adding Error handling
    if (type != 'N') {
      throw std::runtime_error("Not allowed to add option to not N page");
      //cerr << "Not allowed to add option to not N page" << endl;
    }
    ////Error handling
    string s;
    option newOption(dest, op, s, 0, false);
    options.push_back(newOption);
  };
  void addvaroption(size_t dest, string & op, string & var, long int val) {
    if (type != 'N') {
      throw std::runtime_error("Not allowed to add option to not N page");
    }
    option newOption(dest, op, var, val, true);
    options.push_back(newOption);
  }
};

class story {
 private:
  vector<page> pages;
  map<string, long int> varmap;
  void parseline(string & s, string & path);
  ssize_t existedpage(size_t num) {
    for (size_t i = 0; i < pages.size(); i++) {
      if (num == pages[i].getnumber()) {
        return i;
      }
    }
    return -1;
  };
  map<size_t, size_t> buildmap() {
    map<size_t, size_t> pagesmap;
    for (size_t i = 0; i < pages.size(); i++) {
      pagesmap[pages[i].getnumber()] = i;
    }
    return pagesmap;
  };
  void findwayshelper(size_t current, vector<bool> visited, vector<size_t> path) {
    visited[current] = true;
    path.push_back(current);
    if (pages[current].gettype() == 'W') {
      for (size_t i = 0; i < path.size() - 1; i++) {
        cout << pages[path[i]].getnumber();
        for (size_t j = 0; j < pages[path[i]].getopnum(); j++) {
          if (pages[path[i]].selectoption(j) == pages[path[i + 1]].getnumber()) {
            cout << '(' << j + 1 << ')' << ',';
            break;
          }
        }
      }
      cout << pages[current].getnumber() << "(win)" << endl;
    }
    else {
      for (size_t i = 0; i < pages[current].getopnum(); i++) {
        int nextpage = pages[current].selectoption(i);
        if (!visited[nextpage]) {
          findwayshelper(nextpage, visited, path);
        }
      }
    }
    path.pop_back();
    visited[current] = false;
  }

 public:
  ~story() {}
  void addvarmap(string & s) {
    std::map<std::string, long int>::iterator it = varmap.find(s);
    if (it == varmap.end()) {
      varmap[s] = 0;
      //cout << "add to var map successfully" << endl;
    }
  }
  void findways() {
    size_t startpage = 0;
    vector<bool> visited(pages.size(), false);
    vector<size_t> path;
    findwayshelper(startpage, visited, path);
  }
  void playstory() {
    map<size_t, size_t> pagesmap = buildmap();
    size_t pagei = 0;
    //test
    // map<string, long int>::const_iterator it = varmap.begin();
    //while (it != varmap.end()) {
    //cout << "key: " << it->first << "value: " << it->second << endl;
    //it++;
    //}
    //
    while (pages[pagei].gettype() == 'N') {
      pages[pagei].setvariable(varmap);
      pages[pagei].printpage(varmap);
      while (true) {
        size_t choice;
        cin >> choice;
        if (!cin.good()) {
          cin.clear();
          cout << "That is not a valid choice, please try again" << endl;
          continue;
        }
        if (choice <= 0 || choice > pages[pagei].getopnum()) {
          cout << "That is not a valid choice, please try again" << endl;
          continue;
        }
        if (pages[pagei].isoptionreveal(choice - 1) == false) {
          cout << "That choice is not available at this time, please try again" << endl;
          continue;
        }
        pagei = pagesmap[pages[pagei].selectoption(choice - 1)];
        break;
      }
    }
    pages[pagei].printpage(varmap);
    return;
  }
  int verifystory() {
    size_t isW = 0;
    size_t isL = 0;
    map<size_t, size_t> pagemap;
    vector<size_t> referpage;
    for (size_t i = 0; i < pages.size(); i++) {
      char type = pages[i].gettype();
      size_t number = pages[i].getnumber();
      //pagemap.push_back(number);         //pages I have
      pagemap[number] = 0;
      if (type == 'W') {
        isW++;
      }
      else if (type == 'L') {
        isL++;
      }
      else if (type == 'N') {
        for (size_t j = 0; j < pages[i].getopnum(); j++) {
          referpage.push_back(pages[i].selectoption(j));  //pages I referenced
        }
      }
    }
    if (isW == 0 || isL == 0) {  //no Wpage or Lpage
      return EXIT_FAILURE;
    }
    for (size_t i = 0; i < referpage.size(); i++) {
      map<size_t, size_t>::iterator it = pagemap.find(referpage[i]);
      //pagemap.find(referpage[i]);
      if (it == pagemap.end()) {
        return EXIT_FAILURE;
      }
      else {
        it->second++;
      }
    }
    map<size_t, size_t>::iterator it;
    for (it = pagemap.begin(); it != pagemap.end(); it++) {
      if (it->second == 0 && it->first != 0) {
        return EXIT_FAILURE;
      }
    }
    return EXIT_SUCCESS;
  };
  int readstory(const char * filename) {
    ifstream infile(filename);
    string s;
    if (!infile.is_open()) {
      throw std::runtime_error("Unable to open story file.");
      //cerr << "Unable to open file:" << filename << endl;
      //return EXIT_FAILURE;
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
  };
  void printstory() {
    for (size_t i = 0; i < pages.size(); i++) {
      cout << "Page " << pages[i].getnumber() << endl;
      cout << "==========" << endl;
      pages[i].printpage(varmap);
    }
  };
};

string readfile(const char * filename) {
  ifstream infile(filename);
  //infile.open(filename);
  if (!infile.is_open()) {  //if failed to open file
    throw std::runtime_error("Unable to open file.");
    //cerr << "Unable to open file:" << filename << endl;
    //return "";
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
void story::parseline(string & s, string & path) {
  //page or choice
  istringstream line(s);
  size_t number, destpage;
  char at, type, colon;
  string filename, text;
  string pagefilename;
  string remaining;
  line >> number >> at >> type >> colon >> filename;
  //page  0@N:page0.txt
  //ifpage
  if (at == '@' && (type == 'N' || type == 'W' || type == 'L') && colon == ':') {
    line >> remaining;
    if (!remaining.empty()) {
      throw std::runtime_error("Input format is not valid");
    }
    pagefilename = replaceFileName(path, filename);
    text = readfile(pagefilename.c_str());

    page Newpage(number, type, text);
    if (existedpage(number) == -1) {
      pages.push_back(Newpage);
      //  cout << "addpage successfully" << endl;
    }
    else {
      throw std::runtime_error("Two page have the same number");
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
      if (pages[index].gettype() == 'N') {
        pages[index].addoption(destpage, text);
        //cout << text << endl;
        //cout << "addoption successfully" << endl;
        return;
      }
      else {
        throw std::runtime_error("Adding option to not Npage");
      }
    }
    throw std::runtime_error("Page is not existed");
    //cerr << "page " << number << " is not existed" << endl;
  }
  istringstream line3(s);
  string var;
  long int value;
  //4$pastry=1
  line3 >> number >> colon;
  if (colon == '$') {
    getline(line3, var, '=');
    if (!(line3 >> value)) {
      throw std::runtime_error("Invalid input format");
    }
    line3 >> remaining;
    if (!remaining.empty()) {
      throw std::runtime_error("Input format is not valid");
    }
    ssize_t index = existedpage(number);
    if (index >= 0) {
      addvarmap(var);
      //cout << "have used addvarmap" << endl;
      try {
        pages[index].addpagevar(var, value);
        //cout << "addpagevar successfully" << endl;
      }
      catch (const std::exception & e) {
        cerr << "Error: " << e.what() << endl;
        throw std::runtime_error("Failed to add to page varmap");
      }
      return;
    }
    else {
      throw std::runtime_error("Page is not existed");
    }
  }
  istringstream line4(s);
  char colon2, colon3, colon4;
  //8[pastry=1]:12:Offer the dragon the chocolate croissant.
  line4 >> number >> colon;
  if (colon == '[') {
    getline(line4, var, '=');
    if (!(line4 >> value >> colon2 >> colon3 >> destpage >> colon4)) {
      throw std::runtime_error("Invalid input format");
    }
    if (colon2 != ']' || colon3 != ':' || colon4 != ':') {
      throw std::runtime_error("Invalid input format");
    }
    getline(line4, text);
    ssize_t index = existedpage(number);
    if (index >= 0) {
      if (pages[index].gettype() == 'N') {
        try {
          pages[index].addvaroption(destpage, text, var, value);
          //cout << text << endl;
          //cout << "addvaroption successfully" << endl;
        }
        catch (const std::exception & e) {
          cerr << "Error: " << e.what() << endl;
          throw std::runtime_error("Failed to add varoption");
        }
        return;
      }
    }
    else {
      throw std::runtime_error("Page is not existed");
    }
  }
  throw std::runtime_error("Input format is not valid");
}

#endif
