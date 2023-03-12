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
