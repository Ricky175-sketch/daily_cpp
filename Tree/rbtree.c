#include <stdio.h>

typedef int KEY_TYPE;

typedef struct _rbtree_node
{
    unsigned char color;
    struct _rbtree_node *left;
    struct _rbtree_node *right;
    struct _rbtree_node *parent;

    KEY_TYPE key;
    void *value;
} rbtree_node;

typedef struct _rbtree
{
    rbtree_node *root;
    rbtree_node *nil;
} rbtree;

void _left_rotate(rbtree *T, rbtree_node *x)
{
    rbtree_node *y = x->right;

    x->right = y->left;
    if (y->left != T->nil)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == T->nil)
    {
        T->root == y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void _right_rotate(rbtree *T, rbtree_node *y)
{
    rbtree_node *x = y->left;

    y->left = x->right;
    if (x->right != T->nil)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == T->nil)
    {
        T->root = x;
    }
    else if (y == y->parent->left)
    {
         y->parent->left = x;
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}