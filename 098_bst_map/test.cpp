#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "bstmap.h"
#include "map.h"

using namespace std;

int main(void) {
  BstMap<int, int> map;
  try {
    map.add(43, 1);
    map.add(54, 2);
    map.add(23, 3);
    map.add(55, 4);
    map.add(11, 5);
    map.add(25, 6);
    map.add(50, 7);
    map.add(48, 8);

    cout << "Look for: " << 43 << " value is: " << map.lookup(43) << endl;
    map.remove(43);
    cout << "Look for: " << 48 << " value is: " << map.lookup(48) << endl;
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
    cout << "Look for: " << 11 << " value is: " << map.lookup(11) << endl;
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
