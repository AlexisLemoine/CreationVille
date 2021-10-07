#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"
#include "elementVille.h"
#include "immeuble.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Dart_handle Dart_handle;
typedef LCC::Point Point;


//On créé et on affiche un immeuble, aux coordonées (x,z), de longueur lx sur l'axe x, lz sur l'axe z, et d'un nombre d'étage etg
//Pour cela on fait appelle à la fonction étage qui vient créer des étages un à un les uns sur les autres
void elementVille::creerimmeuble (float x, float z, float lx, float lz, int etg, LCC& lcc) {
    immeuble j;
    for (float i=0; i<=etg; i++) {
        j.etage(x, i, z, lx, lz, lcc);
    }
}

//On créé et on affiche une maison, aux coordonnées (x,z), de longueur lx sur l'axe x, lz sur l'axe z
//Pour cela, on fait appel à la fonction étage qui vient créé un étage, auquel on rajoute un toit en faisant appel à la fonction du même nom
void elementVille::creermaison (float x, float z, float lx, float lz, LCC& lcc) {
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

//On génère un quartier de manière totalement aléatoire, en prenant en paramètre le nombre de batiments que l'on veut dans le quartier
void elementVille::genererquartier (int nb, LCC& lcc) {
    int tab[50][50];
    bool good;
    int cases;
    float x, lx, z, lz;
    for (int i=0; i<nb; i++) {
        int imm = rand()%2; //on tire un nombre aléatoire entre 0 et 1 qui va dire si c'est une maison ou un immeuble
        good = false;
        while (good == false){ //on vérifie à chaque  batiment que ses coordonnées tirées au hasard sont bien libres, sinon on retire de nouvelles coordonées
            //ici les coordonées sont entre 0 et 11 en x et z, et les longueurs des batiments entre 1 et 3
            x = rand()%12; 
            z = rand()%12;
            lx = rand()%3 + 1;
            lz = rand()%3 + 1; 
            std::cout<<x<<" "<<z<<" "<<lx<<" "<<lz<<"\n";
            cases=0;

            //on parcourt toutes les cases occupées par le batiment pour voir si elles sont libres ou non
            for (int j=x; j<x+lx; j++) {
                for (int k=z; k<z+lz; k++) {
                    if (tab[j][k]!=1) {
                        tab[j][k]=1;
                    }
                    else cases += 1; //on compte le nombre de cases occupées par le batiment qui sont libres, si ce nombre n'est pas égal à 0, on relance
                }
            }

            ///////////////////////////////////////////////////////////////////
/*          for (int j=x; j<x+lx; j++) {
                for (int k=z; k<z+lz; k++) {
                    if (tab[j][k]=1) {
                        cases += 1;
                    }
                }
            }
            if (cases==0) {
                for (int j=x; j<x+lx; j++) {
                    for (int k=z; k<z+lz; k++) {
                            tab[j][k]=1;
                    }
                }
            }
*/          ////////////////////////////////////////////////////////////////////
            good = (cases==0);
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
