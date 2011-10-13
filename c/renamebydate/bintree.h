#ifndef BINTREE_H
#define BINTREE_H

struct node_t {
  struct node_t * left;
  struct node_t * right;
  void * object;
};

struct tree_t {
  int (*compare) (void *, void *);
  struct node_t * root;
};

typedef struct tree_t * tree;

tree create_tree(int (*compare) (void *, void *));

void destruct_tree(tree t);

void add_object(tree t, void * object);

void walk_tree(tree t, void (*action) (void *));

#endif
