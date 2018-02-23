/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** main.c
*/

#include "objdump.h"

int	is_elf(t_data *s, char *file)
{
	Elf64_Ehdr	*elf_test;

	s->file_data = mmap(NULL, s->filesize, PROT_READ, MAP_SHARED, s->fd, 0);
	if (s->file_data == MAP_FAILED){
		fprintf(stderr, "./my_objdump: '%s': memory dumped\n", file);
		return (0);
	}		
	elf_test = (Elf64_Ehdr*)s->file_data;
	if (s->filesize < sizeof(Elf64_Ehdr*))
		return (0);
	if (elf_test->e_ident[EI_MAG0] == ELFMAG0
	    && elf_test->e_ident[EI_MAG1] == ELFMAG1
	    && elf_test->e_ident[EI_MAG2] == ELFMAG2
	    && elf_test->e_ident[EI_MAG3] == ELFMAG3)
		return (1);
	return (0);
}

int	check_file(char *str, t_data *s)
{
	struct	stat	p;
	
	if ((s->fd = open(str, O_RDONLY)) == -1){
		close(s->fd);
		fprintf(stderr, "./my_objdump: '%s': No such file\n", str);
		return (0);
	}
	stat(str, &p);
	if (p.st_size == 0)
		return (0);
	else if (!S_ISREG(p.st_mode)){
		close(s->fd);
		fprintf(stderr, "./my_objdump: '%s' is not an ordinary file\n", str);
		return (0);
	}
	s->filesize = p.st_size;
	if (!is_elf(s, str)){
		fprintf(stderr, "./my_objdump: %s: File format not recognized\n", str);
		return (0);
	}
	return (1);
}

void	multifile(char **av, int ac, t_data *s)
{
	while (s->i < ac){
		if (check_file(av[s->i], s) != 0)
			objdump(av[s->i], s);
		s->i++;
	}
}

void	single_file(char *av, t_data *s)
{
	if (check_file(av, s) != 0)
		objdump(av, s);
}

int	main(int ac, char **av)
{
	t_data	*s;

	if (!(s = malloc(sizeof(t_data))))
		return (84);
	s->error = 0;
	s->i = 1;
	if (ac > 1)
		multifile(av, ac, s);
	else if (ac == 1)
		single_file("a.out", s);
	return (0);
}
