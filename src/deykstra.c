#include "deykstra.h"

int convert(char *infix, char *polska) {
    char *polska_pointer = polska;
    char *operators_1 = "+-";
    char *operators_2 = "*/%";
    char *operators_3 = "^";
    int status = 0;
    int dot_flag = 0;
    int digit_flag = 0;
    stack stack;
    status = init_stack(&stack);
    
    if(!status) {
        do {
            if (((*infix) >= '0' && (*infix) <= '9') || (*infix) == 'x') {
                dot_flag = 0;
                push_to_str(&polska_pointer, *infix);
                while((*(infix + 1)) != '\0' && (((*(infix + 1)) >= '0' && (*(infix + 1)) <= '9') || (*(infix + 1)) == '.')) {
                    infix++;
                    (*(infix) == '.')? (dot_flag)? status = 22 : dot_flag++ : 0; // ошибка в записи (лишние скобки)
                    push_to_str(&polska_pointer, *infix);
                }
                push_to_str(&polska_pointer, ' ');
            }
            else if ((*infix) == '@') {
                status = push_to_stack(&stack, *infix);
                infix++;
                status = push_to_stack(&stack, *infix);
            }
            else if ((*infix) == '(') {
                status = push_to_stack(&stack, *infix);
            }
            else if (strchr(operators_3, *infix)) {
                status = push_to_stack(&stack, *infix);
            }
            else if (strchr(operators_2, *infix)) {
                while (strchr(operators_3, check_stack(&stack)) || strchr(operators_2, check_stack(&stack))) push_to_str(&polska_pointer, pop_stack(&stack));
                status = push_to_stack(&stack, *infix);
            }
            else if (strchr(operators_1, *infix)) {
                while (strchr(operators_3, check_stack(&stack)) || strchr(operators_2, check_stack(&stack)) || strchr(operators_1, check_stack(&stack))) push_to_str(&polska_pointer, pop_stack(&stack));
                status = push_to_stack(&stack, *infix);
            }
            else if ((*infix) == ')') {
                while ((check_stack(&stack) != '(') && (!status)) {
                    if (check_stack(&stack) == '!') status = 21; // ошибка в записи (скобки)
                    else push_to_str(&polska_pointer, pop_stack(&stack));
                }
                pop_stack(&stack);
                if (check_stack(&stack) >= '0' && check_stack(&stack) <= '9') {
                    push_to_str(&polska_pointer, pop_stack(&stack));
                    push_to_str(&polska_pointer, pop_stack(&stack));
                }
            }
            else status = 20;// ошибка в записи (неопределенные симмволы)
        }while(!status && *(++infix) != '\0');
        
        while((check_stack(&stack) != '!') && (!status)) {

            if (check_stack(&stack) == '(' || check_stack(&stack) == ')') status = 21; // ошибка в записи (скобки)
            else push_to_str(&polska_pointer, pop_stack(&stack));
        }
    }

    destroy_stack(&stack);
    return status;
}

int init_stack(stack *stack) {
    int status = 0;
    stack->stack = (char*)malloc(sizeof(char) * 1);
    if(stack->stack != NULL) {
        stack->count = 0;
        stack->stack[stack->count] = '\0';
    }
    else status = 1;

    return status;
}

void destroy_stack(stack *stack) {
    stack->count = 0;
    free(stack->stack);
}

int push_to_stack(stack *stack, char ch) {
    int status = 0;
    stack->stack[stack->count] = ch;
    stack->count++;
    stack->stack = (char*)realloc(stack->stack, sizeof(char) * ((stack->count) + 1));
    if(stack->stack != NULL) {
        stack->stack[stack->count] = '\0';
    }
    else status = 1;

    return status;
}

char check_stack(stack *stack) {
    return (stack->count > 0)? stack->stack[(stack->count) - 1] : '!';
}

char pop_stack(stack *stack) {
    char ch = '!';
    if (stack->count > 0) {
        ch = stack->stack[(stack->count) - 1];
        stack->stack[(stack->count) - 1] = '\0';
        (stack->count)--;
        // mb realloc (???)
    }
    return ch;
}

void push_to_str(char **str, char ch) {
    **str = ch;
    *str = *str + 1;
}