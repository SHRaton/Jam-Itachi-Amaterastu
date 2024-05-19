##
## EPITECH PROJECT, 2022
## makefile
## File description:
## makefile
##

all:
	gcc -o jam *.c -lcsfml-graphics \
	-lcsfml-audio -lcsfml-system -lcsfml-window -lm

fclean:
	rm -f jam

re:    fclean all
