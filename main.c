#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "header.h"
#include "comment.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: ./a.out filename\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("the file is not present\n");
        return 0;
    }

    FILE *fd = fopen("output.txt", "w");

    if (fd == NULL)
    {
        printf("the file is not opened\n");
        fclose(fp);
        return 1;
    }

    int ch;
    char s[10];

    struct macro m[100];
    int count = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '#')
        {
            fscanf(fp, "%9s", s);

            if (strcmp(s, "define") == 0)
            {
                macro_definition(fp, m, &count);
            }
            else
            {
                header_file_inclusion(fp, fd, s);
            }
        }
        else if (ch == '/')
        {
            comment_removal(ch, fp, fd);
        }
        else
        {
            macro_substitution(ch, fp, fd, m, count);
        }
    }

    fclose(fp);
    fclose(fd);

    return 0;
}
