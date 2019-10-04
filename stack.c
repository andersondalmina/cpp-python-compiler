#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int top;
    int capacity;
    int *items;
};

struct Stack* newStack(int capacity) {
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    if (isFull(stack)) {
        return;
    }

    stack->items[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }

    return stack->items[stack->top--];
}

int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }

    return stack->items[stack->top];
}
