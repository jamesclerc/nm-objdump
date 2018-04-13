/*
** EPITECH PROJECT, 2018
** nm
** File description:
** nm.h
*/

#ifndef NM_H_
#define NM_H_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <elf.h>
#include <sys/mman.h>
#include "flags.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef	struct	s_data
{
	int fd;
	char *file;
	int i;
	size_t filesize;
	void *file_data;
	int error;
	int id;
        char *secttab;
        Elf64_Shdr *symtab;
        Elf64_Shdr *strtab;
        char *section_sym;
        Elf64_Sym *symb;
	Elf64_Ehdr *elf64_ehdr;
	Elf64_Shdr *elf64_shdr;
} t_data;

typedef struct s_symb {
	char *name;
	char type;
	long value;
} t_symb;


int is_elf(t_data *s, char *file);
void nm(char *file, t_data *s, int arg);
t_symb **get_symbol(t_data *s);
char find_flag(Elf32_Word flag);
char find_flag4(t_data *s, int i);
int cmp(const void *s, const void *v);
int print_everything(t_symb **symb);
	

#endif /* !NM_H_ */
