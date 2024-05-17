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

sfSprite *cat(char *path)
{
    sfTexture *texture = sfTexture_createFromFile(path, NULL);
    sfSprite *sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    return (sprite);
}

char *reverse(char *str)
{
    char tmp, *src, *dst;
    size_t len;
    if (str != NULL) {
        len = strlen (str);
    }
    if (len > 1 && str != NULL) {
        src = str;
        dst = src + len - 1;
        while (src < dst) {
            tmp = *src;
            *src++ = *dst;
            *dst-- = tmp;
        }
    }
    return str;
}

char *inttostr(int n, char s[])
{
    int i = 0, sign = n;
    if (sign < 0)
        n = n * -1;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    reverse(s);
    s[i] = '\0';
    return (s);
}

sfText *creer_text(char *path)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile(path);
    sfText_setFont(text, font);
    sfText_setColor(text, sfBlack);
    sfText_setCharacterSize(text, 30);
    return (text);
}

int saut (int *jump, sfVector2f *deplacements, double speed)
{
    if ((sfKeyboard_isKeyPressed(sfKeySpace) || *jump == 1) &&
    *jump != 2) {
        deplacements->y -= 1 + speed - 0.5;
        *jump = 1;
        if (deplacements->y < 340) {
            *jump = 0;
        }
    }
    if (deplacements->y <= 350 || *jump == 2) {
        *jump = 2;
        deplacements->y += 1 + speed - 0.5;
        if (deplacements->y >= 700) {
            *jump = 0;
            deplacements->y = 700;
        }
    }
}

int saut_dog(int *jump, sfVector2f *deplacements)
{
    if ((sfKeyboard_isKeyPressed(sfKeyC) || *jump == 1) &&
    *jump != 2) {
        deplacements->y -= 1;
        *jump = 1;
        if (deplacements->y < 340) {
            *jump = 0;
        }
    }
    if (deplacements->y <= 350 || *jump == 2) {
        *jump = 2;
        deplacements->y += 1;
        if (deplacements->y >= 660) {
            *jump = 0;
            deplacements->y = 660;
        }
    }
}

int saut_piaf(sfVector2f *deplacements)
{
    if ((sfKeyboard_isKeyPressed(sfKeyUp))) {
        deplacements->y = 0;
    }
    if ((sfKeyboard_isKeyPressed(sfKeyDown))) {
        deplacements->y = 200;
    }
}


int jeu(void)
{
    int score_b = 0;
    int score_n = 0;
    char *str = malloc(sizeof(char *) * (999));
    char *str2 = malloc(sizeof(char *) * (999));
    sfText *text = creer_text("Doctor Glitch.otf");
    sfText_setPosition(text, (sfVector2f) {1600, 150});
    sfText *text2 = creer_text("Doctor Glitch.otf");
    sfText_setPosition(text2, (sfVector2f) {1600, 150});
    sfText_setColor(text2, sfWhite);
    int jump = 0, jump_dog = 0;
    int nb = 0;
    sfEvent event;
    sfVideoMode video_mode;
    video_mode.width = 1920;
    video_mode.height = 1080;
    sfSprite *deidapiaf = cat("deidara.png");
    sfSprite *screamers = cat("screamer.jpg");
    sfSprite_setScale(screamers, (sfVector2f) {1.5, 1.5});
    sfSprite *sai = cat("sai_nb.png");
    sfSprite *sai_b = cat("sai_b.png");
    sfSprite *sai_n = cat("sai_nb.png");
    sfSprite *decor = cat("decor.png");
    sfSprite *decor_n = cat("decor.png");
    sfSprite *decor_b = cat("decor_b.png");
    sfSprite *yin_yang = cat("yin_yang.png");
    sfSprite *piaf = cat("piaf.png");
    sfSprite *dog = cat("dog.png");
    sfSprite *barriere = cat("barriere.png");
    sfSprite *trou = cat("trou.png");
    sfSprite *shuriken = cat("shuriken.png");
    sfSprite_setOrigin(shuriken, (sfVector2f) {420, 340});
    sfSprite_setPosition(yin_yang, (sfVector2f) {1720, 200});
    sfSprite_setOrigin(yin_yang, (sfVector2f) {1024, 1024});
    sfSprite_setScale(yin_yang, (sfVector2f) {0.15, 0.15});
    sfSprite_setScale(decor, (sfVector2f) {1.45, 1.45});
    sfSprite_setScale(dog, (sfVector2f) {2, 2});
    sfSprite_setScale(sai, (sfVector2f) {3, 3});
    sfIntRect anim_sai;
    sfVector2f pos_decor = {0, -100};
    sfVector2f pos_sai = {100, 700};
    sfVector2f pos_piaf = {50, 0};
    sfVector2f pos_dog = {300, 660};
    sfVector2f pos_barriere = {1400, 700};
    sfVector2f pos_trou = {2300, 900};
    sfVector2f pos_deidapiaf = {2000, 0};
    sfVector2f pos_shuriken = {2300, 750};
    sfSprite_setPosition(shuriken, pos_shuriken);
    sfSprite_setScale(shuriken, (sfVector2f) {0.1, 0.1});
    sfSprite_setPosition(barriere, pos_barriere);
    sfSprite_setScale(barriere, (sfVector2f) {2, 2});
    sfSprite_setPosition(trou, pos_trou);
    sfSprite_setScale(trou, (sfVector2f) {2, 2});
    sfSprite_setPosition(piaf, pos_piaf);
    sfSprite_setPosition(deidapiaf, pos_deidapiaf);
    anim_sai.top = 0;
    anim_sai.left = 0;
    anim_sai.width = 81;
    anim_sai.height = 82;
    sfIntRect anim_piaf;
    anim_piaf.top = 0;
    anim_piaf.left = 0;
    anim_piaf.width = 129;
    anim_piaf.height = 154;
    sfIntRect anim_dog;
    anim_dog.top = 0;
    anim_dog.left = 0;
    anim_dog.width = 80;
    anim_dog.height = 66;
    sfIntRect anim_deidapiaf;
    anim_deidapiaf.top = 0;
    anim_deidapiaf.left = 0;
    anim_deidapiaf.width = 135;
    anim_deidapiaf.height = 149;
    sfSoundBuffer *soundbuffer;
    sfSound *sound;
    soundbuffer = sfSoundBuffer_createFromFile("ost.ogg");
    sound = sfSound_create();
    sfSound_setBuffer(sound, soundbuffer);
    sfSound_setVolume(sound, 50);
    sfSound_setLoop(sound, sfTrue);
    sfSound_play(sound);
    sfSoundBuffer *sonbuffer;
    sfSound *son;
    sonbuffer = sfSoundBuffer_createFromFile("screamer.ogg");
    son = sfSound_create();
    sfSound_setBuffer(son, sonbuffer);
    sfSound_setVolume(son, 100);
    sfClock *clock_sai = sfClock_create();
    sfClock *clock_decor = sfClock_create();
    sfClock *clock_score = sfClock_create();
    int bolorean = 0;
    double speed = 0.5;
    int rotate = 0;
    int sai_alive = 0;
    int piaf_alive = 0;
    int dog_alive = 0;
    sfRenderWindow *Window = sfRenderWindow_create(video_mode, "Jeu", sfClose | sfResize, NULL);
    while (sfRenderWindow_isOpen(Window)) {
        while (sfRenderWindow_pollEvent(Window, &event)) {
            if (event.type == sfEvtClosed) {
                exit(0);
            }
            if (event.type == sfEvtKeyPressed &&
                sfKeyboard_isKeyPressed(sfKeyEnter)) {
                if (nb == 0) {
                    sai = sai_b;
                    decor = decor_b;
                    sfSprite_setScale(decor, (sfVector2f) {1.45, 1.45});
                    sfSprite_setScale(sai, (sfVector2f) {3, 3});
                    sfSprite_setRotation(yin_yang, 180);
                    nb = 1;
                } else if (nb == 1) {
                    sai = sai_n;
                    decor = decor_n;
                    sfSprite_setScale(decor, (sfVector2f) {1.45, 1.45});
                    sfSprite_setScale(sai, (sfVector2f) {3, 3});
                    sfSprite_setRotation(yin_yang, 0);
                    nb = 0;
                }
            }
        }
        saut(&jump, &pos_sai, speed);
        saut_dog(&jump_dog, &pos_dog);
        saut_piaf(&pos_piaf);
        if (dog_alive == 1 && sai_alive == 1 && piaf_alive == 1) {
            gameover(Window);
        }
        if (pos_barriere.x <= pos_dog.x + 20 && pos_barriere.x >= pos_dog.x - 20 && jump_dog == 0) {
            printf("DOG");
            pos_dog.x = - 100000;
            pos_dog.y = - 500;
            dog_alive = 1;
        }
        if (pos_shuriken.x <= pos_dog.x + 20 && pos_shuriken.x >= pos_dog.x - 20 && jump_dog == 0 && pos_shuriken.y == 750) {
            printf("SHURIKEN DOG");
            pos_dog.x = - 100000;
            pos_dog.y = - 500;
            dog_alive = 1;
        }
        if (pos_trou.x <= pos_sai.x + 2 && pos_trou.x >= pos_sai.x - 2 && jump == 0) {
            printf("SAI");
            pos_sai.x = - 100000;
            pos_sai.y = - 500;
            sai_alive = 1;
        }
        if (pos_shuriken.x <= pos_sai.x + 30 && pos_shuriken.x >= pos_sai.x - 2 && jump == 0 && pos_shuriken.y == 850) {
            printf("SHURIKEN SAI");
            pos_sai.x = - 100000;
            pos_sai.y = - 500;
            sai_alive = 1;
        }
        if (pos_deidapiaf.x <= pos_piaf.x + 20 && pos_piaf.x >= pos_deidapiaf.x - 20 &&
        pos_deidapiaf.y == pos_piaf.y) {
            printf("OISO");
            pos_piaf.x = - 100000;
            pos_piaf.y = - 500;
            piaf_alive = 1;
        }
        if (pos_shuriken.x <= pos_piaf.x + 20 && pos_piaf.x >= pos_shuriken.x - 20 &&
        pos_shuriken.y - 50 == pos_piaf.y) {
            printf("SHURIKEN OISO");
            pos_piaf.x = - 100000;
            pos_piaf.y = - 500;
            piaf_alive = 1;
        }
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock_sai)) > 0.1) {
            anim_sai.left += 81;
            if (anim_sai.left >= 950) {
                anim_sai.left = 0;
            }
            anim_piaf.left += 130;
            if (pos_piaf.x <= 100) {
                pos_piaf.x += 1;
            }
            if (anim_piaf.left >= 1000) {
                anim_piaf.left = 0;
            }
            anim_dog.left += 81;
            if (anim_dog.left >= 400) {
                anim_dog.left = 0;
            }
            anim_deidapiaf.left += 135;
            if (anim_deidapiaf.left >= 800) {
                anim_deidapiaf.left = 0;
            }
            sfClock_restart(clock_sai);
        }
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock_decor)) > 0.001) {
            sfSprite_setRotation(shuriken, rotate);
            rotate -= 1;
            speed += 0.000015;
            pos_decor.x -= speed;
            pos_deidapiaf.x -= speed;
            if (pos_deidapiaf.x <= -200) {
                pos_deidapiaf.x = 2000;
                srand(time(NULL));
                bolorean = rand() % 2;
                if (bolorean == 0) {
                    pos_deidapiaf.y = 0;
                } else if (bolorean == 1) {
                    pos_deidapiaf.y = 200;
                }
            }
            pos_barriere.x -= speed;
            if (pos_barriere.x <= -200) {
                pos_barriere.x = 1900;
            }
            pos_trou.x -= speed;
            if (pos_trou.x <= -200) {
                pos_trou.x = 2300;
            }
            pos_shuriken.x -= 3 * speed;
            if (pos_shuriken.x <= -200) {
                pos_shuriken.x = 4800;
                srand(time(NULL));
                bolorean = rand() % 4;
                if (bolorean == 0 && piaf_alive == 0) {
                    pos_shuriken.y = 50;
                } else if (bolorean == 0) {
                    bolorean = rand() % 4;
                }
                if (bolorean == 1 && piaf_alive == 0) {
                    pos_shuriken.y = 250;
                } else if (bolorean == 1) {
                    bolorean = rand() % 4;
                }
                if (bolorean == 2 && dog_alive == 0) {
                    pos_shuriken.y = 750;
                } else if (bolorean == 2) {
                    bolorean = rand() % 4;
                }
                if (bolorean == 3 && sai_alive == 0) {
                    pos_shuriken.y = 850;
                } else if (bolorean == 3) {
                    bolorean = rand() % 4;
                }
            }
            if (pos_decor.x <= -2020) {
                pos_decor.x = 0;
            }
            sfClock_restart(clock_decor);
        }
        sfText_setString(text, str = inttostr(score_b, str));
        sfText_setString(text2, str2 = inttostr(score_n, str2));
        sfSprite_setPosition(deidapiaf, pos_deidapiaf);
        sfSprite_setPosition(piaf, pos_piaf);
        sfSprite_setPosition(dog, pos_dog);
        sfSprite_setPosition(barriere, pos_barriere);
        sfSprite_setPosition(trou, pos_trou);
        sfSprite_setPosition(shuriken, pos_shuriken);
        sfSprite_setPosition(sai, pos_sai);
        sfSprite_setPosition(decor, pos_decor);
        sfRenderWindow_drawSprite(Window, decor, NULL);
        sfSprite_setTextureRect(sai, anim_sai);
        sfSprite_setTextureRect(piaf, anim_piaf);
        sfSprite_setTextureRect(dog, anim_dog);
        sfSprite_setTextureRect(deidapiaf, anim_deidapiaf);
        sfRenderWindow_drawSprite(Window, piaf, NULL);
        sfRenderWindow_drawSprite(Window, dog, NULL);
        sfRenderWindow_drawSprite(Window, barriere, NULL);
        sfRenderWindow_drawSprite(Window, trou, NULL);
        sfRenderWindow_drawSprite(Window, sai, NULL);
        sfRenderWindow_drawSprite(Window, shuriken, NULL);
        sfRenderWindow_drawSprite(Window, deidapiaf, NULL);
        sfRenderWindow_drawSprite(Window, yin_yang, NULL);
        if (sfKeyboard_isKeyPressed(sfKeyV)) {
            sfSound_play(son);
            sfRenderWindow_drawSprite(Window, screamers, NULL);
        }
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock_score)) > 0.1) {
            if (nb == 1) {
                score_b++;
                sfRenderWindow_drawText(Window, text, NULL);
            } else if (nb == 0) {
                sfRenderWindow_drawText(Window, text2, NULL);
                score_n++;
            }
            sfClock_restart(clock_score);
        }
        if (nb == 1) {
            sfRenderWindow_drawText(Window, text, NULL);
        } else if (nb == 0) {
            sfRenderWindow_drawText(Window, text2, NULL);
        }
        sfRenderWindow_display(Window);
    }
}

int closewindow(sfRenderWindow *window, sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed &&
        sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(window);
}

int gameover(sfRenderWindow* window)
{
    sfVideoMode video_mode;
    sfEvent event;
    sfVector2i mouse;
    sfTexture *texturemenu = sfTexture_createFromFile("gameover.png", NULL);
    sfSprite *spritemenu = sfSprite_create();
    video_mode.width = 1920;
    video_mode.height = 1080;
    video_mode.bitsPerPixel = 32;
    while (sfRenderWindow_isOpen(window)) {
        mouse = sfMouse_getPosition((const sfWindow *)window);
        sfRenderWindow_clear(window, sfBlack);
        if (mouse.x >= 1343 && mouse.x <= 1860 && mouse.y >= 754 && mouse.y <= 859){
            if (event.type == sfEvtMouseButtonPressed)
                jeu();
        }
        if (mouse.x >= 77 && mouse.x <= 577 && mouse.y >= 754 && mouse.y <= 860) {
            if (event.type == sfEvtMouseButtonPressed)
                sfRenderWindow_close(window);
        }
        while (sfRenderWindow_pollEvent(window, &event)) {
           closewindow(window, event);
        }
        sfSprite_setTexture(spritemenu, texturemenu, sfTrue);
        sfRenderWindow_drawSprite(window, spritemenu, NULL);
        sfRenderWindow_display(window);
    }
}

int start(void)
{
    sfVideoMode video_mode;
    sfEvent event;
    sfVector2i mouse;
    sfTexture *texturemenu = sfTexture_createFromFile("start.png", NULL);
    sfSprite *spritemenu = sfSprite_create();
    video_mode.width = 1920;
    video_mode.height = 1080;
    video_mode.bitsPerPixel = 32;
    sfRenderWindow *window = sfRenderWindow_create(video_mode, "Jeu", sfClose | sfResize, NULL);
    while (sfRenderWindow_isOpen(window)) {
        mouse = sfMouse_getPosition((const sfWindow *)window);
        sfRenderWindow_clear(window, sfBlack);
        if (mouse.x >= 600 && mouse.x <= 1300 && mouse.y >= 500 && mouse.y <= 800){
            if (event.type == sfEvtMouseButtonPressed)
                jeu();
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
