// Random test generators (Parts 3 and 4). All coordinates fit in |x|,|y| <= 1e9.
#pragma once
#include "hull.hpp"
#include <random>
#include <set>
#include <string>
inline std::vector<Pt> gen(const std::string& dist, int n, unsigned seed) {
    std::mt19937_64 g(seed);
    std::vector<Pt> P;
    std::uniform_int_distribution<long long> u(-1000000000LL, 1000000000LL);
    if (dist == "square") {                       // uniform in a square: h grows like log n
        for (int i = 0; i < n; i++) P.push_back({u(g), u(g)});
    } else if (dist == "disk") {                  // uniform in a disk: h grows like n^(1/3)
        while ((int)P.size() < n) {
            long long x = u(g), y = u(g);
            if ((long double)x * x + (long double)y * y <= 1e18L) P.push_back({x, y});
        }
    } else {                                      // "parabola": every point is on the hull (h = n), n <= 60001
        std::set<long long> xs;
        std::uniform_int_distribution<long long> v(-30000, 30000);
        while ((int)xs.size() < n) xs.insert(v(g));
        for (long long x : xs) P.push_back({x, x * x});
        std::shuffle(P.begin(), P.end(), g);
    }
    return P;
}
