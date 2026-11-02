#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>

struct macro
{
    char name[100];
    char value[200];
};

void macro_definition(FILE *fp, struct macro m[], int *count);

void macro_substitution(int ch, FILE *fp, FILE *fd,
                        struct macro m[], int count);

#endif
