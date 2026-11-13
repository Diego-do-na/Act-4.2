// Part 5: "Fence the orchard". Input format as always. Output (3 decimals):
//   h, perimeter, area, diameter (largest distance between two trees), and the pair attaining it.
#include "hull.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

// TODO: area with the shoelace formula (keep it exact: return twice the area as long long)
long long twice_area(const std::vector<Pt>& H) {
    long long total = 0;
    for (size_t i = 0; i < H.size(); i++){
        const Pt& a = H[i];
        const Pt& b = (i == H.size() - 1) ? H[0] : H[i + 1];
        total += a.x * b.y - b.x * a.y;
    }
    return total;
}

// TODO: perimeter of the hull
double perimeter(const std::vector<Pt>& H) { 
    double total = 0;
    for (size_t i = 0; i < H.size(); i++){
        const Pt& a = H[i];
        const Pt& b = (i == H.size() - 1) ? H[0] : H[i + 1];
        total += std::sqrt((double)dist2(a, b));
    }
    return total;
}

// TODO: squared diameter with rotating calipers in O(h). Store the farthest pair in a, b.
long long diameter2(const std::vector<Pt>& H, Pt& a, Pt& b) {
    if (H.size() == 0) {
        return 0;
    }
    a = b = H[0];
    if (H.size() == 1) {
        return 0;
    }

    long long best = 0;
    size_t farthest = 1;

    for (size_t i = 0; i < H.size(); i++){
        size_t next = (i == H.size() - 1) ? 0 : i + 1;

        while (true) {
            size_t next_farthest = (farthest == H.size() - 1) ? 0 : farthest + 1;
            if (orient(H[i], H[next], H[next_farthest]) > orient(H[i], H[next], H[farthest])) {
                farthest = next_farthest;
            } else {
                break;
            }
        }

        if (dist2(H[i], H[farthest]) > best) {
            best = dist2(H[i], H[farthest]);
            a = H[i];
            b = H[farthest];
        }
        if (dist2(H[next], H[farthest]) > best) {
            best = dist2(H[next], H[farthest]);
            a = H[next];
            b = H[farthest];
        }
    }
    return best;
}

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
