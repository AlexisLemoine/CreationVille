#ifndef IMMEUBLE_H
#define IMMEUBLE_H

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;

class immeuble
{
public:
    // immeuble();
    void etage (float x, float y, float z, float lx, float lz, LCC& lcc);
};

#endif // IMMEUBLE_H
