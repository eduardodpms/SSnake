#ifndef HEADER_H
#define HEADER_H

void separator(int length);

void space(int length, int line, char msg[100]);

char scan(int *error);

char main_menu(int *error);

void options_menu(int *error, int *config);

void info_menu(int *error);

int exit_menu();

char *print_log(int n);

void clean_field(char **field, int *snake_i, int *snake_j, int *config, int size);

void game(int *config, int *best_score);

#endif