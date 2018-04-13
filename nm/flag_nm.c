/*
** EPITECH PROJECT, 2018
** nm-objdump
** File description:
** flag_nm.c
*/

#include "../include/nm.h"

void free_symb(t_symb **symb)
{
        int i = 0;

        while (symb[i]){
                free(symb[i]);
                i++;
        }
        free(symb);
}

int print_everything(t_symb **symb)
{
        int i = 0;

        while (symb[i]) {
                if (symb[i]->value != -1)
                        printf("%016x", (uint)(symb[i]->value));
                else
                        printf("%16c", ' ');
                printf(" %c", symb[i]->type);
                printf(" %s\n", symb[i]->name);
                i = i + 1;
        }
        free_symb(symb);
        return (1);
}

int cmp(const void *s, const void *v)
{
        t_symb *first = *((t_symb **)s);
        t_symb *sec = *((t_symb **)v);

        return (strcoll(first->name, sec->name));
}

char find_flag4(t_data *s, int i)
{
	uint32_t x = s->elf64_shdr[s->symb[i].st_shndx].sh_flags;
	uint32_t y = s->elf64_shdr[s->symb[i].st_shndx].sh_type;

	if ((x & SHF_WRITE) != SHF_WRITE){
		if (y == SHT_GROUP)
			return ('n');
		else
			return ('r');
	}
	if (s->elf64_shdr[s->symb[i].st_shndx].sh_type == SHT_DYNAMIC)
		return ('d');
	return ('n');
}

char find_flag(Elf32_Word flag)
{
	char c = 'r';

	if (flag == SHF_ALLOC)
		c ='r';
	if (flag == (SHF_ALLOC | SHF_WRITE))
		c = 'd';
	if (flag == (SHF_ALLOC | SHF_EXECINSTR))
		c = 't';
	if (flag == (SHF_ALLOC | SHF_WRITE | SHF_IA_64_SHORT))
		c = 'g';
	if (flag == SHT_NULL)
		c = 'n';
	return (c);
}