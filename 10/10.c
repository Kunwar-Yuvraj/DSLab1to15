/*
Develop a menu driven program to convert infix expression to postfix expression using stack and evaluate the postfix expression. (Test for nested parenthesized expressions)
Note:
Define Stack structure and implement the operations.
Use different stacks for conversion and evaluation.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 25

typedef struct
{
    char stack[MAXSIZE];
    int top;
} STACK;

STACK *init()
{
    STACK *s = (STACK *)malloc(sizeof(STACK));
    if (!s)
    {
        printf("Memory allocation for stack failed!\n");
        exit(1);
    }
    s->top = -1;
}

void convert(char infix[], STACK *postfix);
void evaluate(char postfix[]);

int main()
{
    char infix[MAXSIZE];

    printf("\nMAIN MENU :> \n\n");
    printf("1. Convert\n");
    printf("2. Evaluate\n");
    printf("0. Exit\n");

    int choice;
    do
    {
        STACK *postfix = init();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter infix: ");
            scanf("%s", infix);
            convert(infix, postfix);
            break;

            // case 2:
            //     printf("Enter postfix: ");
            //     scanf("%s", postfix->stack);
            //     evaluate(postfix);
            //     break;

        case 0:
            printf("Exiting...\n");
            free(postfix);
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}

void push(STACK *s, char c)
{
    if (s->top == MAXSIZE - 1)
    {
        printf("Overflow!\n");
        return;
    }
    s->stack[++s->top] = c;
}

char pop(STACK *s)
{
    if (s->top == -1)
    {
        printf("Underflow!\n");
        return '\0';
    }
    return s->stack[s->top--];
}

char peek(STACK *s)
{
    if (s->top == -1)
    {
        printf("Empty!\n");
        return '\0';
    }
    return s->stack[s->top];
}

int empty(STACK *s)
{
    if (s->top == -1)
        return 1;
    return 0;
}

int is_op(char c)
{
    switch (c)
    {
    case '^':
    case '/':
    case '*':
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

int prec(char op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '/':
    case '*':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

void convert(char infix[], STACK *postfix)
{
    STACK *op = init();

    int i;
    for (i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];

        if (c == '(')
        {
            push(op, c);
        }
        else if (c == ')')
        {
            while (peek(op) != '(')
            {
                push(postfix, pop(op));
            }
            pop(op);
        }
        else if (is_op(c))
        {
            if (op->top == -1)
            {
                push(op, c);
            }
            else
            {
                if (prec(c) > prec(peek(op)))
                {
                    push(op, c);
                }
                else
                {
                    while (prec(c) <= prec(peek(op)))
                    {
                        push(postfix, pop(op));
                    }
                    push(op, c);
                }
            }
        }
        else
        {
            push(postfix, c);
        }
    }
    while (!empty(op))
    {
        push(postfix, pop(op));
    }
    push(postfix, '\0');
    free(op);
    printf("Postfix: %s\n", postfix->stack);
}

// void evaluate(char postfix[])
// {
//     int i;
//     STACK *res = init();
//     for (i=0; postfix[i] != '\0'; i++)
//     {
//         char c = postfix[i];

//         if (!is_op(c))
//         {
//             push(res, c);
//         }
//         else{
//             int a = pop(res) - '0';
//             int b = pop(res) - '0';
//             switch (c)
//             {
//                 case '^':
//                 printf("%")
//             }
//         }
//     }
// }
