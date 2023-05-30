#define CGAL_EIGEN3_ENABLED

#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <vector>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <CGAL/subdivision_method_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_3.h>
#include <CGAL/boost/graph/graph_traits_Surface_mesh.h>
#include <boost/foreach.hpp>
#include <CGAL/Surface_mesh_parameterization/IO/File_off.h>
#include <CGAL/Surface_mesh_parameterization/parameterize.h>
#include <CGAL/Polygon_mesh_processing/measure.h>
#include <CGAL/Surface_mesh_simplification/edge_collapse.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_ratio_stop_predicate.h>
#include <igl/PI.h>
#include <CGAL/Dimension.h>
#include <iostream>
#include <fstream>
#include <CGAL/Surface_mesh_parameterization/Circular_border_parameterizer_3.h>
#include <CGAL/Surface_mesh_parameterization/Discrete_authalic_parameterizer_3.h>
#include <CGAL/Surface_mesh_parameterization/Error_code.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include <CGAL/Polyhedron_3.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_3> SurfaceMesh;

class PolyMesh {
    private:
        std::vector<double> vertices;
        std::vector<int> faces;
        SurfaceMesh mesh;
        // SurfaceMesh triangulatedMesh;
    public:
        Kernel::Point_3 sdf_p = Kernel::Point_3(0, 4, 0);
        PolyMesh() {
            std::cout << "created mesh" << std::endl;
        }
        //CGAL::SM_Vertex_index
        int addVertex(double x, double y, double z) {
            auto v0 = mesh.add_vertex(Kernel::Point_3(x, y, z));
            return v0.idx();
        }
        int addFace(emscripten::val vertices){
            std::vector<SurfaceMesh::vertex_index> faceVerts;
            for (int i = 0; i < vertices["length"].as<int>(); i++) {
                faceVerts.push_back(mesh.vertices().begin()[vertices[i].as<int>()]);
            }
            auto fc = mesh.add_face(faceVerts);
            return fc.idx();
        }
        void triangulate(SurfaceMesh & targetMesh){
            CGAL::Polygon_mesh_processing::triangulate_faces(targetMesh);
        }
        void catmull_smooth(){
            CGAL::Subdivision_method_3::CatmullClark_subdivision(mesh, 1);
        }
        void loop_smooth(){
            CGAL::Subdivision_method_3::Loop_subdivision(mesh, 1);
        }
        void dooSabin_smooth(){
            CGAL::Subdivision_method_3::DooSabin_subdivision(mesh, 1);
        }
        void sqrt_smooth(){
            CGAL::Subdivision_method_3::Sqrt3_subdivision(mesh, 1);
        }
        void decimate(double stop_ratio){
            namespace SMS = CGAL::Surface_mesh_simplification;
            std::cout << "decimate stop ratio" << stop_ratio << std::endl;
            SMS::Count_ratio_stop_predicate<SurfaceMesh> stop(stop_ratio);
            int r = SMS::edge_collapse(mesh, stop);
            std::cout << "\nFinished!\n" << r << " edges removed.\n" << mesh.number_of_edges() << " final edges.\n";
        }
        
        static void defineSDF(emscripten::val call_back){
            // auto m = call_back().as<int>();
            //call_back["length"].as<int>();
            // std::cout<<"ping callback: "<<m<<std::endl;
            // call_back();

        }

        void parametizeMesh(){
            typedef Kernel::Point_2 Point_2;
            typedef Kernel::Point_3 Point_3;

            typedef boost::graph_traits<SurfaceMesh>::vertex_descriptor     vertex_descriptor;
            typedef boost::graph_traits<SurfaceMesh>::halfedge_descriptor   halfedge_descriptor;
            typedef boost::graph_traits<SurfaceMesh>::face_descriptor       face_descriptor;

            namespace SMP = CGAL::Surface_mesh_parameterization;
            halfedge_descriptor bhd = CGAL::Polygon_mesh_processing::longest_border(mesh).first;
            // The UV property map that holds the parameterized values
            typedef SurfaceMesh::Property_map<vertex_descriptor, Point_2>  UV_pmap;
            std::cout << "before parametization" << std::endl;
            UV_pmap uv_map = mesh.add_property_map<vertex_descriptor, Point_2>("h:uv").first;
            
            typedef SMP::Circular_border_arc_length_parameterizer_3<SurfaceMesh>  Border_parameterizer;
            typedef SMP::Discrete_authalic_parameterizer_3<SurfaceMesh, Border_parameterizer> Parameterizer;

            SMP::parameterize(mesh, Parameterizer(), bhd, uv_map);
            std::cout << "after parametization" << std::endl;
            for(auto uv : uv_map){
                std::cout<<uv.x()<<" "<<uv.y()<<std::endl;
            }
        }

        emscripten::val getIndices(){
            std::vector<int> indices;
            SurfaceMesh triangulatedMesh = mesh;
            if(!this->isTriangulated(mesh)){
                std::cout<<"non-triangular mesh, triangulating..."<<std::endl;
                this->triangulate(triangulatedMesh); //triangulate first
            }
            
             for(auto faceIt = triangulatedMesh.faces_begin(); faceIt != triangulatedMesh.faces_end(); ++faceIt){
                //get the vertices of the face
                auto halfedgeIt = triangulatedMesh.halfedge(*faceIt);
                auto halfedgeIt2 = triangulatedMesh.next(halfedgeIt);
                auto halfedgeIt3 = triangulatedMesh.next(halfedgeIt2);
                auto vertexIt = triangulatedMesh.target(halfedgeIt);
                auto vertexIt2 = triangulatedMesh.target(halfedgeIt2);
                auto vertexIt3 = triangulatedMesh.target(halfedgeIt3);
                indices.push_back(vertexIt.idx());
                indices.push_back(vertexIt2.idx());
                indices.push_back(vertexIt3.idx());
            }
            triangulatedMesh.clear();
            triangulatedMesh.collect_garbage();
            return emscripten::val(emscripten::typed_memory_view(indices.size(), indices.data()));
        }

        bool isTriangulated(const SurfaceMesh& mesh) {
            for (const auto& f : mesh.faces()) {
                if (mesh.degree(f) != 3) {
                    return false;  // Face does not have 3 vertices, not triangulated
                }
            }
            return true;
        }

        emscripten::val getVertices(){
            std::vector<double> vertices;
            for(auto vertexIt = mesh.vertices_begin(); vertexIt != mesh.vertices_end(); ++vertexIt){
                auto point = mesh.point(*vertexIt);
                vertices.push_back(point.x());
                vertices.push_back(point.y());
                vertices.push_back(point.z());
            }
            return emscripten::val(emscripten::typed_memory_view(vertices.size(), vertices.data()));
        }

        emscripten::val segment(int n_clusters, double sm_lambda){
            typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
            
            typedef boost::graph_traits<SurfaceMesh>::vertex_descriptor vertex_descriptor;
            typedef boost::graph_traits<SurfaceMesh>::face_descriptor face_descriptor;

            // create a property-map
            typedef SurfaceMesh::Property_map<face_descriptor,double> Facet_double_map;
            Facet_double_map sdf_property_map;
            sdf_property_map = mesh.add_property_map<face_descriptor,double>("f:sdf").first;
            // compute SDF values
            // We can't use default parameters for number of rays, and cone angle
            // and the postprocessing
            std::cout<<"before sdf values"<<std::endl;
            CGAL::sdf_values(mesh, sdf_property_map, 2.0 / 3.0 * CGAL_PI, 25, true);
            // create a property-map for segment-ids
            typedef SurfaceMesh::Property_map<face_descriptor, std::size_t> Facet_int_map;
            Facet_int_map segment_property_map = mesh.add_property_map<face_descriptor,std::size_t>("f:sid").first;;

            const std::size_t number_of_clusters = n_clusters;       // use 4 clusters in soft clustering
            const double smoothing_lambda = sm_lambda;  // importance of surface features, suggested to be in-between [0,1]

            std::size_t number_of_segments;
            if(n_clusters == 0 && sm_lambda == 0)
            {
                std::cout<<"using default parameters"<<std::endl;
                number_of_segments = CGAL::segmentation_from_sdf_values(mesh, sdf_property_map, segment_property_map);
            } else
            {
                std::cout<<"using custom parameters"<<std::endl;
                number_of_segments = CGAL::segmentation_from_sdf_values(mesh, sdf_property_map, segment_property_map, number_of_clusters, smoothing_lambda);
            }
            std::cout<<"sdf values"<<std::endl;
            std::cout << "Number of segments: " << number_of_segments << std::endl;
            //get face descriptor os surfacemesh
            std::vector<int> segments;
            for(auto faceIt = mesh.faces_begin(); faceIt != mesh.faces_end(); ++faceIt){
                std::cout << segment_property_map[*faceIt] << " ";
                segments.push_back(segment_property_map[*faceIt]);
            }
            std::cout << std::endl;
            return emscripten::val(emscripten::typed_memory_view(segments.size(), segments.data()));
        }
};

EMSCRIPTEN_BINDINGS(my_module) {
  emscripten::class_<PolyMesh>("PolyMesh")
    .constructor<>()
    .function("addVertex", &PolyMesh::addVertex, emscripten::allow_raw_pointers())
    .function("addFace", &PolyMesh::addFace, emscripten::allow_raw_pointers())
    .function("getIndices", &PolyMesh::getIndices, emscripten::allow_raw_pointers())
    .function("getVertices", &PolyMesh::getVertices, emscripten::allow_raw_pointers())
    .function("parametizeMesh", &PolyMesh::parametizeMesh, emscripten::allow_raw_pointers())
    .function("catmull_smooth", &PolyMesh::catmull_smooth, emscripten::allow_raw_pointers())
    .function("loop_smooth", &PolyMesh::loop_smooth, emscripten::allow_raw_pointers())
    .function("sqrt_smooth", &PolyMesh::sqrt_smooth, emscripten::allow_raw_pointers())
    .function("dooSabin_smooth", &PolyMesh::dooSabin_smooth, emscripten::allow_raw_pointers())
    .function("segment", &PolyMesh::segment, emscripten::allow_raw_pointers())
    .function("decimate", &PolyMesh::decimate, emscripten::allow_raw_pointers());
}