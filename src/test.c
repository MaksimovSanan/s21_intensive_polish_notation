#include "deykstra.h"
#include <stdio.h>

int main(void) {
    char str[255];
    char polska[255];
    scanf("%s", str);

    convert(str, polska);
    printf("%s\n", polska);
    return 0;
}