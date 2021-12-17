#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"
#include "lcc_creations.h"
#include "elementVille.h"
#include "immeuble.h"
#include "lcc_def.h"

typedef std::vector<std::vector<Dart_handle>> GridDH;




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

//recherche si un brin de la grille de DartHandle est déjà dans le vector route de la classe
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
    std::cout<<"   " << x << "    "<< z << "\n";
    Dart_handle d = tabDH[x][z];
    
    //route horizontale, pour chaque case de la route, on associe chaque brin à l'attribut route, pour pouvoir ensuite enlever leur affichage
    //et on associe chaque face à l'attribut route également pour pouvoir l'afficher d'une certaine couleur
    //puis on remplit notre tableau d'entiers avec des 2 partout où il y a des routes
    if (orientation) {
        for (int i=0; i<l; i++) {
            if (tab[x+i][z]==0) {
                for (int j=0; j<4; j++) {
                    d=lcc.beta(d, 1);
                    lcc.template set_attribute<1>(d, lcc.template create_attribute<1>());
                    lcc.template info<1>(d).type=ROUTE;
                }
                lcc.template set_attribute<2>(d, lcc.template create_attribute<2>());
                lcc.template info<2>(d).type=ROUTE;
                lcc.template info<2>(d).color=CGAL::white();
                if (i==0 || i==l-1) {
                    if (tab[x+i][z]==0) tab[x+i][z]=3;         
                    else tab[x+i][z]=2;   
                }
                else tab[x+i][z]=2;
            }
            else if (tab[x+i][z]==3) tab[x+i][z]=2;
            d=lcc.beta(d, 1, 1, 2);
        }
    }
    //cas route verticale
    else {
        d=lcc.beta(d, 1);
        for (int i=0; i<l; i++) {
            if (tab[x][z+i] == 0) {
                for (int j=0; j<4; j++) {
                    d=lcc.beta(d, 1);
                    lcc.template set_attribute<1>(d, lcc.template create_attribute<1>());
                    lcc.template info<1>(d).type=ROUTE;
                }
                lcc.template set_attribute<2>(d, lcc.template create_attribute<2>());
                lcc.template info<2>(d).type=ROUTE;
                lcc.template info<2>(d).color=CGAL::white();
                if (i==0 || i==l-1) {
                    if (tab[x][z+i]==0) tab[x][z+i]=3;
                    else tab[x][z+i]=2;      
                }
                else tab[x][z+i] = 2;
            }
            else if (tab[x][z+i]==3) tab[x][z+i]=2;
            d=lcc.beta(d, 1, 1, 2);
        }
    }
    grilleint();
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

        //on initialise les routes 
        for (int i=0; i<dim/5; i++) {
            lng = rand()%(dim-6)+5;
            x = rand()%3+5*i;
            creerroute(x, rand()%(dim-lng), lng, 0);
            lng = rand()%(dim-6)+5;
            z = rand()%3+5*i;
            creerroute(rand()%(dim-lng), z, lng, 1);
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
                    // std::cout<<p<<" "<<q<<" "<<lx<<" "<<lz<<"\n";
                    cases=0;

                    //on parcourt toutes les cases occupées par le batiment pour voir si elles sont libres ou non
                    //
                    for (int j=p; j<p+lx; j++) {
                        
                        for (int k=q; k<q+lz; k++) {
                            //test si toutes les cases sont libres via le tableau d'entiers
                            if (tab[j][k]!=0) {
                                cases += 1;
                            }
                            //test si le batiment est relié à une route
                            if (q-1>=0) {
                                if (tab[j][q-1]==2) good=true;
                            }
                            if (q+lz<dim) {
                                if (tab[j][q+lz]==2) good=true;
                            }
                            if (p-1>=0) {
                                if (tab[p-1][k]==2) good=true;
                            }
                            if (p+lx<dim) {
                                if (tab[p+lx][k]==2) good=true;
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
                    good = (good && cases==0); //on sort de la boucle seulement si toutes les cases sont libres et si c'est relié à une route
            }

            // std::cout<< imm<<"\n\n"<<i<<"\n\n";
            if (imm==0) sewImmeuble(rand()%(hauteurMax-1) + 2, p, q, lx, lz);
            if (imm==1) sewMaison(p, q, lx, lz);
            // std::cout<< imm<<"bug ?"<<i<<"\n\n";

        }
}