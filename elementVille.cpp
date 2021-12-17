#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"
#include "lcc_creations.h"
#include "elementVille.h"
#include "immeuble.h"
#include "lcc_def.h"

typedef std::vector<std::vector<Dart_handle>> GridDH;



//Méthode qui crée la grille en fonction du nombre de cases en x et z, et du point de départ (que l'on fixe à (0, 0, 0) pour plus de simplicité)
//Elle se sert directement des fonctions du ficher lcc_creations.h
void Ville::creerGrille(  const typename LCC::Point basepoint,
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

//Affiche dans la console la grille des entiers (avec des 0 si la case est libre, 1 s'il y a un immeuble/maison, 2 si c'est une route)
void Ville::grilleint () {
    for (int i=0; i<dim; i++){
        std::cout<<"\n";
        for (int j=0; j<dim; j++) {
            std::cout<<tab[j][i]<<"  ";
        }
    }
}

//créé une route à partir des coordonées (x, z), de longueur l et de largeur 1, et horizontale si orientation=true, verticale si orientation=false
//Préconditions : l+x <= la taille max du tableau si orientation=true, l+z <= la taille max du tableau si orientation=true
void Ville::creerroute (float x, float z, float l, bool orientation) {
    Dart_handle d = tabDH[x][z];
    
    //route horizontale, pour chaque case de la route, on associe chaque brin à l'attribut route, pour pouvoir ensuite enlever leur affichage
    //et on associe chaque face à l'attribut route également pour pouvoir l'afficher d'une certaine couleur
    //puis on remplit notre tableau d'entiers avec des 2 partout où il y a des routes, et des 3 aux extrémités de chacune d'elles afin qu'un batiment ne
    //soit pas placé au bout d'une route.
    if (orientation) {
        for (int i=0; i<l; i++) {
            if (tab[x+i][z]==0) {
                for (int j=0; j<4; j++) { // on donne un attribut ROUTE aux 4 brins qui constitue le carré de la grille ROUTE pour choisir de ne pas les afficher
                    d=lcc.beta(d, 1);
                    lcc.template set_attribute<1>(d, lcc.template create_attribute<1>());
                    lcc.template info<1>(d).type=ROUTE;
                }
                lcc.template set_attribute<2>(d, lcc.template create_attribute<2>()); // on donne un attribut ROUTE à la surface de route pour l'afficher en blanc
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
                for (int j=0; j<4; j++) {// on donne un attribut ROUTE aux 4 brins qui constitue le carré de la grille ROUTE pour choisir de ne pas les afficher
                    d=lcc.beta(d, 1);
                    lcc.template set_attribute<1>(d, lcc.template create_attribute<1>());
                    lcc.template info<1>(d).type=ROUTE;
                }
                lcc.template set_attribute<2>(d, lcc.template create_attribute<2>());// on donne un attribut ROUTE à la surface de route pour l'afficher en blanc
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

}


//Cette méthode prend en paramètre les coordonnés ainsi que les longueurs en x et z d'une maison, elle la créée, supprime les brins
//de la grille à l'endroit où elle doit être posée, et sew la grille avec la maison en question
void Ville::sewMaison(float x, float z, float lx, float lz) {
    immeuble I;
    suppBrinSol(tabDH[x][z], lx, lz);
    lcc.sew<3>(tabDH[x][z], I.structMaison(x, 0, z, lx, lz, lcc));
}

//Cette méthode prend en paramètre le nombre d'étage, les coordonnés ainsi que les longueurs en x et z d'un immeuble, elle le créé, supprime les brins
//de la grille à l'endroit où il doit être posé, et sew la grille avec l'immeuble en question
void Ville::sewImmeuble(int etg, float x, float z, float lx, float lz) {
    immeuble I;
    suppBrinSol(tabDH[x][z], lx, lz);
    lcc.sew<3>(tabDH[x][z], I.structImmeuble(etg, x, z, lx, lz, lcc));
}


//Cette méthode prend en paramètre un brin de la grille (celui le plus en haut à gauche) et le nombre en x et z des cases à supprimer sur la grille
//Elle traite dans chaque cas, la suppresion des brins internes à un carré 2x2 par exemple, afin que l'on ait plus 4 petits carrés, mais un seul carré
void Ville::suppBrinSol(Dart_handle& dh, float lx, float lz) {
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

void Ville::quartier() {
    int p, q, lx, lz, cases, imm;
        bool good;
        float x = 0;
        float z = 0;
        int lng;

        //on initialise les routes, avec un intervalle de 5 (+/-3) cases entre chaque, dans le sens horizontal et vertical, de longueur aléatoire 
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
            while (!good){ //on vérifie à chaque batiment que ses coordonnées tirées au hasard sont bien libres, sinon on retire de nouvelles coordonées
                    //ici les coordonées sont tirées parmi les cases collées à la route, et les longueurs des batiments entre 1 et 3
                    lx = rand()%3 + 1;
                    lz = rand()%3 + 1; 
                    p = rand()%(dim-lx+1); 
                    q = rand()%(dim-lz+1);
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

            if (imm==0) sewImmeuble(rand()%(hauteurMax-1) + 2, p, q, lx, lz);
            if (imm==1) sewMaison(p, q, lx, lz);

        }
}