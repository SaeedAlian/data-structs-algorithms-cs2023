#include "./BinaryTree/BinaryTree.h"

int main() {
  BinaryTree t = BinaryTree();

  t.add(1);
  t.add(2);
  t.add(4);
  t.add(6);
  t.add(3);
  t.add(2);
  t.add(11);
  t.add(7);
  t.add(13);

  t.traverse();

  t.remove(4);
  t.remove(3);

  t.traverse();
  t.remove(11);
  t.remove(6);

  t.traverse();
  return 0;
}
