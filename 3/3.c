/*
Develop a menu driven program to implement the following operations on an array of integers with dynamic
memory allocation. Display the array contents after each operation.
i) Insert by order ii) Delete by position iii) Search by key iv) Reverse the contents
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

int i;

void display(int *arr, int N)
{
    if (N == 0)
    {
        printf("Empty!\n");
        return;
    }
    printf("Array: ");
    for (i = 0; i < N; i++)
    {
        printf("%d\t", *(arr + i));
    }
    printf("\n");
}

void insert_order(int *arr, int *N, int val)
{
    int pos = 0;
    do
    {
        if (val < *(arr + pos))
            break;
        pos++;
    } while (pos < *N);

    for (i = *N - 1; i >= pos; i--)
    {
        *(arr + i + 1) = *(arr + i);
    }

    *(arr + pos) = val;
    *N += 1;
    printf("Inserted!\n");
}

void delete_by_pos(int *arr, int *N, int pos)
{
    if (pos < 0 || pos > *N)
    {
        printf("Invalid position for deletion!\n");
        return;
    }
    if (*N == 0)
    {
        printf("Empty!\n");
        return;
    }
    for (i = pos; i < *N - 1; i++)
    {
        *(arr + pos) = *(arr + pos + 1);
    }
    *N -= 1;
    printf("Deleted!\n");
}

void search_by_key(int *arr, int *N, int key)
{
    if (*N == 0)
    {
        printf("Empty!\n");
        return;
    }
    int pos = 0, exist = 0;
    do
    {
        if (key == *(arr + pos))
        {
            exist = 1;
            break;
        }
        pos++;
    } while (pos < *N);

    if (exist)
    {
        printf("Position of %d is: %d\n", key, pos);
    }
    else
    {
        printf("%d doesn't exist!\n", key);
    }
}

void reverse(int *arr, int *N)
{
    int start = 0;
    int end = *N - 1;

    while (start < end)
    {
        int temp = *(arr + start);
        *(arr + start) = *(arr + end);
        *(arr + end) = temp;
        start++;
        end--;
    }
}

int main()
{
    int N = 0;
    int *arr = (int *)malloc(MAXSIZE * sizeof(int));
    if (!arr)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("\nMAIN MENU :>\n\n");
    printf("1. Insert By Order\n");
    printf("2. Delete By Position\n");
    printf("3. Search By Key\n");
    printf("4. Reverse\n");
    printf("0. Exit\n");

    int choice, pos, val, key;
    do
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d", &val);
            insert_order(arr, &N, val);
            display(arr, N);
            break;

        case 2:
            printf("Enter position: ");
            scanf("%d", &key);
            delete_by_pos(arr, &N, key);
            display(arr, N);
            break;

        case 3:
            printf("Enter key: ");
            scanf("%d", &pos);
            search_by_key(arr, &N, pos);
            display(arr, N);
            break;

        case 4:
            reverse(arr, &N);
            display(arr, N);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}