#include <stdio.h> // Output do código
#include <stdlib.h> // Limpar o terminal e alocar espaços de memória
#include <windows.h> // Função de espera (Sleep())
#include <conio.h> // Input de caracteres
#include <time.h> // Tempo do sistema
#include "header.h" // Arquivo de cabeçalho


// Função para definir o log referente a cada status do jogo
char *print_log(int n){
    if(n==0)      return "";
    else if(n==1) return ">>> Por favor, digite uma entrada valida!\n";
    else if(n==2) return ">>> Pressione (I) para iniciar!\n";
    else if(n==3) return ">>> O jogo foi pausado!\n";
    else if(n==4) return ">>> A cobra bateu em si mesma!\n";
    else if(n==5) return ">>> A cobra bateu na parede!\n";
    else if(n==6) return ">>> A cobra aumentou de tamanho!\n";
    else if(n==7) return ">>> O jogo foi completado! Parabens!\n";
    else          return ">>> Houve um erro.\n";
}


// Função para inicializar/limpar o campo e os vetores de posição
void clean_field(char **field, int *snake_i, int *snake_j, int *config, int size){
    // Inicializa a matriz que representa o campo do jogo
    for(int i=0; i<size; i++) // Loop de linhas
        for(int j=0; j<size; j++) // Loop de colunas
            field[i][j] = '.'; // Atribui o caracter que representa um espaço vazio no jogo ('.')
    
    // Inicializa as posições e a representação da cobra
    for(int k=1; k<config[3]+1; k++){ // Loop pelo tamanho inicial da cobra definido
        snake_i[k] = size/2 +config[3] -k; // Armazena a coordenada i no vetor de posição i
        snake_j[k] = size/2; // Armazena a coordenada j no vetor de posição j

        if(snake_i[k]<size) field[snake_i[k]][snake_j[k]] = config[5]; // Posiciona o corpo no campo
        if(k==config[3]) field[snake_i[k]][snake_j[k]] = config[4]; // Posiciona a cabeça no campo
    }
    
    snake_i[0] = size/2 +config[3]-1, snake_j[0] = size/2; // Cria uma cópia da cauda no índice 0
    field[size/4-1][size-(1-1+size/4)] = config[6]; // Posiciona a Fruta inicial no campo
}


// Função principal do jogo
void game(int *error, int *config,  int *wait, char mode[3][7], int *flag, int *best_score){
    int run = 0, status = 2, free_spaces, value; // Declara as variáveis de execução, status, espaços livres e valor aleatório
    int score = config[3], size = config[2]; // Declara as variáveis de tamanho da cobra e do campo
    int snake_i[size*size+2], snake_j[size*size+2], x = -1, y = 0; // Declara os vetores e as variáveis de posição

    char input, **field = malloc(size * sizeof(char *)); // Aloca a variável de input e a matriz que representa o campo
    for(int k=0; k<size; k++) field[k] = malloc(size * sizeof(char)); // Aloca o espaço de cada linha do campo

    srand(time(NULL)); // Inicializa o gerador de números aleatórios com a semente do tempo

    // Loop principal do jogo
    while(run != 3){
        if(run == 0) clean_field(field, snake_i, snake_j, config, size); // Inicializa/Limpa o campo
        if(score > *best_score) *best_score = score; // Atualiza o melhor score

        // Nesse escopo, está organizado o processo de printar as informações do menu de jogo
        {
            // Limpa o terminal e printa o header do novo menu
            if(config[7]<2) system("cls"); // Limpa o terminal (modo Normal ou Debug)
            else printf("\n\n\n\n\n"); // Printa espaçamento (modo de Debug Avançado)
            printf("|   SSnake  by  eduardodpms   |   Score = %03d ~ Best = %03d  |\n", // Header do menu do jogo
                   (config[0]+1)*(score-config[3]), (config[0]+1)*(*best_score-config[3])); // Scores atual e melhor

            // Printa o campo que representa o jogo
            separator(61, config[7]); // Printa caracteres de separação
            for(int i=0; i<size; i++){ // Loop de linhas
                for(int j=0; j<(29-size); j++) printf(" "); // Printa um espaçamento antes de cada linha
                for(int j=!printf("| "); j<size; j++) // Loop de colunas
                    printf("%c ", field[i][j]); // Printa o elemento (i, j) da matriz do campo

                // Printa as informações de debug no modo de Debug ou Debug Avançado
                if(config[7] && i==0)      printf("|   Wait = %dms (%s)\n", wait[config[0]], mode[config[0]]); // Tempo de espera
                else if(config[7] && i==1) printf("|   Movement: i = %d, j = %d\n", x, y); // Próximas coordenadas da cabeça
                else if(config[7] && i==2) printf("|   Free Spaces = %d\n", size*size-score-1); // Número de espaços livres
                else if(config[7] && i==3) printf("|   Snake Size = %d, Field Size = %d\n", score, size*size); // Tamanhos
                else if(config[7] && i==4) printf("|   Head = (%d, %d), Tail = (%d, %d)\n", // Coordenadas da cabeça e cauda
                                                  snake_i[score], snake_j[score], snake_i[1], snake_j[1]); // Vetores de posição
                else printf("|\n"); // Printa um retorno de linha
            }
            separator(61, 0); // Printa caracteres de separação

            // Printa os guias de tecla e o log do menu de jogo
            if(run==-1) // Se o jogo está finalizado (o jogador morreu/venceu)
                printf("|  (R) Reiniciar   |   (C) Configurar   |    (V) Voltar     |"); // Guia para o jogo finalizado
            else if(run==0) // Se o jogo está zerado (o campo está limpo)
                printf("|   (I) Iniciar    |   (C) Configurar   |    (V) Voltar     |"); // Guia para o jogo zerado
            else if(run==1) // Se o jogo está pausado
                printf("|  (P) Despausar   |   (R) Reiniciar    |    (V) Voltar     |"); // Guia para o jogo pausado
            else if(run==2) // Se o jogo está em andamento
                printf("| (P) Pausar | (R) Reiniciar | (W/A/S/D) Mover | (V) Voltar |"); // Guia para o jogo em andamento
            status = !printf("\n\n%s>", print_log(status)); // Printa o log e reseta a variável "status"
        }

        // Esse escopo processa as entradas de acordo com dois estados do jogo: em andamento (run == 2) e parado (run != 2)
        {
            if(run == 2){ // Se o jogo está em andamento
                Sleep(wait[config[0]]); // Tempo de espera, de acordo com a dificuldade definida

                if(_kbhit()){ // Se alguma tecla foi pressionada
                    input = _getch(); // Armazena o caracter de entrada na variável "input"

                    // Entradas de movimentação: Movem a cobra e o jogo continua a execução (run == 2)
                    if(input == 'W' || input == 'w')      x = -1, y = 0; // 'W': Variáveis de posição vão para cima
                    else if(input == 'A' || input == 'a') x = 0, y = -1; // 'A': Variáveis de posição vão para a esquerda
                    else if(input == 'S' || input == 's') x = 1, y = 0; // 'S': Variáveis de posição vão para baixo
                    else if(input == 'D' || input == 'd') x = 0, y = 1; // 'D': Variáveis de posição vão para a direita
                    
                    // Entradas de suspensão: Interrompem a execução do jogo (run != 2)
                    else if(input == 'P' || input == 'p') run = 1, status = 3; // 'P': O jogo é pausado
                    else if(input == 'R' || input == 'r') run = 0, status = 2, score = config[3]; // 'R': O jogo é zerado
                    else if(input == 'V' || input == 'v') run = 3, *flag = 0; // 'V': O loop do jogo é interrompido
                    
                    else status = 1; // Caso a entrada não seja válida, chama um warning
                    if(run != 2) continue; // Se a entrada foi de suspensão, não é necessário processá-la
                }

                // Impede que a cobra "volte" contra si mesma
                if((snake_i[score]+x == snake_i[score-1]) && // Se a posição i desejada é a mesma do pescoço
                   (snake_j[score]+y == snake_j[score-1])) // Se a posição j desejada é a mesma do pescoço
                    x = -x, y = -y; // Inverte as variáveis de posição desejadas (anula o efeito da entrada)

                // Armazena a posição desejada no índice posterior ao da cabeça
                snake_i[score+1] = snake_i[score] + x; // Posição "i" desejada
                snake_j[score+1] = snake_j[score] + y; // Posição "j" desejada
                
                // Verificam se a cabeça encontrará uma parede
                if(snake_i[score+1] < 0){ // Parede norte
                    if(config[1] == 0) snake_i[score+1] = size-1; // O i da cabeça vai pra baixo (se puder atravessar)
                    else run = -1, status = 5; // Encerra o jogo (se a cobra não puder atravessar)
                }
                else if(snake_i[score+1] > (size-1)){ // Parede sul
                    if(config[1] == 0) snake_i[score+1] = 0; // O i da cabeça vai pra cima (se puder atravessar)
                    else run = -1, status = 5; // Encerra o jogo (se a cobra não puder atravessar)
                }
                else if(snake_j[score+1] < 0){ // Parede oeste
                    if(config[1] == 0) snake_j[score+1] = size-1; // O j da cabeça vai pra direita (se puder atravessar)
                    else run = -1, status = 5; // Encerra o jogo (se a cobra não puder atravessar)
                }
                else if(snake_j[score+1] > (size-1)){ // Parede leste
                    if(config[1] == 0) snake_j[score+1] = 0; // O j da cabeça vai pra esquerda (se puder atravessar)
                    else run = -1, status = 5; // Encerra o jogo (se a cobra não puder atravessar)
                }

                // Verificam se a cabeça colidirá com algo no campo
                if(run == -1) continue; // Pula a verificação caso a cobra tenha batido na parede
                else if(field[snake_i[score+1]][snake_j[score+1]] == config[6]){ // Se colidiu com uma Fruta
                    score++, status = 6; // Atualiza o tamanho da cobra
                    free_spaces = size*size -score; // Calcula a quantidade de espaços livres no campo
                    
                    if(free_spaces <= 0) run = -1, status = 7; // Se a cobra atingiu o tamanho do campo, o jogador vence
                    else value = 1 + (rand() % free_spaces); // Gera uma posição para a nova fruta, dentre os espaços livres
                    
                    for(int i=0, count=0; i<size && run==2; i++) // Loop de linhas
                        for(int j=0; j<size; j++) // Loop de colunas
                            if(field[i][j] == '.' && ++count == value) // Se for uma posição válida pra Fruta
                                field[i][j] = config[6]; // Posiciona a fruta com base na posição gerada
                }
                else if(field[snake_i[score+1]][snake_j[score+1]] == config[5]) // Se colidiu consigo mesma
                    if((snake_i[score+1] != snake_i[1]) || (snake_j[score+1] != snake_j[1])) // Se não foi com a sua ex-cauda
                        run = -1, status = 4; // Encerra o jogo
                
                // Atualiza as coordenadas de cada fragmento da cobra
                for(int k=0; k<=score && status<5; k++) // Para cada fragmento da cobra
                    snake_i[k] = snake_i[k+1], snake_j[k] = snake_j[k+1]; // Um fragmento recebe as coordenadas do próximo
                
                // Atualiza a representação da cobra no campo
                field[snake_i[score-1]][snake_j[score-1]] = config[5]; // Atualiza o pescoço no campo
                if(snake_i[0]<size && status<5) field[snake_i[0]][snake_j[0]] = '.'; // Atualiza a ex-cauda no campo
                field[snake_i[score]][snake_j[score]] = config[4]; // Atualiza a cabeça no campo
            }
            else{ // Se o jogo não está em andamento
                input = _getch(); // Armazena o caracter de entrada na variável "input"

                if(input == 'V' || input == 'v') // Caso se deseje sair do menu de jogo
                    run = 3, *flag = 0; // O loop do jogo é interrompido
                else if(run == 0 && (input == 'I' || input == 'i')) // Se o jogo está zerado e se deseja iniciá-lo
                    run = 2, x = -1, y = 0; // O jogo é posto em execução e as variáveis de posição são inicializadas
                else if(run == 1 && (input == 'P' || input == 'p')) // Se o jogo está pausado e se deseja despausá-lo
                    run = 2; // O jogo é posto em execução
                else if(run == 1 && (input == 'R' || input == 'r')) // Se o jogo está pausado e se deseja reiniciá-lo
                    run = 0, status = 2, score = config[3]; // O jogo é zerado e o score é redefinido
                else if(run == -1 && (input == 'R' || input == 'r')){ // Se o jogo foi finalizado e se deseja reiniciá-lo
                    clean_field(field, snake_i, snake_j, config, size); // Limpa a matriz de representação do campo
                    run = 2, score = config[3], x = -1, y = 0; // Coloca o jogo em andamento e reseta as variáveis do jogo
                }
                else if(run != 1 && (input == 'C' || input == 'c')){ // Caso se deseje acessar as configurações
                    options_menu(error, config, wait, mode); // Chama o menu de ajustes
                    run = 3, *flag = 1; // Após as alterações, é necessário reiniciar a função "game()"
                }
                else status = 1; // Entrada inválida: chama um warning
            }

        } // Fim do escopo de processamento de entradas
    } // Fim do loop principal do jogo
} // Fim da função "game()"