#include "rbtree.h"
#include <stdlib.h>

// 좌회전
void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil)
    y->left->parent = x;
  else
    x->right = t->nil;  

  y->parent = x->parent;
  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}

// 우회전
void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  x->left = y->right;
  if (y->right != t->nil)
    y->right->parent = x;
  else
    x->left = t->nil;  

  y->parent = x->parent;
  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;

  y->right = x;
  x->parent = y;
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
  // caes 1: z의 부모가 빨간색인 경우
  while (z->parent->color == RBTREE_RED) {
    if (z->parent == z->parent->parent->left) {
      node_t *y = z->parent->parent->right;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
      // case 2: z의 부모가 z의 부모의 오른쪽 자식인 경우
    } else {
      node_t *y = z->parent->parent->left;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;

        // case 3: z의 부모가 z의 부모의 왼쪽 자식인 경우
      } else {
        if (z == z->parent->left) {
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