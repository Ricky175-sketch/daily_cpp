#include <stdio.h>

#define M 3

typedef int KEY_TYPE;

typedef struct _btree_node
{
    struct _btree_node *children[M * 2];
    KEY_TYPE keys[2 * M - 1];

    int num;
    int is_leaf;
} btree_node;

typedef struct _btree
{
    btree_node *root;
}btree;
