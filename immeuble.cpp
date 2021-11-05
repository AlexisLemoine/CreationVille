#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"
#include <stdlib.h>
#include "immeuble.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Point Point;
typedef LCC::Dart_handle Dart_handle;

/*Point p = lcc.point(lcc.beta(dh7, 0,0,2,0,0,2,0,3));
std ::cout << p.x() << " " << p.y() << " " << p.z() <<" ";
Point p2 = lcc.point(lcc.other_extremity(lcc.beta(dh7, 0,0,2,0,0,2,0,3))); // Pour avoir l'extrémité du brin
std ::cout << p2.x() << " " << p2.y() << " " << p2.z(); */

void immeuble::murCote (LCC& lcc, Dart_handle D){
    // Point p1 = lcc.point(D); // Pour avoir le debut du brin
    // Point p2 = lcc.point(lcc.other_extremity(D)); // Pour avoir l'extrémité du brin

    Dart_handle dh1 = lcc.beta(D, 1);
    Dart_handle dh4 = lcc.beta(D, 0,0);

    Dart_handle dh2 = lcc.beta(D, 1,1);
    Dart_handle dh3 = lcc.beta(dh4, 0);

    Dart_handle dh6 = lcc.insert_cell_1_in_cell_2(dh4, dh1);
    Dart_handle dh5 = lcc.insert_cell_1_in_cell_2(dh2, dh3);

}

void immeuble::Bas(LCC& lcc, Dart_handle D){
    // création de 4 points sur les arrètes
    Point p1 = lcc.point(D);
    Point p2 = lcc.point(lcc.other_extremity(D));
    Point p3 = lcc.point(lcc.beta(lcc.beta(D, 1), 1));

    float x = p1.x();
    float y = p1.y();
    float z = p3.z();

    float lx = p2.x() - p1.x();
    float lz = p2.z() - p3.z();

    Dart_handle dh7 = lcc.insert_point_in_cell<1>(lcc.beta(D, 1), Point(x + lx, y, z + lz - 0.2));
    Dart_handle dh9 = lcc.insert_point_in_cell<1>(dh7, Point(x+lx, y, z+0.2));
    Dart_handle dh10 = lcc.insert_point_in_cell<1>(lcc.beta(D, 0), Point(x, y, z+0.2));
    Dart_handle dh8 = lcc.insert_point_in_cell<1>(dh10,Point(x, y, z + lz - 0.2));

    // on relie ces quatres points
    Dart_handle dh11 = lcc.insert_cell_1_in_cell_2(dh8, dh7);
    Dart_handle dh12 = lcc.insert_cell_1_in_cell_2(dh9, dh10);

    // on pose 4 points sur les nouvelles lignes

    Dart_handle dh14 = lcc.insert_point_in_cell<1>(dh11, Point(x+lx-0.2, y, z+lz-0.2));
    Dart_handle dh13 = lcc.insert_point_in_cell<1>(dh14, Point(x+0.2, y, z+lz-0.2));
    Dart_handle dh16 = lcc.insert_point_in_cell<1>(dh12, Point(x+0.2, y, z+0.2));
    Dart_handle dh15 = lcc.insert_point_in_cell<1>(dh16, Point(x+lx-0.2, y, z+0.2));

    // on relie ces quatres nouveaux points.
    Dart_handle dh17 = lcc.insert_cell_1_in_cell_2(lcc.beta(dh11,2), lcc.beta(dh16,2));
    Dart_handle dh18 = lcc.insert_cell_1_in_cell_2(lcc.beta(dh12,2), lcc.beta(dh14, 2));

}

void immeuble::Haut(LCC& lcc, Dart_handle D){
    // création de 4 points sur les arrètes
    Point p1 = lcc.point(D);
    Point p2 = lcc.point(lcc.other_extremity(D));
    Point p3 = lcc.point(lcc.beta(lcc.beta(D, 1), 1));

    float x = p1.x();
    float y = p1.y();
    float z = p3.z();

    float lx = p3.x() - p2.x();
    float lz = p1.z() - p2.z();

    // on fait la même chose pour la face du haut :

    // création de 4 points sur la face du haut :
    Dart_handle dh19 = lcc.insert_point_in_cell<1>(lcc.beta(lcc.beta(D, 1), 1), Point(x+lx, y, z+0.2));
    Dart_handle dh20 = lcc.insert_point_in_cell<1>(dh19, Point(x + lx, y, z +lz-0.2));
    Dart_handle dh21 = lcc.insert_point_in_cell<1>(D, Point(x, y, z+lz-0.2));
    Dart_handle dh22 = lcc.insert_point_in_cell<1>(dh21,Point(x, y, z + 0.2));

    // on relie ces quatres points
    Dart_handle dh23 = lcc.insert_cell_1_in_cell_2(dh22, dh19);
    Dart_handle dh24 = lcc.insert_cell_1_in_cell_2(dh20, dh21);

    // on créé 4 points sur ces nouveaux traits
    Dart_handle dh25 = lcc.insert_point_in_cell<1>(dh23, Point(x+lx-0.2, y, z+0.2));
    Dart_handle dh26 = lcc.insert_point_in_cell<1>(dh25, Point(x + 0.2, y, z +0.2));
    Dart_handle dh27 = lcc.insert_point_in_cell<1>(dh24, Point(x+0.2, y, z+lz-0.2));
    Dart_handle dh28 = lcc.insert_point_in_cell<1>(dh27,Point(x+lx-0.2, y, z +lz- 0.2));

    // on relie ces 4 nouveaux points
    Dart_handle dh29 = lcc.insert_cell_1_in_cell_2(lcc.beta(dh24,2), lcc.beta(dh25,2));
    Dart_handle dh30 = lcc.insert_cell_1_in_cell_2(lcc.beta(dh23,2), lcc.beta(dh27, 2));

}

Dart_handle immeuble::murFond(LCC& lcc, Dart_handle D1, Dart_handle D2, Dart_handle D3, Dart_handle D4){
    std::vector<Dart_handle> path;
    path.push_back(lcc.beta(D1, 1, 1));
    path.push_back(lcc.beta(D3, 0,0,0,2,1,1,2,0));
    path.push_back(lcc.beta(D3, 0,0,0,2,1,1,2));
    path.push_back(lcc.beta(D3, 0,0,0,2,1,1,2,1));

    path.push_back(lcc.beta(D2, 1));
    path.push_back(lcc.beta(D4, 1, 1,2,1,1,2,0));
    path.push_back(lcc.beta(D4, 1, 1,2,1,1,2));
    path.push_back(lcc.beta(D4, 1, 1,2,1,1,2,1));

    Dart_handle dh7=lcc.insert_cell_2_in_cell_3(path.begin(),path.end());

    return dh7;
}

Dart_handle immeuble::murFace(LCC& lcc, Dart_handle D1, Dart_handle D2, Dart_handle D3, Dart_handle D4){
    std::vector<Dart_handle> path;
    path.push_back(lcc.beta(D1,0,0,2, 3, 2,1,1,2));
    path.push_back(lcc.beta(D4,1));
    path.push_back(lcc.beta(D4,1,1));
    path.push_back(lcc.beta(D4,1,1,1));

    path.push_back(lcc.beta(D2, 1,2, 3, 2,1,1,2));
    path.push_back(lcc.beta(D3, 1,1));
    path.push_back(lcc.beta(D3, 1,1,1));
    path.push_back(lcc.beta(D3, 1,1,1,1));

    Dart_handle dh8=lcc.insert_cell_2_in_cell_3(path.begin(),path.end());

    return dh8;
}

void immeuble::murGauche(LCC& lcc, Dart_handle D1, Dart_handle D2){
    Dart_handle dh9 = lcc.insert_cell_1_in_cell_2(lcc.beta(D1,1,3), lcc.beta(D1, 0,0,3));

    Dart_handle dh11 = lcc.insert_cell_1_in_cell_2(lcc.beta(D2,1,3), lcc.beta(D2, 0,0,3));



    std::vector<Dart_handle> path;
    path.push_back(dh9);
    path.push_back(lcc.beta(dh9,1,2,1));
    path.push_back(dh11);
    path.push_back(lcc.beta(dh11, 1,2,1));

    Dart_handle dh13=lcc.insert_cell_2_in_cell_3(path.begin(),path.end());

}

void immeuble::murDroite(LCC& lcc, Dart_handle D1, Dart_handle D2){

    Dart_handle dh10 = lcc.insert_cell_1_in_cell_2(lcc.beta(D1, 0,0,2,0,0,3), lcc.beta(D1,1,1,2,1,3));
    Dart_handle dh12 = lcc.insert_cell_1_in_cell_2( lcc.beta(D2, 0,0,2,0,0,3),lcc.beta(D2,1,1,2,1,3));

    std::vector<Dart_handle> path;
    path.push_back(dh10);
    path.push_back(lcc.beta(dh10,1,2,1));
    path.push_back(dh12);
    path.push_back(lcc.beta(dh12, 1,2,1));

    Dart_handle dh14=lcc.insert_cell_2_in_cell_3(path.begin(),path.end());
}


void immeuble::creerFenetreDevant(LCC& lcc, Dart_handle D){
    Point p = lcc.point(D);
    std ::cout << p.x() << " " << p.y() << " " << p.z() <<" ";
    Point p2 = lcc.point(lcc.other_extremity(D)); // Pour avoir l'extrémité du brin
    std ::cout << p2.x() << " " << p2.y() << " " << p2.z();
    float x = 1;
    float y = 0.5;
    float z = 2.8;
    Point p3 = lcc.point(lcc.other_extremity(lcc.beta(D, 2,1)));
    float lz = p3.z() - p.z();
    float lx = (200 + (rand() % (300)));
    lx = lx / 1000;
    float ly = lx;
    std::cout<< lx << ly;
    // float ly = 0.3;
    // float lx = 0.3;
    // std ::cout << lz;
    Dart_handle dh1=
        lcc.make_hexahedron(Point(x,y,z), Point(x+lx,y,z),
                            Point(x+lx,y+ly,z), Point(x,y+ly,z),
                            Point(x,y+ly,z+lz), Point(x,y,z+lz),
                            Point(x+lx,y,z+lz), Point(x+lx,y+ly,z+lz));
}
//créé 6 surfaces d'un parallélépipède rectangle de coordonnées (x,y,z) et de longueur lx et lz, et 1 en hauteur


std::vector<Dart_handle> immeuble::etage (float x, float y, float z, float lx, float lz, LCC& lcc) {
    My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);
    //8 sommets d'un cube
    ib.add_vertex(Point(x , y , z));
    ib.add_vertex(Point(x , y+1 , z));
    ib.add_vertex(Point(x , y , z+lz));
    ib.add_vertex(Point(x , y+1 , z+lz));
    ib.add_vertex(Point(x+lx , y , z));
    ib.add_vertex(Point(x+lx , y+1 , z));
    ib.add_vertex(Point(x+lx , y , z+lz));
    ib.add_vertex(Point(x+lx , y+1 , z+lz));
    ib.begin_surface();
    //on créé les faces du cube
    Dart_handle dh1 = ib.add_facet({0,1,3,2}); // quand on appelle dh1, on est sur l'arrête (0, 1). arrête au même endroit pour les autres dh.
    Dart_handle dh2 = ib.add_facet({4,6,7,5});
    Dart_handle dh3 = ib.add_facet({1,0,4,5});
    Dart_handle dh4 = ib.add_facet({6,2,3,7});
    Dart_handle dh5 = ib.add_facet({2,6,4,0});
    Dart_handle dh6 = ib.add_facet({3,1,5,7});
    ib.end_surface();
    std::vector<Dart_handle> tab = {dh1, dh2, dh3, dh4, dh5, dh6};
    return tab;
}

Dart_handle immeuble::structImmeuble(int etg, float x, float z, float lx, float lz, LCC& lcc) {
    Dart_handle brinretourne;
    Dart_handle brintemp;
    std::vector<std::vector<Dart_handle>> tab(11,std::vector<Dart_handle>(6,NULL));
    std::cout<<"ON RENTRE \n";
    for (int j=0; j<etg; j++) {
        
        std::vector<Dart_handle> t = etage (x, .2+j*1.2, z, lx, lz, lcc);

        Dart_handle dh1 = t[0];
        Dart_handle dh2 = t[1];
        Dart_handle dh3 = t[2];
        Dart_handle dh4 = t[3];
        Dart_handle dh5 = t[4];
        Dart_handle dh6 = t[5];

        tab[j][0]=dh1;
        tab[j][1]=dh2;
        tab[j][2]=dh3;
        tab[j][3]=dh4;
        tab[j][4]=dh5;
        tab[j][5]=dh6;
        
        Dart_handle dh0 = plancher(x, j*1.2, z, lx, lz, lcc);
        
        lcc.sew<3>(lcc.beta(dh0, 2, 1, 1, 2), dh5);
        if (j==0) {
            Dart_handle dh02 =lcc.beta(dh0, 1);
            Dart_handle dh03 =lcc.beta(dh02, 1);
            Dart_handle dh01 =lcc.beta(dh03, 1);
            for (int i=1; i<lz; i++) {
                lcc.insert_point_in_cell<1>(dh01, Point(x, 0, z+lz-i));
            }
            for (int i=1; i<lx; i++) {
                lcc.insert_point_in_cell<1>(dh0, Point(x+lx-i, 0, z+lz));
            }
            for (int i=1; i<lz; i++) {
                lcc.insert_point_in_cell<1>(dh02, Point(x+lx, 0, z+i));
            }
            for (int i=1; i<lx; i++) {
                lcc.insert_point_in_cell<1>(dh03, Point(x+i, 0, z));
            }
            brinretourne = dh01;
        }
        else lcc.sew<3>(lcc.beta(brintemp, 0), dh0);

        brintemp = dh6;
    }

    for (int j=0; j<etg; j++) {
        Dart_handle dh1 = tab[j][0];
        Dart_handle dh2 = tab[j][1];
        Dart_handle dh3 = tab[j][2];
        Dart_handle dh4 = tab[j][3];
        Dart_handle dh5 = tab[j][4];
        Dart_handle dh6 = tab[j][5];
        Bas(lcc, dh5);
        Haut(lcc, dh6);


        // création des points et traits a l'intérieur de la face du bas :
        murCote (lcc, lcc.beta(dh1, 0, 0, 0));
        murCote (lcc, dh2);

        Dart_handle dh7 = murFond (lcc, dh1, dh2, dh5, dh6);
        Dart_handle dh8 = murFace (lcc, dh1, dh2, dh5, dh6);

        murGauche(lcc, dh7, dh8);
        murDroite(lcc, dh7, dh8);
        std::cout<<j << "\n";
    }
    return brinretourne;
}

Dart_handle immeuble::structMaison(float x, float y, float z, float lx, float lz, LCC& lcc) {
    std::vector<Dart_handle> tab = etage (x, y+.2, z, lx, lz, lcc);
    Dart_handle dh1 = tab[0];
    Dart_handle dh2 = tab[1];
    Dart_handle dh3 = tab[2];
    Dart_handle dh4 = tab[3];
    Dart_handle dh5 = tab[4];
    Dart_handle dh6 = tab[5];


    Dart_handle dh0 = plancher(x, y, z, lx, lz, lcc);
    Dart_handle roof = toit(x, y+1.2, z, lx, .5, lz, lcc);

    lcc.sew<3>(lcc.beta(dh6, 1), roof);
    lcc.sew<3>(lcc.beta(dh0, 2, 1, 1, 2), dh5);

    Dart_handle dh02 =lcc.beta(dh0, 1);
    Dart_handle dh03 =lcc.beta(dh02, 1);
    Dart_handle dh01 =lcc.beta(dh03, 1);
    for (int i=1; i<lz; i++) {
        lcc.insert_point_in_cell<1>(dh01, Point(x, y, z+lz-i));
        std::cout<<i <<" \n";
    }
    for (int i=1; i<lx; i++) {
        lcc.insert_point_in_cell<1>(dh0, Point(x+lx-i, y, z+lz));
        std::cout<<i <<" \n";
    }
    for (int i=1; i<lz; i++) {
        lcc.insert_point_in_cell<1>(dh02, Point(x+lx, y, z+i));
        std::cout<<i <<" \n";
    }
    for (int i=1; i<lx; i++) {
        lcc.insert_point_in_cell<1>(dh03, Point(x+i, y, z));
        std::cout<<i <<" \n";
    } 


    Bas(lcc, dh5);
    Haut(lcc, dh6);


    // création des points et traits a l'intérieur de la face du bas :

    murCote (lcc, lcc.beta(dh1, 0, 0, 0));
    murCote (lcc, dh2);

    Dart_handle dh7 = murFond (lcc, dh1, dh2, dh5, dh6);
    Dart_handle dh8 = murFace (lcc, dh1, dh2, dh5, dh6);

    murGauche(lcc, dh7, dh8);
    murDroite(lcc, dh7, dh8);

    creerFenetreDevant(lcc, dh8);
    return dh01;
}


Dart_handle immeuble::plancher(float x, float y, float z, float lx, float lz, LCC& lcc) {
    My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);
    //8 sommets d'un cube
    ib.add_vertex(Point(x , y , z));
    ib.add_vertex(Point(x , y+.2 , z));
    ib.add_vertex(Point(x , y , z+lz));
    ib.add_vertex(Point(x , y+.2 , z+lz));
    ib.add_vertex(Point(x+lx , y , z));
    ib.add_vertex(Point(x+lx , y+.2 , z));
    ib.add_vertex(Point(x+lx , y , z+lz));
    ib.add_vertex(Point(x+lx , y+.2 , z+lz));
    ib.begin_surface();
    //on créé les faces du cube
    ib.add_facet({3,2,0,1}); // quand on appelle dh1, on est sur l'arrête (0, 1). arrête au même endroit pour les autres dh.
    ib.add_facet({7,5,4,6});
    ib.add_facet({4,5,1,0});
    ib.add_facet({6,2,3,7});
    Dart_handle dh1 = ib.add_facet({2,6,4,0});
    ib.add_facet({3,1,5,7});
    ib.end_surface();

    return dh1;
}


//Créé les 4 pentes d'un toit de type pyramide aux coordonnées (x,y,z), de longueur lx, lz, et de hauteur à la pointe ly

Dart_handle immeuble::toit (float x, float y, float z, float lx, float ly, float lz, LCC& lcc) {
    My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);
    //4 sommets de la base d'une pyramide
    ib.add_vertex(Point(x , y , z));
    ib.add_vertex(Point(x , y , z+lz));
    ib.add_vertex(Point(x+lx , y , z));
    ib.add_vertex(Point(x+lx , y , z+lz));
    //sommet de la pyramide
    ib.add_vertex(Point(x+lx/2 , y+ly , z+lz/2));

    //création des faces de la pyramide
    ib.add_facet({0,1,4});
    ib.add_facet({2,0,4});
    ib.add_facet({3,2,4});
    ib.add_facet({1,3,4});
    ib.add_facet({1,0,2,3});
    //Dart_handle dh2 = lcc.insert_point_in_cell<1>(dh, Point(x, y, z + .2));
    return ib.end_surface();

}
