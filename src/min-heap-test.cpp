#include "./Heap/Heap.h"

int main() {
  MinHeap h = MinHeap(256);

  h.insert(4);
  h.insert(2);
  h.insert(16);

  h.inorder_print();
  h.preorder_print();

  h.insert(5);
  h.insert(1);
  h.insert(12);

  h.inorder_print();
  h.preorder_print();

  return 0;
}
