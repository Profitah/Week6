#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

// 외부 함수 선언
void rbtree_insert_fixup(rbtree *t, node_t *z);
void left_rotate(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *x);

// 트리 초기화
rbtree *new_rbtree(void) {
  rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
  if (!t) return NULL;

  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  if (!nil) {
    free(t);
    return NULL;
  }

  nil->color = RBTREE_BLACK;
  nil->left = nil->right = nil->parent = NULL;

  t->nil = nil;
  t->root = t->nil;

  return t;
}

// 트리 메모리 해제
void delete_rbtree(rbtree *t) {
  free(t->nil);
  free(t);
}

// 노드 삽입
node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  if (!z) return t->nil;

  z->key = key;
  z->color = RBTREE_RED;
  z->left = z->right = z->parent = t->nil;

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

  rbtree_insert_fixup(t, z);
  t->root->color = RBTREE_BLACK;

  return z;
}

// 노드 탐색
node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *p = t->root;

  while (p != t->nil) {
    if (key == p->key) {
      return p;
    } else if (key < p->key) {
      p = p->left;
    } else {
      p = p->right;
    }
  }

  return t->nil;
}

// 최소값
q = rbtree_find(t, wrong_key);
#ifdef SENTINEL
  assert(q == t->nil);
#else
  assert(q == NULL);
#endif

node_t *rbtree_min(const rbtree *t) {
  node_t *p = t->root;
  if (p == t->nil) return t->nil;

  while (p->left != t->nil) {
    p = p->left;
  }
  return p;
}

// 최대값
node_t *rbtree_max(const rbtree *t) {
  node_t *p = t->root;
  if (p == t->nil) return t->nil;

  while (p->right != t->nil) {
    p = p->right;
  }
  return p;
}

// 삭제 
int rbtree_erase(rbtree *t, node_t *p) {
  return 0;
}

// 배열로 변환 
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  return 0;
}