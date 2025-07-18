#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "header.h"



char *print_log(int n){
    char *log;
    if(n == 0) log = "";
    else if(n == 1) log = ">>> Por favor, digite uma opção válida!\n";
    else if(n == 2) log = ">>> Pressione (I) para iniciar!\n";
    else if(n == 3) log = ">>> O jogo está pausado!\n";
    else if(n == 4) log = ">>> A cobra bateu em si mesma!\n";
    else if(n == 5) log = ">>> A cobra bateu na parede!\n";
    else if(n == 6) log = ">>> A cobra aumentou de tamanho!\n";
    else if(n == 7) log = ">>> Você completou o jogo! Parabéns!\n";
    return log;
}

void clean_field(char **field, int *snake_i, int *snake_j, int *config, int size){
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            field[i][j] = '.';
    
    for(int k=1; k<config[3]+1; k++){  // Inicializa a cobra (tam. 4)
        snake_i[k] = size/2 +config[3]-k, snake_j[k] = size/2;
        if(snake_i[k]<size) field[snake_i[k]][snake_j[k]] = config[5]; // Posiciona o corpo no campo
    }
    
    snake_i[0] = size/2 +config[3]-1, snake_j[0] = size/2; // A posição 0 é uma cópia da cauda
    field[snake_i[config[3]]][snake_j[config[3]]] = config[4]; // Posiciona a cabeça no campo
    field[size/4-1][size-(1-1+size/4)] = config[6]; // Posiciona a fruta no campo
}

// Run = -1 > O jogador venceu/morreu e o jogo está "pausado"
// Run = 0 > O jogo está "zerado"
// Run = 1 > O jogo está pausado
// Run = 2 > O jogo está rodando
// Run = 3 > O jogo será encerrado

void game(int *error, int *config, int *flag, int *best_score){
    int run = 0, status = 2, sleep_time, free_spaces, value;
    int score = config[3], size = config[2];
    int snake_i[size*size+2], snake_j[size*size+2], x, y;

    char input, **field = malloc(size * sizeof(char *)); // Aloca a variável de input e a matriz que representa o campo
    for(int k=0; k<size; k++) field[k] = malloc(size * sizeof(char)); // Aloca o espaço de cada linha do campo

    srand(time(NULL)); // Inicializa o gerador de números aleatórios com a semente do tempo

    if(config[0] == 0) sleep_time = 800;
    else if(config[0] == 1) sleep_time = 400;
    else if(config[0] == 2) sleep_time = 200;

    while(run != 3){
        if(run == 0) clean_field(field, snake_i, snake_j, config, size); // Inicializa/Limpa o campo
        if(score > *best_score) *best_score = score; // Atualiza o melhor score

        if(!config[7]) system("cls"); // Limpa o terminal (modo normal)
        else printf("\n\n\n\n\n"); // Printa espaçamento (modo de Debug)
        printf("|   SSnake  by  eduardodpms   |   Score = %03d - Best = %03d  |\n", // Header do menu do jogo
               (config[0]+1)*(score-config[3]), (config[0]+1)*(*best_score-config[3])); // Valor dos scores atual e melhor

        separator(61, config[7]); // Printa caracteres de separação
        for(int i=0; i<size; i++, printf("|\n")){
            for(int j=0; j<(29-size); j++) printf(" ");
            for(int j=!printf("| "); j<size; j++) printf("%c ", field[i][j]);
        }
        separator(61, 0); // Printa caracteres de separação

        // Printa os guias de tecla e o log do menu do jogo
        if(run==-1)     printf("|  (R) Reiniciar   |   (C) Configurar   |    (V) Voltar     |");
        else if(run==0) printf("|   (I) Iniciar    |   (C) Configurar   |    (V) Voltar     |");
        else if(run==1) printf("|  (P) Despausar   |   (R) Reiniciar    |    (V) Voltar     |");
        else if(run==2) printf("| (P) Pausar | (R) Reiniciar | (W/A/S/D) Mover | (V) Voltar |");
        status = !printf("\n\n%s>", print_log(status)); // Printa o log e reseta a variável "status"

        if(run == 2){
            Sleep(sleep_time);

            if(_kbhit()){
                input = _getch();

                if(input == 'W' || input == 'w') x = -1, y = 0;
                else if(input == 'A' || input == 'a') x = 0, y = -1;
                else if(input == 'S' || input == 's') x = 1, y = 0;
                else if(input == 'D' || input == 'd') x = 0, y = 1;
                
                else if(input == 'P' || input == 'p') run = 1, status = 3;
                else if(input == 'R' || input == 'r') run = 0, status = 2, score = config[3];
                else if(input == 'V' || input == 'v') run = 3, *flag = 0;
                else status = 1;
                
                if(run != 2) continue;
            }

            if((snake_i[score]+x == snake_i[score-1]) && (snake_j[score]+y == snake_j[score-1])) // Impede que a cobra "volte"
                x = -x, y = -y;
            snake_i[score+1] = snake_i[score]+x, snake_j[score+1] = snake_j[score]+y; // Novo i e j que a cabeça irá, a princípio
            
            // Verificam se a cobra ultrapassará uma parede
            if(snake_i[score]+x < 0){ // Parede norte
                if(config[1] == 0) snake_i[score+1] = size-1;
                else run = -1, status = 5; // Encerra o jogo
            }
            else if(snake_i[score]+x > (size-1)){ // Parede sul
                if(config[1] == 0) snake_i[score+1] = 0;
                else run = -1, status = 5; // Encerra o jogo
            }
            else if(snake_j[score]+y < 0){ // Parede oeste
                if(config[1] == 0) snake_j[score+1] = size-1;
                else run = -1, status = 5; // Encerra o jogo
            }
            else if(snake_j[score]+y > (size-1)){ // Parede leste
                if(config[1] == 0) snake_j[score+1] = 0;
                else run = -1, status = 5; // Encerra o jogo
            }

            // Verificam se a cobra colidirá com algo no campo
            if(field[snake_i[score+1]][snake_j[score+1]] == config[6]){ // Se colidiu com uma Fruta
                score++, status = 6; // Atualiza o tamanho da cobra
                free_spaces = size*size -score; // Calcula a quantidade de espaços livres no campo
                
                if(free_spaces <= 0) run = -1, status = 7; // Se a cobra atingiu o tamanho do campo, o jogador vence
                else value = 1 + (rand() % free_spaces); // Gera uma posição para a nova fruta, dentre os espaços livres no campo
                
                for(int i=0, count=0; i<size && run==2; i++) // Loop de linhas
                    for(int j=0; j<size; j++) // Loop de colunas
                        if(field[i][j] == '.' && ++count == value) // Se for uma posição válida pra fruta
                            field[i][j] = config[6]; // Posiciona a fruta com base na posição gerada
            }
            else if(field[snake_i[score+1]][snake_j[score+1]] == config[5]) // Se colidiu consigo mesma
                if((snake_i[score+1] != snake_i[1]) || (snake_j[score+1] != snake_j[1])) // Se não foi com a sua ex-cauda
                    run = -1, status = 4; // Encerra o jogo
            
            // Atualiza as coordenadas de cada "pedaço" da cobra
            for(int k=0; k<=score && status<5; k++)
                snake_i[k] = snake_i[k+1], snake_j[k] = snake_j[k+1];
            
            // Atualiza a representação da cobra no campo
            field[snake_i[score-1]][snake_j[score-1]] = config[5]; // Atualiza o pescoço no campo
            if(snake_i[0]<size && status<6) field[snake_i[0]][snake_j[0]] = '.'; // Atualiza a ex-cauda no campo
            field[snake_i[score]][snake_j[score]] = config[4]; // Atualiza a cabeça no campo
        }
        else{
            input = _getch();

            if(input == 'V' || input == 'v')
                run = 3, *flag = 0;
            else if(run == 0 && (input == 'I' || input == 'i'))
                run = 2, x = -1, y = 0;
            else if(run == 1 && (input == 'P' || input == 'p'))
                run = 2;
            else if(run == 1 && (input == 'R' || input == 'r')) 
                run = 0, status = 2, score = config[3];
            else if(run == -1 && (input == 'R' || input == 'r')){
                clean_field(field, snake_i, snake_j, config, size); // Inicializa/Limpa o campo
                run = 2, score = config[3], x = -1, y = 0;
            }
            else if(run != 1 && (input == 'C' || input == 'c')){
                options_menu(error, config); // Permite que o usuário altere configurações dentro da função game()
                run = 3, *flag = 1; // Após alterações no menu de configs, é necessário reiniciar a função game()
            }
            else status = 1;
        }
    }
}
