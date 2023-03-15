#include <stdio.h>
#include <stdlib.h>

#define M 3

typedef int KEY_TYPE;

typedef struct _btree_node
{
    struct _btree_node **children;
    KEY_TYPE *keys;

    int num;     // 关键字的数量
    int is_leaf; // 1表示是叶子结点 0表示非叶子结点
} btree_node;

typedef struct _btree
{
    btree_node *root;
    int t; // 2 * t为该树每个结点最大允许的指针数
} btree;

btree_node *btree_create_node(int node_num, int is_leaf)
{
    btree_node *node = (btree_node *)calloc(1, sizeof(btree_node));
    if (node == NULL)
        return;

    node->children = (btree_node **)calloc(1, 2 * node_num * sizeof(btree_node *));
    node->keys = (KEY_TYPE *)calloc(1, (2 * node_num - 1) * sizeof(KEY_TYPE));
    node->num = 0;
    node->is_leaf = is_leaf;

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

void btree_merge(btree *T, btree_node *node, int idx)
{
    btree_node *left = node->children[idx];
    btree_node *right = node->children[idx + 1];

    left->keys[T->t - 1] = node->keys[idx];
    for (int i = 0; i < T->t - 1; i++)
        left->keys[T->t + i] = right->keys[i];
    if (left->is_leaf == 0)
        for (int i = 0; i < T->t; i++)
            left->children[T->t + i] = right->children[i];

    btree_destroy_node(right);

    int i = idx + 1;
    for (; i < node->num; i++)
    {
        node->keys[i - 1] = node->keys[i];
        node->children[i] = node->children[i + 1];
    }
    node->children[i + 1] = NULL;
    node->num--;

    if (node->num == 0)
    {
        T->root = left;
        btree_destroy_node(node);
    }
}

void btree_delete_key(btree *T, btree_node *node, KEY_TYPE key)
{
    if (node == NULL)
        return;

    int idx = 0;
    while (idx < node->num && key > node->keys[idx])
        idx++;

    if (idx < node->num && key == node->keys[idx])
    {
        if (node->is_leaf == 1)
        {
            // 要删除的结点为叶子结点
            for (int i = idx; i < node->num - 1; i++)
                node->keys[i] = node->keys[i + 1];

            node->keys[node->num - 1] = 0;
            node->num--;

            if (node->num == 0)
            {
                free(node);
                T->root = NULL;
            }

            return;
        }
        else if (node->children[idx]->num >= T->t)
        {
            // 左边的子树关键字数大于M/2-1
            btree_node *left = node->children[idx];
            node->keys[idx] = left->keys[left->num - 1];

            btree_delete_key(T, left, left->keys[left->num - 1]);
        }
        else if (node->children[idx + 1]->num >= T->t)
        {
            // 右边的子树关键字数大于M/2-1
            btree_node *right = node->children[idx + 1];
            node->keys[idx] = right->keys[0];

            btree_delete_key(T, right, right->keys[0]);
        }
        else
        {
            // 相邻的两棵子树关键字数都等于M/2-1
            btree_merge(T, node, idx);
            btree_delete_key(T, node->children[idx], key);
        }
    }
    else
    {
        // 要删除的关键字不在该结点则向下递归
        btree_node *child = node->children[idx];
        if (child == NULL)
        {
            printf("Delete key[%d] failed\n", key);
            return;
        }

        if (child->num == T->t - 1)
        {
            btree_node *left = NULL;
            btree_node *right = NULL;

            if (idx - 1 >= 0)
                left = node->children[idx - 1];
            if (idx + 1 <= node->num)
                right = node->children[idx + 1];

            if ((left && left->num >= T->t) || (right && right->num >= T->t))
            {
                int use_right = 0;
                if (right)
                    use_right = 1;
                if (left && right)
                    use_right = (right->num > left->num) ? 1 : 0;

                if (right && right->num >= T->t && use_right)
                {
                    // 从右子树借一个
                    child->keys[child->num] = node->keys[idx];
                    child->children[child->num + 1] = right->children[0];
                    child->num++;

                    node->keys[idx] = right->keys[0];
                    for (int i = 0; i < right->num - 1; i++)
                    {
                        right->keys[i] = right->keys[i + 1];
                        right->children[i] = right->children[i + 1];
                    }

                    right->keys[right->num - 1] = 0;
                    right->children[right->num - 1] = right->children[right->num];
                    right->children[right->num] = NULL;
                    right->num--;
                }
                else
                {
                    // 从左子树借一个
                    for (int i = child->num; i > 0; i--)
                    {
                        child->keys[i] = child->keys[i - 1];
                        child->children[i + 1] = child->children[i];
                    }

                    child->children[1] = child->children[0];
                    child->children[0] = left->children[left->num];
                    child->keys[0] = node->keys[idx - 1];
                    child->num++;

                    node->keys[idx - 1] = left->keys[left->num - 1];
                    left->keys[left->num - 1] = 0;
                    left->children[left->num] = NULL;
                    left->num--;
                }
            }
            else if ((!left || (left->num == T->t - 1)) && (!right || (right->num == T->t - 1)))
            {
                if (left && left->num == T->t - 1)
                {
                    btree_merge(T, node, idx - 1);
                    child = left;
                }
                else if (right && right->num == T->t - 1)
                    btree_merge(T, node, idx);
            }
        }

        btree_delete_key(T, child, key);
    }
}

int btree_delete(btree *T, KEY_TYPE key)
{
    if (T->root == NULL)
        return -1;

    btree_destroy_node(T, T->root, key);
    return 0;
}

int btree_bin_search(btree_node *node, int low, int high, KEY_TYPE key)
{
    // 二分查找结点
    if (low > high || low < 0 || high < 0)
        return -1;

    while (low <= high)
    {
        int mid = low + high >> 1;
        if (key > node->keys[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }

    return low;
}

void btree_print(btree *T, btree_node *node, int layer)
{
    btree_node *t = node;
    if (t)
    {
        printf("\nlayer = %d key_num = %d is_leaf = %d\n", layer, t->num, t->is_leaf);
        for (int i = 0; i < node->num; i++)
            printf("%c ", t->keys[i]);
        puts("");

        printf("%p\n", t);
        for (int i = 0; i <= 2 * T->t; i++)
            printf("%p ", t->children[i]);
        puts("");

        layer++;
        for (int i = 0; i <= t->num; i++)
            if (t->children[i])
                btree_print(T, t->children[i], layer);
    }
    else
        printf("this is a empty tree\n");
}

int main()
{
}