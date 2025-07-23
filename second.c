#include <stdio.h>
#include <stdlib.h>
#include "awtils.h"

struct Word {
	int id;
	char string[word_len + 1];
	char tip[tip_len + 1];
};

typedef struct Word word;

void insertWords(word *words, char *initial, int *level);

int main() {
	char initial[word_len + 1];
	int level;
	word words[num_word];
	
	insertWords(words, initial, &level);

	FILE *save = fopen("palavras.txt", "a");
	
	if(!save) {
	    printf("erro ao abrir o arquv");
	    exit(1);
	}

	fprintf(save, "[\n\tid: %d\n\tlevel: %d\n\theader: %s\n", 0, level, initial);

	for(int i = 0; i < num_word; i++) {
        fprintf(save, "\t{word: %s, tip: %s}\n", words[i].string, words[i].tip);
    }

	fprintf(save, "]\n");
	
	fclose(save);
	printf("palavras salvas com sucesso");

	return 0;
};

void insertWords(word *words, char *initial, int *level) {
	printf("digite a palavra inicial: ");
	scanf(" %s", initial);
	
	printf("liste 4 palavras sendo diferentes apenas por uma letra\n");

	for(int i = 0; i < num_word; i++) {
		printf("palavra %d: ", i+1);
		scanf(" %s", words[i].string);
	}
	
	for(int i = 0; i < num_word; i++) {
		printf("\ndica da palavra %s: ", words[i].string);
		scanf(" %[^\n]", words[i].tip);
	}
	
	int copyLevel;
	printf("\nescolha o nivel de dificuldade desse bloco de palavras");
	while(1) {
		printf("\n[1] - Fácil");
		printf("\n[2] - Médio");
		printf("\n[3] - Difícil\n");
		scanf("%d", &copyLevel);
		if(copyLevel < 1 || copyLevel > 3) printf("escolha um nivel valido.");
		else 					   break;
	}
	*level = copyLevel;
};