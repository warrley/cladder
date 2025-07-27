#include "awtils.h"

void insertWords(word*, char*, char*);
void writeFile(word*, char*, char);

int main() {
    animation();
    char initial[word_len + 1];
    char level;
    word words[num_word];
    
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║               CADASTRO DE PALAVRAS               ║\n");
    printf("╚══════════════════════════════════════════════════╝\n");
    
    insertWords(words, initial, &level);
    writeFile(words, initial, level);

    disable();
	sleep(1);
	enable();
	clearScreen();

    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║       PALAVRAS SALVAS COM SUCESSO! ID: %-4d      ║\n", lastId());
    printf("╚══════════════════════════════════════════════════╝\n");
    
    return 0;
};

void insertWords(word *words, char *initial, char *level) {
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║ Digite a palavra inicial:                        ║\n");
    printf("╚══════════════════════════════════════════════════╝\n");
    printf("> ");
    scanf(" %s", initial);

    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║ Liste %d palavras sendo diferentes apenas por     ║\n", num_word);
    printf("║ uma letra da palavra anterior                    ║\n");
    printf("╚══════════════════════════════════════════════════╝\n");

	disable();
	sleep(3);
	enable();

    for(int i = 0; i < num_word; i++) {
		clearScreen();
        
        // sleep(1.5);
        
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║                    PALAVRA %02d DE %02d                    ║\n", i+1, num_word);
        printf("╚════════════════════════════════════════════════════════╝\n");
        do {
            printf("╔════════════════════════════════════════════════════════╗\n");
            printf("║ Digite uma palavra que difere em 1 letra de %-11s║\n", (i == 0) ? initial : words[i-1].string);
            printf("╚════════════════════════════════════════════════════════╝\n");
            printf("> ");
            scanf(" %s", words[i].string);

			disable();
			sleep(1);
			enable();
			clearScreen();
        } while(!verifyWord(words, initial, i));
    }
    
    for(int i = 0; i < num_word; i++) {
        clearScreen();
		printf("╔══════════════════════════════════════════════════╗\n");
        printf("║  DICA PARA A PALAVRA  %-24s   ║\n", words[i].string);
        printf("╚══════════════════════════════════════════════════╝\n");
        printf("> ");
        scanf(" %[^\n]", words[i].tip);

		disable();
		sleep(1);
		enable();
    }

	disable();
	sleep(1);
	enable();
	clearScreen();
    
    while(1) {
		printf("╔══════════════════════════════════════════════════╗\n");
		printf("║          ESCOLHA O NÍVEL DE DIFICULDADE          ║\n");
		printf("╠══════════════════════════════════════════════════╣\n");
		printf("║ 1 - Fácil                                        ║\n");
		printf("║ 2 - Difícil                                      ║\n");
		printf("╚══════════════════════════════════════════════════╝\n");
        printf("> ");
        scanf(" %c", level);
        if(*level < '1' || *level > '2') {
            printf("╔══════════════════════════════════════════════════╗\n");
            printf("║          NÍVEL INVÁLIDO. TENTE NOVAMENTE.        ║\n");
            printf("╚══════════════════════════════════════════════════╝\n");
			disable();
			sleep(1);
			enable();
			clearScreen();
        }
        else break;
    }
};

void writeFile(word *words, char *initial, char level) {
    int id = lastId() + 1;
    
    FILE *save = fopen("palavras.txt", "a");
    if (save == NULL) {
        printf("╔══════════════════════════════════════════════════╗\n");
        printf("║              ERRO AO ABRIR O ARQUIVO!           ║\n");
        printf("╚══════════════════════════════════════════════════╝\n");
        exit(1);
    }

    fprintf(save, "[\n\tid: %d\n\tlevel: %c\n\tbase: %s\n", id, level, initial);

    for (int i = 0; i < num_word; i++) {
        fprintf(save, "\t{word: %s, tip: %s}\n", words[i].string, words[i].tip);
    }

    fprintf(save, "]\n");
    fclose(save);
}