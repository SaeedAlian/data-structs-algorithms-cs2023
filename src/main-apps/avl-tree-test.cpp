#include "../AVLTree/AVLTree.h"
#include <iostream>

int main() {
  AVLTree avl;

  avl.insert(1);
  avl.insert(3);
  avl.insert(6);
  avl.insert(10);
  avl.insert(9);
  avl.insert(14);
  avl.insert(7);
  avl.insert(2);
  avl.insert(2);
  avl.insert(2);

  avl.traverse_level_order();
  avl.remove(9);
  avl.remove(11);
  avl.remove(2);
  avl.traverse_level_order();
  avl.traverse_inorder();

  std::cout << avl.search(9) << std::endl;
  std::cout << avl.search(7) << std::endl;
  std::cout << avl.search(11) << std::endl;
  std::cout << avl.search(2) << std::endl;
  return 0;
}
