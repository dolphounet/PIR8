Langage : #C puisqu'on cherche des temps d’exécution rapide
Chercher dans https://github.com/natebragg/MegiddoLP
# Welzl 
Algo #randomisé 
Tracer des cercles englobants deux points randoms puis chercher les points à l'extérieur du cercle.
Point a coordonnées entières pour éviter des erreurs d'approximation
In-circle test/predicate (attendre lien)
## Implementation
###### Structure de données
- Points 2D
- Coordonnées entières
- Créer une image avec le nuage de point et des cercles en svg
	- Pouvoir calculer le centre et le rayon du cercle
- Implémenter les prédicats
- Algo #randomisé complet
# Megiddo
Le cercle passe par 2 ou 3 points.
À chaque étape une fraction des points n'est pas utile donc on peut l'enlever, au bout d'un moment on se retrouve avec la solution.
Résolution de sous-problèmes de #LP
#LP : on cherche à minimiser une fonction linéaire
On forme des contraintes : Le centre doit se trouver sur une certaine droite, on peut alors transformer le problème pour le résoudre en #LP 
Les points donnent des demis plans et le point optimum est le centre du cercle.

Problème vertical
Demis plans orientés vers le haut (g) et le bas (h)
On cherche alors le point à l'ordonnée la plus petite

Algo : On fait des paires de contraintes orientées dans la même direction: en croisant des demis plans, on sait que tous les points d'un certain coté du croisement (x) ne pourront pas être la solution. Donc une des deux contraintes n'est pas importante

On calcule x pour chaque paire et on prend la médiane (algo linéaire en temps pour la recherche de la médiane à implémenter) on peut alors choisir de quel côté faire nos recherches et réduire d'un quart l'ensemble.

## Implementation
Chercher la raison du drop de contrainte
Savoir quand on a la solution, comment faire ces calculs avec des prédicats pour rester en nombre entier
	Interpréter les demis plans dans l'espace d'origine (médiatrice de deux points sur la droite qui contient le centre, on divise l'espace en deux, on choisit une partie, le point qui n'est pas dans la partie devient important.)
# Tests
