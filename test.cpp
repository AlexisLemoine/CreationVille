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
  Ville M, I;
  LCC lcc;


  ///////////////////////// A DECOMMENTER SI ON VEUT AFFICHER UN QUARTIER
  M.quartier();
  M.grilleint();

  draw(M.lcc, "Ville", false, Mydrawingfunctor());

  //on peut changer quelques paramètres (taille de la grille, nb de bâtiments, et taille max des immeubles) dans le constructeur par défaut de la classe Ville

  ///////////////////////


  /////////////////////////A decommenter pour afficher une maison
  // Ma.structMaison(0, 0 ,5, 3, 3, lcc);
  // draw(lcc, "Maison", false, Mydrawingfunctor());
  //////////////////////

  /////////////////////////A decommenter pour afficher un immeuble
  // L.structImmeuble(6, 0, -5, 3, 3, lcc);
  // draw(lcc, "Immeuble", false, Mydrawingfunctor());
  /////////////////////

  return EXIT_SUCCESS;
}
