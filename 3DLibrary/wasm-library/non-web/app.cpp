// #define CGAL_GMP_H
/*#define CGAL_GMP_H 1
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <fstream>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;
int main()
{
  // create and read Polyhedron
  Polyhedron mesh;
  std::ifstream input(CGAL::data_file_path("meshes/cactus.off"));
  if ( !input || !(input >> mesh) || mesh.empty() || ( !CGAL::is_triangle_mesh(mesh)) )
  {
    std::cerr << "Input is not a triangle mesh" << std::endl;
    return EXIT_FAILURE;
  }
  // create a property-map
  typedef std::map<face_descriptor, double> Face_double_map;
  Face_double_map internal_map;
  boost::associative_property_map<Face_double_map> sdf_property_map(internal_map);
  // compute SDF values
  std::pair<double, double> min_max_sdf = CGAL::sdf_values(mesh, sdf_property_map);
  // It is possible to compute the raw SDF values and post-process them using
  // the following lines:
  // const std::size_t number_of_rays = 25;  // cast 25 rays per face
  // const double cone_angle = 2.0 / 3.0 * CGAL_PI; // set cone opening-angle
  // CGAL::sdf_values(mesh, sdf_property_map, cone_angle, number_of_rays, false);
  // std::pair<double, double> min_max_sdf =
  //  CGAL::sdf_values_postprocessing(mesh, sdf_property_map);
  // print minimum & maximum SDF values
  std::cout << "minimum SDF: " << min_max_sdf.first
            << " maximum SDF: " << min_max_sdf.second << std::endl;
  // print SDF values
  for(face_descriptor f : faces(mesh))
      std::cout << sdf_property_map[f] << " ";
  std::cout << std::endl;
  return EXIT_SUCCESS;
}*/

/*
#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Gmpfi.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <fstream>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;

// typedef CGAL::Simple_cartesian<double> Kernel;
// typedef Kernel::Point_2 Point_2;
int main()
{

   // create and read Polyhedron
  Polyhedron mesh;
  std::ifstream input(CGAL::data_file_path("meshes/cactus.off"));
  if ( !input || !(input >> mesh) || mesh.empty() || ( !CGAL::is_triangle_mesh(mesh)) )
  {
    std::cerr << "Input is not a triangle mesh" << std::endl;
    return EXIT_FAILURE;
  }
  // create a property-map
  typedef std::map<face_descriptor, double> Face_double_map;
  Face_double_map internal_map;
  boost::associative_property_map<Face_double_map> sdf_property_map(internal_map);
  // compute SDF values
  std::pair<double, double> min_max_sdf = CGAL::sdf_values(mesh, sdf_property_map);
  // It is possible to compute the raw SDF values and post-process them using
  // the following lines:
  // const std::size_t number_of_rays = 25;  // cast 25 rays per face
  // const double cone_angle = 2.0 / 3.0 * CGAL_PI; // set cone opening-angle
  // CGAL::sdf_values(mesh, sdf_property_map, cone_angle, number_of_rays, false);
  // std::pair<double, double> min_max_sdf =
  //  CGAL::sdf_values_postprocessing(mesh, sdf_property_map);
  // print minimum & maximum SDF values
  std::cout << "minimum SDF: " << min_max_sdf.first
            << " maximum SDF: " << min_max_sdf.second << std::endl;
  // print SDF values
  for(face_descriptor f : faces(mesh))
      std::cout << sdf_property_map[f] << " ";
  std::cout << std::endl;

  // {
  //   Point_2 p(0, 0.3), q(1, 0.6), r(2, 0.9);
  //   std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
  // }
  // {
  //   Point_2 p(0, 1.0/3.0), q(1, 2.0/3.0), r(2, 1);
  //   std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
  // }
  // {
  //   Point_2 p(0,0), q(1, 1), r(2, 2);
  //   std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
  // }
  std::cout << "Hello World!\n" << std::endl;
  return 0;
}*/

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>
#include <CGAL/Labeled_mesh_domain_3.h>
#include <CGAL/make_mesh_3.h>
// Domain
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT FT;
typedef K::Point_3 Point;
typedef FT (Function)(const Point&);
typedef CGAL::Labeled_mesh_domain_3<K> Mesh_domain;
#ifdef CGAL_CONCURRENT_MESH_3
typedef CGAL::Parallel_tag Concurrency_tag;
#else
typedef CGAL::Sequential_tag Concurrency_tag;
#endif
// Triangulation
typedef CGAL::Mesh_triangulation_3<Mesh_domain,CGAL::Default,Concurrency_tag>::type Tr;
typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;
// Criteria
typedef CGAL::Mesh_criteria_3<Tr> Mesh_criteria;
// To avoid verbose function and named parameters call
using namespace CGAL::parameters;
// Function
FT sphere_function (const Point& p)
{ return CGAL::squared_distance(p, Point(CGAL::ORIGIN))-1; }
int main()
{
  Mesh_domain domain =
    Mesh_domain::create_implicit_mesh_domain(sphere_function,
                                             K::Sphere_3(CGAL::ORIGIN, 2.));
  // Mesh criteria
  Mesh_criteria criteria(facet_angle=30, facet_size=0.1, facet_distance=0.025,
                         cell_radius_edge_ratio=2, cell_size=0.1);
  // Mesh generation
  C3t3 c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria);
  // Output
  std::ofstream medit_file("out.mesh");
  c3t3.output_to_medit(medit_file);
  return 0;
}