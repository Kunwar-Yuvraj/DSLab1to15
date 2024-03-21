/*
Develop a menu driven program to implement Binary Search tree with the following operations.
i) Construction
ii) Traversals (Pre, In and Post Order)
iii) Searching a node by key and displaying its information along with its parent if exists, otherwise a suitablemessage. iv)Counting all nodes.
v) Finding height.
vi Finding node with the Maximum key value and printing the node details along with the parent.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left, *right;
} NODE;

NODE *create_node(int key)
{
    NODE *node = (NODE *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

NODE *insert(NODE *node, int key)
{
    if (node == NULL)
        return create_node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

void inorder(NODE *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(NODE *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(NODE *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

int is_leaf(NODE *root)
{
    if (root->left == NULL && root->right == NULL)
        return 1;
    return 0;
}

NODE *search(NODE *root, int key, NODE *parent)
{
    if (root == NULL)
    {
        printf("Node with key %d not found.\n", key);
        return NULL;
    }
    if (root->key == key)
    {
        printf("Node with key %d found.\n", key);
        if (is_leaf(root))
        {
            printf("Its a leaf node. No children!\n");
        }
        else
        {
            if (root->right != NULL)
            {
                printf("Right child node: %d\n", root->right->key);
            }
            if (root->left != NULL)
            {
                printf("Left child node: %d\n", root->left->key);
            }
        }
        if (parent != NULL)
            printf("Parent: %d\n", parent->key);
        else
            printf("No parent found. (Root node)\n");
        return root;
    }
    if (key < root->key)
        return search(root->left, key, root);
    return search(root->right, key, root);
}

int countNodes(NODE *root)
{
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(NODE *node)
{
    if (node == NULL)
        return -1;
    return 1 + max(height(node->left), height(node->right));
}

NODE *findMaxNode(NODE *root, NODE *parent)
{
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return NULL;
    }

    if (root->right == NULL)
    {
        printf("Maximum node: %d\n", root->key);
        if (parent != NULL)
            printf("Parent node: %d\n", parent->key);
        return root;
    }
    return findMaxNode(root->right, root);
}

int main()
{
    NODE *root = NULL;
    int choice, key;
    NODE *result;

    do
    {
        printf("\nBinary Search Tree Operations\n");
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Search\n");
        printf("6. Count Nodes\n");
        printf("7. Height\n");
        printf("8. Find Maximum Node\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
            break;
        case 2:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;
        case 3:
            printf("Preorder Traversal: ");
            preorder(root);
            printf("\n");
            break;
        case 4:
            printf("Postorder Traversal: ");
            postorder(root);
            printf("\n");
            break;
        case 5:
            printf("Enter key to search: ");
            scanf("%d", &key);
            result = search(root, key, NULL);
            break;
        case 6:
            printf("Number of nodes: %d\n", countNodes(root));
            break;
        case 7:
            printf("Height of tree: %d\n", height(root));
            break;
        case 8:
            result = findMaxNode(root, NULL);
            break;
        case 9:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 9.\n");
        }
    } while (choice != 9);

    return 0;
}
