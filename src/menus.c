#include <stdio.h> // Output do código
#include <stdlib.h> // Limpar o terminal
#include <conio.h> // Input de caracteres



// Função para printar caracteres de separação
void separator(int length){
    for(int i=0; i<length; i++) printf("=");
    printf("\n");
}


// Função para printar caracteres de espaço + mensagem
void space(int length, int line, char msg[100]){
    if(line) printf("\n");
    for(int i=0; i<length; i++) printf(" ");
    printf("%s\n", msg);
}


// Função para escanear inputs, usando "_getch()"
char scan(int *error){
    if(*error) // Se houve erro (input inválido)
        *error = !printf("%s", ">>> Por favor, digite uma opção válida!\n"); // Reseta a flag e print o log de erro

    printf(">"); // Printa um "indicador de input"
    return _getch(); // Recebe e retorna o caracter de input
}


/*// Função para printar o menu principal e registrar o input
char main_menu(int *error){
    separator(61); // Printa caracteres de separação
    space(24, 0, "Bem Vindo(a)!");
    space(14, 0, " ____  _   _    _    _  __ _____");
    space(14, 0, "/ ___|| \\ | |  / \\  | |/ /| ____|");
    space(14, 0, "\\___ \\|  \\| | / _ \\ | ' / |  _|");
    space(14, 0, " ___) | |\\  |/ ___ \\| . \\ | |___");
    space(14, 0, "|____/|_| \\_/_/   \\_\\_|\\_\\|_____|");
    space(23, 0, "by eduardodpms");
    separator(61); // Printa caracteres de separação
    printf("Selecione uma opção:\n\n");
    printf("1) Iniciar Jogo\n2) Menu de Opções\n");
    printf("3) Informações\n4) Sair\n\n");

    return scan(error); // Escaneia e retorna o input, com a função scan()
}*/


// Função para printar o menu principal e registrar o input
char main_menu(int *error){
    separator(61); // Printa caracteres de separação
    space(24, 0, "Bem Vindo(a)!");
    space(11, 0, " ____  ____  _   _    _    _  __ _____");
    space(11, 0, "/ ___|/ ___|| \\ | |  / \\  | |/ /| ____|");
    space(11, 0, "\\___ \\\\___ \\|  \\| | / _ \\ | ' / |  _|");
    space(11, 0, " ___) )___) | |\\  |/ ___ \\| . \\ | |___");
    space(11, 0, "|____/|____/|_| \\_/_/   \\_\\_|\\_\\|_____|");
    space(23, 0, "by eduardodpms");
    separator(61); // Printa caracteres de separação
    printf("Selecione uma opção:\n\n");
    printf("1) Iniciar Jogo\n2) Menu de Opções\n");
    printf("3) Informações\n4) Sair\n\n");

    return scan(error); // Escaneia e retorna o input, com a função scan()
}


// Função para printar e processar o menu de opções
void options_menu(int *error, int *config){
    int run = 1; // Flag de execução
    const char *config_1, *config_2;

    while(run == 1){
        if(config[0] == 0) config_1 = "FÁCIL";
        else if(config[0] == 1) config_1 = "MÉDIO";
        else if(config[0] == 2) config_1 = "DIFÍCIL";

        if(config[1] == 0) config_2 = "ATRAVESSA";
        else if(config[1] == 1) config_2 = "BATE";

        system("cls"); // Limpa o terminal

        space(23, 0, "Menu de Opções"); // Cabeçalho do menu
        separator(60); // Printa caracteres de separação
        printf("\n1) Dificuldade do Jogo  - - - - [%s]\n", config_1);
        printf("2) Contato com a Parede - - - - [%s]\n", config_2);
        printf("3) Tamanho do Campo - - - - - - [%dx%d]\n", config[2], config[2]);
        printf("4) Tamanho Inicial da Cobra - - [%d]\n", config[3]);
        printf("5) Caracter da Cabeça - - - - - ['%c']\n", config[4]);
        printf("6) Caracter do Corpo  - - - - - ['%c']\n", config[5]);
        printf("7) Caracter da Fruta  - - - - - ['%c']\n\n", config[6]);
        printf("R) Resetar Opções\n\n");
        separator(60); // Printa caracteres de separação
        printf("Selecione o número correspondente à opção que deseja\n"); // Guia de input
        printf("alterar, ou digite 'V' para voltar ao menu principal.\n\n"); // Guia de input

        char input = scan(error); // Escaneia o input, com a função scan()

        if(input == '1'){
            config[0]++;
            if(config[0] > 2) config[0] = 0;
        }
        else if(input == '2'){
            config[1]++;
            if(config[1] > 1) config[1] = 0;
        }
        else if(input == '3'){
            config[2] = config[2] + 2;
            if(config[2] > 29) config[2] = 5;
            if(config[3] > ((config[2]*config[2])-1)) config[3] = config[2]*config[2]-1;
        }
        else if(input == '4'){
            config[3]++;
            if(config[3] > ((config[2]*config[2])-1)) config[3] = 1;
        }
        else if(input == '5'){
            if(config[4] == 'O') config[4] = 'o';
            else if(config[4] == 'o') config[4] = 'O';
        }
        else if(input == '6'){
            if(config[5] == 'C') config[5] = 'c';
            else if(config[5] == 'c') config[5] = 'C';
        }
        else if(input == '7'){
            if(config[6] == '*') config[6] = 'X';
            else if(config[6] == 'X') config[6] = '*';
        }
        else if(input == 'R' || input == 'r')
            config[0] = 1, config[1] = 0, config[2] = 15, config[3] = 4, config[4] = 'O', config[5] = 'C', config[6] = '*';
        else if(input == 'V' || input == 'v') run = 0; // Caso se deseje voltar ao menu anterior
        else *error = 1; // Flag de leitura inválida
    }
}


// Função para o menu de informações
void info_menu(int *error){
    int run = 1; // Flag de execução
    while(run){
        system("cls"); // Limpa o terminal
                
        space(21, 0, "Menu de Informações"); // Cabeçalho do menu
        separator(61); // Printa caracteres de separação
        printf("      Copyright Eduardo de Pina // GitHub: @eduardodpms\n");
        separator(61); // Printa caracteres de separação
        printf("Digite 'V' para voltar ao menu principal.\n\n"); // Guia de input

        char input = scan(error); // Escaneia o input, com a função scan()

        if(input == 'V' || input == 'v') run = 0; // Caso se deseje voltar ao menu anterior
        else *error = 1; // Flag de leitura inválida
    }
}


// Função para o "menu" de saída
int exit_menu(){
    system("cls"); // Limpa o terminal

    separator(61); // Printa caracteres de separação
    space(21, 1, "Obrigado por Jogar!");
    space(19, 0, "-----------------------");
    space(27, 1, "SSnake");
    space(23, 0, "by eduardodpms");
    separator(61); // Printa caracteres de separação

    return 0; // Retorna o código para encerrar a execução
}
