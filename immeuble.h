#ifndef IMMEUBLE_H
#define IMMEUBLE_H

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Dart_handle Dart_handle;

class immeuble
{
public:
    // immeuble();
    void murCote (LCC& lcc, Dart_handle D);
    void etage (float x, float y, float z, float lx, float lz, LCC& lcc);
    void toit (float x, float y, float z, float lx, float ly, float lz, LCC& lcc);
//    Dart_handle etage (float x, float y, float z, float lx, float lz, LCC& lcc);
//    Dart_handle toit (float x, float y, float z, float lx, float ly, float lz, LCC& lcc);
};

#endif // IMMEUBLE_H
