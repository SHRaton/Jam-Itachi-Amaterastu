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
    int gameover(sfRenderWindow* window);
    char *reverse(char *str);
    char *inttostr(int n, char s[]);
    sfText *creer_text(char *path);
    int saut (int *jump, sfVector2f *deplacements, double speed);
    int saut_dog(int *jump, sfVector2f *deplacements);
    int saut_piaf(sfVector2f *deplacements);
    int jeu(sfRenderWindow *window);
    int closewindow(sfRenderWindow *window, sfEvent event);
    int gameover(sfRenderWindow* window);
    int history(sfRenderWindow *window);
    int start(void);

#endif /* !MY_H_ */
