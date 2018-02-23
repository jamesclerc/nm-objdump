/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** main.c
*/

#include "objdump.h"

int	check_file2(char *str, t_data *s)
{
	struct	stat	p;

	stat(str, &p);
	if (p.st_size == 0)
		return (0);
	else if (!S_ISREG(p.st_mode)){
		close(s->fd);
		fprintf(stderr, "./my_objdump: '%s' ", str);
		fprintf(stderr, "is not an ordinary file\n");
		return (0);
	}
	s->filesize = p.st_size;
	return (1);
}

int	check_file(char *str, t_data *s)
{
	if ((s->fd = open(str, O_RDONLY)) == -1){
		close(s->fd);
		fprintf(stderr, "./my_objdump: '%s': No such file\n", str);
		return (0);
	}
	if (check_file2(str, s) == 0)
		return (0);
	if (!is_elf(s, str)){
		fprintf(stderr, "./my_objdump: %s: ", str);
		fprintf(stderr, "File format not recognized\n");
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
