#include <stdio.h> // Output do código
#include <stdlib.h> // Limpar o terminal
#include <conio.h> // Input de caracteres
#include "header.h" // Arquivo de cabeçalho



// Função main do código
int main(){
    int run = 1, error = 0, flag = 1, best_score = 0; // Flags e melhor score
    int config[8] = {1, 0, 15, 4, 'O', 'C', '*', 0}; // Vetor de configs

    int wait[3] = {800, 400, 200}; // Tempos de espera dos modos Fácil, Médio e Difícil
    char mode[3][7] = {"EASY", "MEDIUM", "HARD"}; // Nome dos modos de jogo

    // Loop de execução do menu principal
    while(run == 1){
        if(!config[7]) system("cls"); // Limpa o terminal (modo normal)
        else printf("\n\n\n\n\n"); // Printa espaçamento (modo de Debug)
        char input = main_menu(&error, config[7]); // Executa a rotina do menu principal

        if(input=='1') while(flag++) game(&error, config, wait, mode, &flag, &best_score); // Função para o menu do jogo em si
        else if(input=='2') options_menu(&error, config, wait, mode); // Função para o menu de opções
        else if(input=='3') info_menu(&error, config[7]); // Função para o menu de informações
        else if(input=='4') run = exit_menu(config[7]); // Função para o "menu" de saída
        else error = 1; // Flag de leitura inválida
    }
    return 0;
}