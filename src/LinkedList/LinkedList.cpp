#include "./LinkedList.h"

#include <iostream>

LinkedList::LinkedList() { head = NULL; }

LLNode *LinkedList::search(int key) {
  LLNode *current = head;

  while (current != NULL) {
    if (current->key == key) {
      return current;
    }

    current = current->next;
  }

  return NULL;
}

void LinkedList::push(int key) {
  LLNode *new_node = new LLNode;

  if (new_node == NULL) {
    std::cout << "Memory is out of space." << std::endl;
    return;
  }

  new_node->key = key;
  new_node->next = head;
  head = new_node;
}

void LinkedList::pop() {
  if (head == NULL) {
    std::cout << "LinkedList is empty." << std::endl;
    return;
  }

  LLNode *temp = head;
  head = head->next;

  delete temp;
}

void LinkedList::print() {
  LLNode *current = head;

  std::cout << "LinkedList: " << std::endl;

  while (current != NULL) {
    std::cout << current->key << " --> ";
    current = current->next;
  }

  std::cout << "NULL";
  std::cout << std::endl;
}

LinkedList::~LinkedList() {
  LLNode *current = head;

  while (current != NULL) {
    LLNode *temp = current;
    current = current->next;
    delete temp;
  }
}
