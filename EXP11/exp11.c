#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 100
#define MAXPROD 20

typedef struct
{
    char st[MAXSIZE];
    int top;
} stack;

typedef struct
{
    char stack[MAXSIZE][MAXSIZE];
    char action[MAXSIZE][40];
    int pos[MAXSIZE];
    int steps;
} table;

void record(int post, char action[], stack *s, table *t)
{
    int len = s->top + 1;
    strncpy(t->stack[t->steps], s->st, len);
    t->stack[t->steps][len] = '\0';

    t->pos[t->steps] = post;
    strcpy(t->action[t->steps], action);

    t->steps++;
}

void display(char input[], table *t)
{

    strcat(input, "$");

    printf("\n%-20s%-20s%-20s\n", "STACK", "INPUT", "ACTION");
    printf("%-20s%-20s%-20s\n", "$", input, "START");

    for (int i = 0; i < t->steps; i++)
    {
        printf("%-19s%-20s%-20s\n", t->stack[i], input + t->pos[i], t->action[i]);
    }
}

int srp(int n, char prod[][MAXSIZE], char input[], int pos, stack *s, table *t)
{
    if (input[pos] == '\0' && s->top == 0 && s->st[0] == prod[0][0])
    {
        display(input, t);
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        int rhsLen = strlen(prod[i]) - 2;
        int stackLen = s->top + 1;
        if (stackLen >= rhsLen && strncmp(s->st + stackLen - rhsLen, prod[i] + 2, rhsLen) == 0)
        {
            s->top -= rhsLen;
            s->st[++s->top] = prod[i][0];

            char action[40];
            sprintf(action, "REDUCE %c -> %s", prod[i][0], prod[i] + 2);
            record(pos, action, s, t);

            if (srp(n, prod, input, pos, s, t))
            {
                return 1;
            }
            strncpy(s->st + s->top, prod[i] + 2, rhsLen);
            s->top += rhsLen - 1;
            t->steps--;
        }
    }
    if (input[pos] != '\0')
    {
        s->st[++s->top] = input[pos];
        record(pos + 1, "SHIFT", s, t);
        if (srp(n, prod, input, pos + 1, s, t))
        {
            return 1;
        }
        s->top--;
        t->steps--;
    }
    return 0;
}

int main()
{
    stack s;
    table t;
    int n;
    char prod[MAXPROD][MAXSIZE], input[MAXSIZE];
    printf("Enter the number of productions:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", prod[i]);
    }
    printf("Enter the input:");
    scanf("%s", input);

    s.top = -1;
    t.steps = 0;

    if (srp(n, prod, input, 0, &s, &t))
    {
        printf("String accepted\n");
    }
    else
    {
        printf("String rejected\n");
    }

    return 0;
}
