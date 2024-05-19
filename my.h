/*
** EPITECH PROJECT, 2022
** my2.h
** File description:
** task02
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>

#ifndef MY_H_
    #define MY_H_

    sfSprite *cat(char *path);
    char *reverse(char *str);
    char *inttostr(int n, char s[]);
    sfText *creer_text(char *path);
    int saut (int *jump, sfVector2f *deplacements, double speed);
    int saut_dog(int *jump, sfVector2f *deplacements);
    int saut_piaf(sfVector2f *deplacements);
    int jeu(sfRenderWindow *window, char **av);
    int closewindow(sfRenderWindow *window, sfEvent event);
    int gameover(sfRenderWindow* window, char **av);
    int gamewin(sfRenderWindow* window, char **av);
    int history(sfRenderWindow *window, char **av);
    int start(char **av);

    typedef struct {
    char nom[50];
    int score;
} Score;


#endif /* !MY_H_ */
