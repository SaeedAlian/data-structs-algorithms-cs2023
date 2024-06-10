#include "./CDLinkedList/CDLinkedList.h"
#include <iostream>

int main() {
  CDLinkedList ll = CDLinkedList();
  ll.push(2);
  ll.push(8);
  ll.push(5);
  ll.print();
  ll.push(11);
  ll.append(10);

  ll.print();
  CDLLNode *n = ll.search(5);
  std::cout << n->key << std::endl;
  ll.push_at(n, 123);
  ll.print();

  ll.remove(n);
  //
  ll.print();
  //
  // std::cout << ll.search(2) << std::endl;
  // std::cout << ll.search(11) << std::endl;

  return 0;
}
