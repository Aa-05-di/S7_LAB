#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char str[])
{
    const char *keywords[] = {
        "int", "float", "char", "if", "else", "while", "for", "return"};

    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    FILE *fp;
    char ch, str[100];
    int i = 0, num, line = 1;

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return 0;
    }

    while ((ch = getc(fp)) != EOF)
    {

        /* Ignore spaces */
        if (ch == ' ' || ch == '\t')
            continue;

        /* Count lines */
        if (ch == '\n')
        {
            line++;
            continue;
        }

        /* Numbers */
        if (isdigit(ch))
        {
            num = ch - '0';

            while (isdigit(ch = getc(fp)))
            {
                num = num * 10 + (ch - '0');
            }

            printf("%d -> Number\n", num);

            ungetc(ch, fp);
        }

        /* Identifiers / Keywords */
        else if (isalpha(ch) || ch == '_')
        {
            i = 0;

            while (isalnum(ch) || ch == '_')
            {
                str[i++] = ch;
                ch = getc(fp);
            }

            str[i] = '\0';

            if (isKeyword(str))
                printf("%s -> Keyword\n", str);
            else
                printf("%s -> Identifier\n", str);

            ungetc(ch, fp);
        }

        /* Comments or Division Operator */
        else if (ch == '/')
        {
            char next = getc(fp);

            /* Single-line comment */
            if (next == '/')
            {
                while ((ch = getc(fp)) != '\n' && ch != EOF)
                    ;

                line++;
            }

            /* Multi-line comment */
            else if (next == '*')
            {
                char prev = 0;

                while ((ch = getc(fp)) != EOF)
                {
                    if (ch == '\n')
                        line++;

                    if (prev == '*' && ch == '/')
                        break;

                    prev = ch;
                }
            }

            /* Division Operator */
            else
            {
                printf("/ -> Operator\n");
                ungetc(next, fp);
            }
        }

        /* Other Operators */
        else if (ch == '+' || ch == '-' || ch == '*' ||
                 ch == '%' || ch == '=' || ch == '<' ||
                 ch == '>' || ch == '&' || ch == '|')
        {
            printf("%c -> Operator\n", ch);
        }

        /* Separators */
        else if (ch == ';' || ch == ',' || ch == '(' ||
                 ch == ')' || ch == '{' || ch == '}' ||
                 ch == '[' || ch == ']')
        {
            printf("%c -> Separator\n", ch);
        }

        /* Unknown Characters */
        else
        {
            printf("%c -> Unknown Symbol\n", ch);
        }
    }

    printf("\nTotal Lines = %d\n", line);

    fclose(fp);

    return 0;
}