#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Dart_handle Dart_handle;
typedef LCC::Point Point;

void etage (float x, float y, float z, float lx, float lz, LCC& lcc) {
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
  ib.add_facet({0,1,3,2});
  ib.add_facet({4,6,7,5});
  ib.add_facet({1,0,4,5});
  ib.add_facet({6,2,3,7});
  ib.add_facet({2,6,4,0});
 // ib.add_facet({3,1,5,7});


//  const Point& i0=(Point(x , y , z));
//  const Point& i1=(Point(x+lx , y , z));
//  const Point& i2=(Point(x+lx , y , z+lz));
//  const Point& i3=(Point(x , y , z+lz));
//  const Point& i4=(Point(x , y+1 , z));
//  const Point& i5=(Point(x+lx , y+1 , z));
//  const Point& i6=(Point(x+lx , y+1 , z+lz));
//  const Point& i7=(Point(x , y+1 , z+lz));
//  make_hexahedron_with_builder(ib, i0, i1, i2, i3, i4, i5, i6, i7)

  ib.end_surface();
}

void immeuble (float x, float z, float lx, float lz, int etg, LCC& lcc) {
    for (float i=0; i<=etg; i++) {
        etage (x, i, z, lx, lz, lcc);
    }
}

void maison (float x, float z, float lx, float lz, LCC& lcc) {
    My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);
    My_linear_cell_complex_incremental_builder_3<LCC> ibb(lcc);
    //MAISON EN FONCTION DES PARAMETRES
    //8 sommets d'un cube
  ib.add_vertex(Point(x,0,z));
  ib.add_vertex(Point(x,1,z));
  ib.add_vertex(Point(x,0,z+lz));
  ib.add_vertex(Point(x,1,z+lz));
  ib.add_vertex(Point(x+lx,0,z));
  ib.add_vertex(Point(x+lx,1,z));
  ib.add_vertex(Point(x+lx,0,z+lz));
  ib.add_vertex(Point(x+lx,1,z+lz));
    //sommet d'un toit
  ib.add_vertex(Point(x+lx/2,1.5,z+lz/2));
  ib.begin_surface();
  //on créé les faces du cube
  ib.add_facet({0,1,3,2});
  ib.add_facet({4,6,7,5});
  ib.add_facet({1,0,4,5});
  ib.add_facet({6,2,3,7});
  ib.add_facet({2,6,4,0});
 // ib.add_facet({3,1,5,7});
  //on crée le toit
  ib.add_facet({1,8,3});
  ib.add_facet({7,3,8});
  ib.add_facet({5,7,8});
  ib.add_facet({5,8,1});
  ib.end_surface();


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

int main()
{
  LCC lcc;
  maison (5,5,3,2,lcc);
  immeuble (10, 10, 10, 3, 7, lcc);

  /*  Dart_handle dh1=
    lcc.make_hexahedron(Point(0,0,0), Point(5,0,0),
                        Point(5,5,0), Point(0,5,0),
                        Point(0,5,4), Point(0,0,4),
                        Point(5,0,4), Point(5,5,4));
  Dart_handle dh2=
    lcc.make_hexahedron(Point(5,0,0), Point(10,0,0),
                        Point(10,5,0), Point(5,5,0),
                        Point(5,5,4), Point(5,0,4),
                        Point(5,0,4), Point(5,5,4));

  Dart_handle dh3=
    lcc.make_hexahedron(Point(0,0,0), Point(-5,0,0),
                        Point(-5,0,4), Point(0,0,4),
                        Point(0,5,4), Point(0,5,0),
                        Point(0,5,0), Point(0,5,4));

                        lcc.sew<3>(lcc.beta(dh1, 1, 1, 2), lcc.beta(dh2, 2));*/

  //  lcc.sew<3>(lcc.beta(dh1), lcc.beta(dh3,2,1,1));

  lcc.display_characteristics(std::cout)<<", valid="
                                        <<lcc.is_valid()<<std::endl;
  CGAL::draw(lcc);

  return EXIT_SUCCESS;
}
