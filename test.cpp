#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>
#include "My_linear_cell_complex_incremental_builder.h"
#include "lcc_creations.h"
#include "elementVille.h"
#include "immeuble.h"
#include "lcc_def.h"

int main()
{
  immeuble L, Ma;
  elementVille M, I;
  LCC lcc;


  ///////////////////////// A DECOMMENTER SI ON VEUT AFFICHER UN QUARTIER
  // intGrid tab(M.dim,std::vector<int>(M.dim,0));
  //GridDH tabDH = M.creerGrille(Point(0,0,0), M.dim, M.dim, M.dim, M.dim);
  //M.quartier();
  //M.grilleint();

  //draw(M.lcc, "Ville", false, Mydrawingfunctor());

  ///////////////////////


  /////////////////////////A decommenter pour afficher une maison
  Ma.structMaison(0, 0 ,5, 3, 3, lcc);
  draw(lcc, "Ville", false, Mydrawingfunctor());
  //////////////////////

  /////////////////////////A decommenter pour afficher un immeuble
  //L.structImmeuble(6, 0, -5, 3, 3, lcc);
  //draw(lcc, "Ville", false, Mydrawingfunctor());
  /////////////////////
  // M.quartier();
  // M.grilleint();

//  My_linear_cell_complex_incremental_builder_3<LCC> ib(lcc);




  // draw(lcc);

  return EXIT_SUCCESS;
}
