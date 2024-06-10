#include "./Heap.h"

#include <iostream>

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

MaxHeap::MaxHeap(int default_max_size) {
  max_size = default_max_size;
  current_size = 0;
  heap = new int[max_size];
}

int MaxHeap::search(int key) {
  for (int i = 0; i < current_size; i++) {
    if (heap[i] == key) {
      return i;
    }
  }

  return -1;
}

int MaxHeap::get_item(int index) {
  if (index >= current_size || index < 0) {
    return -1;
  }

  return heap[index];
}

void MaxHeap::insert(int key) {
  current_size++;

  heap[current_size - 1] = key;

  int i = current_size - 1;
  while (heap[i] > heap[i / 2]) {
    swap(heap[i], heap[i / 2]);
    i = i / 2;
  }
}

void MaxHeap::remove_root() {
  heap[0] = heap[current_size - 1];
  current_size--;

  int i = 0;
  int right = 2 * i + 1;
  int left = 2 * i + 2;

  while (left < current_size || right < current_size) {
    if (left < current_size && heap[left] > heap[i]) {
      swap(heap[left], heap[i]);
      i = left;

      right = 2 * i + 1;
      left = 2 * i + 2;
    } else if (right < current_size && heap[right] > heap[i]) {
      swap(heap[right], heap[i]);
      i = right;

      right = 2 * i + 1;
      left = 2 * i + 2;
    } else {
      return;
    }
  }
}

void MaxHeap::inorder_print_helper(int idx) {
  if (idx > current_size - 1)
    return;

  inorder_print_helper(2 * idx + 1);
  std::cout << heap[idx] << " ";
  inorder_print_helper(2 * idx + 2);
}

void MaxHeap::inorder_print() {
  inorder_print_helper(0);
  std::cout << std::endl;
}

void MaxHeap::preorder_print_helper(int idx) {
  if (idx > current_size - 1)
    return;

  std::cout << heap[idx] << " ";
  preorder_print_helper(2 * idx + 1);
  preorder_print_helper(2 * idx + 2);
}

void MaxHeap::preorder_print() {
  preorder_print_helper(0);
  std::cout << std::endl;
}

MaxHeap::~MaxHeap() { delete[] heap; }
