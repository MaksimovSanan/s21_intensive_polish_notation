#include "notation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int main() {
//     char str[100] = "(1+2)*(-3+x)-4";  //начальная строка
//     // 2*3/(-(2+1))    2 3 * 0 2 1 + - /
//     //(1+2)*(-3+x)-4   1 2 + 0 3 - x + * 4 -
//     //(1+2)*(3+x)-4   1 2 + 3 x + * 4 -
//     //(1+2)*(3+x)-4*sin(x)   1 2 + 3 x + * 4 x s * -
//     char note[100];      //нотация
//     char *pnote = NULL;  // польская нотация
//     char *st = str;
//     printf("%s", st);  //проверяем содержимое строки
//     printf("\n");

//     pnote = parser(str, note);
//     printf("%s", pnote);  // проверяем? что выдала функция
//     return 0;
// }

char mat_func(char *str) {
    char ch[][1] = {"s", "c", "t", "g", "q", "l"};  // массив итоговых символов
    char mat[][4] = {"sin", "cos", "tg", "ctg", "sqrt", "ln"};  //массив возможных функций
    char *st = str;  // указатель на строку, чтобы не испортить входящий
    char *st_m = NULL;  // указатель вхождения искомой строки
    int i = 0, flag = 0;
    for (i = 0; i < 6; i++) {
        st_m = strstr(st, mat[i]);  // вернет либо null, либо указатель на вхождение
        if (st_m == st) {           // нашлось вхождение
            flag = 1;
            break;
        }
    }
    if (flag && i < 6) {  // нашлось вхождение
        return *ch[i];
    } else {  //здесь условие ошибки
    }
    return '0';
}

char *parser(char *str, char *note) {
    note[0] = '\0';
    char *st = str;
    char ch;
    char ch_math;
    char steck[100];  // *ct = steck; //стек для знаков
    steck[0] = '\0';
    int nt = 0, ct = 0;  //кол-во в строке note и в стеке знаков
    while (*st != '\0') {
        sscanf(st, "%c", &ch);
        if (((int)ch > 47) && ((int)ch < 58)) {
            note[nt] = ch;
            nt++;  //смотрит на пустое место в строке нотации
            // note[nt] = '\0';
        } else if (ch == 's' || ch == 'c' || ch == 't' || ch == 'l') {
            ch_math = mat_func(st);  // получаем сокращение математической функции
            // printf(" w - %c \n", ch_math);
            if (ch_math != '0') {
                steck[ct] = ch_math;
                ct++;
            }
        } else {
            distributor(str, st, note, &nt, steck, &ct);
        }
        // note[nt] = '\0';
        steck[ct] = '\0';
        st++;
        if (note[nt - 1] != ' ' && nt != 0) {
            note[nt] = ' ';
            nt++;
        }
        // printf(" --- note = %s     steck = %s\n", note, steck);
    }
    ct--;
    while (ct > -1) {
        note[nt] = steck[ct];
        nt++;
        ct--;
        note[nt] = ' ';
        nt++;
    }
    ct++;
    note[nt - 1] = '\0';
    // steck[ct];
    return note;
}

void distributor(char *str, char *st, char *note, int *n, char *steck, int *c) {
    char ch = *st;
    int nt = *n;
    int ct = *c;
    switch (ch) {
        case 'x': {  //х как число
            // if ((st-1) != str) {
            //     note[nt] = ' ';
            //     nt++;
            // }
            note[nt] = ch;
            nt++;
            break;
        }
        case ')': {
            ct--;
            while (steck[ct] != '(' && ct > -1) {  //выкидываем, пока не встретим скобку открывающую
                note[nt] = steck[ct];
                ct--;
                nt++;
            }
            steck[ct] = '\0';
            break;
        }
        case '(': {  //записываем в стек
            steck[ct] = ch;
            ct++;
            break;
        }
        case '*': {
            multiply(st, note, &nt, steck, &ct);
            break;
        }
        case '/': {
            divide(st, note, &nt, steck, &ct);
            break;
        }
        case '+': {
            plus(st, note, &nt, steck, &ct);
            break;
        }
        case '-': {
            minus(str, st, note, &nt, steck, &ct);
            break;
        }
        default: {
        }
    }
    *n = nt;
    *c = ct;
}

void minus(char const *str, char const *st, char *note, int *n, char *steck, int *c) {
    char ch = *st;
    int nt = *n;
    int ct = *c;
    // printf(" \"-\" str = %c  ch = %c note[%d] = %c steck[%d] = %c\n", str[0], ch, nt-1, note[nt-1], ct-1,
    // steck[ct-1]);
    if (st == str || *(st - 1) == '(') {  // унарный минус обрабатываем
        note[nt] = '0';
        nt++;
        steck[ct] = ch;
        ct++;
    } else if (steck[0] == '\0' || steck[ct - 1] == '(') {  // записываем в стек
        steck[ct] = ch;
        ct++;
        steck[ct] = '\0';
    } else if (steck[ct - 1] == '+' || steck[ct - 1] == '-' || steck[ct - 1] == '*' || steck[ct - 1] == '/') {
        ct--;
        while (steck[ct] != '(' && ct > -1) {  //выкидываем до скобки или начала строки
            note[nt] = steck[ct];
            ct--;
            nt++;
        }
        ct++;
        steck[ct] = ch;
        ct++;
    }
    *n = nt;
    *c = ct;
}

void plus(char const *st, char *note, int *n, char *steck, int *c) {
    char ch = *st;
    int nt = *n;
    int ct = *c;
    // printf(" \"+\" str = %c  ch = %c note[%d] = %c steck[%d] = %c\n", str[0], ch, nt-1, note[nt-1], ct-1,
    // steck[ct-1]);
    if (steck[0] == '\0' || steck[ct - 1] == '(') {  // записываем в стек
        steck[ct] = ch;
        // printf("!!!до steck[%d] = %c !!!\n", ct, steck[ct]);
        ct++;
        steck[ct] = '\0';
        // printf("!!!после steck[%d] = %c !!!\n", ct, steck[ct]);
    } else if (steck[ct - 1] == '+' || steck[ct - 1] == '-' || steck[ct - 1] == '*' || steck[ct - 1] == '/') {
        ct--;
        while (steck[ct] != '(' && ct > -1) {  //выкидываем до скобки или начала строки
            note[nt] = steck[ct];
            ct--;
            nt++;
        }
        ct++;
        steck[ct] = ch;
        ct++;
    }
    *n = nt;
    *c = ct;
}

void multiply(char const *st, char *note, int *n, char *steck, int *c) {
    char ch = *st;
    int nt = *n;
    int ct = *c;
    if (ct == 0 || steck[ct - 1] == '(' || steck[ct - 1] == '+' ||
        steck[ct - 1] == '-') {  // записываем в стек
        steck[ct] = ch;
        ct++;
        steck[ct] = '\0';
    } else {
        ct--;
        while (steck[ct] != '(' && ct > -1) {  //выкидываем до скобки или начала строки
            note[nt] = steck[ct];
            ct--;
            nt++;
        }
        ct++;
        steck[ct] = ch;
        ct++;
    }
    *n = nt;
    *c = ct;
}

void divide(char const *st, char *note, int *n, char *steck, int *c) {
    char ch = *st;
    int nt = *n;
    int ct = *c;
    if (ct == 0 || steck[ct - 1] == '(' || steck[ct - 1] == '+' ||
        steck[ct - 1] == '-') {  // записываем в стек
        steck[ct] = ch;
        ct++;
        steck[ct] = '\0';
    } else {
        ct--;
        while (steck[ct] != '(' && ct > -1) {  //выкидываем до скобки или начала строки
            note[nt] = steck[ct];
            ct--;
            nt++;
        }
        ct++;
        steck[ct] = ch;
        ct++;
    }
    *n = nt;
    *c = ct;
}
