#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"
typedef LinkedList<int> IntList;

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    std::srand(time(0));
    IntList il;
    int t = std::rand();
    il.addFront(t);
    assert(il.head->data == t);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    t++;
    il.addFront(t);
    assert(il.head->data == t);
    assert(il.head->next == il.tail);
    assert(il.head->prev == NULL);
    assert(il.tail->data == t - 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == il.head);
    assert(il.getSize() == 2);
  }
  // many more tester methods

  void testAddBack() {
    std::srand(time(0));
    IntList il;
    int t = std::rand();
    il.addBack(t);
    assert(il.head->data == t);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);

    il.addBack(t + 1);
    assert(il.head->data == t);
    assert(il.head->next == il.tail);
    assert(il.head->prev == NULL);
    assert(il.tail->prev == il.head);
    assert(il.tail->next == NULL);
    assert(il.tail->data == t + 1);
    assert(il.getSize() == 2);
  }
  void testCopy() {
    IntList il;
    IntList il4(il);
    assert(il4.head == NULL);
    assert(il4.tail == NULL);
    assert(il4.getSize() == 0);
    IntList il5 = il;
    assert(il5.head == NULL);
    assert(il5.tail == NULL);
    assert(il5.getSize() == 0);
    for (int i = 1; i < 4; i++) {
      il.addBack(i);
    }
    IntList il2(il);
    assert(il.getSize() == 3);
    assert(il2.getSize() == il.getSize());
    assert(il2.head->prev == NULL);
    assert(il2.head->data == 1);
    assert(il2.head->next->data == 2);
    assert(il2.head->next->next->data == 3);
    assert(il2.head->next->next->next == NULL);
    assert(il2.tail->next == NULL);
    assert(il2.tail->data == 3);
    assert(il2.tail->prev->data == 2);
    assert(il2.tail->prev->prev->data == 1);
    assert(il2.tail->prev->prev->prev == NULL);

    IntList il3;
    il3 = il;
    assert(il3.getSize() == il.getSize());
    assert(il3.head->prev == NULL);
    assert(il3.head->data == 1);
    assert(il3.head->next->data == 2);
    assert(il3.head->next->next->data == 3);
    assert(il3.head->next->next->next == NULL);
    assert(il3.tail->next == NULL);
    assert(il3.tail->data == 3);
    assert(il3.tail->prev->data == 2);
    assert(il3.tail->prev->prev->data == 1);
    assert(il3.tail->prev->prev->prev == NULL);

    il.addBack(4);
    assert(il2.head->next->next->next == NULL);
    assert(il3.head->next->next->next == NULL);
    il.addFront(5);
    assert(il2.tail->prev->prev->prev == NULL);
    assert(il3.tail->prev->prev->prev == NULL);

    IntList il6;
    il6.addBack(1);
    il3 = il6;
    assert(il3.getSize() == 1);
    assert(il3.head->data == 1);
    assert(il3.head->prev == NULL);
    assert(il3.tail->next == NULL);
    assert(il3.head == il3.tail);
  }
  void testRemove() {
    bool k;
    IntList il;
    //il.addBack(1);
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);
    il.addBack(4);
    il.addBack(1);
    k = il.remove(4);
    assert(k);
    assert(il.getSize() == 4);
    assert(il.head->next->next->next == il.tail);
    assert(il.tail->prev == il.head->next->next);
    k = il.remove(1);
    assert(k);
    assert(il.getSize() == 3);
    assert(il.head->data == 2);
    assert(il.head->next->data == 3);
    assert(il.head->next->next->data == 1);
    assert(il.head->next->next->next == NULL);
    assert(il.head->next->next = il.tail);
    assert(il.tail->prev->data == 3);
    assert(il.tail->prev->prev->data == 2);
    assert(il.tail->prev->prev->prev == NULL);
    k = il.remove(1);
    assert(k);
    assert(il.getSize() == 2);
    assert(il.head->next == il.tail);
    assert(il.head->data == 2);
    assert(il.head->next->data == 3);
    assert(il.head->next->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->prev == il.head);
    k = il.remove(3);
    assert(k);
    assert(il.getSize() == 1);
    assert(il.head == il.tail);
    assert(il.head->data == 2);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    k = il.remove(2);
    assert(k);
    assert(il.getSize() == 0);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    k = il.remove(1);
    assert(!k);
    assert(il.getSize() == 0);
    assert(il.head == NULL);
    assert(il.tail == NULL);
  }
};
int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopy();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
