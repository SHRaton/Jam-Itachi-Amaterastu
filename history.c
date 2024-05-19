/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** rpg
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my.h"

int history(sfRenderWindow *window, char **av)
{
    int skip = 0;
    sfVideoMode video_mode;
    sfEvent event;
    sfVector2i mouse;
    sfTexture *texturemenu = sfTexture_createFromFile("utilities/slide1.png", NULL);
    sfSprite *spritemenu = sfSprite_create();
    sfSoundBuffer *soundbuffer_menu;
    sfSound *sound_menu;
    soundbuffer_menu = sfSoundBuffer_createFromFile("utilities/history.wav");
    sound_menu = sfSound_create();
    sfSound_setBuffer(sound_menu, soundbuffer_menu);
    sfSound_setVolume(sound_menu, 50);
    sfSound_setLoop(sound_menu, sfTrue);
    sfSound_play(sound_menu);

    sfTexture *texturemenu2 = sfTexture_createFromFile("utilities/slide2.png", NULL);
    sfSprite *spritemenu2 = sfSprite_create();
    sfTexture *texturemenu3 = sfTexture_createFromFile("utilities/slide3.png", NULL);
    sfSprite *spritemenu3 = sfSprite_create();


    sfSoundBuffer *soundbuffer_effect;
    sfSound *sound_effect;
    soundbuffer_effect = sfSoundBuffer_createFromFile("utilities/swap_page.wav");
    sound_effect = sfSound_create();
    sfSound_setBuffer(sound_effect, soundbuffer_effect);
    sfSound_setVolume(sound_effect, 100);

    sfSoundBuffer *soundbuffer_game;
    sfSound *sound_game;
    soundbuffer_game = sfSoundBuffer_createFromFile("utilities/effect.wav");
    sound_game = sfSound_create();
    sfSound_setBuffer(sound_game, soundbuffer_game);
    sfSound_setVolume(sound_game, 100);


    video_mode.width = 1920;
    video_mode.height = 1080;
    video_mode.bitsPerPixel = 32;

    while (sfRenderWindow_isOpen(window)) {
        mouse = sfMouse_getPosition((const sfWindow *)window);
        sfRenderWindow_clear(window, sfBlack);
        while (sfRenderWindow_pollEvent(window, &event)) {
           closewindow(window, event);
           if (event.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeySpace)) {
            sfSound_play(sound_effect);
            skip++;
           }
        }
        if (skip == 0) {
            sfSprite_setTexture(spritemenu, texturemenu, sfTrue);
            sfRenderWindow_drawSprite(window, spritemenu, NULL);
        }
        if (skip == 1) {
            sfSprite_setTexture(spritemenu2, texturemenu2, sfTrue);
            sfRenderWindow_drawSprite(window, spritemenu2, NULL);
        }
        if (skip == 2) {
            sfSprite_setTexture(spritemenu3, texturemenu3, sfTrue);
            sfRenderWindow_drawSprite(window, spritemenu3, NULL);
        }
        if (skip == 3) {
            sfSprite_setTexture(spritemenu3, texturemenu3, sfTrue);
            texturemenu3 = sfTexture_createFromFile("utilities/slide4.png", NULL);
            sfRenderWindow_drawSprite(window, spritemenu3, NULL);
        }
        if (skip == 4) {
            sfSprite_setTexture(spritemenu3, texturemenu3, sfTrue);
            texturemenu3 = sfTexture_createFromFile("utilities/slide5.png", NULL);
            sfRenderWindow_drawSprite(window, spritemenu3, NULL);
        }
        if (skip == 5) {
            sfSprite_setTexture(spritemenu3, texturemenu3, sfTrue);
            texturemenu3 = sfTexture_createFromFile("utilities/slide6.png", NULL);
            sfRenderWindow_drawSprite(window, spritemenu3, NULL);
        }
        if (skip == 6) {
            sfSprite_setTexture(spritemenu3, texturemenu3, sfTrue);
            texturemenu3 = sfTexture_createFromFile("utilities/slide7.png", NULL);
            sfRenderWindow_drawSprite(window, spritemenu3, NULL);
        }
        if (skip == 7) {
            sfSprite_setTexture(spritemenu3, texturemenu3, sfTrue);
            texturemenu3 = sfTexture_createFromFile("utilities/slide 10.png", NULL);
            sfRenderWindow_drawSprite(window, spritemenu3, NULL);
        }
        if (skip == 8) {
            sfSprite_setTexture(spritemenu3, texturemenu3, sfTrue);
            texturemenu3 = sfTexture_createFromFile("utilities/slide8.png", NULL);
            sfRenderWindow_drawSprite(window, spritemenu3, NULL);
        }
        if (skip == 9) {
            sfSprite_setTexture(spritemenu3, texturemenu3, sfTrue);
            texturemenu3 = sfTexture_createFromFile("utilities/slide9.png", NULL);
            sfRenderWindow_drawSprite(window, spritemenu3, NULL);
        }
        if (skip == 10) {
            sfSound_stop(sound_menu);
            sfSound_play(sound_game);
            jeu(window, av);
        }
        sfRenderWindow_display(window);
    }
}
