# Avant toute chose

Exécuter:

```
./prepare.sh
```

# Pour compiler un exécutable et le lancer

```
./run.sh DIRNAME
```

Par exemple:

```
./run.sh dummy
```

# A noter

- Chaque sous-répertoire de `codes` doit avoir un Makefile qui définit la cible `all`
- Le Makefile DOIT produire un exécutable nommé `a.out`
- Le fichier à modifier pour ajouter les librairies (pthread, etc.) et utilitaires nécessaires à la compilation de tous les fichiers est `.docker/Dockerfile-base`

# TODO

- Les scripts devraient fonctionner pour Mac OS X (mais il faut vérifier)
- Il faut adapter ces scripts pour Windows
- Il faut écrire des instructions pour que les élèves téléchargent Docker (qui devrait être le seul prérequis)