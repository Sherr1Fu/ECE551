#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "bstset.h"
#include "set.h"

using namespace std;

int main(void) {
  BstSet<int> set;
  try {
    set.add(43);
    set.add(54);
    set.add(23);
    set.add(55);
    set.add(11);
    set.add(25);
    set.add(50);
    set.add(48);

    cout << "Look for: " << 43 << " value is: " << set.contains(43) << endl;
    set.remove(43);
    /*cout << "Look for: " << 48 << " value is: " << map.lookup(48) << endl;
    map.add(43, 5);
    cout << "Look for: " << 43 << " value is: " << map.lookup(43) << endl;

    map.remove(11);
    cout << "Look for: " << 11 << " value is: " << map.lookup(11) << endl;

    map.remove(11);
    map.remove(43);
    map.remove(54);
    map.remove(23);
    map.remove(55);
    map.remove(19);
    //cout << "Look for: " << 11 << " value is: " << map.lookup(11) << endl;
    map.add(11, 5);
    cout << "Look for: " << 11 << " value is: " << map.lookup(11) << endl;*/
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
