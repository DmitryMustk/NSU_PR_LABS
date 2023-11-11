#include <stdio.h>
#include <stdlib.h>
 
#define MAX_INPUT_LENGTH 1000
#define MAX_STACK_SIZE 1000

enum error_code{
    NO_ERROR,
    SYNTAX_ERROR,
    DIV_BY_ZERO,
};
 
typedef struct stack_t{
    int data[MAX_STACK_SIZE];
    int top;
} stack_t;
 
 
void push(stack_t *stack, const int value){
    stack -> top++;
    stack -> data[stack -> top] = value;
}
 
int is_empty(const stack_t *stack){
    return stack -> top < 0;
}
 
int pop(stack_t *stack, enum error_code* error){
    if(is_empty(stack)) {
        *error = SYNTAX_ERROR;
        return 0;
    }
    return stack -> data[stack -> top--];
}
 
int get_top(const stack_t *stack, enum error_code* error){
    if(is_empty(stack)){
        *error = SYNTAX_ERROR;
        return 0;
    }
    return stack -> data[stack -> top];
}
 
int is_number(const char c){
    return c <= '9' && c >= '0';
}
 
int is_operation(const char c){
    return c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/';
}
 
int get_priority(const char c){
    if(c == '+' || c == '-')
        return 1;
    if(c == '*' || c == '/')
        return 2;
    return 0;
}
 
void calculate(stack_t *numbers, const char operation, enum error_code* error){
    int b = pop(numbers, error);
    int a = pop(numbers, error);
    if(*error == SYNTAX_ERROR){
        return;
    }
 
    if(operation == '+')
        push(numbers, a + b);
    if(operation == '-')
        push(numbers, a - b);
    if(operation == '*')
        push(numbers, a * b);
    if(operation == '/'){
        if(b == 0){               
            *error = DIV_BY_ZERO;
            return;
        }
        push(numbers, a / b);
    }
}
 
int str_to_int(const char *exp, const int exp_len, int *index){
    int res = 0;
    while(*index < exp_len && is_number(exp[*index])) {
        res *= 10;
        res += exp[*index] - '0';
        (*index)++;
    }
    (*index)--;
    return res;
}
 
int shunting_yard_algorithm(char *exp, const int exp_len, enum error_code* error){
    stack_t numbers;
    stack_t operations;
    numbers.top = -1;
    operations.top = -1;
 
    for(int i = 0; i < exp_len; i++){
        if(exp[i] == '(')
            push(&operations, (int) exp[i]);
        else if(exp[i] == ')') {
            if(i == 0 || exp[i - 1] == '('){
                *error = SYNTAX_ERROR;
                return 0;
            }
            char buf;
            while ((buf = (char)pop(&operations, error)) != '('){
                if(*error == SYNTAX_ERROR){
                    return 0;
                }
                calculate(&numbers, buf, error);
                if(*error == SYNTAX_ERROR || *error == DIV_BY_ZERO){
                    return 0;
                }
            }
        }
        else if(is_operation(exp[i])){
            while (!is_empty(&operations) && get_priority((char) get_top(&operations, error)) >= get_priority(exp[i])){
                char operation = (char)pop(&operations, error);
                if(*error == SYNTAX_ERROR){
                    return 0;
                }
                calculate(&numbers, operation, error);
                if(*error == SYNTAX_ERROR || *error == DIV_BY_ZERO){
                    return 0;
                }
            }
            push(&operations, (int)exp[i]);
        }
        else if(is_number(exp[i])){
            int number = str_to_int(exp, exp_len, &i);
            push(&numbers, number);
        }
    }
 
    while(!is_empty(&operations)){
        char operation = (char)pop(&operations, error);
        if(*error == SYNTAX_ERROR){
            return 0;
        }
        calculate(&numbers, operation, error);
        if(*error == SYNTAX_ERROR || *error == DIV_BY_ZERO){
            return 0;
        }
    }
 
    int res = pop(&numbers, error);
    if(*error == SYNTAX_ERROR)
        return 0;
    return res;
}
 
//function returns length of input
int read_input(char* exp){
    int i;
    char buf;
    for(i = 0; i < MAX_INPUT_LENGTH; i++) {
        if(!scanf("%c", &buf))
            return 0;
        if(buf == '\n')
            break;
        if(!(is_number(buf) ||is_operation(buf))) {
            printf("syntax error\n");
            return 0;
        }
        exp[i] = buf;
    }
    return i;
}
 
int main(void){
    char exp[MAX_INPUT_LENGTH];
    int exp_len = read_input(exp);
 
    enum error_code error;
    int res = shunting_yard_algorithm(exp, exp_len, &error);
    if(error == DIV_BY_ZERO){
        printf("division by zero\n");
        return 0;
    }
 
    if(error == SYNTAX_ERROR){
        printf("syntax error\n");
        return 0;
    }
    printf("%d", res);
    return 0;
}
