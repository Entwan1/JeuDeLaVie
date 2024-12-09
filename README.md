#Jeu de la Vie
Ce projet est une implémentation en C++ orienté objet du célèbre Jeu de la Vie de John Conway. Ce programme simule l'évolution d'une grille de cellules selon des règles prédéfinies, permettant d'observer des phénomènes intéressants d'automates cellulaires.

Fonctionnalités

Configuration personnalisable :
Taille de la grille.
État initial des cellules (manuellement ou aléatoirement).

Simulation des générations :
Calcul et affichage des générations suivantes.

Visualisation dynamique :
Affichage des cellules vivantes et mortes dans une interface console.

Extensibilité :
Structure orientée objet permettant une évolution facile du programme.

Règles du Jeu de la Vie
Une cellule vivante reste vivante si elle a 2 ou 3 voisins vivants.
Une cellule morte devient vivante si elle a exactement 3 voisins vivants.
Dans tous les autres cas, la cellule meurt ou reste morte.
