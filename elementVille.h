#ifndef ELEMENTVILLE_H
#define ELEMENTVILLE_H

#include "lcc_def.h"

typedef std::vector<std::vector<int>> intGrid;
typedef std::vector<std::vector<Dart_handle>> GridDH;

// Ici c'est la classe principale. C'est a dire que chaque élément de la ville aura une classe
// secondaire pour être créer. Pour l'instant, un exemple avec immeuble.

class elementVille
{
public:
    LCC lcc;
    intGrid tab;
    GridDH tabDH;
    int dim;
    int nbBat;
    int hauteurMax;
    std::vector<Dart_handle> route;

    elementVille() {
        dim = 20;
        nbBat = 35;
        hauteurMax = 10;
        tabDH = GridDH(dim, std::vector<Dart_handle>(dim, NULL));
        creerGrille(LCC::Point(0,0,0), dim, dim, dim, dim);
        tab = intGrid(dim,std::vector<int>(dim,0));
        // route = std::vector<Dart_handle>(0,NULL);
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
    bool rechercheRoute (Dart_handle dh);
    void grilleint ();
};

#endif // ELEMENTVILLE_H
