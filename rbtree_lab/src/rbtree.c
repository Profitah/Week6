#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>
void rbtree_insert_fixup(rbtree *t, node_t *z);
void left_rotate(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *x);
rbtree *new_rbtree(void) {
  rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil_node = (node_t*)calloc(1, sizeof(node_t));
  nil_node->color = RBTREE_BLACK;
  nil_node->left = nil_node->right = nil_node->parent = nil_node;
  t->nil = nil_node;
  t->root = nil_node;
  return t;
}
void delete_rbtree(rbtree *t) {
  if (t == NULL) return;
  if (t->nil != NULL) {
    free(t->nil);
  }
  free(t);
}
node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *z = (node_t *)malloc(sizeof(node_t));
  if (z == NULL) return NULL;
  z->key = key;
  z->color = RBTREE_RED;
  z->parent = z->left = z->right = t->nil;
  node_t *y = t->nil;
  node_t *x = t->root;
  while (x != t->nil) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (y == t->nil) {
    t->root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
  z->left = t->nil;
  z->right = t->nil;
  if (z->parent == t->nil) {
    z->color = RBTREE_BLACK;
    return z;
  }
  rbtree_insert_fixup(t, z);
  if (z->left == NULL || z->right == NULL) {
    printf("ERROR: z has NULL children!\n");
  }
  return z;
}
void left_rotate(rbtree *t, node_t *x){
  node_t *y = x->right;
  x->right = y->left;
  if(y->left != t->nil){
    y->left->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == t->nil){
    t->root = y;
  } else if (x == x->parent->left){
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}
void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  x->left = y->right;
  if(y->right != t->nil){
    y->right->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == t->nil){
    t->root = y;
  } else if (x == x->parent->right)
  {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}
void rbtree_insert_fixup(rbtree *t, node_t *z) {
  while(z->parent->color == RBTREE_RED){
    if (z->parent == z->parent->parent->left){
      node_t *y = z->parent->parent->right;
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } else {
        if(z == z->parent->right){
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
    else {
      node_t *y = z->parent->parent->left;
      if(y->color ==RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }else{
        if (z == z->parent->left)
        {
          z = z->parent;
          right_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}
node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *cur = t->root;
  while (cur != t->nil)
  {
    if(key == cur->key){
      return cur;
    } else {
      cur = (key < cur->key) ? cur->left : cur->right;
    }
    return NULL;
  }
}
node_t *rbtree_min(const rbtree *t) {
  node_t *cur = t->root;
  while (cur->left != t->nil)
  {
    cur = cur->left;
  }
  return cur;
}
node_t *rbtree_max(const rbtree *t) {
  node_t *cur = t->root;
  while (cur->right != t->nil)
  {
    cur = cur->right;
  }
  return cur;
}
int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}