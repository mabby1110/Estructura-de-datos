#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

void push(Stack* stack, char element) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Error: La pila está llena\n");
        exit(1);
    }
    stack->data[++(stack->top)] = element;
}

char pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Error: La pila está vacía\n");
        exit(1);
    }
    return stack->data[(stack->top)--];
}

int isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')')
        return 1;
    return 0;
}

int isBalanced(char expression[]) {
    Stack stack;
    initialize(&stack);

    int i = 0;
    while (expression[i] != '\0') {
        if (expression[i] == '(') {
            push(&stack, expression[i]);
        } else if (expression[i] == ')') {
            if (stack.top == -1 || !isMatchingPair(stack.data[stack.top], expression[i])) {
                return 0;
            } else {
                pop(&stack);
            }
        }
        i++;
    }

    return stack.top == -1;
}

int main() {
    char text[] = "(ksks)(df(123)";
    printf("Cadena a validar: %s\n\n", text);

    if (isBalanced(text)) {
        printf("La cadena está correctamente balanceada\n");
    } else {
        printf("La cadena no está correctamente balanceada\n");
    }

    return 0;
}
