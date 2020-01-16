/*
** EPITECH PROJECT, 2019
** nm objdump
** File description:
** print_arch_thirty_two.c
*/

#include <stdio.h>
#include "my_objdump.h"

static bool ofile_st = false;

bool get_elf_fields_thirty_two(file_info_t *file_info,
     elf_fformat_t *elf_field)
{
    elf_field->elf_header_ttwo = (Elf32_Ehdr *)file_info->mmaped_data;
    elf_field->fcontent_ttwo = (Elf32_Shdr *)(file_info->mmaped_data +
    elf_field->elf_header_ttwo->e_shoff);
    elf_field->name_sections = (char *)(file_info->mmaped_data +
    elf_field->fcontent_ttwo[elf_field->elf_header_ttwo->e_shstrndx].sh_offset);
    return (SUCCESS);
}

static void flag_f(const char *file, Elf32_Ehdr elf_header)
{
    printf("\n%s:%5cfile format elf32-i386\n", file, ' ');
    printf("architecture: i386, ");
    if (elf_header.e_type == ET_REL) {
        printf("flags 0x00000011:\nHAS_RELOC, HAS_SYMS\n");
        ofile_st = true;
    }
    else if (elf_header.e_type == ET_DYN)
        printf("flags 0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED\n");
    else
        printf("flags 0x00000112:\nEXEC_P, HAS_SYMS, D_PAGED\n");
    printf("start address 0x%08x\n\n", elf_header.e_entry);
}

static void flag_s(Elf32_Shdr curr_section, Elf32_Ehdr *elf_header,
       const char *name_section, fbrowse_t fbrws)
{
    unsigned char *content_section =
    (unsigned char *)elf_header + curr_section.sh_offset;

    fbrws.addr = curr_section.sh_addr;
    printf("Contents of section %s:\n", name_section);
    for (int ndx = 0; fbrws.x < (int)curr_section.sh_size; ++ndx) {
       fbrws.max = curr_section.sh_offset + curr_section.sh_size - fbrws.top;
       printf(" %04x", fbrws.addr + fbrws.x);
       for (register int it = fbrws.x; it < 16 + fbrws.x; ++it) {
            if (!(it % 4))
                printf(" ");
            if (it < fbrws.max)
                printf("%02x", content_section[it]);
            else
                printf("  ");
        }
        printf("  ");
        fbrws.x += 16;
        print_ascii(fbrws.x, content_section, fbrws.max);
    }
}

void arch_thirty_two(const char *file,
     Elf32_Ehdr *elf_header,
     Elf32_Shdr *file_content,
     const char *name_sections)
{
    fbrowse_t fbrws;

    flag_f(file, *elf_header);
    for (int i = 1; i < elf_header->e_shnum; i++) {
        fbrws.top = file_content[i].sh_offset;
        if ((file_content[i].sh_size && file_content[i].sh_name
        && strcmp(&name_sections[file_content[i].sh_name], ".shstrtab")
        && strcmp(&name_sections[file_content[i].sh_name], ".strtab")
        && strcmp(&name_sections[file_content[i].sh_name], ".symtab")
        && strcmp(&name_sections[file_content[i].sh_name], ".bss")
        && strncmp(&name_sections[file_content[i].sh_name], ".rela", 5))
        || (!strncmp(&name_sections[file_content[i].sh_name], ".rela", 5)
        && ofile_st == false)) {
            fbrws.max = 0;
            fbrws.x = 0;
            flag_s(file_content[i], elf_header,
            &name_sections[file_content[i].sh_name], fbrws);
            fbrws.top += 16;
        }
    }
}
