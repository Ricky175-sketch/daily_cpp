#include <stdio.h>
#include <stdlib.h>

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

btree_node *btree_create_node(int node_num, int is_leaf)
{
    btree_node *node = (btree_node*)calloc(1, sizeof(btree_node));
    if (node == NULL)
        return;

    node->children = (btree_node**)calloc(1, 2 * node_num * sizeof(btree_node*));
    node->keys = (KEY_TYPE*)calloc(1, (2 * node_num - 1) * sizeof(KEY_TYPE));
    node->num = 0;
    node ->is_leaf = is_leaf;

    return node;
}