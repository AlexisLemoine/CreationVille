#ifndef ELEMENTVILLE_H
#define ELEMENTVILLE_H

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Dart_handle Dart_handle;
typedef std::vector<std::vector<int>> MyGrid;
typedef std::vector<std::vector<Dart_handle>> GridDH;

// Ici c'est la classe principale. C'est a dire que chaque élément de la ville aura une classe
// secondaire pour être créer. Pour l'instant, un exemple avec immeuble.

class elementVille
{
public:
    int dim = 50;
    GridDH creerGrille(LCC& lcc,
                            const typename LCC::Point basepoint,
                           typename LCC::FT sx,
                           typename LCC::FT sy,
                           std::size_t nbx,
                           std::size_t nby);
    void creerimmeuble (float x, float z, float lx, float lz, int etg, LCC& lcc);
    Dart_handle creermaison (float x, float z, float lx, float lz, LCC& lcc);
    void sewMaison(float x, float z, float lx, float lz, LCC& lcc, GridDH& grid);
    void genererquartier (int nb, int dim, LCC& lcc);
    void creerroute (float x, float z, float l, bool orientation, MyGrid& tab, LCC& lcc);
    void creerrue (float x, float z, float l, bool orientation, MyGrid& tab, LCC& lcc);
};

#endif // ELEMENTVILLE_H
