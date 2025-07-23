#include <stdio.h>
#include <stdlib.h>

struct Word {
	int id;
	char string[501];
	char tip[101];
};

typedef struct Word word;

int main() {
	printf("liste 5 palavras sendo diferentes apenas por uma letra\n");
	word words[5];
	
	for(int i = 0; i < 5; i++) {
	    printf("palavra %d: ", i+1);
		scanf(" %s", words[i].string);
	}
	
	for(int i = 0; i < 5; i++) {
	    printf("\ndica da palavra %s: ", words[i].string);
		scanf(" %s", words[i].tip);
	}

	int level;
	printf("\nescolha o nivel de dificuldade desse bloco de palavras");
	while(1) {
		printf("\n[1] - Fácil");
		printf("\n[2] - Médio");
		printf("\n[3] - Difícil\n");
		scanf("%d", &level);
		if(level < 1 || level > 3) printf("escolha um nivel valido.");
		else 					   break;
	}

	FILE *save = fopen("palavras.txt", "a");
	
	if(!save) {
	    printf("erro ao abrir o arquv");
	    exit(1);
	}

	fprintf(save, "[\n\tid:%d\n\tlevel:%d\n", 0, level);

	for(int i = 0; i < 5; i++) {
        fprintf(save, "\t{word: %s, tip: %s}\n", words[i].string, words[i].tip);
    }

	fprintf(save, "]\n");
	
	fclose(save);
	printf("palavras salvas com sucesso");

	return 0;
};