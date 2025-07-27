#include <stdio.h> // Output do código
#include <stdlib.h> // Limpar o terminal
#include <conio.h> // Input de caracteres


// Função para printar caracteres de separação
void separator(int length, int debug){
    for(int i=0; i<(length/2-3); i++) printf("="); // Printa a primeira parte dos separadores
    if(debug) printf("[DEBUG]"); // Indicador do modo de Debug
    else printf("======="); // Modo normal
    for(int i=0; i<(length/2-3); i++) printf("="); // Printa a segunda parte dos separadores
    printf("\n"); // Printa um retorno de linha
}


// Função para printar caracteres de espaço + mensagem
void space(int length, int line, char msg[100]){
    if(line) printf("\n"); // Se deseja printar um retorno de lina antes ou não
    for(int i=0; i<length; i++) printf(" "); // Printa o espaçamento desejado
    printf("%s\n", msg); // Printa a string desejada + retorno de linha
}


// Função para escanear inputs, usando "_getch()"
char scan(int *error){
    if(*error) // Se houve erro (input inválido)
        *error = !printf(">>> Por favor, digite uma entrada valida!\n"); // Printa o log de erro e reseta a flag

    printf(">"); // Printa um "indicador de input"
    return _getch(); // Recebe e retorna o caracter de input
}


// Função para printar o menu principal e registrar o input
char main_menu(int *error, int debug){
    if(!debug) system("cls"); // Limpa o terminal (modo normal)
    else printf("\n\n\n\n\n"); // Printa espaçamento (modo de Debug)

    separator(61, debug); // Printa caracteres de separação
    space(24, 0, "Bem Vindo(a)!");
    space(11, 0, " ____  ____  _   _    _    _  __ _____");
    space(11, 0, "/ ___|/ ___|| \\ | |  / \\  | |/ /| ____|");
    space(11, 0, "\\___ \\\\___ \\|  \\| | / _ \\ | ' / |  _|");
    space(11, 0, " ___) )___) | |\\  |/ ___ \\| . \\ | |___");
    space(11, 0, "|____/|____/|_| \\_/_/   \\_\\_|\\_\\|_____|");
    space(23, 0, "by eduardodpms");
    separator(61, 0); // Printa caracteres de separação
    printf("Selecione uma entrada:\n\n"); // Guias de tecla
    printf("1) Iniciar Jogo\n2) Menu de Ajustes\n"); // Guias de tecla
    printf("3) Menu de Infos\n4) Sair\n\n"); // Guias de tecla

    return scan(error); // Escaneia e retorna o input, com a função "scan()"
}


// Função para printar e processar o menu de ajustes
void options_menu(int *error, int *config, int *wait, char mode[3][7]){
    int run = 1, backup[8]; // Flag de execução e vetor de backup
    char config_1[2][10] = {"ATRAVESSA", "BATE"}; // Strings para exibição da opção "1"
    char config_7[2][10] = {"ATIVAR", "DESATIVAR"}; // Strings para exibição da opção "7"

    for(int k=0; k<8; k++) backup[k] = config[k]; // Armazena os ajustes no vetor de backup

    // Loop principal do menu de ajustes
    while(run){
        // Esse escopo define o processo de printar as informações do menu de ajustes
        {
            if(!config[7]) system("cls"); // Limpa o terminal (modo normal)
            else printf("\n\n\n\n\n"); // Printa espaçamento (modo de Debug)

            space(23, 0, "Menu de Ajustes"); // Cabeçalho do menu
            separator(60, config[7]); // Printa caracteres de separação
            printf("\n1) Dificuldade do Jogo  - - - - [%s]", mode[config[0]]); // 1: Dificuldade (MEDIUM/HARD/EASY)
            if(config[7]) printf("   --  %dms", wait[config[0]]); // Debug: mostra o tempo de espera do modo selecionado
            printf("\n2) Contato com a Parede - - - - [%s]", config_1[config[1]]); // 2: Evento ao cruzar a parede (ATRAVESSA/BATE)
            printf("\n3) Tamanho do Campo - - - - - - [%02dx%02d]", config[2], config[2]); // 3: Tamanho do campo
            if(config[7]) printf("  --  min: 5x5, max: 29x29"); // Debug: tamanhos mínimo e máximo do campo
            printf("\n4) Tamanho Inicial da Cobra - - [%03d]", config[3]); // 4: Tamanho inicial da cobra
            if(config[7]) printf("    --  min: 1, max: %d", (config[2]*config[2])-1); // Debug: tamanhos mín e máx da cobra
            printf("\n5) Caracter da Cabeca - - - - - ['%c']", config[4]); // 5: Caracter da cabeça ('O', 'o')
            printf("\n6) Caracter do Corpo  - - - - - ['%c']", config[5]); // 6: Caracter do corpo ('C', 'c')
            printf("\n7) Caracter da Fruta  - - - - - ['%c']", config[6]); // 7: Caracter da fruta ('*', 'X')
            printf("\n\nD) Modo de DEBUG  - - - - - - - [%s]", config_7[config[7]]); // 8: Modo de Debug (ATIVAR/DESATIVAR)
            printf("\nR) Resetar Ajustes\n\n"); // 9: Resetar ajustes (com o vetor de backup)
            separator(60, 0); // Printa caracteres de separação
            space(20, 0, "|    (V) Voltar    |"); // Guia de input
        }

        // Esse escopo processa a entrada, alterando a configuração desejada
        {
            char input = scan(error); // Escaneia o input, com a função "scan()"

            if(input == '1'){ // Opção 1: Dificuldade do jogo
                config[0] = config[0] + 1; // Alterna entre "MEDIUM", "HARD" e "EASY"
                if(config[0] > 2) config[0] = 0; // Volta pra "EASY"
            }
            else if(input == '2'){ // Opção 2: Evento ao cruzar a parede
                config[1] = !config[1]; // Alterna entre "ATRAVESSA" e "BATE"
            }
            else if(input == '3'){ // Opção 3: Tamanho do campo
                config[2] = config[2] + 2; // Aumenta a configuração em 2
                if(config[2] > 29) config[2] = 5; // Reseta para 5x5 se maior que o máximo permitido (29x29)
                if(config[3] > ((config[2]*config[2])-1)) config[3] = config[2]*config[2]-1; // Corrige o tamanho da cobra
            }
            else if(input == '4'){ // Opção 4: Tamanho inicial da cobra
                config[3] = config[3] + 1;  // Aumenta a configuração em 1
                if(config[3] > ((config[2]*config[2])-1)) config[3] = 1; // Reseta para 1 se maior que o máximo permitido
            }
            else if(input == '5'){ // Opção 5: Caracter da cabeça
                if(config[4] == 'O') config[4] = 'o'; // Alternar para 'o'
                else if(config[4] == 'o') config[4] = 'O'; // Alternar para 'O'
            }
            else if(input == '6'){ // Opção 6: Caracter do corpo
                if(config[5] == 'C') config[5] = 'c'; // Alternar para 'c'
                else if(config[5] == 'c') config[5] = 'C'; // Alternar para 'C'
            }
            else if(input == '7'){ // Opção 7: Caracter da fruta
                if(config[6] == '*') config[6] = 'X'; // Alternar para 'X'
                else if(config[6] == 'X') config[6] = '*'; // Alternar para '*'
            }
            else if(input == 'D' || input == 'd') config[7] = !config[7]; // Alterna o modo (normal ou Debug)
            else if(input == 'R' || input == 'r') for(int k=0; k<8; k++) config[k] = backup[k]; // Recupera o backup
            else if(input == 'V' || input == 'v') run = 0; // Retorna ao menu anterior
            else *error = 1; // Flag de leitura inválida
        }
    }
}


// Função para o menu de informações
void info_menu(int *error, int debug){
    int run = 1; // Flag de execução
    while(run){
        if(!debug) system("cls"); // Limpa o terminal (modo normal)
        else printf("\n\n\n\n\n"); // Printa espaçamento (modo de Debug)
                
        space(24, 0, "Menu de Infos"); // Cabeçalho do menu
        separator(61, debug); // Printa caracteres de separação
        printf("   O SSnake e um projeto pessoal meu, o qual iniciei com o\n");
        printf("   objetivo de testar as minhas habilidades com a linguagem\n");
        printf("   C apos um contato inicial com programacao na disciplina\n");
        printf("   de Algoritmos, na Universidade de Brasilia (UnB/FCTE).\n\n");
        printf("   Trata-se de uma replica do classico 'Jogo da Cobrinha',\n");
        printf("   feita em C para ser executada inteiramente em terminais\n");
        printf("   do sistema Windows. E um projeto completo, dotado de uma\n");
        printf("   serie de funcionalidades, tais como as seguintes:\n\n");
        printf("   - Navegacao completa entre menus;\n");
        printf("   - Menu de ajustes, para personalizacao;\n");
        printf("   - Contagem de score e diferentes dificuldades;\n");
        printf("   - Modo de Debug, para controle dos eventos;\n");
        printf("   - Sistema para pausar e reiniciar o jogo.\n\n");
        printf("     Obrigado por jogar! Sinta-se a vontade para enviar\n");
        printf("     sugestoes, reclamacoes ou comentarios pelo GitHub.\n");
        printf("  ---------------------------------------------------------  \n");
        printf("   Copyright Eduardo de Pina // GitHub: eduardodpms/SSnake\n");
        separator(61, 0); // Printa caracteres de separação
        space(20, 0, "|    (V) Voltar    |"); // Guia de input

        char input = scan(error); // Escaneia o input, com a função scan()
        if(input == 'V' || input == 'v') run = 0; // Caso se deseje voltar ao menu anterior
        else *error = 1; // Flag de leitura inválida
    }
}


// Função para o "menu" de saída
int exit_menu(int debug){
    if(!debug) system("cls"); // Limpa o terminal (modo normal)
    else printf("\n\n\n\n\n"); // Printa espaçamento (modo de Debug)

    separator(61, debug); // Printa caracteres de separação
    space(21, 1, "Obrigado por Jogar!");
    space(19, 0, "-----------------------");
    space(27, 1, "SSnake");
    space(23, 0, "by eduardodpms");
    separator(61, 0); // Printa caracteres de separação

    return 0; // Retorna o código para encerrar a execução
}