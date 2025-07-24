#include <stdio.h>
#include "awtils.h"

struct Word {
	char string[word_len + 1];
	char tip[tip_len + 1];
};

typedef struct Word word;

int awlen(char *s1) {
    int i;
    for(i = 0; s1[i] != '\0'; i++);
    return i; 
};

int awcmp(char *s1, char *s2) {
    int diff = 0;
    for(int i = 0; (i < awlen(s1) || i < awlen(s2)) && diff == 0; i++) {
        if(s1[i] != s2[i]) {
            diff = s1[i] - s2[i];
        };
    };
    return diff;
};

void awcpy(char *s1, char *s2) {
    int i;
    for(i = 0; s2[i] != '\0'; i++) {
        s1[i] = s2[i];
    };
    s1[i] = '\0';
};

int verifyWord(word *words, char *initial, int index) {
    char *reference = (index == 0) ? initial : words[index-1].string;
    if(!diffLetter(words[index].string, reference)) {
        return 0;
    }
    
    for (int i = 0; i < num_word; i++) {
        if (index == i) continue;
        if (awcmp(words[index].string, words[i].string) == 0) {
            printf("a palavara %s ja esta no jogo\n", words[i].string);
            return 0;
        }
    }

    return 1;
}

int diffLetter(char *word1, char *word2) {
    if(awlen(word1) != awlen(word2)) {
        printf("as palavras devem ter o mesmo tamanho\n");
        return 0;
    }

    int diff = 0;
    for(int i = 0; i < awlen(word1); i++) {
        if(word1[i] != word2[i]) diff++;
    }

    if(diff == 0) {
        printf("a palavra %s ja esta no jogo\n", word2);
        return 0;
    }
    else if(diff > 1) {
        printf("apenas uma letra deve ser diferente de %s\n", word2);
        return 0;
    }

    return 1;
}