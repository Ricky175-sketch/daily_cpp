#include <stdio.h>

#define RED 0
#define BLACK 1

typedef int KEY_TYPE;

int key_compare(KEY_TYPE *a, KEY_TYPE *b)
{
    //TODO
}

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

void rbtree_insert_fixup(rbtree *T, rbtree_node *z)
{
    
}

void rbtree_insert(rbtree *T, rbtree_node *z)
{
    rbtree_node *x = T->root;
    rbtree_node *y = T->nil;

    while (x != T->nil)
    {
        y = x;
        // 如果是自定义类型，可以实现key_compare接口来进行比较
        if (x->key > z->key)
        {
            x = x->right;
        }
        else if (x->key < z->key)
        {
            x = x->left;
        }
        else
        {
            return;
        }
    }

    z->parent = y;
    if (y == T->nil)
    {
        T->root = z;
    }
    else if (z->key > y->key)
    {
        y->right = z;
    }
    else
    {
        y->left = z;
    }

    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;

    rbtree_insert_fixup(T, z);
}