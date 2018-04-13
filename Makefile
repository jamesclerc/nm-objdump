##
## EPITECH PROJECT, 2018
## nm-objdump
## File description:
## Makefile
##

SRCNM	=	nm/main.c	\
		nm/elf.c	\
		nm/nm.c		\
		nm/symbol.c	\
		nm/flag_nm.c	

SRCOBJ	=	src/objdump.c	\
		src/header.c	\
		src/section.c	\
		src/elf.c	\
		src/obj_32.c

NAMENM	=	my_nm

NAMEOBJ	=	my_objdump

OBJNM	=	$(SRCNM:.c=.o)

OBJOBJ	=	$(SRCOBJ:.c=.o)

CFLAGS	=	-g3 -W -Wall -Wextra -I./include

all:	$(NAMENM) $(NAMEOBJ)

nm:	$(NAMENM)

objdump:	$(NAMEOBJ)

$(NAMENM): $(OBJNM)
	gcc -o $(NAMENM) $(OBJNM)

$(NAMEOBJ): $(OBJOBJ)
	gcc -o $(NAMEOBJ) $(OBJOBJ)

clean:
	rm -f $(OBJNM)
	rm -f $(OBJOBJ)

fclean:	clean
	rm -f $(NAMENM)
	rm -f $(NAMEOBJ)

re:	fclean all

.PHONY:	all clean fclean re
