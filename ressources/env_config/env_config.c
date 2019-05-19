/**
 * NE PAS MODIFIER CE FICHIER
 * Fichier permettant de stocker argc et argv venant des variables env de docker
 * vers les variables argc et argv du programme
*/

#define MAX_ARGC 50
#define DELIM " "

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void convertArgc(int* argc) {
    *argc = atoi(getenv("ARGC"));
}

void convertArgv(char** argv[]) {
    char** newArgv = calloc(MAX_ARGC, sizeof(char*));
    
    char* argPtr = strtok(getenv("ARGV"), DELIM);
    for (int i = 0; argPtr != NULL; ++i)
    {
        newArgv[i] = argPtr;
        printf("argv::: %s\n", argPtr);
        argPtr = strtok(NULL, DELIM);
    }
    *argv = newArgv;
}

void bootEnvVars(int* argc, char** argv[]) {

    convertArgc(argc);
    convertArgv(argv);
}