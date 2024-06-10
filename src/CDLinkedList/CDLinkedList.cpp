#include "./CDLinkedList.h"

#include <iostream>

CDLinkedList::CDLinkedList() {
  head = NULL;
  tail = NULL;
}

/*
 * It will search through the linked list and then returns the
 * pointer to the node which its key is equal to the input key
 * If the node doesn't exist then it will return the NULL pointer
 *
 * @param key: int
 * @return CDLLNode* | NULL
 */
CDLLNode *CDLinkedList::search(int key) {
  CDLLNode *current = head;

  while (current != NULL) {
    if (current->key == key) {
      return current;
    } else if (current == tail && current->key != key) {
      return NULL;
    }

    current = current->next;
  }

  return NULL;
}

/*
 * It will push a new node with the input key at the
 * head of linked list, and it will return the pointer to
 * the added node
 * If it was unsuccessful it will return the NULL pointer
 *
 * @param key: int
 * @return CDLLNode* | NULL
 */
CDLLNode *CDLinkedList::push(int key) {
  CDLLNode *new_node = new CDLLNode;

  if (new_node == NULL) {
    std::cout << "Memory is out of space." << std::endl;
    return NULL;
  }

  new_node->key = key;

  if (head == NULL && tail == NULL) {
    head = new_node;
    tail = new_node;
    new_node->next = head;
    new_node->prev = tail;
  } else {
    new_node->next = head;
    new_node->prev = tail;
    head = new_node;
  }

  return new_node;
}

/*
 * It will push a new node with the input key at the rear of
 * input at_node, and it will return the pointer to the new node
 * If it was unsuccessful it will return the NULL pointer
 *
 * @param at_node: CDLLNode*
 * @param key: int
 * @return CDLLNode* | NULL
 */
CDLLNode *CDLinkedList::push_at(CDLLNode *at_node, int key) {
  if (head == NULL && tail == NULL) {
    std::cout << "LinkedList is empty, use push instead." << std::endl;
    return NULL;
  }

  CDLLNode *new_node = new CDLLNode;

  if (new_node == NULL) {
    std::cout << "Memory is out of space." << std::endl;
    return NULL;
  }

  new_node->key = key;

  CDLLNode *current = head;

  while (current->next != at_node) {
    if (current->next == tail && current->next != at_node) {
      break;
    }

    current = current->next;
  }

  if (current->next == at_node) {
    new_node->next = current->next;
    new_node->prev = current;
    current->next->prev = new_node;
    current->next = new_node;
    return new_node;
  }

  std::cout << "Node not found." << std::endl;
  return NULL;
}

/*
 * It will append a new node with the input key at the
 * tail of linked list, and it will return the pointer to
 * the added node
 * If it was unsuccessful it will return the NULL pointer
 *
 * @param key: int
 * @return CDLLNode* | NULL
 */
CDLLNode *CDLinkedList::append(int key) {
  CDLLNode *new_node = new CDLLNode;

  if (new_node == NULL) {
    std::cout << "Memory is out of space." << std::endl;
    return NULL;
  }

  new_node->key = key;

  if (head == NULL && tail == NULL) {
    head = new_node;
    tail = new_node;
    new_node->next = head;
    new_node->prev = tail;
  } else {
    new_node->next = head;
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
  }

  return new_node;
}

/*
 * It will remove the head of linked list, if the linked list is not empty
 *
 * @return void
 */
void CDLinkedList::pop() {
  if (head == NULL && tail == NULL) {
    std::cout << "LinkedList is empty." << std::endl;
    return;
  }

  CDLLNode *temp = head;

  if (tail == head && head->next == head->prev) {
    tail = head = NULL;
  } else {
    head = head->next;
    head->prev = tail;
  }

  delete temp;
}

/*
 * It will remove the tail of linked list, if the linked list is not empty
 *
 * @return void
 */
void CDLinkedList::unshift() {
  if (head == NULL && tail == NULL) {
    std::cout << "LinkedList is empty." << std::endl;
    return;
  }

  CDLLNode *temp = tail;

  if (tail == head && head->next == head->prev) {
    tail = head = NULL;
  } else {
    tail = tail->prev;
    head->prev = tail;
  }

  delete temp;
}

/*
 * It will remove the input node of linked list, if it exists
 *
 * @return void
 */
void CDLinkedList::remove(CDLLNode *node) {
  if (head == NULL && tail == NULL) {
    std::cout << "LinkedList is empty." << std::endl;
    return;
  }

  CDLLNode *temp = NULL;

  if (tail == head && head->next == head->prev) {
    temp = head;
    head = tail = NULL;
    delete temp;
    return;
  }

  CDLLNode *current = head;

  while (current != node) {
    if (current == tail && current != node) {
      break;
    }

    current = current->next;
  }

  if (current == node) {
    temp = current;
    std::cout << current->key << std::endl;
    std::cout << current->prev->key << std::endl;
    std::cout << current->next->key << std::endl;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete temp;
    return;
  }

  std::cout << "Node not found." << std::endl;
  return;
}

/*
 * It will print the linked list
 *
 * @return void
 */
void CDLinkedList::print() {
  CDLLNode *current = head;

  std::cout << "LinkedList: " << std::endl;

  std::cout << "'" << tail->key << "'"
            << " <--> ";

  while (current != NULL) {
    std::cout << current->key << " <--> ";
    if (current == tail) {
      break;
    }
    current = current->next;
  }

  std::cout << "'" << head->key << "'";
  std::cout << std::endl;
}

CDLinkedList::~CDLinkedList() {
  CDLLNode *current = head;

  while (current != NULL) {
    CDLLNode *temp = current;

    if (current == tail) {
      delete temp;
      return;
    }

    current = current->next;
    delete temp;
  }
}
