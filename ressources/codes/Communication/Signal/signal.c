#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigintHandler(int num) {
    printf("Eh bien! Vous avez appuye sur CTRL+C\n");
}

int main() {

    printf("Nous allons utiliser la fonction signal pour assigner un gestionnaire personnalise a SIGING\n");
    printf("Le programme se terminera apres avoir execute le gestionnaire\n");
    signal(SIGINT, sigintHandler);

    printf("Voila!\n");
    printf("On se met maintenant en attente de SIGINT, Appuyez sur CTRL+C!\n");
    
    pause();

    return 0;

}