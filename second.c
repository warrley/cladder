#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "awtils.h"

struct Word {
	char string[word_len + 1];
	char tip[tip_len + 1];
};

typedef struct Word word;

void insertWords(word *words, char *initial, char *level);
void writeFile(word *words, char *initial, char level);
void clearScreen();

int main() {
	char initial[word_len + 1];
	char level;
	word words[num_word];
	
	insertWords(words, initial, &level);

	writeFile(words, initial, level);

	return 0;
};

void insertWords(word *words, char *initial, char *level) {
	printf("digite a palavra inicial: ");
	scanf(" %s", initial);
	
	printf("liste %d palavras sendo diferentes apenas por uma letra\n", num_word);

	for(int i = 0; i < num_word; i++) {
        clearScreen();
        printf("--- Palavra %d de %d ---\n", i+1, num_word);
        printf("Palavra anterior: %s\n", (i == 0) ? initial : words[i-1].string);
        
        do {
			// sleep(1);
			// clearScreen();
            printf("\ndigite uma palavra que difere em 1 letra de %s: ", (i == 0) ? initial : words[i-1].string);
            scanf(" %s", words[i].string);
        } while(!verifyWord(words, initial, i));
    }
	
	for(int i = 0; i < num_word; i++) {
		printf("\ndica da palavra %s: ", words[i].string);
		scanf(" %[^\n]", words[i].tip);
	}
	
	char copyLevel;
	printf("\nescolha o nivel de dificuldade desse bloco de palavras");
	while(1) {
		printf("\n[1] - Fácil");
		printf("\n[2] - Médio");
		printf("\n[3] - Difícil\n");
		scanf(" %c", &copyLevel);
		if(copyLevel < '1' || copyLevel > '3') printf("escolha um nivel valido.");
		else 					   break;
	}
	*level = copyLevel;
};

void writeFile(word *words, char *initial, char level){
	FILE *save = fopen("palavras.txt", "a");
	if(!save) {
		printf("erro ao abrir o arquv");
		exit(1);
	}
	fprintf(save, "[\n\tid: %d\n\tlevel: %c\n\theader: %s\n", 0, level, initial);

	for(int i = 0; i < num_word; i++) {
		fprintf(save, "\t{word: %s, tip: %s}\n", words[i].string, words[i].tip);
	}

	fprintf(save, "]\n");
	
	fclose(save);
	printf("palavras salvas com sucesso");
};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};