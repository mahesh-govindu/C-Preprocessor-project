#include <stdio.h>
#include "comment.h"

void comment_removal(int ch, FILE *fp, FILE *fd)
{
    int next;

    next = fgetc(fp);

    if (next == '/')
    {
        while ((ch = fgetc(fp)) != EOF && ch != '\n');

        if (ch == '\n')
            fputc('\n', fd);
    }
    else if (next == '*')
    {
        int prev = 0;

        while ((ch = fgetc(fp)) != EOF)
        {
            if (prev == '*' && ch == '/')
                break;

            prev = ch;
        }
    }
    else
    {
        fputc('/', fd);

        if (next != EOF)
            fputc(next, fd);
    }
}
