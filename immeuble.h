#ifndef IMMEUBLE_H
#define IMMEUBLE_H

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
typedef LCC::Dart_handle Dart_handle;

class immeuble
{
public:
    // immeuble();
    Dart_handle plancher(float x, float y, float z, float lx, float lz, LCC& lcc);
    void murCote (LCC& lcc, Dart_handle D);
    void Bas(LCC& lcc, Dart_handle D);
    void Haut(LCC& lcc, Dart_handle D);

    Dart_handle etage (float x, float y, float z, float lx, float lz, LCC& lcc);
    Dart_handle toit (float x, float y, float z, float lx, float ly, float lz, LCC& lcc);
    void murCoteGauche (LCC& lcc, Dart_handle D);
};

#endif // IMMEUBLE_H
