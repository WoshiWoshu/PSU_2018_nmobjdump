/*
** EPITECH PROJECT, 2019
** nm/objdump
** File description:
** my_objdump.h
*/

#ifndef _MY_OBJ_DUMP_H_
#define _MY_OBJ_DUMP_H_

#include <string.h>
#include <stdbool.h>
#include <elf.h>

static const bool SUCCESS = true;
static const bool FAILURE = false;
static const int HANDLE_LIB = 2;

static const char WRONG_FILE[] = "[ERROR] Not an object file\n";
static const char FILE_CORRUPTED[] = "[ERROR] Can't open the file\n";
static const char FILE_NOT_CLOSE[] =
"[ERROR] The file didn't close correctly\n";
static const char PROJ_NOT_CLOSE[] =
"[ERROR] The projection didn't exited correctly\n";

typedef struct elf_fformat_s {
    Elf64_Ehdr *elf_header;
    Elf64_Shdr *fcontent;
    Elf32_Ehdr *elf_header_ttwo;
    Elf32_Shdr *fcontent_ttwo;
    const char *name_sections;
} elf_fformat_t;

typedef struct file_info_s file_info_t;

struct file_info_s {
    int fd;
    size_t fsize;
    void *mmaped_data;
};

typedef struct fbrowse_s {
    int top;
    int x;
    int max;
    int addr;
} fbrowse_t;

extern bool my_objdump(const char *file);
extern bool unset_file_projection(file_info_t *file_info);
extern bool set_file_projection(const char *file, file_info_t *file_info);
extern bool get_elf_fields_thirty_two(file_info_t *file_info,
       elf_fformat_t *elf_field);
extern bool get_elf_fields_sixty_four(file_info_t *file_info,
       elf_fformat_t *elf_field);
extern void arch_sixty_four(const char *file,
       Elf64_Ehdr *elf_header,
       Elf64_Shdr *file_content,
       const char *name_sections);
extern void arch_thirty_two(const char *file,
       Elf32_Ehdr *elf_header,
       Elf32_Shdr *file_content,
       const char *name_sections);
extern void print_ascii(int index, unsigned char *str, int max);

#endif /* _MY_OBJ_DUMP_H_ */
