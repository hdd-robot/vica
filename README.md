
% VICA

Vica pour vicarius. Représente l'implémentation d'une architecture cognitive dans un robot mobile (vika).

# Organication du dossier de travail

Le dossier de travail s'appel workspace_ros, il contient 
 1. README.md  : cet documentaion 
 2. src/       : le dossier qui contiens les différents packages
 3. .gitignore :
 4. TODOLIST   : fichier text qui permet d'indiquer les choses qui restent à faire
 5. build/     :  dossier de compilation ncessaire pour le fonctionnement de ROS 
 6. devel      :  dossier de configuration ncessaire pour le fonctionnement de ROS

## Dépot git
Pour récupérer le dépot git, sur le serveur halim.info :

```


```

## Configuration 
### Configuration de l'expace de travail 
Après récupération du dossier workspace_vica via le dépot git, vous 
devez configurer votre fichier ".bashrc" et ajouter cette ligne: 

```
source ~/workspace_vica/devel/setup.bash

```
### Configuration de eclipse
Télécharger eclipse CPP sur le site internet et ne pas utiliser apt-get install eclipse.
http://wiki.ros.org/IDEs



## Bonnes pratiques pour l'utilisation du GIT:
 
 1. Créer une brache pour chaques fonctionalié, merger dans dev une fois que ça fonctionne
 2. Préférer rebase que merge pour avoir, particulièrement pour la branche master
 3. Ne jamais faire un rebase d'un commit déjà envoyé sur le serveur 
 4. Supprimer les branches non utilisé 
 5. Mettre des TAG avec des bons commentaires 
 6. Les commits doivent être bien commentés 
 
 Trois branches principales dans le projet :
 1. master : version stable du travail
 2. work   : version qui fonctionne du travail
 2. dev    : le travail en cours 
# Construction générale des packages ROS

Dans vica on trouve 4 packages:
 1. vica_detect
 2. vica_sim
 3. vica_eval
 4. vica_act
 5. vica_robot
 6. vica_robot_gazebo
 7. vica_launch
Dans le workspace on trouver d'autres packages, généralement ils servent uniquement pour tester certaines fonctionnalités avant leur implémentation dans les packages.

## vica_detect

## vica_sim

## vica_eval 

## vica_act


# Execution 
Pour lancer le tout il suffi :

```
roslaunch vica_launch vica.launch

```
