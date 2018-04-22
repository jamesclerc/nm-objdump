/*
** EPITECH PROJECT, 2018
** nm-objdump
** File description:
** header.c
*/

#include "objdump.h"

void	print_flag_header2(t_data *s, int prev)
{
	if (s->flags & DYNAMIC) {
		if (prev == 1)
			printf(", ");
		printf("DYNAMIC");
		prev = 1;
	}
	if (s->flags & D_PAGED) {
		if (prev == 1)
			printf(", ");
		printf("D_PAGED");
		prev = 1;
	}
	printf("\n");
	printf("start address 0x%016zx\n", (size_t)(s->elf64_ehdr->e_entry));
	printf("\n");
}

void	print_flag_header(t_data *s)
{
	int	prev = 0;

	if (s->flags & HAS_RELOC) {
		printf("HAS_RELOC");
		prev = 1;
	}
	if (s->flags & EXEC_P) {
		if (prev == 1)
			printf(", ");
		printf("EXEC_P");
		prev = 1;
	}
	if (s->flags & HAS_SYMS) {
		if (prev == 1)
			printf(", ");
		printf("HAS_SYMS");
		prev = 1;
	}
	print_flag_header2(s, prev);
}

int	print_header(int type, t_data *s)
{
	int i = 0;

	s->flags = 0;
	if (type == ET_EXEC)
		s->flags |= EXEC_P;
	else if (type == ET_DYN)
		s->flags |= DYNAMIC;
	else if (type == ET_REL)
		s->flags |= HAS_RELOC;
	while (i < s->elf64_ehdr->e_shnum) {
		if (s->elf64_shdr[i].sh_type == SHT_SYMTAB
			|| s->elf64_shdr[i].sh_type == SHT_DYNSYM)
			s->flags |= HAS_SYMS;
		if (s->elf64_shdr[i].sh_type == SHT_DYNAMIC)
			s->flags |= D_PAGED;
		i++;
	}
	return (s->flags);
}

void	archi_64(t_data *s)
{
	printf("\n%s:     file format elf64-x86-64\n", s->file);
	s->elf64_ehdr = (Elf64_Ehdr*)s->file_data;
	s->elf64_shdr = (Elf64_Shdr*)(s->file_data + s->elf64_ehdr->e_shoff);
	printf("architecture: i386:x86-64, flags 0x%08x:\n",
	print_header(s->elf64_ehdr->e_type, s));
	print_flag_header(s);
	section(s);
}

void	objdump(char *file, t_data *s)
{
	char	*archi = (char *)s->file_data;

	s->file = file;
	if (s->filesize < 5) {
		fprintf(stderr, "./my_objdump: %s: File ", file);
		fprintf(stderr, "format not recognized\n");
		s->error = 64;
		return;
	}
	if (archi[4] == ELFCLASS64)
		archi_64(s);
	else if (archi[4] == ELFCLASS32)
		archi_32(s);
	else {
		fprintf(stderr, "./my_objdump: %s: File ", file);
		fprintf(stderr, "format not recognized\n");
		s->error = 64;
	}
}
