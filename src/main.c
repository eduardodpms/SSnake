#include <stdio.h> // Output do código
#include <stdlib.h> // Limpar o terminal
#include <conio.h> // Input de caracteres
#include "header.h" // Arquivo de cabeçalho



// Função main do código
int main(){
    int run = 1, error = 0, best_score = 0; // Flags e melhor score
    int config[8] = {1, 0, 15, 4, 'O', 'C', '*', 0}; // Vetor de configs

    // Loop de execução do menu principal
    while(run == 1){
        if(!config[7]) system("cls"); // Limpa o terminal
        else printf("\n\n\n\n\n"); // Printa espaçamento (modo de Debug)
        char input = main_menu(&error, config[7]); // Executa a rotina do menu principal

        if(input == '1') game(config, &best_score); // Função para o menu jogo em si
        else if(input == '2') options_menu(&error, config); // Função para o menu de opções
        else if(input == '3') info_menu(&error, config[7]); // Função para o menu de informações
        else if(input == '4') run = exit_menu(config[7]); // Função para o "menu" de saída
        else error = 1; // Flag de leitura inválida
    }
    return 0;
}