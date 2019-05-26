/**
 * NE PAS MODIFIER CE FICHIER
 * Fichier permettant de stocker argc et argv venant des variables env de docker
 * vers les variables argc et argv du programme
 * 
 * TODO free unused pointers
*/

#define MAX_ARGC 50 // D:
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
        newArgv[i] = i == 0 ? "./a.out" : argPtr;
        argPtr = strtok(NULL, DELIM);
    }
    *argv = newArgv;
}

void bootEnvVars(int* argc, char** argv[]) {

    convertArgc(argc);
    convertArgv(argv);
}