/*
** EPITECH PROJECT, 2019
** nm/objdump
** File description:
** conduct_projection.c
*/

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "my_objdump.h"

bool unset_file_projection(file_info_t *file_info)
{
    if (close(file_info->fd) == -1) {
        write(2, FILE_NOT_CLOSE, strlen(FILE_NOT_CLOSE));
        return (FAILURE);
    }
    if (munmap(file_info->mmaped_data, file_info->fsize) == -1) {
        write(2, PROJ_NOT_CLOSE, strlen(PROJ_NOT_CLOSE));
        return (FAILURE);
    }
    return (SUCCESS);
}

bool set_file_projection(const char *file, file_info_t *file_info)
{
    char *projection;

    if ((file_info->fd = open(file, O_RDONLY, 0)) == -1) {
        write(2, FILE_CORRUPTED, strlen(FILE_CORRUPTED));
        return (FAILURE);
    }
    if ((file_info->mmaped_data = mmap(NULL, file_info->fsize, PROT_READ,
    MAP_PRIVATE | MAP_POPULATE, file_info->fd, 0)) == MAP_FAILED) {
        close(file_info->fd);
        write(2, WRONG_FILE, strlen(WRONG_FILE));
        return (FAILURE);
    }
    projection = (char *)file_info->mmaped_data;
    if ((projection[1] != 'E' && projection[2] != 'L' && projection[3] != 'F')
    && (projection[0] != '!' && projection[1] != '<' && projection[2] != 'a')) {
        unset_file_projection(file_info);
        write(2, WRONG_FILE, strlen(WRONG_FILE));
        return FAILURE;
    }
    return (SUCCESS);
}
