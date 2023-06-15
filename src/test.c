#include "deykstra.h"
#include "my_func.h"
#include <stdio.h>

int main(void) {
    char *str = (char*)calloc(255, sizeof(char));
    char *polska = (char*)calloc(255, sizeof(char));
    scanf("%s", str);
    // sscanf("123/43", "%s", str);
    int status = convert(str, polska);
    if(!status) {
        printf("%s\n", polska);
        char *polska_pointer = polska + (strlen(polska) - 1);
        double x = 0;
        printf("Введите значение x: ");
        scanf("%lf", &x);
        printf("%.7lf\n", calculate(&polska_pointer, x));
    }
    else printf("ERROR\nERROR\nERROR\n%d\n", status);

    return 0;
}