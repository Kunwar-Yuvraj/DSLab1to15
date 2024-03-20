/*
Implement circular single linked list to perform the following operations
i) Insert by position
ii) Delete rear
iii) Delete Front
iv) Search for an item by value
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
void insert_pos(CSL *list, int data, int pos);
void delete_rear(CSL *list);
void delete_front(CSL *list);
void search_key(CSL *list, int key);

int main()
{
    CSL *list = create_list();

    printf("\nMAIN MENU :>\n\n");
    printf("1. Insert By Position\n");
    printf("2. Delete At Front\n");
    printf("3. Delete At Rear\n");
    printf("4. Search By Key\n");
    printf("0. Exit\n");

    int choice, data, pos, key;
    do
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data and position: ");
            scanf("%d %d", &data, &pos);
            insert_pos(list, data, pos);
            display(list);
            break;

        case 2:
            delete_front(list);
            display(list);
            break;

        case 3:
            delete_rear(list);
            display(list);
            break;

        case 4:
            printf("Enter key: ");
            scanf("%d", &key);
            search_key(list, key);
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

void insert_pos(CSL *list, int data, int pos)
{
    if (pos < 0 || pos > list->count)
    {
        printf("Invalid position!\n");
        return;
    }
    if (pos == 0)
        insert_front(list, data);
    else if (pos == list->count)
        insert_rear(list, data);
    else
    {
        NODE *new = create_node(data);
        NODE *cur = list->head->n;
        NODE *prev = NULL;
        while (pos--)
        {
            prev = cur;
            cur = cur->n;
        }
        new->n = cur;
        prev->n = new;
        list->count += 1;
        printf("Inserted!\n");
    }
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

void search_key(CSL *list, int key)
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
        printf("Position is: %d\n", pos);
    else
        printf("Key not found!\n");
}