#include <stdio.h>

char op[50];            // operator stack
char val[50][10];       // operand stack
int ot = -1, vt = -1;   // tops of the two stacks
int temp = 1;           // temporary counter (t1, t2, ...)

int prec(char c)
{
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;                       // '(' has lowest priority
}

void compute()                      // one step of code generation
{
    printf("t%d = %s %c %s\n", temp, val[vt-1], op[ot], val[vt]);
    ot--;                           // pop operator
    vt--;                           // pop 2 operands, push 1 result
    sprintf(val[vt], "t%d", temp);
    temp++;
}

int main()
{
    char exp[50];
    int i;

    printf("Enter expression: ");
    scanf("%s", exp);

    for (i = 0; exp[i] != '\0'; i++)
    {
        char c = exp[i];

        if (c >= 'a' && c <= 'z')           // operand
        {
            vt++;
            val[vt][0] = c;
            val[vt][1] = '\0';
        }
        else if (c == '(')
            op[++ot] = c;
        else if (c == ')')
        {
            while (op[ot] != '(')
                compute();
            ot--;                           // remove '('
        }
        else                                // operator
        {
            while (ot >= 0 && prec(op[ot]) >= prec(c))
                compute();
            op[++ot] = c;
        }
    }

    while (ot >= 0)                         // empty the operator stack
        compute();

    printf("Result = %s\n", val[vt]);
    return 0;
}