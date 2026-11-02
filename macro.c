#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "macro.h"

void macro_definition(FILE *fp, struct macro m[], int *count)
{
    int l1 = 0, l2 = 0, ch1;
    int i;

    ch1 = fgetc(fp);

    while (ch1 == ' ' || ch1 == '\t')
        ch1 = fgetc(fp);

    fseek(fp, -1, SEEK_CUR);

    while (ch1 != ' ' && ch1 != '\t' &&
           ch1 != '\n' && ch1 != EOF)
    {
        l1++;
        ch1 = fgetc(fp);
    }

    char macro_name[l1 + 1];

    fseek(fp, -(l1 + 1), SEEK_CUR);
    fscanf(fp, "%s", macro_name);

    ch1 = fgetc(fp);

    while (ch1 == ' ' || ch1 == '\t')
        ch1 = fgetc(fp);

    fseek(fp, -1, SEEK_CUR);

    while ((ch1 = fgetc(fp)) != '\n' && ch1 != EOF)
        l2++;

    char macro_val[l2 + 1];

    fseek(fp, -(l2 + 1), SEEK_CUR);
    macro_val[0] = '\0';

    if (l2 > 0)
        fgets(macro_val, l2 + 1, fp);

    if (*count < 100)
    {
        strcpy(m[*count].name, macro_name);
        strcpy(m[*count].value, macro_val);
        (*count)++;
    }
}

void macro_substitution(int ch, FILE *fp, FILE *fd,
                        struct macro m[], int count)
{
    int i, j, flag = 0;
    char token[100];

    if (isalpha(ch) || ch == '_')
    {
        j = 0;
        token[j++] = ch;

        while ((ch = fgetc(fp)) != EOF &&
               (isalnum(ch) || ch == '_'))
        {
            if (j < 99)
                token[j++] = ch;
        }

        token[j] = '\0';

        if (ch != EOF)
            ungetc(ch, fp);

        for (i = 0; i < count; i++)
        {
            if (strcmp(token, m[i].name) == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag)
            fputs(m[i].value, fd);
        else
            fputs(token, fd);
    }
    else
    {
        fputc(ch, fd);
    }
}
