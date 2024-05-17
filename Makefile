##
## EPITECH PROJECT, 2022
## makefile
## File description:
## makefile
##

all:
	gcc -o jam-bon *.c -lcsfml-graphics \
	-lcsfml-audio -lcsfml-system -lcsfml-window -lm

fclean:
	rm -f jam-bon

re:    fclean all
