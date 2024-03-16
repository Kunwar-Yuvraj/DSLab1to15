/*
Define a structure called Student with the members: Name, Reg_no, marks in 3 tests and average_ marks.
Develop a menu driven program to perform the following by writing separate function for each operation: a) read
information of N students b) display student’s information c) to calculate the average of best two test marks of each
student.

Note: Allocate memory dynamically and illustrate the use of pointer to an array of structure
*/


#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char name[25];
    int reg_no;
    int marks[3];
    float avg;
} Student;


int i, j;


void read(Student *arr, int N){
    for (i = 0; i < N; i++){
        printf("Enter student #%d:\n", (i+1));
        printf("Name: ");
        scanf("%s", (arr + i)->name);
        printf("Reg No: ");
        scanf("%d", &(arr + i)->reg_no);

        printf("Marks in 3 subjects: ");
        for (j = 0; j < 3; j++){
            scanf("%d", &(arr + i)->marks[j]);
        }
        (arr + i)->avg = 0.0;
    }
}


void display(Student *arr, int N){
    for (i = 0; i < N; i++)
        printf(
            "%s\t%d\t%d %d %d\t%f\n", 
            (arr + i)->name, (arr + i)->reg_no, (arr + i)->marks[0], (arr + i)->marks[1], (arr + i)->marks[2], (arr + i)->avg
        );
}


void calc_avg(Student *arr, int N){
    for (i = 0; i < N; i++){
        int min = (arr + i)->marks[0];
        int j;
        for (j = 1; j < 3; j++){
            if (min < (arr + i)->marks[j]){
                min = (arr + i)->marks[j];
            }
        }
        int sum = (arr + i)->marks[0] + (arr + i)->marks[1] + (arr + i)->marks[2];
        (arr + i)->avg = (sum - min)/2.0;
    }
}


int main(){
    int N;
    printf("Enter number of students: ");
    scanf("%d", &N);
    Student *arr = (Student *)malloc(N * sizeof(Student));
    if (!arr){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    printf("\nMAIN MENU :>\n\n");
    printf("1. Read\n");
    printf("2. Display\n");
    printf("3. Calculate Average\n");
    printf("0. Exit\n");

    int choice;
    do{
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter %d students:\n", N);
                read(arr, N);
                break;
            
            case 2:
                printf("NAME\tREG NO\tMARKS IN 3\tAVERAGE\n");
                display(arr, N);
                break;
            
            case 3:
                calc_avg(arr, N);
                printf("Averages calculated!\n");
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    free(arr);

    return 0;
}