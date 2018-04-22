/*
** EPITECH PROJECT, 2018
** nm-objdump
** File description:
** section.c
*/

#include "objdump.h"

void	aff_ascii_line(int j, int *move, unsigned char *tab, char *t)
{
	int	x = j - 1;
	int	i = (*move);

	while (++x % 16 != 0) {
		(x % 4 == 0 && x % 16) ? printf(" "): 0;
		printf("  ");
	}
	printf("  ");
	while (i < j) {
		(isprint(tab[i]) ? printf("%c", t[i]) : printf("."));
		i++;
	}
	while (i % 16 != 0) {
		printf(" ");
		i++;
	}
	*move = j;
}

void	print_sect(t_data *s, int index)
{
	int	i = 0;
	int	addr = s->elf64_shdr[index].sh_addr;
	int	move = 0;
	unsigned char	*tab = (unsigned char *)((char *)s->elf64_ehdr
		+ (int)s->elf64_shdr[index].sh_offset);

	while (i < (int)s->elf64_shdr[index].sh_size){
		(i % 16 == 0 ? printf(" %04x ", addr) : 0);
		printf("%02x", tab[i++]);
		if ((i % 4 == 0) && (i % 16)
			&& (i < (int)s->elf64_shdr[index].sh_size))
			printf(" ");
		addr = ((i % 16 == 0) ? addr + 16: addr);
		if (i >= (int)s->elf64_shdr[index].sh_size || i % 16 == 0){
			aff_ascii_line(i, &move, tab, (char *)tab);
			printf("\n");
		}
	}
}

int	check_section_printable(char *section_n, int size, t_data *s, int i)
{
	if (!size)
		return (0);
	if (strcmp(section_n, ".bss") == 0 ||
		strcmp(section_n, ".symtab") == 0 ||
		strcmp(section_n, ".shstrtab") == 0 ||
		strcmp(section_n, ".strtab") == 0)
		return (0);
	if ((s->elf64_ehdr->e_type == ET_REL &&
		(s->elf64_shdr[i].sh_type == SHT_REL ||
		s->elf64_shdr[i].sh_type == SHT_RELA)) ||
		s->elf64_shdr[i].sh_type == SHT_NOBITS)
		return (0);
	return (1);
}

void	section(t_data *s)
{
	char	*strtab;

	strtab = (char *)(s->file_data +
		s->elf64_shdr[s->elf64_ehdr->e_shstrndx].sh_offset);
	for (int i = 1; i < s->elf64_ehdr->e_shnum; i++){
		if (check_section_printable(&strtab[s->elf64_shdr[i].sh_name],
			s->elf64_shdr[i].sh_size, s, i)){
			printf("Contents of section %s:\n",
				&strtab[s->elf64_shdr[i].sh_name]);
			print_sect(s, i);
		}
	}
}
