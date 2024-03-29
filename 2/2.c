/*
Develop a menu driven program to implement the following operations on an array of integers with dynamic
memory allocation. Display the array contents after each operation.
i) Insert by position ii) Delete by key iii) Search by position iv) Reverse the contents
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

void insert_by_pos(int *arr, int *N, int pos, int val)
{
    if (pos < 0 || pos > *N)
    {
        printf("Invalid position!\n");
        return;
    }
    for (i = *N - 1; i >= pos; i--)
    {
        *(arr + i + 1) = *(arr + i);
    }
    *(arr + pos) = val;
    *N += 1;
    printf("Inserted!\n");
}

void delete_by_key(int *arr, int *N, int key)
{
    if (*N == 0)
    {
        printf("Empty!\n");
        return;
    }
    int pos = -1;

    for (i = 0; i < *N; i++)
    {
        if (key == *(arr + i))
        {
            pos = i;
            break;
        }
    }
    if (pos != -1)
    {
        for (i = pos; i < *N - 1; i++)
        {
            *(arr + pos) = *(arr + pos + 1);
        }
        printf("Deleted!\n");
        *N -= 1;
    }
    else
    {
        printf("Key element not found!\n");
    }
}

void search_by_pos(int *arr, int *N, int pos)
{
    if (pos < 0 || pos >= *N)
    {
        printf("Invalid position!\n");
        return;
    }
    printf("Element at position %d is: %d\n", pos, *(arr + pos));
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
    printf("1. Insert At Position\n");
    printf("2. Delete By Key\n");
    printf("3. Search By Position\n");
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
            printf("Enter position and value: ");
            scanf("%d %d", &pos, &val);
            insert_by_pos(arr, &N, pos, val);
            display(arr, N);
            break;

        case 2:
            printf("Enter key: ");
            scanf("%d", &key);
            delete_by_key(arr, &N, key);
            display(arr, N);
            break;

        case 3:
            printf("Enter position: ");
            scanf("%d", &pos);
            search_by_pos(arr, &N, pos);
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