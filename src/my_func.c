#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

#include "my_func.h"
// double calculate(char *ch, int k, double x);

// int main(void) {
//     char ch[MAX] = "2 x * c s";
//     int n = 0;
//     while (ch[n] != '\0') n++;
//     double y = calculate(ch, n, (3.0 * M_PI * 4.0 / 79.0));
//     printf("%lf", y);
//     return 0;
// }

double calculate(char *ch, int k, double x) {
    // printf("--%c--\n", ch[k-1]);
    while (ch[k - 2] > 47 && ch[k - 2] < 58) k--;
    double res;
    int tmp = 0;
    if (ch[k - 3] == 'l' || ch[k - 3] == 'c' || ch[k - 3] == 's' || ch[k - 3] == 't' || ch[k - 3] == 'q')
        while (ch[k - 5 - tmp] != ' ') tmp++;
    switch (*(ch + k - 1)) {
        case '+':
            res = calculate(ch, k - 4 - tmp, x) + calculate(ch, k - 2, x);
            break;
        case '-':
            res = calculate(ch, k - 4 - tmp, x) - calculate(ch, k - 2, x);
            break;
        case '*':
            res = calculate(ch, k - 4 - tmp, x) * calculate(ch, k - 2, x);
            break;
        case '/':
            res = calculate(ch, k - 4 - tmp, x) / calculate(ch, k - 2, x);
            break;
        case 's':
            res = sinl(calculate(ch, k - 2, x));
            break;
        case 'c':
            res = cosl(calculate(ch, k - 2, x));
            break;
        case 't':
            res = tanl(calculate(ch, k - 2, x));
            break;
        case 'g':
            res = tanl(M_PI_2 - calculate(ch, k - 2, x));
            break;
        case 'q':
            res = sqrtl(calculate(ch, k - 2, x));
            break;
        case 'l':
            res = logl(calculate(ch, k - 2, x));
            break;
    }
    if (ch[k - 1] > 47 && ch[k - 1] < 58) {
        res = atoi(ch + k - 1);
    }
    if (ch[k - 1] == 'x') res = x;
    // printf("res = %lf\n", res);
    return res;
}
