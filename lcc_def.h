#pragma once
const int UNKNOWN = 0;
const int MUR = 1;
const int SOL = 2;
const int FENETRE = 3;
const int PORTE = 4;
const int ROUTE = 5;
const int TOIT = 6;
const int GRILLE = 7;
struct Volume
{
  CGAL::Color color;
  int type;
  Volume() {type=UNKNOWN;}
};
struct Edge
{
  int type;
};
struct Face 
{
  CGAL::Color color;
  int type;
};
struct Myitem
{
  template<class Refs>
  struct Dart_wrapper
  {
    typedef CGAL::Cell_attribute_with_point< Refs >
    Vertex_attribute;
    typedef CGAL::Cell_attribute< Refs, Edge >
    Edge_attribute;
    typedef CGAL::Cell_attribute< Refs, Face >
    Face_attribute;
    typedef CGAL::Cell_attribute< Refs, Volume >
    Volume_attribute;
    typedef std::tuple<Vertex_attribute, Edge_attribute, Face_attribute, Volume_attribute > Attributes;
  };
};
typedef CGAL::Linear_cell_complex_traits<3, CGAL::Exact_predicates_inexact_constructions_kernel> Traits;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3,3,Traits,Myitem> LCC;
typedef LCC::Point Point;
typedef LCC::Dart_handle Dart_handle;
typedef LCC::FT FT;

struct Mydrawingfunctor:public CGAL::DefaultDrawingFunctorLCC
{

  /// @return true iff the edge containing dh is drawn.
  template<typename LCC>
  bool draw_edge(const LCC& lcc,
                 typename LCC::Dart_const_handle dh) const
  { 
    if (lcc.template attribute<1>(dh)!=nullptr) {
      if (lcc.template info<1>(dh).type==ROUTE) {
        dh = lcc.beta(dh, 2);
        if (dh!=nullptr) {
          if (lcc.template attribute<1>(dh)!=nullptr) {
            if (lcc.template info<1>(dh).type==ROUTE) {
              return false;
            }
          }
        }
      }
    }
    return true; }

  /// @return the color of the volume containing dh
  ///  used only if colored_volume(alcc, dh) and !colored_face(alcc, dh)
  template<typename LCC>
  CGAL::IO::Color volume_color(const LCC& lcc,
                           typename LCC::Dart_const_handle dh) const
  {
    if (lcc.template attribute<3>(dh)!=nullptr) {
      if (lcc.template info<3>(dh).type==MUR
          || lcc.template info<3>(dh).type==GRILLE) return lcc.template info<3>(dh).color;
      // else {if (lcc.template info<3>(dh).type==GRILLE) return lcc.template info<3>(dh).color;}
    }
      CGAL::Random random((unsigned int)(lcc.darts().index(dh)));
      return get_random_color(random);
  }

  /// @return the color of the face containing dh
  ///  used only if colored_face(alcc, dh)
  template<typename LCC>
  CGAL::IO::Color face_color(const LCC& lcc,
                         typename LCC::Dart_const_handle dh) const
  { 
    if (lcc.template attribute<2>(dh)!=nullptr) {
      if (lcc.template info<2>(dh).type==ROUTE) return lcc.template info<2>(dh).color;
    }
    CGAL::Random random((unsigned int)(lcc.darts().index(dh)));
    return get_random_color(random);
  }

  /// @return true iff the face containing dh is colored.
  ///  if we have also colored_volume(alcc, dh), the volume color is
  ///  ignored and only the face color is considered.
  template<typename LCC>
  bool colored_face(const LCC& lcc,
                    typename LCC::Dart_const_handle dh) const
  { 
    if (lcc.template attribute<2>(dh)!=nullptr) {
      if (lcc.template info<2>(dh).type==ROUTE ) return true;
    }
    return false; }
};