#ifndef NOTATION_H
#define NOTATION_H

char *parser(char *str, char *note);  //преобразует строку в нотацию
void distributor(char *str, char *st, char *note, int *nt, char *steck, int *ct);  //распределяет по знакам
char mat_func(char *str);  // достаем из строки математическую функцию и возвращаем ее сокращение
void minus(char const *str, char const *st, char *note, int *nt, char *steck, int *ct);  // обработка минуса
void plus(char const *st, char *note, int *n, char *steck, int *c);      // обработка плюса
void multiply(char const *st, char *note, int *n, char *steck, int *c);  //обработка умножения
void divide(char const *st, char *note, int *n, char *steck, int *c);    //обработка деления

#endif