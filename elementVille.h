#ifndef ELEMENTVILLE_H
#define ELEMENTVILLE_H

#include "lcc_def.h"

typedef std::vector<std::vector<int>> intGrid;
typedef std::vector<std::vector<Dart_handle>> GridDH;

// Ici c'est la classe principale pour générer la ville, elle est dépendante de la classe immeuble qui elle va gérer les détails des batiments

class Ville
{
public:
    LCC lcc;
    intGrid tab;
    GridDH tabDH;
    int dim; // les dimensions de la grille, modifiable dans le constructeur ci dessous
    int nbBat; // le nombre de batiments dans la ville, modifiable ci dessous
    int hauteurMax; // la hauteur maximale des immeubles, modifiable elle aussi
    std::vector<Dart_handle> route;

    Ville() {
        dim = 20;
        nbBat = 20;
        hauteurMax = 10;
        tabDH = GridDH(dim, std::vector<Dart_handle>(dim, NULL));
        creerGrille(LCC::Point(0,0,0), dim, dim, dim, dim);
        tab = intGrid(dim,std::vector<int>(dim,0));
    };
    void creerGrille(    const typename LCC::Point basepoint,
                           typename LCC::FT sx,
                           typename LCC::FT sy,
                           std::size_t nbx,
                           std::size_t nby);
    void creerimmeuble (float x, float z, float lx, float lz, int etg);
    Dart_handle creermaison (float x, float z, float lx, float lz);
    void sewMaison(float x, float z, float lx, float lz);
    void sewImmeuble(int etg, float x, float z, float lx, float lz);
    void genererquartier (int nb, int dim);
    void creerroute (float x, float z, float l, bool orientation);
    void creerrue (float x, float z, float l, bool orientation);
    void suppBrinSol(Dart_handle& dh, float lx, float lz);
    void quartier();
    void grilleint ();
};

#endif // ELEMENTVILLE_H
