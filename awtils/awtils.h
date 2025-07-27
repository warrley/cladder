#ifndef AWTILS_H
#define AWTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define word_len 45
#define tip_len 45
#define num_word 4
#define max_line 256

struct Word {
    char string[word_len + 1];
    char tip[tip_len + 1];
};

typedef struct Word word;

int awcmp(char *s1, char *s2);
int awlen(char *s1);
void awcpy(char *s1, char *s2);
char *awfind(char *text, char *search);
int verifyWord(word *words, char *initial, int index);
int diffLetter(char *word1, char *word2);
void clearScreen();
int lastId();
void animation();
void disable();
void enable();

#endif
