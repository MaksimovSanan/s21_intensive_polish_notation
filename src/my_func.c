
#define MAX 100

#include "my_func.h"

// @0 - cos(x)
// @1 - sin(x)
// @2 - tan(x)
// @3 - acos(x)
// @4 - asin(x)
// @5 - atan(x)
// @6 - sqrt(x)
// @7 - ln(x)
// @8 - log(x)

double calculate(char **str, double x) {
    double res = 0;

    (*((*str) + 1)) = '\0';

    char specifier = (**str);
    (**str) = '\0';
    (*str) = (*str) - 1;
    printf("tmp specifier = %c\n", specifier);
    if(specifier == ' ') {
        if((**str) == 'x') res = x;
        else {
            while(((*((*str) - 1)) >= '0' && (*((*str) - 1)) <= '9') || (*((*str) - 1)) == '.') { // добавить проверку на выход за границы
                (*str) = (*str) - 1;
            }
            sscanf((*str), "%lf", &res);
        }
        // (**str) = '\0'; // необязательная (вроде) строка
        (*str) = (*str) - 1;
    }

    else if(specifier == '/') res = pow(calculate(str, x), -1) * calculate(str, x);
    else if(specifier == '*') res = calculate(str, x) * calculate(str, x);
    else if(specifier == '+') res = calculate(str, x) + calculate(str, x);
    else if(specifier == '-') {
        double x1 = calculate(str, x);
        double x2 = calculate(str, x);
        res = x1 * -1 + x2;
    }
    else if(specifier == '^') {
        double x1 = calculate(str, x);
        double x2 = calculate(str, x);
        res = pow(x2,x1);
    }
    else if(specifier == '%') {
        double x1 = calculate(str, x);
        double x2 = calculate(str, x);
        res = fmod(x2,x1);
    }
    else if(specifier == '@') {
        char func_specifier = (**str);
        (**str) = '\0';
        (*str) = (*str) - 1;
        if(func_specifier == '0') res = cos(calculate(str,x));
        else if(func_specifier == '1') res = sin(calculate(str,x));
        else if(func_specifier == '2') res = tan(calculate(str,x));
        else if(func_specifier == '3') res = acos(calculate(str,x));
        else if(func_specifier == '4') res = asin(calculate(str,x));
        else if(func_specifier == '5') res = atan(calculate(str,x));
        else if(func_specifier == '6') res = sqrt(calculate(str,x));
        else if(func_specifier == '7') res = log(calculate(str,x));
        else if(func_specifier == '8') res = log10(calculate(str,x));
    }
    printf("tmp res = %lf\n", res);
    return res;
}