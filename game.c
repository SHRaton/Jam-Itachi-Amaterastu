/*
** EPITECH PROJECT, 2024
** Jam-Itachi-Amaterastu
** File description:
** game
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

int saut(int *jump, sfVector2f *deplacements, double speed)
{
    if ((sfKeyboard_isKeyPressed(sfKeySpace) || *jump == 1) &&
    *jump != 2) {
        deplacements->y -= 0.5 + speed + (deplacements->y / 1400);
        *jump = 1;
        if (deplacements->y < 340) {
            *jump = 0;
        }
    }
    if (deplacements->y <= 350 || *jump == 2) {
        *jump = 2;
        deplacements->y += 0.5 + speed + (deplacements->y / 1400);
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

int compare_scores(const void *a, const void *b) {
    const Score *scoreA = (const Score *)a;
    const Score *scoreB = (const Score *)b;

    return scoreB->score - scoreA->score;
}

void save_score(int score, char *nom) {
    FILE *fichier;
    Score scores[100];
    int nb_scores = 0;

    fichier = fopen("highscore.txt", "r");
    if (fichier != NULL) {
        while (fscanf(fichier, "%49s %d", scores[nb_scores].nom, &scores[nb_scores].score) == 2) {
            nb_scores++;
        }
        fclose(fichier);
    }
    strcpy(scores[nb_scores].nom, nom);
    scores[nb_scores].score = score;
    nb_scores++;
    qsort(scores, nb_scores, sizeof(Score), compare_scores);
    fichier = fopen("highscore.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
    for (int i = 0; i < nb_scores; i++) {
        fprintf(fichier, "%s %d\n", scores[i].nom, scores[i].score);
    }
    fclose(fichier);
}

int jeu(sfRenderWindow *window, char **av)
{
    int score_b = 0;
    int score_n = 0;
    char *str = malloc(sizeof(char *) * (999));
    char *str2 = malloc(sizeof(char *) * (999));
    sfText *text = creer_text("utilities/Doctor Glitch.otf");
    sfText_setPosition(text, (sfVector2f) {1600, 150});
    sfText *text2 = creer_text("utilities/Doctor Glitch.otf");
    sfText_setPosition(text2, (sfVector2f) {1600, 150});
    sfText_setColor(text2, sfBlack);
    int jump = 0, jump_dog = 0;
    int nb = 0;
    sfEvent event;
    sfVideoMode video_mode;
    video_mode.width = 1920;
    video_mode.height = 1080;
    sfSprite *deidapiaf = cat("utilities/fireball.png");
    sfSprite *sai = cat("utilities/itachi_run.png");
    sfSprite *sai_b = cat("utilities/itachi_run.png");
    sfSprite *sai_n = cat("utilities/itachi_run.png");
    sfSprite *decor = cat("utilities/decor1.png");
    sfSprite *decor_n = cat("utilities/decor2.png");
    sfSprite *decor_b = cat("utilities/decor_b.png");
    sfSprite *yin_yang = cat("utilities/score.png");
    sfSprite *piaf = cat("utilities/crow.png");
    sfSprite *dog = cat("utilities/dog.png");
    sfSprite *barriere = cat("utilities/barriere.png");
    sfSprite *trou = cat("utilities/trou.png");
    sfSprite *shuriken = cat("utilities/shuriken.png");
    sfSprite *talk = cat("utilities/itachitalk.png");
    sfSprite *talk2 = cat("utilities/talk2.png");
    sfSprite *talk3 = cat("utilities/talk3.png");
    sfSprite *talk4 = cat("utilities/talk4.png");
    sfSprite *talk5 = cat("utilities/talk5.png");
    sfSprite *talk6 = cat("utilities/talksasuke.png");
    sfSprite *talk7 = cat("utilities/talk7.png");

    sfSprite *allrace = cat("utilities/0p.png");
    sfSprite *onep = cat("utilities/1p.png");
    sfSprite *twop = cat("utilities/2p.png");
    sfSprite *threep = cat("utilities/3p.png");

    sfSprite_setOrigin(shuriken, (sfVector2f) {420, 340});
    sfSprite_setPosition(yin_yang, (sfVector2f) {1380, 70});
    sfSprite_setScale(yin_yang, (sfVector2f) {0.5, 0.5});
    sfSprite_setScale(decor, (sfVector2f) {1.45, 1.45});
    sfSprite_setScale(dog, (sfVector2f) {2, 2});
    sfSprite_setScale(sai, (sfVector2f) {4, 4});
    sfSprite_setScale(deidapiaf, (sfVector2f) {0.5, 0.5});
    sfSprite_setScale(piaf, (sfVector2f) {4, 4});
    sfIntRect anim_sai;
    sfVector2f pos_decor = {0, -65};
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
    anim_sai.width = 74;
    anim_sai.height = 56;
    sfIntRect anim_piaf;
    anim_piaf.top = 0;
    anim_piaf.left = 0;
    anim_piaf.width = 65;
    anim_piaf.height = 42;
    sfIntRect anim_dog;
    anim_dog.top = 0;
    anim_dog.left = 0;
    anim_dog.width = 80;
    anim_dog.height = 66;
    sfIntRect anim_deidapiaf;
    anim_deidapiaf.top = 0;
    anim_deidapiaf.left = 0;
    anim_deidapiaf.width = 580;
    anim_deidapiaf.height = 172;
    sfSoundBuffer *soundbuffer;
    sfSound *sound;
    soundbuffer = sfSoundBuffer_createFromFile("utilities/ost.wav");
    sound = sfSound_create();
    sfSound_setBuffer(sound, soundbuffer);
    sfSound_setVolume(sound, 50);
    sfSound_setLoop(sound, sfTrue);
    sfSound_play(sound);

    sfSoundBuffer *voixbuffer;
    sfSound *soundvoix;
    voixbuffer = sfSoundBuffer_createFromFile("utilities/itachivoice.wav");
    soundvoix = sfSound_create();
    sfSound_setBuffer(soundvoix, voixbuffer);
    sfSound_setVolume(soundvoix, 75);

    sfSoundBuffer *voix2buffer;
    sfSound *soundvoix2;
    voix2buffer = sfSoundBuffer_createFromFile("utilities/laurentvoice.wav");
    soundvoix2 = sfSound_create();
    sfSound_setBuffer(soundvoix2, voix2buffer);
    sfSound_setVolume(soundvoix2, 80);

    sfSoundBuffer *bfbuffer;
    sfSound *soundbf;
    bfbuffer = sfSoundBuffer_createFromFile("utilities/fireball.wav");
    soundbf = sfSound_create();
    sfSound_setBuffer(soundbf, bfbuffer);
    sfSound_setVolume(soundbf, 100);

    sfSoundBuffer *shuribuffer;
    sfSound *soundshuri;
    shuribuffer = sfSoundBuffer_createFromFile("utilities/soundshuri.wav");
    soundshuri = sfSound_create();
    sfSound_setBuffer(soundshuri, shuribuffer);
    sfSound_setVolume(soundshuri, 80);

    sfSoundBuffer *buffernaru;
    sfSound *soundnaru;
    buffernaru = sfSoundBuffer_createFromFile("utilities/naruvoice.wav");
    soundnaru = sfSound_create();
    sfSound_setBuffer(soundnaru, buffernaru);
    sfSound_setVolume(soundnaru, 80);

    sfSoundBuffer *buffermedal;
    sfSound *soundmedal;
    buffermedal = sfSoundBuffer_createFromFile("utilities/checkpoint.wav");
    soundmedal = sfSound_create();
    sfSound_setBuffer(soundmedal, buffermedal);
    sfSound_setVolume(soundmedal, 80);

    sfSoundBuffer *buffersasuke;
    sfSound *soundsasuke;
    buffersasuke = sfSoundBuffer_createFromFile("utilities/sasukescream.wav");
    soundsasuke = sfSound_create();
    sfSound_setBuffer(soundsasuke, buffersasuke);
    sfSound_setVolume(soundsasuke, 80);

    sfSoundBuffer *buffersc;
    sfSound *soundsc;
    buffersc = sfSoundBuffer_createFromFile("utilities/itachiscream.wav");
    soundsc = sfSound_create();
    sfSound_setBuffer(soundsc, buffersc);
    sfSound_setVolume(soundsc, 100);


    sfClock *clock_jump = sfClock_create();
    sfClock *clock_sai = sfClock_create();
    sfClock *clock_decor = sfClock_create();
    sfClock *clock_score = sfClock_create();
    sfClock *clock_talk = sfClock_create();
    int bolorean = 0;
    double speed = 0.5;
    int rotate = 0;
    int sai_alive = 0;
    int piaf_alive = 0;
    int dog_alive = 0;

    int is_talk1 = 0;
    int is_talk2 = 0;
    int is_talk3 = 0;

    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed || event.type == sfEvtKeyPressed &&
                sfKeyboard_isKeyPressed(sfKeyEscape)) {
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
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock_jump)) > 0.00001) {
            saut(&jump, &pos_sai, speed);
            saut_dog(&jump_dog, &pos_dog);
            sfClock_restart(clock_jump);
        }
        saut_piaf(&pos_piaf);
        if (dog_alive == 1 && sai_alive == 1 && piaf_alive == 1) {
            sfSound_stop(sound);
            save_score(score_n, av[1]);
            gameover(window, av);
        }
        if (pos_barriere.x <= pos_dog.x + 20 && pos_barriere.x >= pos_dog.x - 20 && jump_dog == 0) {
            printf("DOG");
            pos_dog.x = -100000;
            pos_dog.y = -500;
            dog_alive = 1;
        }
        if (pos_shuriken.x <= pos_dog.x + 20 && pos_shuriken.x >= pos_dog.x - 20 && jump_dog == 0 && pos_shuriken.y == 750) {
            printf("SHURIKEN DOG");
            pos_dog.x = -100000;
            pos_dog.y = -500;
            dog_alive = 1;
        }
        if (pos_trou.x <= pos_sai.x + 190 && pos_trou.x >= pos_sai.x + 180 && jump == 0) {
            printf("SAI");
            pos_sai.x = -100000;
            pos_sai.y = -500;
            sai_alive = 1;
        }
        if (pos_shuriken.x <= pos_sai.x + 190 && pos_shuriken.x >= pos_sai.x + 180 && jump == 0 && pos_shuriken.y == 850) {
            printf("SHURIKEN SAI");
            pos_sai.x = -100000;
            pos_sai.y = -500;
            sai_alive = 1;
        }
        if (pos_deidapiaf.x <= pos_piaf.x + 20 && pos_piaf.x >= pos_deidapiaf.x - 20 &&
        pos_deidapiaf.y == pos_piaf.y) {
            printf("OISO");
            pos_piaf.x = -100000;
            pos_piaf.y = -500;
            piaf_alive = 1;
        }
        if (pos_shuriken.x <= pos_piaf.x + 20 && pos_piaf.x >= pos_shuriken.x - 20 &&
        pos_shuriken.y - 50 == pos_piaf.y) {
            printf("SHURIKEN OISO");
            pos_piaf.x = -100000;
            pos_piaf.y = -500;
            piaf_alive = 1;
        }
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock_sai)) > 0.1) {
            anim_sai.left += 74;
            if (anim_sai.left >= 444) {
                anim_sai.left = 0;
            }
            anim_piaf.left += 65;
            if (pos_piaf.x <= 100) {
                pos_piaf.x += 1;
            }
            if (anim_piaf.left >= 520) {
                anim_piaf.left = 0;
            }
            anim_dog.left += 81;
            if (anim_dog.left >= 400) {
                anim_dog.left = 0;
            }
            anim_deidapiaf.left += 580;
            if (anim_deidapiaf.left >= 2320) {
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
            if (pos_deidapiaf.x == 2000) {
                sfSound_play(soundbf);
            }
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
            if (pos_shuriken.x <= 2000 && pos_shuriken.x >= 1980) {
                sfSound_play(soundshuri);
            }
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
        sfRenderWindow_drawSprite(window, decor, NULL);
        sfSprite_setTextureRect(sai, anim_sai);
        sfSprite_setTextureRect(piaf, anim_piaf);
        sfSprite_setTextureRect(dog, anim_dog);
        sfSprite_setTextureRect(deidapiaf, anim_deidapiaf);
        sfRenderWindow_drawSprite(window, piaf, NULL);
        sfRenderWindow_drawSprite(window, dog, NULL);
        sfRenderWindow_drawSprite(window, barriere, NULL);
        sfRenderWindow_drawSprite(window, trou, NULL);
        sfRenderWindow_drawSprite(window, shuriken, NULL);
        sfRenderWindow_drawSprite(window, sai, NULL);
        sfRenderWindow_drawSprite(window, deidapiaf, NULL);
        sfRenderWindow_drawSprite(window, yin_yang, NULL);
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock_score)) > 0.1) {
            if (nb == 0) {
                score_n++;
            }
            sfClock_restart(clock_score);
        }
        if (nb == 0) {
            sfRenderWindow_drawText(window, text2, NULL);
        }

        if (sfTime_asSeconds(sfClock_getElapsedTime(clock_talk)) > 0.00001) {
            if (score_n == 100)
                sfSound_play(soundvoix);
            if (score_n >= 100 && score_n <= 135)
                sfRenderWindow_drawSprite(window, talk, NULL);
            if (score_n == 150)
                sfSound_play(soundvoix2);
            if (score_n > 150 && score_n < 200)
                sfRenderWindow_drawSprite(window, talk2, NULL);
            if (score_n == 220)
                sfSound_play(soundnaru);
            if (score_n > 220 && score_n < 250)
                sfRenderWindow_drawSprite(window, talk3, NULL);
            if (score_n >= 0 && score_n < 250)
                sfRenderWindow_drawSprite(window, allrace, NULL);
            if (score_n == 250)
                sfSound_play(soundmedal);
            if (score_n >= 250 && score_n < 550)
                sfRenderWindow_drawSprite(window, onep, NULL);
            if (score_n >= 550 && score_n < 800)
                sfRenderWindow_drawSprite(window, twop, NULL);
            if (score_n == 550)
                sfSound_play(soundmedal);
            if (score_n >= 800 && score_n < 1050)
                sfRenderWindow_drawSprite(window, threep, NULL);
            if (score_n == 800)
                sfSound_play(soundmedal);
            if (score_n == 570)
                sfSound_play(soundvoix2);
            if (score_n >= 570 && score_n < 620)
                sfRenderWindow_drawSprite(window, talk4, NULL);

            if (score_n == 745)
                sfSound_play(soundvoix);
            if (score_n >= 745 && score_n <= 785)
                sfRenderWindow_drawSprite(window, talk5, NULL);

            if (score_n == 850)
                sfSound_play(soundsasuke);
            if (score_n >= 850 && score_n <= 875)
                sfRenderWindow_drawSprite(window, talk6, NULL);

            if (score_n == 890)
                sfSound_play(soundsc);
            if (score_n >= 890 && score_n <= 905)
                sfRenderWindow_drawSprite(window, talk7, NULL);

            sfClock_restart(clock_talk);
        }
        if (score_n >= 1000) {
            sfSound_stop(sound);
            save_score(score_n, av[1]);
            gamewin(window, av);
        }
        sfRenderWindow_display(window);
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

int gameover(sfRenderWindow* window, char **av)
{
    sfVideoMode video_mode;
    sfEvent event;
    sfVector2i mouse;
    sfTexture *texturemenu = sfTexture_createFromFile("utilities/gameover.png", NULL);
    sfSprite *spritemenu = sfSprite_create();
    sfSoundBuffer *soundbuffer_gameover;
    sfSound *sound_gameover;
    soundbuffer_gameover = sfSoundBuffer_createFromFile("utilities/gameover.wav");
    sound_gameover = sfSound_create();
    sfSound_setBuffer(sound_gameover, soundbuffer_gameover);
    sfSound_setVolume(sound_gameover, 100);
    sfSound_play(sound_gameover);

    video_mode.width = 1920;
    video_mode.height = 1080;
    video_mode.bitsPerPixel = 32;
    while (sfRenderWindow_isOpen(window)) {
        mouse = sfMouse_getPosition((const sfWindow *)window);
        sfRenderWindow_clear(window, sfBlack);
        if (mouse.x >= 1343 && mouse.x <= 1860 && mouse.y >= 754 && mouse.y <= 859){
            if (event.type == sfEvtMouseButtonPressed) {
                sfSound_stop(sound_gameover);
                jeu(window, av);
            }
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

int gamewin(sfRenderWindow* window, char **av)
{
    sfVideoMode video_mode;
    sfEvent event;
    sfVector2i mouse;
    sfTexture *texturemenu = sfTexture_createFromFile("utilities/gamewin.png", NULL);
    sfSprite *spritemenu = sfSprite_create();
    sfSoundBuffer *soundbuffer_gameover;
    sfSound *sound_gameover;
    soundbuffer_gameover = sfSoundBuffer_createFromFile("utilities/gamewin.wav");
    sound_gameover = sfSound_create();
    sfSound_setBuffer(sound_gameover, soundbuffer_gameover);
    sfSound_setVolume(sound_gameover, 100);
    sfSound_play(sound_gameover);

    video_mode.width = 1920;
    video_mode.height = 1080;
    video_mode.bitsPerPixel = 32;
    while (sfRenderWindow_isOpen(window)) {
        mouse = sfMouse_getPosition((const sfWindow *)window);
        sfRenderWindow_clear(window, sfBlack);
        if (mouse.x >= 1343 && mouse.x <= 1860 && mouse.y >= 754 && mouse.y <= 859){
            if (event.type == sfEvtMouseButtonPressed) {
                sfSound_stop(sound_gameover);
                jeu(window, av);
            }
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
