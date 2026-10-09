#include <stdio.h>
#include <string.h>

/* ---------- GRAMMAR: only this part changes ---------- */
#define N 6
char  lhs[N]  = {'E',   'E',   'T',   'T', 'F', 'F'};
char *rhs[N]  = {"E+T", "T", "T*F", "F","(E)","i"};
char  start   = 'E';
/* ----------------------------------------------------- */

char stack[50], input[50];
int top = -1, i = 0;

int prec(char c)                    /* operator priority, 0 if not operator */
{
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

int rule_prec(int r)                /* priority of the last operator in rhs */
{
    for (int k = strlen(rhs[r]) - 1; k >= 0; k--)
        if (prec(rhs[r][k]))
            return prec(rhs[r][k]);
    return 0;
}

int ends_with(const char *s)        /* does the stack end with s? */
{
    int len = strlen(s);
    if (top + 1 < len) return 0;
    return strncmp(stack + top + 1 - len, s, len) == 0;
}

int reduce(char next)               /* returns rule number, or -1 */
{
    for (int r = 0; r < N; r++)
    {
        if (!ends_with(rhs[r]))
            continue;
        int rp = rule_prec(r);
        if (rp && prec(next) > rp)  /* next operator is stronger: shift */
            continue;
        top -= strlen(rhs[r]) - 1;
        stack[top] = lhs[r];
        return r;
    }
    return -1;
}

int main()
{
    printf("Enter string: ");
    scanf("%49s", input);
    printf("\n%-12s %-12s %s\n", "STACK", "INPUT", "ACTION");

    while (1)
    {
        int r = reduce(input[i]);
        if (r >= 0)
        {
            stack[top + 1] = '\0';
            printf("%-12s %-12s REDUCE %c->%s\n",
                   stack, input + i, lhs[r], rhs[r]);
            continue;
        }
        if (input[i] == '\0')
            break;
        stack[++top] = input[i++];
        stack[top + 1] = '\0';
        printf("%-12s %-12s SHIFT\n", stack, input + i);
    }

    if (top == 0 && stack[0] == start)
        printf("\nAccepted\n");
    else
        printf("\nRejected\n");
    return 0;
}