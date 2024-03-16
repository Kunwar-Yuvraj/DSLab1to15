/*
Define a structure called Time containing 3 integer members (hour, minute,
second). Develop a menu driven program to perform the following by writing
separate function for each operation.

a) read (T): To read time 
b) display (T):To display time 
c) update(T): To update time 
d) add (T1, T2) : Add two times.

update function increments the time by one second and returns the new time
(if the increment results in 60 seconds, then the second member is set to zero
and minute member is incremented by one. If the result is 60 minutes, the
minute member is set to zero and the hour member is incremented by one.
Finally, when the hour becomes 24, Time should be reset to zero. While
adding two time variable, normalize the resultant time value as in the case of
update function.

Note: Illustrate the use of pointer to pass time variable to different functions.
*/


#include<stdio.h>
#include<stdlib.h>


typedef struct{
    int hour;
    int minute;
    int second;
} TIME;


TIME * initialize_time(){
    TIME *time = (TIME *)malloc(sizeof(TIME));
    if (!time){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    time->hour = 0;
    time->minute = 0;
    time->second = 0;

    return time;
}


void read(TIME *T){
    printf("Enter time (HH:MM:SS): ");
    scanf("%d:%d:%d", &T->hour, &T->minute, &T->second);
}


void display(TIME *T){
    printf("\nTime is: %02d:%02d:%02d\n", T->hour, T->minute, T->second);
}


void normalize(TIME *T){
    if (T->second > 59){
        T->second -= 60;
        T->minute += 1;
    }
    if (T->minute > 59){
        T->minute -= 60;
        T->hour += 1;
    }
    if (T->hour > 23){
        T->hour -= 24;
    }
}


void update(TIME *T){
    T->second += 1;
    normalize(T);
    printf("Time updated!\n");
}


void add(TIME *T1, TIME *T2){
    TIME *res = initialize_time();
    res->hour = T1->hour + T2->hour;
    res->minute = T1->minute + T2->minute;
    res->second = T1->second + T2->second;
    normalize(res);
    display(res);
    free(res);
}


int main()
{
    TIME *T = initialize_time();
    TIME *T1 = initialize_time();
    TIME *T2 = initialize_time();
    
    printf("\nMAIN MENU :> \n\n");
    printf("1. Read\n");
    printf("2. Display\n");
    printf("3. Update\n");
    printf("4. Add\n");
    printf("0. Exit\n");

    int choice;
    do
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                read(T);
                break;
            
            case 2:
                display(T);
                break;
            
            case 3:
                update(T);
                break;
            
            case 4:
                read(T1);
                read(T2);
                add(T1, T2);
                break;
            
            case 0:
                printf("Exiting...\n");
                break;
            
            default:
                printf("Invalid choice!\n");

        }
    } while (choice != 0);
    
    free(T);
    free(T1);
    free(T2);

    return 0;
}