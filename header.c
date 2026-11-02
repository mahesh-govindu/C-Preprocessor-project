#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void header_file_inclusion(FILE *fp, FILE *fd, char *s)
{
    char a[] = "include";
    char *filename = malloc(100 * sizeof(char));

    if (filename == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    int i = 0;
    int ch, capacity = 100, found = 0;
    int len;
    char end;

    len = strlen(s);
    fseek(fp, -len, SEEK_CUR);

    ch = fgetc(fp);

    while (ch == ' ' || ch == '\t')
        ch = fgetc(fp);

    i = 0;

    while ((ch == a[i]) && a[i])
    {
        ch = fgetc(fp);
        i++;
    }

    if (a[i] == '\0' &&
        (ch == ' ' || ch == '\t' || ch == '<' || ch == '"'))
    {
        while (ch == ' ' || ch == '\t')
            ch = fgetc(fp);

        i = 0;

        if (ch == '<')
            end = '>';
        else if (ch == '"')
            end = '"';
        else
        {
            free(filename);
            return;
        }

        while ((ch = fgetc(fp)) != end && ch != EOF)
        {
            if (i >= capacity - 1)
            {
                int new_capacity = capacity * 2;

                char *temp = realloc(filename, new_capacity);

                if (temp == NULL)
                {
                    printf("Memory allocation failed\n");
                    free(filename);
                    return;
                }

                filename = temp;
                capacity = new_capacity;
            }

            filename[i++] = ch;
        }

        if (ch == end)
        {
            filename[i] = '\0';
            found = 1;
        }
    }

    if (found == 1)
    {
        FILE *fr = fopen(filename, "r");

        if (fr == NULL)
        {
            char path[200];

            sprintf(path, "/usr/include/%s", filename);

            fr = fopen(path, "r");
        }

        if (fr == NULL)
        {
            printf("Header file not found: %s\n", filename);
        }
        else
        {
            while ((ch = fgetc(fr)) != EOF)
                fputc(ch, fd);

            fclose(fr);
        }
    }

    free(filename);
}
