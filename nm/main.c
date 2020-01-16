/*
** EPITECH PROJECT, 2019
** nm/objdump
** File description:
** main.c
*/

#include <unistd.h>
#include <sys/stat.h>
#include "my_objdump.h"

static size_t get_file_size(const char *file)
{
    struct stat file_info;

    stat(file, &file_info);
    return (file_info.st_size);
}

static bool my_nm(const char *file)
{
    file_info_t file_info;

    file_info.fsize = get_file_size(file);
    if (set_file_projection(file, &file_info) == FAILURE)
        return (FAILURE);
    if (unset_file_projection(&file_info) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}

static int check_access_file(char **av, int i, int j)
{
    if (av[i][j] == '.' && av[i][j + 1] == 'a'
    && av[i][j + 2] == '\0') {
        if (access(av[i], F_OK) == -1) {
            write(2, FILE_CORRUPTED, strlen(FILE_CORRUPTED));
            return (FAILURE);
        } else
            return (HANDLE_LIB);
    }
    return (SUCCESS);
}

static int handle_lib_file(char **av, int i)
{
    for (int j = 0; av[i][j] != '\0'; ++j) {
        if (check_access_file(av, i, j) == FAILURE)
            return (FAILURE);
        if(check_access_file(av, i, j) == HANDLE_LIB)
            return (HANDLE_LIB);
    }
    return (SUCCESS);
}

int main(int ac, char **av)
{
    if (ac <= 1)
        if (my_nm("./a.out") == FAILURE)
            return (84);
    for (int i = 1; i < ac; ++i) {
        if (handle_lib_file(av, i) == FAILURE)
            return (84);
        if (handle_lib_file(av, i) == HANDLE_LIB)
            return (0);
        if (my_nm(av[i]) == FAILURE)
            return (84);
    }
    return (0);
}
