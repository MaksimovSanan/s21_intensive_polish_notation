#include "deykstra.h"
#include "my_func.h"
#include <stdio.h>

int main(void) {
    char *str = (char*)calloc(255, sizeof(char));
    char *polska = (char*)calloc(255, sizeof(char));
    scanf("%s", str);
    // sscanf("123/43", "%s", str);
    int status = convert(str, polska);
    if(!status) printf("%s\n", polska);
    else printf("ERROR");

    char *polska_pointer = polska + (strlen(polska) - 1);
    printf("%.7lf\n", calculate(&polska_pointer, 5356));

    // printf("%lf\n", calculate(&polska_pointer, 1));
    return 0;
}