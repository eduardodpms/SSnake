#ifndef HEADER_H
#define HEADER_H

void separator(int length, int debug);

void space(int length, int line, char msg[100]);

char scan(int *error);

char main_menu(int *error, int debug);

void options_menu(int *error, int *config, int *wait, char mode[3][7]);

void info_menu(int *error, int debug);

int exit_menu(int debug);

char *print_log(int n);

void clean_field(char **field, int *snake_i, int *snake_j, int *config, int size);

void game(int *error, int *config, int *wait, char mode[3][7], int *flag, int *best_score);

#endif