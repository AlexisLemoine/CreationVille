#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"
#include "elementVille.h"
#include "immeuble.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Dart_handle Dart_handle;
typedef LCC::Point Point;

void elementVille::creerimmeuble (float x, float z, float lx, float lz, int etg, LCC& lcc) {
    immeuble j;
    for (float i=0; i<=etg; i++) {
        j.etage(x, i, z, lx, lz, lcc);
    }
}

void elementVille::creermaison (float x, float z, float lx, float lz, LCC& lcc) {
//    My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);
    My_linear_cell_complex_incremental_builder_3<LCC> ibb(lcc);
    //MAISON EN FONCTION DES PARAMETRES
    immeuble j;
    j.etage (x, 0, z, lx, lz, lcc);
    j.toit (x, 1, z, lx, 0.5, lz, lcc);

    //MAISON FIXE
    //8 sommets d'un cube
  ibb.add_vertex(Point(0,0,0));
  ibb.add_vertex(Point(0,1,0));
  ibb.add_vertex(Point(0,0,1));
  ibb.add_vertex(Point(0,1,1));
  ibb.add_vertex(Point(1,0,0));
  ibb.add_vertex(Point(1,1,0));
  ibb.add_vertex(Point(1,0,1));
  ibb.add_vertex(Point(1,1,1));
    //sommet d'un toit
  ibb.add_vertex(Point(.5,1.5,.5));
  ibb.begin_surface();
  //on créé les faces du cube
  ibb.add_facet({0,1,3,2});
  ibb.add_facet({4,6,7,5});
  ibb.add_facet({1,0,4,5});
  ibb.add_facet({6,2,3,7});
  ibb.add_facet({2,6,4,0});
//  ibb.add_facet({3,1,5,7});
  //on crée le toit
  ibb.add_facet({1,8,3});
  ibb.add_facet({7,3,8});
  ibb.add_facet({5,7,8});
  ibb.add_facet({5,8,1});
  ibb.end_surface();
}


void elementVille::genererquartier (int nb, LCC& lcc) {
    int tab[50][50];
    bool good;
    int cases;
    float x, lx, z, lz;
    for (int i=0; i<nb; i++) {
        int imm = rand()%2;
        good = false;
        while (good == false){
            x = rand()%12;
            z = rand()%12;
            lx = rand()%3 + 1;
            lz = rand()%3 + 1;
            std::cout<<x<<" "<<z<<" "<<lx<<" "<<lz<<"\n";
            cases=0;
            for (int j=x; j<x+lx; j++) {
                for (int k=z; k<z+lz; k++) {
                    if (tab[j][k]!=1) {
                        tab[j][k]=1;
                    }
                    else cases += 1;
                }
            }
            good = (cases==0);
            std::cout<<good << "\n";
        }
        if (imm==0) {
            creermaison(x, z, lx, lz, lcc);
        }
        else {
            int etage = rand()%10 + 1;
            creerimmeuble(x, z, lx, lz, etage, lcc);
        }
    }
}
