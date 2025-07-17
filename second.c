#include <stdio.h>
#include <stdlib.h>

struct Word {
	char string[501];
	char tip[101];
};

typedef struct Word word;

int main() {
	printf("liste 5 palavras sendo diferentes apenas por uma letra\n");
	word words[5];
	
	FILE *file = fopen("palavras.txt", "w");
	
	if(!file) {
	    printf("erro ao abrir o arquv");
	    exit(1);
	}
	

	for(int i = 0; i < 5; i++) {
	    printf("palavra %d: ", i+1);
		scanf(" %s", words[i].string);
	}
	
	for(int i = 0; i < 5; i++) {
	    printf("\ndica da palavra %s: ", words[i].string);
		scanf(" %s", words[i].tip);
	}
	

	for(int i = 0; i < 5; i++) {
	    // fprintf(file, "[%s -> %s]\n", words[i].string, words[i].tip);
        fprintf(file, "{word: %s, tip: %s}\n", words[i].string, words[i].tip);
    }
	
	fclose(file);
	
// 	for(int i = 0; i < 5; i++) {
// 		printf(" %s", words[i].string);
// 	}

	return 0;
}