# PIR8

# Présentation du problème "Plus petit cercle englobant"

Le problème du plus petit cercle englobant consiste a trouver un cercle de rayon minimum englobant un ensemble de points dans un espace euclidien en deux dimensions. Il est possible de généraliser ce problème à d'autres dimensiosn, par exemple dans la dimension 3, on pourrait cherche la plus petite sphère englibant un ensemble des points. Ce problème a proposé pour la première fois par le mathématicien anglais James Joseph Sylvester en 1857.

Pour résoudre ce problème il faut admettre 3 lemmes différents : 

1. La solution su plus petit cercle englobant un ensemble des points est unique.
2. Si on trouve un cercle dont le diamètre est la distance passant par deux points, et ce cercle englobe tous les autres points, donc ce cercle est le plus petit cercle englobant (la solution).
3. Iy n'existe qu'un unique cercle passant par trois points non-colinéaires.

#  Objectifs et réalisations

Dans ce projet, nous avons cherché à implémenter des algorithmes pour trouver le plus petit cercle englobant un ensemble des points.
Nous avons impléménté deux approches principales : l'algorithme naïf et l'algorithme de Wzlz. L'algorithme naîf teste toutes les combinaisons possibles de deux ou trois points pour trouver le plus petit cercle englobant un ensemble des points, tandis que l'algorithme de Welz utilise une approche récursive et probabiliste pour trouver ce cercle. 
Nous avons également inclus des fonctionnalités pour la visualisation des résultats à l'aide de fichiers SVG. 

Nous avons essayé de faire l'implémentation de l'algorithme de Megiddo mais malheuresement nous avons pas réussi à finir notre code dans le temps donné.
