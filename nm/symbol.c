/*
** EPITECH PROJECT, 2018
** nm-objdump
** File description:
** symbol.c
*/

#include "../include/nm.h"

char find_type3(t_data *s, int i)
{
	Elf32_Word flag = s->elf64_shdr[s->symb[i].st_shndx].sh_flags;
	uint32_t x = s->elf64_shdr[s->symb[i].st_shndx].sh_type;

	if (x == SHT_NOBITS){
		if (flag == (SHF_ALLOC | SHF_WRITE) ||
		flag == (SHF_ALLOC | SHF_WRITE | SHF_TLS))
			return ('b');
		if (flag == (SHF_ALLOC | SHF_WRITE | SHF_IA_64_SHORT))
			return ('s');
	}
	if (x == SHT_PROGBITS)
		return (find_flag(flag));
	else if (x == SHT_FINI_ARRAY || x == SHT_INIT_ARRAY)
		return ('t');
	else
		return ('?');
}

char find_type2(t_data *s, int i, int bind, int type)
{
	char c = 'M';

	if (s->symb[i].st_shndx == SHN_UNDEF) {
		if (bind != STB_WEAK)
			c = 'U';
		else
			c = (type == STT_OBJECT) ? 'v' : 'w';
	}
	if (c == 'M' && bind == STB_WEAK)
		c = (type != STT_OBJECT) ? 'W' : 'V';
	if (c == 'M' && bind == STB_GNU_UNIQUE)
		c = 'u';
	if (c == 'M')
		c = '?';
	if (c == '?')
		c = find_type3(s, i);
	if (c == '?')
		c = find_flag4(s, i);
	return ((bind != STB_GLOBAL) ? c : toupper(c));
	
}

char find_type(int i, t_data *s, char k)
{
	int bind = ELF64_ST_BIND(s->symb[i].st_info);
	int type = ELF64_ST_TYPE(s->symb[i].st_info);

	if (s->symb[i].st_shndx == SHN_COMMON)
		return 'C';
	else if (s->symb[i].st_shndx == SHN_ABS)
		return 'A';
	k = find_type2(s, i, bind, type);
	return (k);
}

t_symb *sym_tab_create(t_data *s, int i)
{
	t_symb *new = malloc(sizeof(t_symb));

	if (!new)
		return NULL;
	new->type = find_type(i, s, '?');
	if (s->symb[i].st_shndx == SHN_UNDEF)
		new->value = -1;
	else
		new->value = s->symb[i].st_value;
	new->name = &s->section_sym[s->symb[i].st_name];
	return (new);
}

t_symb **get_symbol(t_data *s)
{
	int i = 0;
	int nb_sym = s->symtab->sh_size / s->symtab->sh_entsize;
	t_symb **sym = calloc(sizeof(t_symb), nb_sym);
	
	s->id = 0;
	while (i < nb_sym){
		if (s->symb[i].st_info != STT_FILE
		&& s->symb[i].st_name != 0) {
			sym[s->id] = sym_tab_create(s, i);
                        printf("%s  %c  %ld\n", sym[s->id]->name, sym[s->id]->type , sym[s->id]->value);
                        s->id = s->id + 1;
		}
                i = i + 1;
	}
        exit(0);
	return (sym);
}