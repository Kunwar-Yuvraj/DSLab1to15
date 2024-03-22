/*
Develop a menu driven program to implement Binary Search tree with the followingoperations.
i) Construction
ii) Traversals (Pre, In and Post Order)
iii) Searching a node by key and deleting if exists ( node to be deleted may be leaf or non- leaf with one child ortwo children)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct N
{
    int key;
    struct N *left, *right;
} Node;

Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *insert(Node *root, int key)
{
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

Node *search(Node *root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

Node *findMin(Node *node)
{
    Node *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node *deleteNode(Node *root, int k)
{
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key, then it lies in the left subtree
    if (k < root->key)
        root->left = deleteNode(root->left, k);
    // If the key to be deleted is greater than the root's key, then it lies in the right subtree
    else if (k > root->key)
        root->right = deleteNode(root->right, k);
    // If key is same as root's key, then this is the node to be deleted
    else
    {
        // Node with only one child or no child
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node *temp = findMin(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main()
{
    Node *root = NULL;
    int choice, key;
    Node *result;

    do
    {
        printf("\nBinary Search Tree Operations\n");
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Search and Delete\n");
        printf("6. Exit\n");
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
            printf("Enter key to search and delete: ");
            scanf("%d", &key);
            result = search(root, key);
            if (result != NULL)
            {
                printf("Node with key %d found and deleted.\n", key);
                root = deleteNode(root, key);
            }
            else
            {
                printf("Node with key %d not found.\n", key);
            }
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
