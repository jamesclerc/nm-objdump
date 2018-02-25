/*
** EPITECH PROJECT, 2018
** nm-objdump
** File description:
** obj32
*/

#include "objdump.h"

void	print_sect_32(t_data *s, int index)
{
	unsigned char	*w = (unsigned char *)((char *)s->elf32_ehdr
	+ (int)s->elf32_shdr[index].sh_offset);
	int	i = 0;
	int	addr = s->elf32_shdr[index].sh_addr;
	int	move = 0;

	while (i < (int)s->elf32_shdr[index].sh_size){
		(i % 16 == 0 ? printf(" %04x ", addr) : 0);
		printf("%02x", w[i++]);
		if ((i % 4 == 0) && (i % 16)
			&& (i < (int)s->elf32_shdr[index].sh_size))
			printf(" ");
		addr = ((i % 16 == 0) ? addr + 16: addr);
		if (i >= (int)s->elf32_shdr[index].sh_size || i % 16 == 0){
			aff_ascii_line(i, &move, w, (char *)w);
			printf("\n");
		}
	}
}

int	check_section_print_32(char *section_n, int size, t_data *s, int i)
{
	if (!size)
		return (0);
	if (strcmp(section_n, ".bss") == 0 ||
		strcmp(section_n, ".symtab") == 0 ||
		strcmp(section_n, ".shstrtab") == 0 ||
		strcmp(section_n, ".strtab") == 0)
		return (0);
	if ((s->elf32_ehdr->e_type == ET_REL &&
		(s->elf32_shdr[i].sh_type == SHT_REL ||
		s->elf32_shdr[i].sh_type == SHT_RELA)) ||
		s->elf32_shdr[i].sh_type == SHT_NOBITS)
		return (0);
	return (1);
}

void	section_32(t_data *s)
{
	char	*strtab;

	strtab = (char *)(s->file_data +
		s->elf32_shdr[s->elf32_ehdr->e_shstrndx].sh_offset);
	for (int i = 1; i < s->elf32_ehdr->e_shnum; i++){
		if (check_section_print_32(&strtab[s->elf32_shdr[i].sh_name],
			s->elf32_shdr[i].sh_size, s, i)){
			printf("Contents of section %s:\n",
				&strtab[s->elf32_shdr[i].sh_name]);
			print_sect_32(s, i);
		}
	}
}

void	archi_32(t_data *s)
{
	printf("\n%s:     file format elf32-i386\n", s->file);
	s->elf32_ehdr = (Elf32_Ehdr*)s->file_data;
	s->elf32_shdr = (Elf32_Shdr*)(s->file_data + s->elf32_ehdr->e_shoff);
	printf("architecture: i386, flags 0x%08x:\n",
	print_header_32(s->elf32_ehdr->e_type, s));
	print_flag_header_32(s);
	section_32(s);
}
