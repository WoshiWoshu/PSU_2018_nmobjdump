/*
** EPITECH PROJECT, 2019
** nm/objdump
** File description:
** my_objdump.c
*/

#include <sys/stat.h>
#include <unistd.h>
#include "my_objdump.h"

static size_t get_file_size(const char *file)
{
    struct stat file_info;

    stat(file, &file_info);
    return (file_info.st_size);
}

static bool trigger_arch(elf_fformat_t elf_fformat, file_info_t file_info,
       Elf32_Ehdr *arch, const char *file)
{
    if (arch->e_ident[EI_CLASS] == ELFCLASS64) {
        if (get_elf_fields_sixty_four(&file_info, &elf_fformat) == FAILURE)
            return (FAILURE);
        arch_sixty_four(file, elf_fformat.elf_header,
        elf_fformat.fcontent, elf_fformat.name_sections);
    }
    if (arch->e_ident[EI_CLASS] == ELFCLASS32) {
        if (get_elf_fields_thirty_two(&file_info, &elf_fformat) == FAILURE)
            return (FAILURE);
        arch_thirty_two(file, elf_fformat.elf_header_ttwo,
        elf_fformat.fcontent_ttwo, elf_fformat.name_sections);
    }
    return (SUCCESS);
}

bool my_objdump(const char *file)
{
    elf_fformat_t elf_fformat;
    file_info_t file_info;
    Elf32_Ehdr *arch;

    file_info.fsize = get_file_size(file);
    if (set_file_projection(file, &file_info) == FAILURE)
        return (FAILURE);
    arch = (Elf32_Ehdr *)file_info.mmaped_data;
    if (trigger_arch(elf_fformat, file_info, arch, file) == FAILURE)
        return (FAILURE);
    if (unset_file_projection(&file_info) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}
