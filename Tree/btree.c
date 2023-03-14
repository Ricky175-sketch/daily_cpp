#include <stdio.h>
#include <stdlib.h>

#define M 3

typedef int KEY_TYPE;

typedef struct _btree_node
{
    struct _btree_node **children;
    KEY_TYPE *keys;

    int num; // 关键字的数量
    int is_leaf; // 1表示是叶子结点 0表示非叶子结点
} btree_node;

typedef struct _btree
{
    btree_node *root;
    int t; // 2 * t为该树每个结点最大允许的指针数
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
    T->t = num;
    btree_node *node = btree_create_node(num, 1);
    T->root = node;
}

void btree_split_child(btree *T, btree_node *parent, int i)
{
    btree_node *child = parent->children[i];
    btree_node *new_node = btree_create_node(T->t, child->is_leaf);

    // 关键字迁移
    for (int j = 0; j < T->t - 1; j++)
        new_node->keys[j] = child->keys[T->t + j];

    // 子树迁移
    if (child->is_leaf == 0)
        for (int j = 0; j < T->t - 1; j++)
            new_node->children[j] = child->children[T->t + j];

    child->num = T->t - 1;

    // 将新结点插入到父亲结点中
    for (int j = parent->num; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[i] = new_node;

    // 将分裂结点中间位置的关键字添加到父亲结点中
    for (int j = parent->num - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = child->keys[T->t - 1];
    parent->num++;
}

void btree_insert_not_full(btree *T, btree_node *x, KEY_TYPE key)
{
    int i = x->num - 1;
    if (x->is_leaf == 1)
    {
        for (; i >= 0 && x->keys[i] > key; i--)
            x->keys[i + 1] = x->keys[i];
        x->keys[i + 1] = key;
        x->num++;
    }
    else
    {
        while (i >= 0 && x->keys[i] > key)
            i--;
        if (x->children[i + 1]->num == 2 * T->t - 1)
        {
            btree_split_child(T, x, i + 1);
            if (x->keys[i + 1] < key)
                i++;
        }
        btree_insert_not_full(T, x->children[i + 1], key);
    }

}

void btree_insert(btree *T, KEY_TYPE key)
{
    btree_node *root = T->root;

    if (root->num == 2 * T->t - 1)
    {
        btree_node *new_node = btree_create_node(T->t, 0);
        T->root = new_node;
        T->root->children[0] = root;
        btree_split_child(T, T->root, 0);
    }
    else
        btree_insert_not_full(T, root, key);
}

int main()
{

}