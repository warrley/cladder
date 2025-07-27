#include "awtils.h"

void playGame(char);

int main() {
    animation();

    srand(time(NULL));
    char choice;
    
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════════════════╗\n");
    printf("║                          ESCOLHA O NÍVEL                            ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════╣\n");
    printf("║ 1 - Fácil   │ Palavras de nível 1, mostra a dica e a letra faltando ║\n");
    printf("║ 2 - Médio   │ Palavras de nível 1 e mostra a dica                   ║\n");
    printf("║ 3 - Difícil │ Palavras de nível 2 e mostra a dica                   ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════╝\n");

    while(1) {
        printf("> ");
        scanf(" %c", &choice);
        if(choice < '1' || choice > '3') printf("Nível inválido. Tente novamente.\n");
        else                             break;
    }

    disable();
    sleep(1.5);
    clearScreen();
    enable();

    playGame(choice);
    return 0;
}

void playGame(char difficulty) {
    srand(time(NULL));
    FILE *file = fopen("data/palavras.txt", "r");
    if (!file) {
        printf("╔════════════════════════════════╗\n");
        printf("║                                ║\n");
        printf("║  Arquivo 'palavras.txt' não    ║\n");
        printf("║          encontrado!           ║\n");
        printf("║                                ║\n");
        printf("╚════════════════════════════════╝\n");
        return;
    };

    int valid_ids[100];
    int num_valid_ids = 0;
    char line[max_line];
    char current_level;
    int current_id;

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
        printf("╔════════════════════════════════╗\n");
        printf("║                                ║\n");
        printf("║  Nenhum bloco válido para este ║\n");
        printf("║             nível!             ║\n");
        printf("║                                ║\n");
        printf("╚════════════════════════════════╝\n");
        fclose(file);
        return;
    };

    int target_id = valid_ids[rand() % num_valid_ids];
    rewind(file);

    word words[num_word];
    char base[word_len + 1];
    int word_count = 0;
    char level;
    int found = 0;

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
    awcpy(previous, base);

    for (int i = 0; i < word_count; i++) {
        printf("╔══════════════════════════════════════════════════╗\n");
        printf("║                                                  ║\n");
        printf("║   Nível: %-12s         %02d de %02d palavras   ║\n", (difficulty == '1') ? "Fácil" : (difficulty == '2') ? "Médio" : "Difícil",i+1, num_word);
        printf("║                                                  ║\n");
        printf("╚══════════════════════════════════════════════════╝\n");
        
        char guess[word_len + 1];
        char masked[word_len + 1];
        awcpy(masked, words[i].string);

        if (difficulty == '1') {
            for (int j = 0; j < awlen(previous); j++) {
                if (previous[j] != words[i].string[j]) {
                    masked[j] = '_';
                    break;
                };
            };
            printf("╔══════════════════════════════════════════════════╗\n");
            printf("║ Palavra anterior: %-30s ║\n", (i == 0) ? base : words[i-1].string);
            printf("╠══════════════════════════════════════════════════╣\n");
            printf("║ Dica: %-42s ║\n", words[i].tip);
            printf("║ Palavra: %-39s ║\n", masked);
            printf("╚══════════════════════════════════════════════════╝\n");
        }
        else {
            printf("╔══════════════════════════════════════════════════╗\n");
            printf("║ Palavra anterior: %-30s ║\n", (i > 0) ? words[i-1].string : base);
            printf("╠══════════════════════════════════════════════════╣\n");
            printf("║ Dica: %-42s ║\n", words[i].tip);
            printf("╚══════════════════════════════════════════════════╝\n");
        };

        // printf("╔══════════════════════════════════════════════════\n");
        printf("Digite a palavra \n> ");
        // printf("╚══════════════════════════════════════════════════╝\n");
        // printf("> ");
        scanf("%s", guess);

        printf("╔══════════════════════════════════════════════════╗\n");
        if (awcmp(guess, words[i].string) == 0) {
            printf("║                   ✓ Correto!                     ║\n");
            score++;
        } else {
            printf("║ ✗ Errado! Era: %-33s ║\n", words[i].string);
        }
        printf("╚══════════════════════════════════════════════════╝\n");
        
        disable();
        sleep(2);
        enable();
        clearScreen();
        awcpy(previous, words[i].string);
    }

    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║                   FIM DO JOGO                    ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║    Acertos: %d/%d                Precisão: %6.2f  ║\n", score, word_count, (float)score / word_count * 100);
    printf("╚══════════════════════════════════════════════════╝\n");
}