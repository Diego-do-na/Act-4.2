#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/point_generators_3.h>
#include <iostream>
#include <vector>
using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Mesh = CGAL::Surface_mesh<K::Point_3>;
int main() {
    CGAL::Random_points_in_sphere_3<K::Point_3> gen(1.0);
    std::vector<K::Point_3> pts;
    std::copy_n(gen, 10000, std::back_inserter(pts));
    Mesh m;
    CGAL::convex_hull_3(pts.begin(), pts.end(), m);
    std::cout << "V = " << m.number_of_vertices() << ", E = " << m.number_of_edges()
              << ", F = " << m.number_of_faces() << "\n";
}
