/*
** EPITECH PROJECT, 2018
** nm-objdump
** File description:
** elf.c
*/

#include "objdump.h"

int	is_elf(t_data *s, char *file)
{
	Elf64_Ehdr	*elf_test;

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

void	print_flag_header2_32(t_data *s, int prev)
{
	if (s->flags & DYNAMIC){
		if (prev == 1)
			printf(", ");
		printf("DYNAMIC");
		prev = 1;
	}
	if (s->flags & D_PAGED){
		if (prev == 1)
			printf(", ");
		printf("D_PAGED");
		prev = 1;
	}
	printf("\n");
	printf("start address 0x%08zx\n\n", (size_t)(s->elf32_ehdr->e_entry));
}

void	print_flag_header_32(t_data *s)
{
	int	prev = 0;

	if (s->flags & HAS_RELOC){
		printf("HAS_RELOC");
		prev = 1;
	}
	if (s->flags & EXEC_P){
		if (prev == 1)
			printf(", ");
		printf("EXEC_P");
		prev = 1;
	}
	if (s->flags & HAS_SYMS){
		if (prev == 1)
			printf(", ");
		printf("HAS_SYMS");
		prev = 1;
	}
	print_flag_header2_32(s, prev);
}

int	print_header_32(int type, t_data *s)
{
	int i = 0;

	if (type == ET_EXEC)
		s->flags |= EXEC_P;
	else if (type == ET_DYN)
		s->flags |= DYNAMIC;
	else if (type == ET_REL)
		s->flags |= HAS_RELOC;
	while (i < s->elf32_ehdr->e_shnum){
		if (s->elf32_shdr[i].sh_type == SHT_SYMTAB
			|| s->elf32_shdr[i].sh_type == SHT_DYNSYM)
			s->flags |= HAS_SYMS;
		if (s->elf32_shdr[i].sh_type == SHT_DYNAMIC)
			s->flags |= D_PAGED;
		i++;
	}
	return (s->flags);
}
