#include "awtils.h"

void showInstructions();
void insertWords(word*, char*, char*);
void writeFile(word*, char*, char);

int main() {
    animation();
    char play = 's';

    while(play == 's' || play == 'S') {
        showInstructions();
        char initial[word_len + 1];
        char level;
        word words[num_word];
        
        printf(CYAN "╔══════════════════════════════════════════════════╗\n" RESET);
        printf(CYAN "║" BOLD "               CADASTRO DE PALAVRAS               " CYAN "║\n" RESET);
        printf(CYAN "╚══════════════════════════════════════════════════╝\n" RESET);
        
        insertWords(words, initial, &level);
        writeFile(words, initial, level);

        printf(BOLD_CYAN "\n╔══════════════════════════════════════════════════╗\n" RESET);
        printf(BOLD_CYAN "║         Deseja jogar novamente? (S/N)            ║\n" RESET);
        printf(BOLD_CYAN "╚══════════════════════════════════════════════════╝\n" RESET);
        printf(BOLD_BLUE "> " RESET);
        scanf(" %c", &play);
        while (getchar() != '\n');

        clearScreen();
    }

    return 0;
};

void showInstructions() {
    clearScreen();
    
    printf(BOLD_CYAN "╔══════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD_CYAN "║" BOLD_YELLOW "                         INSTRUÇÕES DO MODO CADASTRO          " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "╠══════════════════════════════════════════════════════════════╣\n" RESET);
    printf(BOLD_CYAN "║" RESET " Você vai criar um conjunto de palavras para o jogo.          " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " Siga cuidadosamente estas regras:                            " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET "                                                              " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " " BOLD_GREEN "1." RESET " Digite uma palavra inicial (base)                         " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " " BOLD_GREEN "2." RESET " Cadastre %d palavras consecutivas                          " BOLD_CYAN "║\n" RESET, num_word);
    printf(BOLD_CYAN "║" RESET " " BOLD_GREEN "3." RESET " Cada nova palavra deve diferir da anterior por            " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET "    APENAS UMA LETRA (ex: mala → cala → cama)                 " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " " BOLD_GREEN "4." RESET " Crie uma dica útil                                        " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " " BOLD_GREEN "5." RESET " Escolha o nível de dificuldade                            " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET "    Fácil: Palavras comuns | Difícil: Palavras complexas      " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET "                                                              " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " " BOLD_RED "ATENÇÃO:" RESET "                                                     " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " - Todas as palavras devem ter ao máximo %d letras            " BOLD_CYAN "║\n" RESET, word_len);
    printf(BOLD_CYAN "║" RESET " - Todas as dicas devem ter ao máximo %d letras               " BOLD_CYAN "║\n" RESET, tip_len);
    printf(BOLD_CYAN "║" RESET " - Não são permitidos acentos ou caracteres especiais         " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "╚══════════════════════════════════════════════════════════════╝\n" RESET);
    
    printf("\n\n" BOLD_BLUE "Pressione qualquer tecla para começar o cadastro..." RESET);
    
    disable();
    getchar();
    enable();
    clearScreen();
}

void insertWords(word *words, char *initial, char *level) {
    printf(BLUE "╔══════════════════════════════════════════════════╗\n" RESET);
    printf(BLUE "║ Digite a palavra inicial:                        " BLUE "║\n" RESET);
    printf(BLUE "╚══════════════════════════════════════════════════╝\n" RESET);
    printf(BOLD "> " RESET);
    scanf(" %s", initial);
    toLower(initial);

    printf(YELLOW "╔══════════════════════════════════════════════════╗\n" RESET);
    printf(YELLOW "║ Liste %d palavras sendo diferentes apenas por     " YELLOW "║\n" RESET, num_word);
    printf(YELLOW "║ uma letra da palavra anterior                    " YELLOW "║\n" RESET);
    printf(YELLOW "╚══════════════════════════════════════════════════╝\n" RESET);

    disable();
    sleep(3);
    enable();

    for(int i = 0; i < num_word; i++) {
        clearScreen();
        
        printf(MAGENTA "╔════════════════════════════════════════════════════════╗\n" RESET);
        printf(MAGENTA "║" BOLD "                    PALAVRA %02d DE %02d                    " MAGENTA "║\n" RESET, i+1, num_word);
        printf(MAGENTA "╚════════════════════════════════════════════════════════╝\n" RESET);
        
        do {
            printf(CYAN "╔════════════════════════════════════════════════════════╗\n" RESET);
            printf(CYAN "║ Digite uma palavra que difere em 1 letra de %-11s" CYAN "║\n" RESET, 
                  (i == 0) ? initial : words[i-1].string);
            printf(CYAN "╚════════════════════════════════════════════════════════╝\n" RESET);
            printf(BOLD "> " RESET);
            char str[word_len];
            scanf(" %s", str);
            awcpy(words[i].string, toLower(str));

            disable();
            sleep(1);
            enable();
            clearScreen();
        } while(!verifyWord(words, initial, i));
    }
    
    for(int i = 0; i < num_word; i++) {
        clearScreen();
        printf(BLUE "╔══════════════════════════════════════════════════╗\n" RESET);
        printf(BLUE "║" BOLD "  DICA PARA A PALAVRA  %-24s   " BLUE "║\n" RESET, words[i].string);
        printf(BLUE "╚══════════════════════════════════════════════════╝\n" RESET);
        printf(BOLD "> " RESET);
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
        printf(YELLOW "╔══════════════════════════════════════════════════╗\n" RESET);
        printf(YELLOW "║" BOLD "          ESCOLHA O NÍVEL DE DIFICULDADE          " YELLOW "║\n" RESET);
        printf(YELLOW "╠══════════════════════════════════════════════════╣\n" RESET);
        printf(YELLOW "║ 1 - Fácil                                        " YELLOW "║\n" RESET);
        printf(YELLOW "║ 2 - Difícil                                      " YELLOW "║\n" RESET);
        printf(YELLOW "╚══════════════════════════════════════════════════╝\n" RESET);
        printf(BOLD "> " RESET);
        scanf(" %c", level);
        while (getchar() != '\n');
        
        if(*level < '1' || *level > '2') {
            printf(RED "╔══════════════════════════════════════════════════╗\n" RESET);
            printf(RED "║" BOLD "          NÍVEL INVÁLIDO. TENTE NOVAMENTE.        " RED "║\n" RESET);
            printf(RED "╚══════════════════════════════════════════════════╝\n" RESET);
            sleep(1);
            clearScreen();
        }
        else break;
    }
};

void writeFile(word *words, char *initial, char level) {
    int id = lastId() + 1;
    
    FILE *save = fopen(data_path, "a");
    if (save == NULL) {
        printf(RED "╔══════════════════════════════════════════════════╗\n" RESET);
        printf(RED "║" BOLD "              ERRO AO ABRIR O ARQUIVO!           " RED "║\n" RESET);
        printf(RED "╚══════════════════════════════════════════════════╝\n" RESET);
        exit(1);
    }

    fprintf(save, "[\n\tid: %d\n\tlevel: %c\n\tbase: %s\n", id, level, initial);

    for (int i = 0; i < num_word; i++) {
        fprintf(save, "\t{word: %s, tip: %s}\n", words[i].string, words[i].tip);
    }

    sleep(1);
    clearScreen();

    printf(GREEN "╔══════════════════════════════════════════════════╗\n" RESET);
    printf(GREEN "║" BOLD "       PALAVRAS SALVAS COM SUCESSO! ID: %-4d      " GREEN "║\n" RESET, lastId());
    printf(GREEN "╚══════════════════════════════════════════════════╝\n" RESET);

    fprintf(save, "]\n");
    fclose(save);
}