/**
 * NE PAS MODIFIER CE FICHIER
 * Fichier permettant de stocker argc et argv venant des variables env de docker
 * vers les variables argc et argv du programme
*/

#define MAX_ARGC 50
#define DELIM " "

#include <stdlib.h>
#include <string.h>

void bootEnvVars(int* argc, char** argv[]) {

    char** newArgv = calloc(MAX_ARGC, sizeof(char*));
    *argc = atoi(getenv("ARGC"));
    
    char* argPtr = strtok(getenv("ARGV"), DELIM);
    for (int i = 0; argPtr != NULL; ++i)
    {
        newArgv[i] = argPtr;
        argPtr = strtok(getenv("ARGV"), DELIM);
    }
    argv = newArgv;
}