#include "./AVLTree.h"

#include <iostream>

int AVLTree::get_max_int(int a, int b) { return (a > b) ? a : b; }

int AVLTree::get_node_height(AVLTreeNode *node) {
  if (node == NULL)
    return -1;

  return 1 + get_max_int(get_node_height(node->left_child),
                         get_node_height(node->right_child));
}

int AVLTree::get_balance_factor(AVLTreeNode *node) {
  if (node == NULL)
    return 0;

  return get_node_height(node->left_child) - get_node_height(node->right_child);
}

AVLTreeNode *AVLTree::left_rotation(AVLTreeNode *root) {
  AVLTreeNode *root_right = root->right_child;
  AVLTreeNode *sub_left_of_root_right = root_right->left_child;

  root->right_child = sub_left_of_root_right;
  root_right->left_child = root;

  root->height = get_node_height(root);
  root_right->height = get_node_height(root_right);

  return root_right;
}

AVLTreeNode *AVLTree::right_rotation(AVLTreeNode *root) {
  AVLTreeNode *root_left = root->left_child;
  AVLTreeNode *sub_right_of_root_left = root_left->right_child;

  root_left->right_child = root;
  root->left_child = sub_right_of_root_left;

  root->height = get_node_height(root);
  root_left->height = get_node_height(root_left);

  return root_left;
}

AVLTreeNode *AVLTree::new_node(int key) {
  AVLTreeNode *node = new AVLTreeNode();
  node->key = key;
  node->left_child = NULL;
  node->right_child = NULL;
  node->height = 0;

  return (node);
}

AVLTreeNode *AVLTree::insert_node_helper(AVLTreeNode *node, int key) {
  if (node == NULL) {
    return new_node(key);
  } else if (key < node->key) {
    node->left_child = insert_node_helper(node->left_child, key);
  } else if (key > node->key) {
    node->right_child = insert_node_helper(node->right_child, key);
  } else {
    return node;
  }

  node->height = get_node_height(node);
  int balance_fact = get_balance_factor(node);

  if (balance_fact > 1) {
    if (node->left_child->key > key) {
      return right_rotation(node);
    } else if (node->left_child->key < key) {
      node->left_child = left_rotation(node->left_child);
      return right_rotation(node);
    }
  }

  if (balance_fact < -1) {
    if (node->right_child->key < key) {
      return left_rotation(node);
    } else if (node->right_child->key > key) {
      node->right_child = right_rotation(node->right_child);
      return left_rotation(node);
    }
  }

  return node;
}

AVLTreeNode *AVLTree::find_inorder_successor(AVLTreeNode *node) {
  if (node == NULL) {
    return NULL;
  }

  if (node->right_child == NULL) {
    return node;
  }

  AVLTreeNode *current_node = node->right_child;

  while (current_node->left_child != NULL) {
    current_node = current_node->left_child;
  }

  return current_node;
}

AVLTreeNode *AVLTree::remove_node_helper(AVLTreeNode *node, int key) {
  if (node == NULL) {
    return node;
  } else if (key < node->key) {
    node->left_child = remove_node_helper(node->left_child, key);
  } else if (key > node->key) {
    node->right_child = remove_node_helper(node->right_child, key);
  } else {
    if (node->left_child == NULL && node->right_child == NULL) {
      delete node;
      node = NULL;
    } else if (node->left_child == NULL || node->right_child == NULL) {
      AVLTreeNode *non_empty_child =
          node->left_child != NULL ? node->left_child : node->right_child;

      AVLTreeNode *temp = node;
      node = non_empty_child;

      delete temp;
    } else {
      AVLTreeNode *inorder_successor = find_inorder_successor(node);

      node->key = inorder_successor->key;

      node->right_child =
          remove_node_helper(node->right_child, inorder_successor->key);
    }
  }

  if (node == NULL) {
    return node;
  }

  node->height = get_node_height(node);
  int balance_fact = get_balance_factor(node);

  if (balance_fact > 1) {
    if (get_balance_factor(node->left_child) >= 0) {
      return right_rotation(node);
    } else if (get_balance_factor(node->left_child) < 0) {
      node->left_child = left_rotation(node->left_child);
      return right_rotation(node);
    }
  }

  if (balance_fact < -1) {
    if (get_balance_factor(node->right_child) <= 0) {
      return left_rotation(node);
    } else if (get_balance_factor(node->right_child) > 0) {
      node->right_child = right_rotation(node->right_child);
      return left_rotation(node);
    }
  }

  return node;
}

AVLTreeNode *AVLTree::search_node_helper(AVLTreeNode *node, int key) {
  if (node == NULL) {
    return NULL;
  } else if (node->key == key) {
    return node;
  } else if (node->key > key) {
    if (node->left_child == NULL)
      return NULL;

    return search_node_helper(node->left_child, key);
  } else if (node->key < key) {
    if (node->right_child == NULL)
      return NULL;

    return search_node_helper(node->right_child, key);
  } else {
    return NULL;
  }
}

AVLTree::AVLTree() { root = NULL; }

int AVLTree::insert(int key) {
  root = insert_node_helper(root, key);

  if (root == NULL)
    return 0;

  return 1;
}

int AVLTree::remove(int key) {
  if (root == NULL)
    return 0;

  root = remove_node_helper(root, key);

  return 1;
}

int AVLTree::search(int key) {
  AVLTreeNode *searched_node = search_node_helper(root, key);
  if (searched_node == NULL)
    return 0;

  return 1;
}

void AVLTree::traverse_inorder_helper(AVLTreeNode *node) {
  if (node == NULL) {
    return;
  }

  traverse_inorder_helper(node->left_child);
  std::cout << node->key << "  ";
  traverse_inorder_helper(node->right_child);
}

void AVLTree::traverse_postorder_helper(AVLTreeNode *node) {
  if (node == NULL) {
    return;
  }

  traverse_inorder_helper(node->left_child);
  traverse_inorder_helper(node->right_child);
  std::cout << node->key << "  ";
}

void AVLTree::traverse_inorder() {
  if (root == NULL) {
    std::cout << "Tree is empty" << std::endl;
    return;
  }

  traverse_inorder_helper(root);
  std::cout << std::endl;
}

void AVLTree::traverse_postorder() {
  if (root == NULL) {
    std::cout << "Tree is empty" << std::endl;
    return;
  }

  traverse_postorder_helper(root);
  std::cout << std::endl;
}

void AVLTree::traverse_level_order() {
  if (root == NULL) {
    std::cout << "Tree is empty" << std::endl;
    return;
  }

  Queue<AVLTreeNode *> q;
  q.enqueue(root);
  AVLTreeNode *current_node;

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

  std::cout << std::endl;
}

AVLTree::~AVLTree() {
  if (root == NULL) {
    return;
  }

  Queue<AVLTreeNode *> q;

  q.enqueue(root);
  AVLTreeNode *current_node;

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
