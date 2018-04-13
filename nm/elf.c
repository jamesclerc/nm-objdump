/*
** EPITECH PROJECT, 2018
** nm-objdump
** File description:
** elf.c
*/

#include "../include/nm.h"

int     is_elf(t_data *s, char *file)
{
	Elf64_Ehdr      *elf_test;

	s->file_data = mmap(NULL, s->filesize, PROT_READ, MAP_SHARED, s->fd, 0);
	if (s->file_data == MAP_FAILED){
		fprintf(stderr, "./my_objdump: '%s': ", file);
		fprintf(stderr, "memory dumped\n");
		return (0);
	}
	elf_test = (Elf64_Ehdr*)s->file_data;
	if (s->filesize < sizeof(Elf64_Ehdr*))
		return (0);
	if (elf_test->e_ident[EI_MAG0] == ELFMAG0 &&
	                    elf_test->e_ident[EI_MAG1] == ELFMAG1 &&
	                    elf_test->e_ident[EI_MAG2] == ELFMAG2 &&
	    elf_test->e_ident[EI_MAG3] == ELFMAG3)
		return (1);
	return (0);
}


