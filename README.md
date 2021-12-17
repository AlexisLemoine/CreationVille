# projet création de ville 

Consignes pour utiliser le code du projet de création d'une ville.
/// utilisation de cgal :
lien pour télécharger cgal : https://www.cgal.org/download/linux.html
packages a télécharger : voir sur CGAL pour les dépendances avec CGAL

/// utilisation du projet :

un fichier CMake est fourni avec 
Dans le main (test.cpp), on peut afficher afficher 3 rendus différents. Pour les utiliser on a besoin de décommenter
les lignes indiquées :
- afficher un quartier dans la première partie. On peut changer la taille du quartier en changeant les paramètres dans
le constructeur Ville du fichier elementVille.h. On peut modifier la taille, le nombre  de bâtiments et la longueur max
d'un immeuble.
- afficher une maison dans une seconde partie. On peut changer les paramètres directement dans test.cpp, avec en premier
les trois coordonnéess x, y et z de la maions, puis la taille de celle-ci.
- afficher un immeuble dans une troisième partie. Comme pour changer les paramètres de la maison, on peut changer le
nombre d'étages de l'immeuble, puis deux coordonnées, x et z.
