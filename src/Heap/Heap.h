#pragma once

class MaxHeap {
private:
  int *heap;
  int max_size;
  int current_size;

  void inorder_print_helper(int idx);
  void preorder_print_helper(int idx);

public:
  MaxHeap(int default_max_size);
  int search(int key);
  int get_item(int index);
  void insert(int key);
  void remove_root();
  void inorder_print();
  void preorder_print();
  ~MaxHeap();
};

class MinHeap {
private:
  int *heap;
  int max_size;
  int current_size;

  void inorder_print_helper(int idx);
  void preorder_print_helper(int idx);

public:
  MinHeap(int default_max_size);
  int search(int key);
  int get_item(int index);
  void insert(int key);
  void remove_root();
  void inorder_print();
  void preorder_print();
  ~MinHeap();
};
