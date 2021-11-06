#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"
#include "lcc_creations.h"
#include "elementVille.h"
#include "immeuble.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Dart_handle Dart_handle;
typedef LCC::Point Point;
typedef std::vector<std::vector<Dart_handle>> GridDH;


struct Volume
{
  CGAL::Color color;
  int type;
};
struct Myitem
{
  template<class Refs>
  struct Dart_wrapper
  {
    typedef CGAL::Cell_attribute_with_point< Refs >
    Vertex_attribute;
    typedef CGAL::Cell_attribute< Refs, Volume >
    Volume_attribute;
    typedef std::tuple<Vertex_attribute, void, void, Volume_attribute > Attributes;
  };
};
typedef CGAL::Linear_cell_complex_traits<3, CGAL::Exact_predicates_inexact_constructions_kernel> Traits;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3,3,Traits,Volume> LCC_3;


void elementVille::creerGrille(  const typename LCC::Point basepoint,
                                   typename LCC::FT sx,
                                   typename LCC::FT sy,
                                   std::size_t nbx,
                                   std::size_t nby) 
{
    tabDH[0][0] = make_xy_grid(lcc, basepoint, sx, sy, nbx, nby);
    for (int i=0; i<nby; i++) {
        for (int j=0; j<nbx; j++) {
            if (j==0 && i>0) tabDH[j][i]=lcc.beta(tabDH[j][i-1], 0, 2, 0);
            if (j>0) tabDH[j][i] = lcc.beta(tabDH[j-1][i], 1, 1, 2);

        }
    }
}

bool elementVille::rechercheRoute (Dart_handle dh) {
    for (int i=0; i<route.size(); i++) {
        if (route[i]==dh) return true;
    }
    return false;
}

void elementVille::grilleint () {
    for (int i=0; i<dim; i++){
        std::cout<<"\n";
        for (int j=0; j<dim; j++) {
            std::cout<</*"tab["<<j<<"]["<<i<<"] = "<<*/tab[j][i]<<"  ";
        }
    }
}

//créé une route à partir des coordonées (x, z), de longueur l et de largeur 1, et horizontale si orientation=true, verticale si orientation=false
//Préconditions : l+x <= la taille max du tableau si orientation=true, l+z <= la taille max du tableau si orientation=true
void elementVille::creerroute (float x, float z, float l, bool orientation) {
    // //les 4 angles de la route
    std::cout<<"   " << x << "    "<< z << "\n";
    Dart_handle d = tabDH[x][z];
    // if (tab[x][z]==0)  lcc.sew<2>(d, lcc.make_quadrangle(Point(x, 0, z),  Point(x, 0, z+1),  Point(x+1, 0, z+1),  Point(x+1, 0, z) ));
    tab[x][z] = 2;
    
    if (orientation) {

        if (x>0) {
            if (tab[x-1][z]==2 && (!rechercheRoute(d) && !rechercheRoute(lcc.beta(d, 2)))) route.push_back(d);
        }
        if (z+1<dim) {
            if (tab[x][z+1]==2 && (!rechercheRoute(lcc.beta(d, 0)) && !rechercheRoute(lcc.beta(d, 0, 2)))) route.push_back(lcc.beta(d, 0));
        }
        if(z>0) {
            if (tab[x][z-1]==2 && (!rechercheRoute(lcc.beta(d, 1)) && !rechercheRoute(lcc.beta(d, 1, 2)))) route.push_back(lcc.beta(d, 1));
        }


        for (int i=1; i<l; i++) {
            d=lcc.beta(d, 1, 1, 2);
            if (!rechercheRoute(d)) {
                route.push_back(d);
                tab[x+i][z] = 2;
                // lcc.sew<2>(d, lcc.make_quadrangle(Point(x+i, 0, z),  Point(x+i, 0, z+1),  Point(x+i+1, 0, z+1),  Point(x+i+1, 0, z) ));
            }
            if (z+1<dim) {
                if (tab[x+i][z+1]==2 && (!rechercheRoute(lcc.beta(d, 0)) && !rechercheRoute(lcc.beta(d, 0, 2)))) route.push_back(lcc.beta(d, 0));
            }
            if(z>0) {
                if (tab[x+i][z-1]==2 && (!rechercheRoute(lcc.beta(d, 1)) && !rechercheRoute(lcc.beta(d, 1, 2)))) route.push_back(lcc.beta(d, 1));
            }
        }
    }
    else {
        d=lcc.beta(d, 1);
        if (z>0) {
            if (tab[x][z-1]==2 && (!rechercheRoute(d) && !rechercheRoute(lcc.beta(d, 2)))) route.push_back(d);
        }
        if (x+1<dim) {
            if (tab[x+1][z]==2 && (!rechercheRoute(lcc.beta(d, 1)) && !rechercheRoute(lcc.beta(d, 1, 2)))) route.push_back(lcc.beta(d, 1));
        }
        if(x>0) {
            if (tab[x-1][z]==2 && (!rechercheRoute(lcc.beta(d, 0)) && !rechercheRoute(lcc.beta(d, 0, 2)))) route.push_back(lcc.beta(d, 0));
        }

        for (int i=1; i<l; i++) {
            d=lcc.beta(d, 1, 1, 2);
            if (!rechercheRoute(d)) {
                route.push_back(d);
                tab[x][z+i]=2;
                // lcc.sew<2>(d, lcc.make_quadrangle(Point(x, 0, z+i),  Point(x, 0, z+i+1),  Point(x+1, 0, z+i+1),  Point(x+1, 0, z+i) ));
            }
            if (x+1<dim) {
                if (tab[x+1][z+i]==2 && (!rechercheRoute(lcc.beta(d, 1)) && !rechercheRoute(lcc.beta(d, 1, 2)))) route.push_back(lcc.beta(d, 1));
            }
            if(x>0) {
                if (tab[x-1][z+i]==2 && (!rechercheRoute(lcc.beta(d, 0)) && !rechercheRoute(lcc.beta(d, 0, 2)))) route.push_back(lcc.beta(d, 0));
            }
        }

        if (z+l<dim) {
            if (tab[x][z+l]==2 && (!rechercheRoute(lcc.beta(d, 1, 1)) && !rechercheRoute(lcc.beta(d, 1, 1, 2)))) route.push_back(lcc.beta(d, 1, 1));
        }

    }
}

//créé une route à partir des coordonées (x, z), de longueur l et de largeur 1, et horizontale si orientation=true, verticale si orientation=false
//Préconditions : l+x <= la taille max du tableau si orientation=true, l+z <= la taille max du tableau si orientation=true
void elementVille::creerrue (float x, float z, float l, bool orientation) {
    My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);

    if ((orientation && x+l<=dim) || (!orientation && z+l<=dim)) {
        creerroute (x, z, l, orientation);
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
                creermaison(p, q, lx, lz);
            }
            else {
                int etage = rand()%10 + 1;
                creerimmeuble(p, q, lx, lz, etage);
            }
        }
    }
}

//On créé et on affiche un immeuble, aux coordonées (x,z), de longueur lx sur l'axe x, lz sur l'axe z, et d'un nombre d'étage etg
//Pour cela on fait appelle à la fonction étage qui vient créer des étages un à un les uns sur les autres
void elementVille::creerimmeuble (float x, float z, float lx, float lz, int etg) {
    immeuble j;
    for (float i=0; i<=etg; i++) {
        j.etage(x, i, z, lx, lz, lcc);
    }
}

//On créé et on affiche une maison, aux coordonnées (x,z), de longueur lx sur l'axe x, lz sur l'axe z
//Pour cela, on fait appel à la fonction étage qui vient créé un étage, auquel on rajoute un toit en faisant appel à la fonction du même nom

Dart_handle elementVille::creermaison (float x, float z, float lx, float lz) {
    My_linear_cell_complex_incremental_builder_3<LCC> ibb(lcc);
    //MAISON EN FONCTION DES PARAMETRES
    immeuble j;
    std::cout<<"je rentre \n";
    // Dart_handle dh1 = j.etage (x, 0, z, lx, lz, lcc);
    // Dart_handle dh = lcc.beta(dh1, 1);
    // Dart_handle dh2 = j.toit (x, 1, z, lx, 0.5, lz, lcc);
    //lcc.sew<3>(dh1, lcc.beta(dh2, 1));
    // return lcc.beta(dh1, 2, 1, 1, 2);
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

void elementVille::sewMaison(float x, float z, float lx, float lz) {
    immeuble I;
    suppBrinSol(tabDH[x][z], lx, lz);
    lcc.sew<3>(tabDH[x][z], I.structMaison(x, 0, z, lx, lz, lcc));
}

void elementVille::sewImmeuble(int etg, float x, float z, float lx, float lz) {
    immeuble I;
    suppBrinSol(tabDH[x][z], lx, lz);
    lcc.sew<3>(tabDH[x][z], I.structImmeuble(etg, x, z, lx, lz, lcc));
}

//On génère un quartier de manière totalement aléatoire, en prenant en paramètre le nombre de batiments que l'on veut dans le quartier
// et les dimensions du quartier
void elementVille::genererquartier (int nb, int dim) {
    //on initialise un tableau avec des 0 à l'intérieur
    //1 = batiment
    //2 = route
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
        creerroute(i, 0, dim, false);
        creerroute(0, i, dim, true);
    }

    for (int i=5; i<dim-5; i+=4) {
        int compteur = 0;
        for (int j=0; j<dim; j++) {
            if (tab[i][j]==1) {
                compteur += 1;
            }
        }    
        if (compteur == 0) creerrue(i, 0, dim, false);
        compteur = 0;
        for (int j=0; j<dim; j++) {
            if (tab[j][i]==1) {
                compteur += 1;
            }
        }   
        if (compteur == 0) creerrue(0, i , dim, true);
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
            creermaison(x, z, lx, lz);
        }
        else {
            int etage = rand()%10 + 1;
            creerimmeuble(x, z, lx, lz, etage);
        }
    }
}

void elementVille::suppBrinSol(Dart_handle& dh, float lx, float lz) {
    if (lx==3 && lz==2) {
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1, 2, 1, 1, 2, 0));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 2, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1, 2, 1, 1, 2));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1, 2, 0));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 0));
    }
    if (lx==2 && lz==2) {
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1, 2, 0));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 0));
    }
    if (lx==1 && lz==2) {
        lcc.remove_cell<1>(lcc.beta(dh, 0));
    }
    if (lx==2 && lz==1) {
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1));
    }
    if (lx==2 && lz==3) {
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 1, 2, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 2, 0));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1, 2, 0));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 0));
    }
    if (lx==3 && lz==3) {
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 1, 2, 1, 2, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 1, 2, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1, 2, 1, 1, 2, 0));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 2, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1, 2, 1, 1, 2));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 2, 0));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1, 2, 0));
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 0));
    }
    if (lx==1 && lz==3) {
        lcc.remove_cell<1>(lcc.beta(dh, 0, 2, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 0));
    }
    if (lx==3 && lz==1) {
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1, 2, 1, 1));
        lcc.remove_cell<1>(lcc.beta(dh, 1, 1));
    }
}

void elementVille::quartier() {
    int p, q, lx, lz, cases, imm;
        bool good;
        float x = 0;
        float z = 0;
        int lng;
        int hor;

        //on initialise les routes et on stock tous les brins de la grille à supprimer pour faire une route
        for (int i=0; i<dim/5; i++) {
            hor = rand()%2;
            lng = rand()%(dim-6)+5;
            x = rand()%3+x+3;
            creerroute(x, rand()%(dim-lng), lng, 0);
            lng = rand()%(dim-6)+5;
            z = rand()%3+z+3;
            creerroute(rand()%(dim-lng), z, lng, 1);
            std::cout<<" c \n\n"<<i<<"   "<<lng<<std::endl<<std::endl;
            // if (hor==1) { 
            //     std::cout<<"  iii "<<hor<<std::endl;
            //     creerroute(rand()%(dim-lng), rand()%dim, lng, hor);
            //     std::cout<<"  aaa "<<hor<<std::endl;
            // }
            // else { 
            //     std::cout<<" ooo  "<<hor<<std::endl;
            //     creerroute(rand()%dim, rand()%(dim-lng), lng, hor);
            //     std::cout<<"  bbbmake "<<hor<<std::endl;
            // }
                std::cout<<"  aaa "<<hor<<std::endl;
        }
        std::cout<<"on est là \n";
                // creerroute(1, 1, 10, 1);
                // creerroute(1, 1, 10, 1);
        //on supprimer les brins des routes
        for(int i=0; i<route.size(); i++) {
            std::cout<<i<<"\n";
            lcc.remove_cell<1>(route[i]);
        }

        for (int i=0; i<nbBat; i++) {
            imm = rand()%2; //on tire un nombre aléatoire entre 0 et 1 qui va dire si c'est une maison ou un immeuble
            good = false;
            while (!good){ //on vérifie à chaque  batiment que ses coordonnées tirées au hasard sont bien libres, sinon on retire de nouvelles coordonées
                    //ici les coordonées sont tirées parmi les cases collées à la route, et les longueurs des batiments entre 1 et 3
                    lx = rand()%3 + 1;
                    lz = rand()%3 + 1; 
                    p = rand()%(dim-lx+1); 
                    q = rand()%(dim-lz+1);
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

        std::cout<<cases<<"\n";
                    //si elles sont toutes libres, on change leur valeur à 1
                    if (cases==0) {
                        for (int j=p; j<p+lx; j++) {
                            for (int k=q; k<q+lz; k++) {
                                    tab[j][k]=1;
                            }
                        }
                    }
                    good = (cases==0);
            }
            std::cout<< imm<<"\n\n"<<i<<"\n\n";
            if (imm==0) sewImmeuble(rand()%(hauteurMax-1) + 2, p, q, lx, lz);
            if (imm==1) sewMaison(p, q, lx, lz);
            std::cout<< imm<<"bug ?"<<i<<"\n\n";

        }
}