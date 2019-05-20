/*
 *  Created on: 2018-02-17
 *      Authors: Loïc Gelle, Hanifa Boucheneb
 */
#include "../../env_config/env_config.c"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compteur pour le nombre d'appels récursifs
unsigned count=0;

// Gestionnaire pour le signal SIGSEGV
void signal_segv_handler(int sig) {
    char s[50];
    sprintf(s, "Segmentation fault! count=%u\n", count);
    write(2, s, strlen(s));
    _exit(1);
}

// sum_b: Calcul de la somme 1 + 2 + ... + x
unsigned long long *sum_b(unsigned long long x) {
    unsigned long long *s;
    count++;
    if (x>0)
        *s = *sum_b(x - 1) + x;
    else
        *s = 0;
    return s;
}

// sum_a: Calcul de la somme 1 + 2 + ... + x
unsigned long long sum_a(unsigned long long x) {
    count++;
    if (x>0)
        return sum_a(x - 1) + x;
    else
        return 0;
}

// -----------------------------------------------------
// RAPPEL: vous ne pouvez pas modifier la fonction main!
// -----------------------------------------------------
int main(int argc, char** argv) {
    bootEnvVars(&argc, &argv);
    unsigned long long x;
    unsigned long long *sum_result;
    char result[100];

    // On va traiter le signal SIGSEGV en utilisant une autre pile
    static char stack[SIGSTKSZ];
    stack_t ss; 
       ss.ss_size = SIGSTKSZ;
        ss.ss_sp = stack;
  
    struct sigaction sa; 
	    sa.sa_handler = signal_segv_handler; 
	    sa.sa_flags = SA_ONSTACK;
   
    sigaltstack(&ss, 0);
    sigfillset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, 0);

    // Traiter les arguments en entrée
    if (argc < 3) {
        printf("Please specify the sum function to use (a or b) and the target number of integers to sum.\n");
        return -1;
    }
    x = atoll(argv[2])*10;
    // x = strtoul(argv[2],NULL,10)*10;
    // Cas 1: Exécuter la fonction sum_a
    if (strcmp(argv[1], "a") == 0)
        sprintf(result, "sum_a = %llu for x=%llu, count=%u \n", sum_a(x), x, count);

    // Cas 2: Exécuter la fonction sum_b
    else if (strcmp(argv[1], "b") == 0) {
        sum_result = sum_b(x);
        sprintf(result, "sum_b = %llu for x=%llu, count=%u \n", *sum_result, x, count);
        free(sum_result);
    }
    else {
        printf("error: function must be a or b\n");
        return -1;
    }
    
    write(1, result, strlen(result));

    return 0;
}

