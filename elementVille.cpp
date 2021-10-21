#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"
#include "lcc_creations.h"
#include "elementVille.h"
#include "immeuble.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Dart_handle Dart_handle;
typedef LCC::Point Point;


struct Volume
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
  std::string type;
};
struct Myitem
{
  template<class Refs>
  struct Dart_wrapper
  {
    typedef CGAL::Cell_attribute_with_point< Refs, int, CGAL::Tag_true,
                                             Volume >
    Vertex_attribute;
    typedef std::tuple<Vertex_attribute> Attributes;
  };
};
typedef CGAL::Linear_cell_complex_traits<3, CGAL::Exact_predicates_inexact_constructions_kernel> Traits;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3,3,Traits,Volume> LCC_3;


void elementVille::creerGrille(LCC& lcc,
                                    const typename LCC::Point basepoint,
                                   typename LCC::FT sx,
                                   typename LCC::FT sy,
                                   std::size_t nbx,
                                   std::size_t nby) 
{
    std::cout<<"ça marche \n";
    make_xy_grid(lcc, basepoint, sx, sy, nbx, nby);
    std::cout<<"ça marche pas \n";
}
//créé une route à partir des coordonées (x, z), de longueur l et de largeur 1, et horizontale si orientation=true, verticale si orientation=false
//Préconditions : l+x <= la taille max du tableau si orientation=true, l+z <= la taille max du tableau si orientation=true
void elementVille::creerroute (float x, float z, float l, bool orientation, MyGrid& tab, LCC& lcc) {
    My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);
    //les 4 angles de la route
    ib.add_vertex(Point(x, 0, z));
    if (orientation) {
        ib.add_vertex(Point(x+l, 0, z));
        ib.add_vertex(Point(x+l, 0, z+1));
        ib.add_vertex(Point(x, 0, z+1));
        for (int i=0; i<l; i++) {
            tab[(int)x+i][(int)z]=2;
        }
    }
    else {
        ib.add_vertex(Point(x+1, 0, z));
        ib.add_vertex(Point(x+1, 0, z+l));
        ib.add_vertex(Point(x, 0, z+l));
        for (int i=0; i<l; i++) {
            tab[(int)x][(int)z + i]=2;
        }
    }
    ib.add_facet({0,1,2,3});
    ib.end_surface();
}

//créé une route à partir des coordonées (x, z), de longueur l et de largeur 1, et horizontale si orientation=true, verticale si orientation=false
//Préconditions : l+x <= la taille max du tableau si orientation=true, l+z <= la taille max du tableau si orientation=true
void elementVille::creerrue (float x, float z, float l, bool orientation, MyGrid& tab, LCC& lcc) {
    My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);

    if ((orientation && x+l<=dim) || (!orientation && z+l<=dim)) {
        creerroute (x, z, l, orientation, tab, lcc);
        int p, q, r, lx, lz, cases, imm;
        bool good;
        for (int i=0; i<10; i++) {
            imm = rand()%2; //on tire un nombre aléatoire entre 0 et 1 qui va dire si c'est une maison ou un immeuble
            good = false;
            while (!good){ //on vérifie à chaque  batiment que ses coordonnées tirées au hasard sont bien libres, sinon on retire de nouvelles coordonées
                if (orientation) { //cas pour une route horizontale
                    //ici les coordonées sont tirées parmi les cases collées à la route, et les longueurs des batiments entre 1 et 3
                    p = x + rand()%(int)(l-3); 
                    q = z + (rand()%2)*2 - 1;
                    std::cout<<q<<"\n";
                    lx = rand()%3 + 1;
                    lz = rand()%3 + 1; 
                    if (q==z-1) q=q-lz+1;
                    std::cout<<p<<" "<<q<<" "<<lx<<" "<<lz<<"\n";
                    cases=0;

                    //on parcourt toutes les cases occupées par le batiment pour voir si elles sont libres ou non
                    for (int j=p; j<p+lx; j++) {
                        for (int k=q; k<q+lz; k++) {
                            if (tab[j][k]!=0) {
                                cases += 1;
                            }
                        }
                    }
                    //si elles sont toutes libres, on change leur valeur à 1
                    if (cases==0) {
                        for (int j=p; j<p+lx; j++) {
                            for (int k=q; k<q+lz; k++) {
                                    tab[j][k]=1;
                            }
                        }
                    }
                }
                
                if (!orientation) { //cas pour une route verticale
                    //ici les coordonées sont tirées parmi les cases collées à la route, et les longueurs des batiments entre 1 et 3
                    p = x + (rand()%2)*2 - 1;
                    q = z + rand()%(int)(l-3); 
                    std::cout<<q<<"\n";
                    lx = rand()%3 + 1;
                    lz = rand()%3 + 1; 
                    if (p==x-1) p=p-lx+1;
                    std::cout<<p<<" "<<q<<" "<<lx<<" "<<lz<<"\n";
                    cases=0;

                    //on parcourt toutes les cases occupées par le batiment pour voir si elles sont libres ou non
                    for (int j=p; j<p+lx; j++) {
                        for (int k=q; k<q+lz; k++) {
                            if (tab[j][k]!=0) {
                                cases += 1;
                            }
                        }
                    }
                    //si elles sont toutes libres, on change leur valeur à 1
                    if (cases==0) {
                        for (int j=p; j<p+lx; j++) {
                            for (int k=q; k<q+lz; k++) {
                                    tab[j][k]=1;
                            }
                        }
                    }
                }

                good = (cases==0);
            }
            if (imm==0) {
                creermaison(p, q, lx, lz, lcc);
            }
            else {
                int etage = rand()%10 + 1;
                creerimmeuble(p, q, lx, lz, etage, lcc);
            }
        }
    }
}

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
    std::cout<<"je rentre \n";
    Dart_handle dh1 = j.etage (x, 0, z, lx, lz, lcc);
    Dart_handle dh = lcc.beta(dh1, 1);
    // Dart_handle dh2 = j.toit (x, 2, z, lx, 0.5, lz, lcc);
    // lcc.sew<3>(dh1, lcc.beta(dh2, 1));
    // lcc.sew<2>(lcc.beta(dh1, 1, 2, 1, 1), lcc.beta(dh2, 2, 1));
    // //return j.etage (x, 0, z, lx, lz, lcc);
    // j.etage (x, 0, z, lx, lz, lcc);
    // j.toit (x, 2, z, lx, 0.5, lz, lcc);

//     //MAISON FIXE
//     //8 sommets d'un cube
//   ibb.add_vertex(Point(0,0,0));
//   ibb.add_vertex(Point(0,1,0));
//   ibb.add_vertex(Point(0,0,1));
//   ibb.add_vertex(Point(0,1,1));
//   ibb.add_vertex(Point(1,0,0));
//   ibb.add_vertex(Point(1,1,0));
//   ibb.add_vertex(Point(1,0,1));
//   ibb.add_vertex(Point(1,1,1));
//     //sommet d'un toit
//   ibb.add_vertex(Point(.5,1.5,.5));
//   ibb.begin_surface();
//   //on créé les faces du cube
//   ibb.add_facet({0,1,3,2});
//   ibb.add_facet({4,6,7,5});
//   ibb.add_facet({1,0,4,5});
//   ibb.add_facet({6,2,3,7});
//   ibb.add_facet({2,6,4,0});
// //  ibb.add_facet({3,1,5,7});
//   //on crée le toit
//   ibb.add_facet({1,8,3});
//   ibb.add_facet({7,3,8});
//   ibb.add_facet({5,7,8});
//   ibb.add_facet({5,8,1});
//   ibb.end_surface();
}

//On génère un quartier de manière totalement aléatoire, en prenant en paramètre le nombre de batiments que l'on veut dans le quartier
// et les dimensions du quartier
void elementVille::genererquartier (int nb, int dim, LCC& lcc) {
    //on initialise un tableau avec des 0 à l'intérieur
    //1 = batiment
    //2 = route
    MyGrid tab(dim,std::vector<int>(dim,0));
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            std::cout << tab[i][j] << " ";
        }
        std::cout<< endl;
    }
    //for (int i=0; i<dim; i++) {tab[i].resize(dim, 0);}

    //int tab[dim][dim] = {0};

    bool good;
    int cases;
    float x, lx, z, lz;

    //on génère un quadrillage de routes au milieu du quartier
    for (int i=5; i<dim-5; i+=4) {
        creerroute(i, 0, dim, false, tab, lcc);
        creerroute(0, i, dim, true, tab, lcc);
    }

    for (int i=5; i<dim-5; i+=4) {
        int compteur = 0;
        for (int j=0; j<dim; j++) {
            if (tab[i][j]==1) {
                compteur += 1;
            }
        }    
        if (compteur == 0) creerrue(i, 0, dim, false, tab, lcc);
        compteur = 0;
        for (int j=0; j<dim; j++) {
            if (tab[j][i]==1) {
                compteur += 1;
            }
        }   
        if (compteur == 0) creerrue(0, i , dim, true, tab, lcc);
    }
        // creerrue(0, 9, dim, true, tab, lcc);
        // creerrue(14, 0, dim, false, tab, lcc);
        // creerrue(39, 9, dim/2, false, tab, lcc);


    for (int i=0; i<nb; i++) {
        int imm = rand()%2; //on tire un nombre aléatoire entre 0 et 1 qui va dire si c'est une maison ou un immeuble
        good = false;
        while (!good){ //on vérifie à chaque  batiment que ses coordonnées tirées au hasard sont bien libres, sinon on retire de nouvelles coordonées
            //ici les coordonées sont entre 0 et 11 en x et z, et les longueurs des batiments entre 1 et 3
            x = rand()%45; 
            z = rand()%45;
            lx = rand()%3 + 1;
            lz = rand()%3 + 1; 
            std::cout<<x<<" "<<z<<" "<<lx<<" "<<lz<<"\n";
            cases=0;

        //on parcourt toutes les cases occupées par le batiment pour voir si elles sont libres ou non
            for (int j=x; j<x+lx; j++) {
                for (int k=z; k<z+lz; k++) {
                    if (tab[j][k]!=0) {
                        cases += 1;
                    }
                }
            }
        //si toutes les cases sont disponibles pour poser un batiments, on les place dans le terrain et dans le tableau virtuel
            good = (cases==0);
            if (good) {
                for (int j=x; j<x+lx; j++) {
                    for (int k=z; k<z+lz; k++) {
                            tab[j][k]=1;
                    }
                }
            }
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
