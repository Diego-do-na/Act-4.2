// Part 0: check that CGAL works. Reads the same input format and prints the hull.
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <iostream>
#include <vector>
using K  = CGAL::Exact_predicates_inexact_constructions_kernel;
using P2 = K::Point_2;
int main() {
    int n; std::cin >> n;
    std::vector<P2> in, out;
    for (int i = 0; i < n; i++) { double x, y; std::cin >> x >> y; in.emplace_back(x, y); }
    CGAL::convex_hull_2(in.begin(), in.end(), std::back_inserter(out));
    std::cout << out.size() << "\n";
    for (const P2& p : out) std::cout << p << "\n";   // counter-clockwise, CGAL picks the start
}
