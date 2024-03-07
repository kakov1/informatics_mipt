#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    double key;
    struct _node *left, *right;
} node;

node *newNode(int item)
{

    node *temp = (node *)malloc(sizeof(node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

node *insert(node *node, int key)
{
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}

node *min(node *root)
{
    node *current = root;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

node *max(node *root)
{
    node *current = root;

    while (current && current->right != NULL)
        current = current->right;

    return current;
}

node *delete(node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = delete (root->left, key);
    else if (key > root->key)
        root->right = delete (root->right, key);
    else
    {
        if (root->left == NULL)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }

        node *temp = min(root->right);

        root->key = temp->key;

        root->right = delete (root->right, temp->key);
    }
    return root;
}

node *delete_max(node *root) {
    if (root == NULL)
        return root;

    if (root->right != NULL) {
        root->right = delete_max(root->right);
    }
    else
    {
        node *temp = root->left;
        free(root);
        return temp;
    }
    return root;
}

node *delete_min(node *root) {
    if (root == NULL) {
        return root;
    }
    
    if (root->left != NULL) {
        root->left = delete_min(root->left);
    }
    else {
        node *temp = root->right;
        free(root);
        return temp;
    }
    return root;
}

int main()
{
    node *root = NULL;
    double num;
    int count = 0;

    while (scanf("%lf", &num) == 1)
    {
        root = insert(root, num);
        count++;
    }

    count = (count + 1)/2;

    for (; count != 1; count--)
    {
        root = delete_max(root);
        root = delete_min(root);
    }

    printf("Медиана: ");
    if (root->left == NULL && root->right == NULL)
    {
        printf("%lf\n", root->key);
    }
    else
    {
        if (root->left != NULL) {
            printf("%lf\n", (root->left->key + root->key) / 2);
        }
        else {
            printf("%lf\n", (root->right->key + root->key) / 2);
        }
    }
}
