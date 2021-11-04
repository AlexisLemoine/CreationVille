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
  immeuble L, Ma;
  elementVille M, I;
  LCC lcc;

  // intGrid tab(M.dim,std::vector<int>(M.dim,0));

  ///////////////////////// A DECOMMENTER SI ON VEUT AFFICHER UN QUARTIER
  // GridDH tabDH = M.creerGrille(lcc, Point(0,0,0), M.dim, M.dim, M.dim, M.dim);
  // M.quartier(lcc, tabDH, tab);
  ////////////////////////
  Ma.structMaison(0, 0 ,0, 3, 3, lcc);
  // L.structImmeuble(-5, 0, -5, 3, 3, lcc);
  //M.quartier();


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
