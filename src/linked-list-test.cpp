#include "./LinkedList/LinkedList.h"
#include <iostream>

int main() {
  LinkedList ll = LinkedList();
  ll.push(2);
  ll.push(8);
  ll.push(5);
  ll.print();
  ll.push(11);

  ll.pop();
  ll.pop();

  ll.print();

  std::cout << ll.search(2) << std::endl;
  std::cout << ll.search(11) << std::endl;

  return 0;
}
