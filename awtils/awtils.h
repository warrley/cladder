#ifndef AWTILS_H
#define AWTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#define word_len 45
#define tip_len 45
#define num_word 4
#define max_line (word_len + tip_len + 17)
#define data_path "data/palavras.txt"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define BOLD_RED     BOLD RED
#define BOLD_GREEN   BOLD GREEN
#define BOLD_YELLOW  BOLD YELLOW
#define BOLD_BLUE    BOLD BLUE
#define BOLD_MAGENTA BOLD MAGENTA
#define BOLD_CYAN    BOLD CYAN
#define BOLD_WHITE   BOLD WHITE

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
char *toLower(char *str);

#endif
