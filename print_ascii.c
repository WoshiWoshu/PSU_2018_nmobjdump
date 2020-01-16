/*
** EPITECH PROJECT, 2019
** libmy
** File description:
** print_ascii characters
*/

#include <ctype.h>
#include <stdio.h>
#include "my_objdump.h"

void print_ascii(int index, unsigned char *str, int max)
{
    for (int i = index - 16; i < index; ++i)
        if (i < max) {
            if (isprint(str[i]))
                printf("%c", str[i]);
            else
                printf(".");
        } else
            printf(" ");
    printf("\n");
}
