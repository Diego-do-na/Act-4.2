// Part 5: "Fence the orchard". Input format as always. Output (3 decimals):
//   h, perimeter, area, diameter (largest distance between two trees), and the pair attaining it.
#include "hull.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

// TODO: area with the shoelace formula (keep it exact: return twice the area as long long)
long long twice_area(const std::vector<Pt>& H) { return 0; }

// TODO: perimeter of the hull
double perimeter(const std::vector<Pt>& H) { return 0; }

// TODO: squared diameter with rotating calipers in O(h). Store the farthest pair in a, b.
long long diameter2(const std::vector<Pt>& H, Pt& a, Pt& b) { return 0; }

int main() {
    int n; std::cin >> n;
    std::vector<Pt> P(n);
    for (auto& p : P) std::cin >> p.x >> p.y;
    auto H = graham(P);
    Pt a{0, 0}, b{0, 0};
    long long d2 = diameter2(H, a, b);
    std::cout << std::fixed << std::setprecision(3)
              << "h = " << H.size() << "\nperimeter = " << perimeter(H)
              << "\narea = " << twice_area(H) / 2.0 << "\ndiameter = " << std::sqrt((double)d2)
              << "  between (" << a.x << ", " << a.y << ") and (" << b.x << ", " << b.y << ")\n";
}
