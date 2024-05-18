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

int start(void)
{
    sfVideoMode video_mode;
    sfEvent event;
    sfVector2i mouse;
    sfTexture *texturemenu = sfTexture_createFromFile("utilities/start.png", NULL);
    sfSprite *spritemenu = sfSprite_create();
    sfSoundBuffer *soundbuffer_menu;
    sfSound *sound_menu;
    soundbuffer_menu = sfSoundBuffer_createFromFile("utilities/music_menu.wav");
    sound_menu = sfSound_create();
    sfSound_setBuffer(sound_menu, soundbuffer_menu);
    sfSound_setVolume(sound_menu, 50);
    sfSound_setLoop(sound_menu, sfTrue);
    sfSound_play(sound_menu);


    sfSoundBuffer *soundbuffer_effect;
    sfSound *sound_effect;
    soundbuffer_effect = sfSoundBuffer_createFromFile("utilities/effect.wav");
    sound_effect = sfSound_create();
    sfSound_setBuffer(sound_effect, soundbuffer_effect);
    sfSound_setVolume(sound_effect, 100);


    video_mode.width = 1920;
    video_mode.height = 1080;
    video_mode.bitsPerPixel = 32;
    sfSprite_setScale(spritemenu, (sfVector2f) {1.2, 1.2});
    sfRenderWindow *window = sfRenderWindow_create(video_mode, "Itachi : The Lost Brother", sfClose | sfResize, NULL);

    while (sfRenderWindow_isOpen(window)) {
        mouse = sfMouse_getPosition((const sfWindow *)window);
        sfRenderWindow_clear(window, sfBlack);
        if (mouse.x >= 600 && mouse.x <= 1300 && mouse.y >= 500 && mouse.y <= 800){
            if (event.type == sfEvtMouseButtonPressed) {
                sfSound_play(sound_effect);
                sfSound_stop(sound_menu);
                history(window);
            }
        }
        while (sfRenderWindow_pollEvent(window, &event)) {
           closewindow(window, event);
        }
        sfSprite_setTexture(spritemenu, texturemenu, sfTrue);
        sfRenderWindow_drawSprite(window, spritemenu, NULL);
        sfRenderWindow_display(window);
    }
}

int main(void)
{
    start();
}
