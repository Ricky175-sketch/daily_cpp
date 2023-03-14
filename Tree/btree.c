#include <stdio.h>
#include <stdlib.h>

#define M 3

typedef int KEY_TYPE;

typedef struct _btree_node
{
    struct _btree_node **children;
    KEY_TYPE *keys;

    int num;
    int is_leaf; // 1表示是叶子结点 0表示非叶子结点
} btree_node;

typedef struct _btree
{
    btree_node *root;
    int num;
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

void btree_destroy_node(btree_node *node)
{
    if (node)
    {
        if (node->children)
            free(node->children);
        if (node->keys)
            free(node->keys);
        free(node);
    }
}

void btree_create(btree *T, int num)
{
    T->num = num;
    btree_node *node = btree_create_node(num, 1);
    T->root = node;
}

int main()
{

}