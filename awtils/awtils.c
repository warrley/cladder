#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include "awtils.h"

//tamanho string
int awlen(char *s1) {
    int i;
    for(i = 0; s1[i] != '\0'; i++);
    return i; 
};

//comparar strings
int awcmp(char *s1, char *s2) {
    int diff = 0;
    for(int i = 0; (i < awlen(s1) || i < awlen(s2)) && diff == 0; i++) {
        if(s1[i] != s2[i]) {
            diff = s1[i] - s2[i];
        };
    };
    return diff;
};

//copiar string
void awcpy(char *s1, char *s2) {
    int i;
    for(i = 0; s2[i] != '\0'; i++) {
        s1[i] = s2[i];
    };
    s1[i] = '\0';
};

//buscar string em outra
char *awfind(char *text, char *search) {
    int i, j;

    if (search[0] == '\0') return text;

    for (i = 0; i < awlen(text); i++) {
        for (j = 0; j < awlen(search); j++) {
            if (text[i + j] != search[j]) {
                break;
            };
        };

        if (j == awlen(search)) {
            return &text[i];
        };
    };

    return NULL;
};

//verificar se a palavra é valida
int verifyWord(word *words, char *initial, int index) {
    char *reference = (index == 0) ? initial : words[index-1].string;
    if(!diffLetter(words[index].string, reference)) {
        return 0;
    };
    
    for (int i = 0; i < num_word; i++) {
        if (index == i) continue;
        if (awcmp(words[index].string, words[i].string) == 0) {
            printf("a palavara %s ja esta no jogo\n", words[i].string);
            return 0;
        };
    };

    return 1;
};

//quantas letras diferentes
int diffLetter(char *word1, char *word2) {
    if(awlen(word1) != awlen(word2)) {
        printf("as palavras devem ter o mesmo tamanho\n");
        return 0;
    };

    int diff = 0;
    for(int i = 0; i < awlen(word1); i++) {
        if(word1[i] != word2[i]) diff++;
    };

    if(diff == 0) {
        printf("a palavra %s ja esta no jogo\n", word2);
        return 0;
    } else if(diff > 1) {
        printf("apenas uma letra deve ser diferente de %s\n", word2);
        return 0;
    };

    return 1;
};

//limpar tela
void clearScreen() {
    system("clear || cls");
};

//pegar o ultimo id
int lastId() {
    FILE *file = fopen("palavras.txt", "r");
    if (file == NULL) {
        return 0;
    }

    int max_id = -1;
    char line[545];

    while (fgets(line, sizeof(line), file)) {
        if (awfind(line, "id:")) {
            int current_id;
            if (sscanf(line, "\tid: %d", &current_id) == 1) {
                if (current_id > max_id) {
                    max_id = current_id;
                }
            }
        }
    }

    fclose(file);
    return max_id;
}

// char* toLower(char *str) {
//     for (int i = 0; str[i] != '\0'; i++) {
//         if (str[i] >= 'A' && str[i] <= 'Z') {
//             str[i] = str[i] + 32;
//         }
//     }
//     return *str;
// }

//animacao
void animation() {
    clearScreen();
    printf("\n\n\n");
    printf("       █████╗ ██╗    ██╗ ██████╗██╗     ██████╗ \n");
    printf("      ██╔══██╗██║    ██║██╔════╝██║     ██╔══██╗\n");
    printf("      ███████║██║ █╗ ██║██║     ██║     ██║  ██║\n");
    printf("      ██╔══██║██║███╗██║██║     ██║     ██║  ██║\n");
    printf("      ██║  ██║╚███╔███╔╝╚██████╗███████╗██████╔╝\n");
    printf("      ╚═╝  ╚═╝ ╚══╝╚══╝  ╚═════╝╚══════╝╚═════╝ \n");
    printf("\n");
    
    printf("        ");
    for(int i = 0; i < 30; i++) {
        printf("▓");
        fflush(stdout);
        usleep(50000 + rand() % 100000);
    }
    
    printf("\n\n                Bem Vindo!\n");
    sleep(1);
    clearScreen();
};

//desativar o teclado no terminal
void disable() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
};

//ativar o teclado no terminal
void enable() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    tcflush(STDIN_FILENO, TCIFLUSH);
};