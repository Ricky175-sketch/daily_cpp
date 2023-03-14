#include <stdio.h>

#define M 3

typedef int KEY_TYPE;

typedef struct _btree_node
{
    struct _btree_node **children;
    KEY_TYPE *keys;

    int num;
    int is_leaf;
} btree_node;

typedef struct _btree
{
    btree_node *root;
}btree;
