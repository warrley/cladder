#include <stdio.h>
#include <stdlib.h>

struct Word {
	char string[51];
	char tip[101];
};

typedef struct Word word;

int verifyWord(char [], char []);

int main() {
	word words[5];

	FILE *file = fopen("palavras.txt", "r");

	if(!file) {
		printf("não foi possível abrir o arquivo\n");
		exit(1);
	}

	for(int i = 0; i < 5; i++) {
        fscanf(file, " {word: %[^,], tip: %[^}]}", words[i].string, words[i].tip);
	}

	printf("primeira palavra: %s\n", words[0].string);
	printf("tente acertar as próximas 4 palavras, elas irão mudar apenas uma letra\n");
	
	int count = 0;
	for(int i = 1; i < 5; i++) {
		char guess[51];
		printf("dica da palavra %d: %s\n", i+1, words[i].tip);
		printf("escolha uma palavra: ");
		scanf(" %s", guess);

		if(verifyWord(guess, words[i].string)) {
			printf("parabens, palavra correta\n");
			count++;
		} else {
			printf("palavra errada\n");
            printf("a palavra era: %s\n", words[i].string);
		}
	}	

	printf("voce acertou %d de 4 palavras", count);
	
	return 0;
}

int verifyWord(char guess[], char correct[]) {
	for(int i = 0; guess[i] != '\0' || correct[i] != '\0'; i++) {
		if(guess[i] != correct[i]) return 0;
	}
	return 1;
}

// precisa ser aleatório?
// precisa de tempo?
// precisar ter avisos de erro?
//