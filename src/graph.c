#include <stdio.h>
#include <string.h>

#include "notation.h"
#include "output.h"
#define MAX 100

int main(void) {
    char str[MAX];
    scanf("%99s", str);
    char note[MAX];
    parser(str, note);
    // printf("%s", note);
    // double data[2][80];
    // double tmp = 0;
    // for (int i = 0; i < 80; i++) {
    //     data[0][i] = tmp;
    //     tmp = tmp + 1;
    // }

    // for (int i = 0; i < 80; i++) {
    //     printf("x = %lf\n", data[0][i]);
    // }

    // for (int i = 0; i < 80; i++) {
    //     data[1][i] = calculate(note, strlen(note), data[0][i]);
    // }
    // printf("\n");
    // printf("\n");
    // for (int i = 0; i < 80; i++) {
    //     printf("x == %lf y = %lf\n", data[0][i], data[1][i]);
    // }

    printf("\n");

    my_output(note);
}
