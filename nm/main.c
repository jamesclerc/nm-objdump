/*
** EPITECH PROJECT, 2018
** nm
** File description:
** nm
*/

#include "../include/nm.h"

static int check_file2(char *str, t_data *s)
{
	struct  stat    p;

	stat(str, &p);
	if (p.st_size == 0){
		close(s->fd);
		return (0);
	}
	else if (!S_ISREG(p.st_mode)){
		close(s->fd);
		fprintf(stderr, "./my_nm: '%s' ", str);
		fprintf(stderr, "is not an ordinary file\n");
		return (0);
	}
	s->filesize = p.st_size;
	return (1);
}

static int check_file(char *str, t_data *s)
{
	s->fd = open(str, O_RDONLY);
	if (s->fd == -1) {
		close(s->fd);
		fprintf(stderr, "./my_nm: '%s': No such file\n", str);
		return (0);
	}
	if (check_file2(str, s) == 0) {
		return (0);
	}
	if (!is_elf(s, str)) {
		fprintf(stderr, "./my_nm: %s: ", str);
		fprintf(stderr, "File format not recognized\n");
		close(s->fd);
		return (0);
	}
	close(s->fd);
	return (1);
}

static void single_file(char *av, t_data *s, int ac)
{
	if (check_file(av, s) != 0)
		nm(av, s, ac);
	else
		s->error = 84;
}

static void multifile(char **av, int ac, t_data *s)
{
	s->error = 0;
	s->i = 1;
	while (s->i < ac){
		if (check_file(av[s->i], s) != 0)
			nm(av[s->i], s, ac);
		else
			s->error = 84;
		s->i++;
	}
}

int main(int ac, char **av)
{
	t_data *s = malloc(sizeof(t_data));
	int res;

	if (!s)
		return 84;
	if (ac == 1) {
		single_file("a.out", s, ac);
	}
	else
		multifile(av, ac, s);
	res = s->error;
        free(s);
	return res;
}
