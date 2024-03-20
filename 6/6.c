/*
Implement circular single linked list to perform the following operations
i) Insert front
ii) Insert rear
iii) Delete a node with the given key
iv) Search for an item by position
Display the list contents after each operation
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *n;
} NODE;

typedef struct
{
    int count;
    NODE *head;
} CSL;

NODE *create_node(int data)
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    if (!new)
    {
        printf("Memory allocation for node failed!\n");
        exit(1);
    }
    new->data = data;
    new->n = NULL;

    return new;
}

CSL *create_list()
{
    CSL *list = (CSL *)malloc(sizeof(CSL));
    if (!list)
    {
        printf("Memory allocation for list failed!\n");
        exit(1);
    }
    list->head = create_node(0);
    list->count = 0;

    return list;
}

void display(CSL *list);
void insert_front(CSL *list, int data);
void insert_rear(CSL *list, int data);
void delete_key(CSL *list, int key);
void search_pos(CSL *list, int pos);

int main()
{
    CSL *list = create_list();

    printf("\nMAIN MENU :>\n\n");
    printf("1. Insert At Front\n");
    printf("2. Insert At Rear\n");
    printf("3. Delete By Key\n");
    printf("4. Search By Position\n");
    printf("0. Exit\n");

    int choice, data, pos, key;
    do
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            insert_front(list, data);
            display(list);
            break;

        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            insert_rear(list, data);
            display(list);
            break;

        case 3:
            printf("Enter key: ");
            scanf("%d", &key);
            delete_key(list, key);
            display(list);
            break;

        case 4:
            printf("Enter position: ");
            scanf("%d", &pos);
            search_pos(list, pos);
            display(list);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    free(list->head);
    free(list);

    return 0;
}

void display(CSL *list)
{
    if (list->count == 0)
    {
        printf("Emtpy!\n");
        return;
    }
    printf("List: ");
    NODE *cur = list->head->n;
    do
    {
        printf("%d->", cur->data);
        cur = cur->n;
    } while (cur != list->head->n);
    printf("(%d)\nCount: %d\n", cur->data, list->count);
}

void insert_front(CSL *list, int data)
{
    NODE *new = create_node(data);
    if (list->count == 0)
    {
        new->n = new;
    }
    else
    {
        NODE *cur = list->head->n;
        NODE *last = cur;
        while (last->n != list->head->n)
            last = last->n;
        new->n = cur;
        last->n = new;
    }
    list->head->n = new;
    list->count += 1;
    printf("Inserted!\n");
}

void insert_rear(CSL *list, int data)
{
    if (list->count == 0)
    {
        insert_front(list, data);
        return;
    }
    NODE *new = create_node(data);
    NODE *front = list->head->n;
    NODE *last = front;
    while (last->n != list->head->n)
        last = last->n;
    new->n = front;
    last->n = new;
    list->count += 1;
    printf("Inserted!\n");
}

void delete_front(CSL *list)
{
    if (list->count == 0)
    {
        printf("Empty!\n");
        return;
    }
    NODE *front = list->head->n;
    if (list->count == 1)
    {
        list->head->n = NULL;
    }
    else
    {
        NODE *last = front;
        while (last->n != front)
            last = last->n;
        list->head->n = front->n;
        last->n = front->n;
    }
    free(front);
    list->count -= 1;
    printf("Deleted!\n");
}

void delete_rear(CSL *list)
{
    if (list->count == 0 || list->count == 1)
    {
        delete_front(list);
        return;
    }
    NODE *front = list->head->n;
    NODE *last = front;
    NODE *prev = NULL;
    while (last->n != front)
    {
        prev = last;
        last = last->n;
    }
    prev->n = front;
    free(last);
    list->count -= 1;
    printf("Deleted!\n");
}

void delete_pos(CSL *list, int pos)
{
    if (pos < 0 || pos >= list->count)
    {
        printf("Invalid position!\n");
        return;
    }
    if (list->count == 0)
    {
        printf("Emtpy!\n");
        return;
    }
    if (pos == 0)
        delete_front(list);
    else if (pos == list->count - 1)
        delete_rear(list);
    else
    {
        NODE *cur = list->head->n;
        NODE *prev = NULL;
        while (pos--)
        {
            prev = cur;
            cur = cur->n;
        }
        prev->n = cur->n;
        free(cur);
        list->count -= 1;
        printf("Deleted!\n");
    }
}

void delete_key(CSL *list, int key)
{
    if (list->count == 0)
    {
        printf("Empty!\n");
        return;
    }
    int pos = 0, exist = 0;
    NODE *cur = list->head->n;
    do
    {
        if (key == cur->data)
        {
            exist = 1;
            break;
        }
        pos++;
        cur = cur->n;
    } while (cur != list->head->n);
    if (exist)
        delete_pos(list, pos);
    else
        printf("Key not found!\n");
}

void search_pos(CSL *list, int pos)
{
    if (pos < 0 || pos >= list->count)
    {
        printf("Invalid position!\n");
        return;
    }
    NODE *cur = list->head->n;
    while (pos--)
        cur = cur->n;
    printf("Element is: %d\n", cur->data);
}