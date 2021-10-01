#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"

#include "immeuble.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Point Point;
typedef LCC::Dart_handle Dart_handle;

void immeuble::etage (float x, float y, float z, float lx, float lz, LCC& lcc) {
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
    Dart_handle dh1 = ib.add_facet({0,1,3,2});
    Dart_handle dh2 = ib.add_facet({4,6,7,5});
    Dart_handle dh3 = ib.add_facet({1,0,4,5});
    Dart_handle dh4 = ib.add_facet({6,2,3,7});
    Dart_handle dh5 = ib.add_facet({2,6,4,0});
    Dart_handle dh6 = ib.add_facet({3,1,5,7});

    lcc.insert_point_in_cell<1>(dh4,Point(x + 0.2, y, z + lz));
    lcc.insert_point_in_cell<1>(dh4,Point(x + lx - 0.2, y, z + lz));
    lcc.insert_point_in_cell<1>(dh2,Point(x + lx, y, z + 0.2));
    lcc.insert_point_in_cell<1>(dh2,Point(x + lx, y, z + lz - 0.2));
    lcc.insert_point_in_cell<1>(lcc.beta(dh3, 1), Point(x + 0.2, y, z));
    lcc.insert_point_in_cell<1>(lcc.beta(dh3, 1),Point(x + lx - 0.2, y, z));
    lcc.insert_point_in_cell<1>(lcc.beta(dh1, 0),Point(x, y, z + 0.2));
    lcc.insert_point_in_cell<1>(lcc.beta(dh1, 0),Point(x, y, z + lz - 0.2));
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
