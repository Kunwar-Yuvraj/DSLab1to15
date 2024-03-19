/*
Implement circular single linked list to perform the following operations
i) Insert by order
ii ) Delete by position
iii) Search for an item by key
iv) Delete by key
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
        printf("Memory allocation failed for node!\n");
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

void display(CSL *list)
{
    if (list->count == 0)
    {
        printf("List is empty!\n");
        return;
    }
    printf("List :\n");
    NODE *cur = list->head->n;
    do
    {
        printf("%d->", cur->data);
        cur = cur->n;
    } while (cur != list->head->n);
    printf("(%d)\nCount : %d\n", cur->data, list->count);
}

void insert_front(CSL *list, int data)
{
    NODE *new = create_node(data);
    if (list->count == 0)
    {
        list->head->n = new;
        new->n = new;
    }
    else
    {
        NODE *cur = list->head->n;
        NODE *last = cur;
        while (last->n != cur)
        {
            last = last->n;
        }
        list->head->n = new;
        new->n = cur;
        last->n = new;
    }
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
    NODE *cur = list->head->n;
    NODE *last = cur;
    while (last->n != cur)
        last = last->n;

    last->n = new;
    new->n = cur;
    list->count += 1;
}

void insert_pos(CSL *list, int pos, int data)
{
    if (pos < 0 || pos > list->count)
        printf("Invalid position for insertion!\n");

    else if (pos == 0)
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
        prev->n = new;
        new->n = cur;
        list->count += 1;
    }
}

void delete_front(CSL *list)
{
    if (list->count == 0)
    {
        printf("Empty list!\n");
        return;
    }
    NODE *cur = list->head->n;
    if (list->count == 1)
    {
        list->head->n = NULL;
    }
    else
    {
        NODE *prev = NULL;
        NODE *last = cur;
        while (last->n != cur)
            last = last->n;

        list->head->n = cur->n;
        last->n = cur->n;
    }
    free(cur);
    list->count -= 1;
    printf("Deleted!\n");
}

void delete_rear(CSL *list)
{
    if (list->count == 0)
    {
        printf("Empty list!\n");
        return;
    }
    if (list->count == 1)
    {
        delete_front(list);
    }
    else
    {
        NODE *cur = list->head->n;
        NODE *prev = NULL;
        while (cur->n != list->head->n)
        {
            prev = cur;
            cur = cur->n;
        }
        prev->n = list->head->n;
        free(cur);
        list->count -= 1;
        printf("Deleted!\n");
    }
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
        printf("Empty list!\n");
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

void insert_order(CSL *list, int data)
{
    if (list->count == 0)
    {
        insert_front(list, data);
        return;
    }
    int pos = 0;
    NODE *cur = list->head->n;
    do
    {
        if (data < cur->data)
            break;
        pos++;
        cur = cur->n;
    } while (cur != list->head->n);
    insert_pos(list, pos, data);
}

int search_key(CSL *list, int key)
{
    int pos = -1;
    if (list->count == 0)
    {
        printf("List is empty!\n");
    }
    else
    {
        NODE *cur = list->head->n;
        do
        {
            pos++;
            if (key == cur->data)
                return pos;
            cur = cur->n;
        } while (cur != list->head->n);
    }
    return pos;
}

void delete_key(CSL *list, int key)
{
    int pos = search_key(list, key);
    if (pos != -1)
        delete_pos(list, pos);

    else
        printf("Key not found!\n");
}

int main()
{
    CSL *list = create_list();
    printf("\nMAIN MENU :>\n\n");
    printf("1. Insert By Order\n");
    printf("2. Delete By Position\n");
    printf("3. Search By Key\n");
    printf("4. Delete By Key\n");
    printf("0. Exit\n");

    int choice, pos, data, key;
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
            printf("Enter position: ");
            scanf("%d", &pos);
            delete_pos(list, pos);
            display(list);
            break;

        case 3:
            printf("Enter key: ");
            scanf("%d", &key);
            pos = search_key(list, key);
            if (pos != -1)
                printf("%d found at: %d\n", key, pos);
            else
                printf("Key not found!\n");
            display(list);
            break;

        case 4:
            printf("Enter key: ");
            scanf("%d", &key);
            delete_key(list, key);
            display(list);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    free(list);

    return 0;
}