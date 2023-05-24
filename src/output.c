#include "output.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_func.h"
// по оси абсцисс
#define scene_length 80
// по оси ординат
#define scene_width 12
void my_output(char *note) {
    // рисуем график, по оси ординат делаем в 2 раза больше (под отрицательные значения), проставляем точки в
    // массиве.
    char scene[scene_length + 1][scene_width * 2 + 1];
    for (int x = 0; x < scene_length + 1; x++) {
        for (int y = 0; y < scene_width * 2 + 1; y++) {
            scene[x][y] = '.';
        }
        // scene[x][scene_width]='-'; // это будет абсцисса (__рисует ось)
    }
    // тут будем обрабатывать функцию и рисовать график
    double step = (M_PI * 4) / 79;
    for (int x = 0; x < 80; x++) {
        double y = calculate(note, strlen(note), x * step);  // sin(cos(2*(x-1)*step)));; //место для функции
        if (fabs(y) < scene_width) {
            y = y * -11.99 + 12.5;
            // printf("--%lf--\n", y);
            // if(fabs(y)<scene_width) // проверяем чтобы значение за пределы "экрана" не выходило
            scene[x][(int)y] = '*';  // ставим точку
        }
    }
    // выводим на экран
    for (int y = scene_width * 2; y >= 0; y--) {
        // printf("%03d ", y - scene_width);  // (__выводит значение ординат)
        for (int x = 0; x < scene_length; x++) {
            printf("%c", scene[x][y]);
        }
        printf("\n");
    }
}