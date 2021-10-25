#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"
#include "lcc_creations.h"
#include "elementVille.h"
#include "immeuble.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Dart_handle Dart_handle;
typedef LCC::Point Point;

int main()
{
  LCC lcc;
  immeuble L;
  elementVille M, I;

  std::cout<<"alpha";
  // Dart_handle dh1 = M.creermaison (-5, -5, 1, 1,lcc);
  //I.creerimmeuble (-10, -10, 10, 3, 7, lcc);
  //  L.plancher(5, 0, 5, 4, 3, lcc);
   GridDH tab = I.creerGrille(lcc, Point(0,0,0), 5, 5, 5, 5);

  
  // Dart_handle dh2 = tab[0][0];
  // M.suppBrinSol(dh2, 3, 2, lcc);

  // Dart_handle dh3 = tab[3][3];
  // M.suppBrinSol(dh3, 2, 2, lcc);

  M.sewMaison(0, 0, 1, 2, lcc, tab);
  M.sewMaison(1, 0, 2, 1, lcc, tab);
  M.sewMaison(3, 0, 2, 2, lcc, tab);
  M.sewMaison(1, 1, 1, 1, lcc, tab);
  M.sewMaison(2, 2, 3, 3, lcc, tab);
  // L.structMaison(0, 1, 0, 3, 2, lcc);

  //lcc.remove_cell<0>(lcc.beta(dh2, 1, 1));
  // lcc.sew<2>(dh1, dh2);

  //M.genererquartier(0, 30, lcc);

//  My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);

//    ib.add_vertex(Point(0,0,0));
//    ib.add_vertex(Point(1,0,0));
//    ib.add_vertex(Point(1,1,0));

//  // My_linear_cell_complex_incremental_builder_3 ib;
//  ib.begin_surface();
//    ib.add_facet({0,1,2});
//  ib.end_surface();

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

  lcc.sew<3>(lcc.beta(dh1, 1, 1, 2), lcc.beta(dh2, 2));

  lcc.sew<3>(lcc.beta(dh1), lcc.beta(dh3,2,1,1));

  lcc.display_characteristics(std::cout)<<", valid="
                                        <<lcc.is_valid()<<std::endl; */
  draw(lcc);

  return EXIT_SUCCESS;
}
