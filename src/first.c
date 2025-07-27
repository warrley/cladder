#include "awtils.h"

void showInstructions();
void playGame(char);
char choose();

int main() {
    animation();
    char play = 's';
    
    while (play == 'S' || play == 's') {
        showInstructions();

        srand(time(NULL));
        char choice = choose();

        disable();
        sleep(1.5);
        clearScreen();
        enable();

        playGame(choice);
        
        printf(BOLD_CYAN "\n╔══════════════════════════════════════════════════╗\n" RESET);
        printf(BOLD_CYAN "║         Deseja jogar novamente? (S/N)            ║\n" RESET);
        printf(BOLD_CYAN "╚══════════════════════════════════════════════════╝\n" RESET);
        printf(BOLD_BLUE "> " RESET);
        scanf(" %c", &play);
        while (getchar() != '\n');
        
        clearScreen();
    }
    
    return 0;
}

void showInstructions() {
    clearScreen();
    
    printf(BOLD_CYAN "╔═════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD_CYAN "║" BOLD_YELLOW "                       INSTRUÇÕES DO JOGO                            " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "╠═════════════════════════════════════════════════════════════════════╣\n" RESET);
    printf(BOLD_CYAN "║" RESET " O objetivo é acertar uma sequência de %d palavras relacionadas.      "   BOLD_CYAN "║\n" RESET, num_word);
    printf(BOLD_CYAN "║" RESET " Cada palavra difere da anterior por apenas UMA letra.               " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║                                                                     ║\n" RESET);
    printf(BOLD_CYAN "║" BOLD_GREEN " ▶ Nível Fácil:" RESET " Mostra dica e a letra que muda                       " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" BOLD_YELLOW " ▶ Nível Médio:" RESET " Mostra apenas a dica                                 " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" BOLD_RED " ▶ Nível Difícil:" RESET " Mostra dica e usa palavras mais complexas          " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║                                                                     ║\n" RESET);
    printf(BOLD_CYAN "║" RESET " Você ganha pontos por cada acerto!                                  " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║                                                                     ║\n" RESET);
    printf(BOLD_CYAN "║" BOLD_WHITE " RESTRIÇÕES:                                                         " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " 1. Todas as palavras devem ter ao máximo %d letras                  " BOLD_CYAN "║\n" RESET, word_len);
    printf(BOLD_CYAN "║" RESET " 2. Não são permitidas palavras com acentos ou caracteres especiais  " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "╚═════════════════════════════════════════════════════════════════════╝\n" RESET);
    
    printf("\n\n" BOLD_BLUE "Pressione qualquer tecla para continuar..." RESET);
    
    disable(); 
    getchar();
    enable();
    clearScreen();
};

char choose() {
    printf("\n");
    printf(BOLD_CYAN "╔═════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD_CYAN "║" RESET "                          " BOLD_YELLOW "ESCOLHA O NÍVEL" RESET "                            " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "╠═════════════════════════════════════════════════════════════════════╣\n" RESET);
    printf(BOLD_CYAN "║" RESET " " BOLD_GREEN "1 - Fácil" RESET "   │ Palavras de nível 1, mostra a dica e a letra faltando " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " " BOLD_YELLOW "2 - Médio" RESET "   │ Palavras de nível 1 e mostra a dica                   " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" RESET " " BOLD_RED "3 - Difícil" RESET " │ Palavras de nível 2 e mostra a dica                   " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "╚═════════════════════════════════════════════════════════════════════╝\n" RESET);
    
    char choice;

    while(1) {
        printf(BOLD_BLUE "> " RESET);
        scanf(" %c", &choice);
        while (getchar() != '\n');  limpa o buffer para pegar apenas a primeira letra
        if(choice < '1' || choice > '3') printf(BOLD_RED "Nível inválido. Tente novamente.\n" RESET);
        else                             break;
    };

    return choice;
};

void playGame(char difficulty) {
    srand(time(NULL));
    FILE *file = fopen(data_path, "r");
    if (!file) {
        printf(BOLD_RED "╔════════════════════════════════╗\n" RESET);
        printf(BOLD_RED "║                                ║\n" RESET);
        printf(BOLD_RED "║  Arquivo 'palavras.txt' não    ║\n" RESET);
        printf(BOLD_RED "║          encontrado!           ║\n" RESET);
        printf(BOLD_RED "║                                ║\n" RESET);
        printf(BOLD_RED "╚════════════════════════════════╝\n" RESET);
        exit(1);
    };

    int valid_ids[100];
    int num_valid_ids = 0;
    char line[max_line];
    char current_level;
    int current_id;

    // pega todos os blocos validos para o nivel escolhido
    while (fgets(line, sizeof(line), file)) {
        if (awfind(line, "id:")) {
            sscanf(line, "\tid: %d", &current_id);
        } else if (awfind(line, "level:")) {
            sscanf(line, "\tlevel: %c", &current_level);
            
            if ((difficulty != '3' && current_level == '1') || (difficulty == '3' && current_level == '2')) {
                valid_ids[num_valid_ids] = current_id;
                num_valid_ids++;
            };
        };
    };

    if (num_valid_ids == 0) {
        printf(BOLD_RED "╔════════════════════════════════╗\n" RESET);
        printf(BOLD_RED "║                                ║\n" RESET);
        printf(BOLD_RED "║  Nenhum bloco válido para este ║\n" RESET);
        printf(BOLD_RED "║             nível!             ║\n" RESET);
        printf(BOLD_RED "║                                ║\n" RESET);
        printf(BOLD_RED "╚════════════════════════════════╝\n" RESET);
        fclose(file);
        exit(1);
    };

    // sortea um id valido
    int target_id = valid_ids[rand() % num_valid_ids];
    rewind(file);

    word words[num_word];
    char base[word_len + 1];
    int word_count = 0;
    char level;
    int found = 0;

    // armazena as informacoes do bloco sorteado
    while (fgets(line, sizeof(line), file) && !found) {
        if (awfind(line, "id:")) {
            int id;
            sscanf(line, "\tid: %d", &id);
            if (id == target_id) {
                found = 1;
                while (fgets(line, sizeof(line), file) && !awfind(line, "[")) {
                    if (awfind(line, "base:")) {
                        sscanf(line, "\tbase: %s", base);
                    } else if (awfind(line, "level:")) {
                        sscanf(line, "\tlevel: %c", &level);
                    } else if (awfind(line, "{word:")) {
                        sscanf(line, "\t{word: %[^,], tip: %[^}]}", words[word_count].string, words[word_count].tip);
                        word_count++;
                    };
                };
            };
        };
    };
    fclose(file);

    int score = 0;
    char previous[word_len + 1];
    awcpy(previous, base); // o previous comeca sendo a palavra base

    for (int i = 0; i < word_count; i++) {
        printf(CYAN "╔══════════════════════════════════════════════════╗\n" RESET);
        printf(CYAN "║                                                  ║\n" RESET);
        printf(CYAN "║   Nível: %-12s         %02d de %02d palavras   ║\n" RESET, (difficulty == '1') ? "Fácil" : (difficulty == '2') ? "Médio" : "Difícil",i+1, num_word);
        printf(CYAN "║                                                  ║\n" RESET);
        printf(CYAN "╚══════════════════════════════════════════════════╝\n" RESET);
        
        char guess[word_len + 1];
        char masked[word_len + 1];
        awcpy(masked, words[i].string); // copia a palavra na mascara

        if (difficulty == '1') {
            for (int j = 0; j < awlen(previous); j++) {
                if (previous[j] != words[i].string[j]) {
                    masked[j] = '_'; // substitui a letra diferente na mascara
                    break;
                };
            };
            printf(BOLD_CYAN "╔══════════════════════════════════════════════════╗\n" RESET);
            printf(BOLD_CYAN "║ Palavra anterior: " RESET "%-30s " BOLD_CYAN "║\n" RESET, (i == 0) ? base : words[i-1].string);
            printf(BOLD_CYAN "╠══════════════════════════════════════════════════╣\n" RESET);
            printf(BOLD_CYAN "║ Dica: " RESET "%-42s " BOLD_CYAN "║\n" RESET, words[i].tip);
            printf(BOLD_CYAN "║ Palavra: " RESET "%-39s " BOLD_CYAN "║\n" RESET, masked);
            printf(BOLD_CYAN "╚══════════════════════════════════════════════════╝\n" RESET);
        }
        else {
            printf(BOLD_CYAN "╔══════════════════════════════════════════════════╗\n" RESET);
            printf(BOLD_CYAN "║ Palavra anterior: " RESET "%-30s " BOLD_CYAN "║\n" RESET, (i > 0) ? words[i-1].string : base);
            printf(BOLD_CYAN "╠══════════════════════════════════════════════════╣\n" RESET);
            printf(BOLD_CYAN "║ Dica: " RESET "%-42s " BOLD_CYAN "║\n" RESET, words[i].tip);
            printf(BOLD_CYAN "╚══════════════════════════════════════════════════╝\n" RESET);
        };

        printf(BOLD_BLUE "Digite a palavra\n" BOLD_BLUE "> " RESET);
        scanf("%s", guess);

        printf(BOLD_CYAN "╔══════════════════════════════════════════════════╗\n" RESET);
        if (awcmp(guess, words[i].string) == 0) {
            printf(BOLD_CYAN "║                   " BOLD_GREEN "✓ Correto!" RESET "                     " BOLD_CYAN "║\n" RESET);
            score++;
        } else {
            printf(BOLD_CYAN "║ " BOLD_RED "✗ Errado! Era: " RESET "%-33s " BOLD_CYAN "║\n" RESET, words[i].string);
        }
        printf(BOLD_CYAN "╚══════════════════════════════════════════════════╝\n" RESET);
        
        disable();
        sleep(2);
        enable();
        clearScreen();
        awcpy(previous, words[i].string);
    }

    printf(BOLD_CYAN "╔══════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD_CYAN "║                   " BOLD_MAGENTA "FIM DO JOGO" RESET "                    " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "╠══════════════════════════════════════════════════╣\n" RESET);
    printf(BOLD_CYAN "║    " RESET "Acertos: " BOLD_YELLOW "%d/%d" RESET "                Precisão: " BOLD_YELLOW "%6.2f%%" RESET " " BOLD_CYAN "║\n" RESET, score, word_count, (float)score / word_count * 100);
    printf(BOLD_CYAN "╚══════════════════════════════════════════════════╝\n" RESET);
};