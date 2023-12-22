#include "./BinaryTree.h"

#include <iostream>

BinaryTree::BinaryTree() { root = NULL; }

/*
 * Creates a node and adds it to the tree.
 * Returns 1 if it was successful, otherwise returns 0
 */
int BinaryTree::add(int key) {
  TreeNode *new_node = new TreeNode;
  new_node->key = key;
  new_node->right_child = NULL;
  new_node->left_child = NULL;

  if (root == NULL) {
    root = new_node;
    return 1;
  }

  Queue<TreeNode *> q;

  q.enqueue(root);
  TreeNode *current_node = NULL;

  while (!q.is_empty()) {
    q.dequeue(current_node);

    if (current_node->left_child == NULL) {
      current_node->left_child = new_node;
      return 1;
    }

    if (current_node->right_child == NULL) {
      current_node->right_child = new_node;
      return 1;
    }

    q.enqueue(current_node->left_child);
    q.enqueue(current_node->right_child);
  }

  delete new_node;
  return 0;
}

void BinaryTree::remove_deepest_node(TreeNode *node) {
  Queue<TreeNode *> q;

  q.enqueue(root);
  TreeNode *current_node = NULL;

  while (!q.is_empty()) {
    q.dequeue(current_node);

    if (current_node == node) {
      current_node = NULL;
      delete (node);
      return;
    }

    if (current_node->left_child) {
      if (current_node->left_child == node) {
        current_node->left_child = NULL;
        delete (node);
        return;
      } else {
        q.enqueue(current_node->left_child);
      }
    }

    if (current_node->right_child) {
      if (current_node->right_child == node) {
        current_node->right_child = NULL;
        delete (node);
        return;
      } else {
        q.enqueue(current_node->right_child);
      }
    }
  }
}

/*
 * Removes a node from the tree.
 * Returns 1 if it was successful, otherwise returns 0
 */
int BinaryTree::remove(int key) {
  if (root == NULL) {
    return 0;
  }

  if (root->right_child == NULL && root->left_child == NULL) {
    if (root->key == key) {
      root = NULL;
      return 1;
    } else {
      return 0;
    }
  }

  Queue<TreeNode *> q;
  q.enqueue(root);

  TreeNode *current_node = NULL;
  TreeNode *key_node = NULL;

  while (!q.is_empty()) {
    q.dequeue(current_node);

    if (current_node->key == key) {
      key_node = current_node;
    }

    if (current_node->left_child) {
      q.enqueue(current_node->left_child);
    }

    if (current_node->right_child) {
      q.enqueue(current_node->right_child);
    }
  }

  if (key_node != NULL) {
    int deepest_node_key = current_node->key;
    remove_deepest_node(current_node);
    key_node->key = deepest_node_key;
    return 1;
  }

  return 0;
}

/*
 * Traverse the tree in level order
 */
void BinaryTree::traverse() {
  if (root == NULL) {
    std::cout << "Tree is empty" << std::endl;
    return;
  }

  Queue<TreeNode *> q;

  q.enqueue(root);
  TreeNode *current_node;

  std::cout << "Tree: " << std::endl;

  while (!q.is_empty()) {
    q.dequeue(current_node);

    std::cout << current_node->key << "  ";

    if (current_node->left_child) {
      q.enqueue(current_node->left_child);
    }

    if (current_node->right_child) {
      q.enqueue(current_node->right_child);
    }
  }
}

BinaryTree::~BinaryTree() {
  if (root == NULL) {
    return;
  }

  Queue<TreeNode *> q;

  q.enqueue(root);
  TreeNode *current_node;

  while (!q.is_empty()) {
    q.dequeue(current_node);

    if (current_node->left_child) {
      q.enqueue(current_node->left_child);
    }

    if (current_node->right_child) {
      q.enqueue(current_node->right_child);
    }

    delete current_node;
  }
}
