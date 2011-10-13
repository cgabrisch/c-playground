#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

tree create_tree(int (*compare) (void *, void *)) {
  tree t = (tree) malloc(sizeof(struct tree_t));

  t->compare = compare;
  t->root = NULL;

  return t;
}

typedef struct node_t * node;

void destruct_node(node n) {
  if (n == NULL) {
    return;
  }

  destruct_node(n->left);
  destruct_node(n->right);

  free(n->object);
  free(n);
}

void destruct_tree(tree t) {
  if (t == NULL) {
    return;
  }

  destruct_node(t->root);
  free(t);
}

node create_node(void) {
  node n = (node) malloc(sizeof(struct node_t));

  n->left = n->right = n->object = NULL;

  return n;
}

void add(node n, void * object, int (*comp) (void *, void *)) {
  int result = (*comp) (object, n->object);

  if (result < 0) { 
    if (n->left) {
      add(n->left, object, comp);
    } else {
      n->left = create_node();
      n->left->object = object;
    }
  } else if (result > 0) {
    if (n->right) {
      add(n->right, object, comp);
    } else {
      n->right = create_node();
      n->right->object = object;
    }
  } else {
    n->object = object;
  }
}

void add_object(tree t, void * object) {
  if (t->root) {
    add(t->root, object, t->compare);
  } else {
    t->root = create_node();
    t->root->object = object;
  }
}

void walk(node n, void (*action) (void *)) {
  if (n->left) {
    walk(n->left, action);
  } 

  (*action) (n->object);

  if (n->right) {
    walk(n->right, action);
  }
}

void walk_tree(tree t, void (*action) (void *)) {
  if (t->root) {
    walk(t->root, action);
  }
}

