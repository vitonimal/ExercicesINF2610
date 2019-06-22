#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct Operands {
    float operandA;
    float operandB;
};

void* add(float a, float b) {
    float sum = a + b;
    printf("sum: %f\n", sum);
    return NULL;
};

void* addWrapper(void* args) {
    struct Operands* ops = (struct Operands*) args;
    return add(ops->operandA, ops->operandB);
}

int main() {
    struct Operands* ops = calloc(1, sizeof(struct Operands));
    ops->operandA = 1;
    ops->operandB = 3;

    pthread_t tid;
    pthread_create(&tid, NULL, addWrapper, (void*)ops);
    pthread_join(tid, NULL);

    return 0;
}