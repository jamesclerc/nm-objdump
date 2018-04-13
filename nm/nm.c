/*
** EPITECH PROJECT, 2018
** nm-objdump
** File description:
** nm.c
*/

#include "../include/nm.h"

void add_sym_sect(t_data *s)
{
        s->symb = (Elf64_Sym *)((s->file_data) + s->symtab->sh_offset);
        s->section_sym = ((char *)((s->file_data) + s->strtab->sh_offset));
}

void check_symbol(t_data *s, char *file)
{
        t_symb **symb = NULL;
        int i = 0;

        if (!s->symtab || (s->symtab->sh_size / s->symtab->sh_entsize) == 0){
                fprintf(stderr, "./my_nm: %s: no symbols\n", file);
        } else {
                add_sym_sect(s);
                symb = get_symbol(s);
                for (i = 0; symb[i]; i++);
                qsort(symb, i, sizeof(t_symb *), &cmp);
                print_everything(symb);
        }
}

void do_nm(t_data *s, char *file)
{
	int i = -1;

        s->secttab = (char *)((s->file_data) + s->elf64_shdr[s->elf64_ehdr->e_shstrndx].sh_offset);
        while (i++ < s->elf64_ehdr->e_shnum){
                if (!strcmp(&s->secttab[s->elf64_shdr[i].sh_name], ".symtab"))
                        s->symtab = (Elf64_Shdr *)&s->elf64_shdr[i];
                else if (!strcmp(&s->secttab[s->elf64_shdr[i].sh_name], ".strtab"))
                        s->strtab = (Elf64_Shdr *)&s->elf64_shdr[i];
        }
	check_symbol(s, file);
}

void nm(char *file, t_data *s, int arg)
{
	s->elf64_ehdr = (Elf64_Ehdr *)s->file_data;
	if (s->elf64_ehdr->e_ident[EI_CLASS] == ELFCLASS32)
		printf("\n%s:     file format elf32-i386\n", file);
	else {
		s->elf64_shdr = (Elf64_Shdr *)(s->file_data + s->elf64_ehdr->e_shoff);
		(arg > 2) ? printf("\n%s:\n", file): 1;
		do_nm(s, file);
	}
	munmap(s->file_data, s->filesize);
}
