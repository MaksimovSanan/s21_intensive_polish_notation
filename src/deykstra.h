#include <stdlib.h>
#include <string.h>

typedef struct stack_struct {
    char *stack;
    int count;
}stack;

int convert(char *infix, char *polska);
int init_stack(stack *stack);
void destroy_stack(stack *stack);
int push_to_stack(stack *stack, char ch);
char check_stack(stack *stack);
char pop_stack(stack *stack);