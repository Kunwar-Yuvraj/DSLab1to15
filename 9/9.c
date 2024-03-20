/*
Implement circular double linked list to perform the following operations
i) Insert by order
ii) Delete rear
iii) Delete Front
iv) Search for an item by position
Display the list contents after each operation
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *p, *n;
} NODE;

typedef struct
{
    int count;
    NODE *head;
} CDL;

NODE *create_node(int data)
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    if (!new)
    {
        printf("Memory allocation for node failed!\n");
        exit(1);
    }
    new->data = data;
    new->n = new->p = NULL;

    return new;
}

CDL *create_list()
{
    CDL *list = (CDL *)malloc(sizeof(CDL));
    if (!list)
    {
        printf("Memory allocation for list failed!\n");
        exit(1);
    }
    list->head = create_node(0);
    list->count = 0;

    return list;
}

void display(CDL *list);
void insert_order(CDL *list, int data);
void delete_rear(CDL *list);
void delete_front(CDL *list);
void search_pos(CDL *list, int pos);

int main()
{
    CDL *list = create_list();

    printf("\nMAIN MENU :> \n\n");
    printf("1. Insert By Order\n");
    printf("2. Delete At Rear\n");
    printf("3. Delete At Front\n");
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
            insert_order(list, data);
            display(list);
            break;

        case 2:
            delete_rear(list);
            display(list);
            break;

        case 3:
            delete_front(list);
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

void display(CDL *list)
{
    if (list->count == 0)
    {
        printf("Empty!\n");
        return;
    }
    printf("List: ");
    NODE *cur = list->head->n;
    do
    {
        printf("%d<-->", cur->data);
        cur = cur->n;
    } while (cur != list->head->n);
    printf("(%d)\nCount: %d\n", cur->data, list->count);
}

void insert_front(CDL *list, int data)
{
    NODE *new = create_node(data);
    if (list->count == 0)
    {
        new->n = new;
        new->p = new;
    }
    else
    {
        NODE *front = list->head->n;
        NODE *last = front->p;
        new->n = front;
        new->p = last;
        front->p = new;
        last->n = new;
    }
    list->head->n = new;
    list->count += 1;
    printf("Inserted!\n");
}

void insert_rear(CDL *list, int data)
{
    if (list->count == 0)
    {
        insert_front(list, data);
        return;
    }
    NODE *new = create_node(data);
    NODE *front = list->head->n;
    NODE *last = front->p;
    new->n = front;
    new->p = last;
    front->p = new;
    last->n = new;
    list->count += 1;
    printf("Inserted!\n");
}

void insert_pos(CDL *list, int data, int pos)
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
        new->p = prev;
        cur->p = new;
        prev->n = new;
        list->count += 1;
        printf("Inserted!\n");
    }
}

void insert_order(CDL *list, int data)
{
    if (list->count == 0)
    {
        insert_front(list, data);
        return;
    }

    NODE *cur = list->head->n;
    int pos = 0;
    do
    {
        if (data < cur->data)
            break;
        pos++;
        cur = cur->n;
    } while (cur != list->head->n);
    insert_pos(list, data, pos);
}

void delete_front(CDL *list)
{
    if (list->count == 0)
    {
        printf("Emtpy!\n");
        return;
    }
    NODE *front = list->head->n;
    NODE *last = front->p;
    list->head->n = front->n;
    last->n = front->n;
    front->n->p = last;
    free(front);
    list->count -= 1;
    printf("Deleted!\n");
}

void delete_rear(CDL *list)
{
    if (list->count == 0)
    {
        delete_front(list);
        return;
    }
    NODE *front = list->head->n;
    NODE *last = front->p;
    front->p = last->p;
    last->p->n = front;
    free(last);
    list->count -= 1;
    printf("Deleted!\n");
}

void search_pos(CDL *list, int pos)
{
    if (list->count == 0)
    {
        printf("Empty!\n");
        return;
    }
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