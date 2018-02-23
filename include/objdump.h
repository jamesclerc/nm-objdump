/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** objdump.h
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <elf.h>
#include <sys/mman.h>
#include "flags.h"
#include <string.h>
#include <ctype.h>

typedef	struct	s_data
{
	int	fd;
	char	*file;
	int	i;
	size_t	filesize;
	void	*file_data;
	int	flags;
	int	error;
	Elf64_Ehdr    *elf64_ehdr;
	Elf64_Shdr    *elf64_shdr;
}		t_data;

void	section(t_data *s);
void	objdump(char *file, t_data *s);
int	is_elf(t_data *s, char *file);

#endif /* !OBJDUMP_H_ */
