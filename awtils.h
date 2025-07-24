#ifndef AWTILS_H
#define AWTILS_H

#define word_len 45
#define tip_len 500
#define num_word 4

struct Word;
typedef struct Word word;

int awcmp(char *s1, char *s2);
int awlen(char *s1);
void awcpy(char *s1, char *s2);
int verifyWord(word *words, char *initial, int index);
int diffLetter(char *word1, char *word2);

#endif
