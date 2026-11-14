// Part 3: compare your implementations with CGAL on thousands of random inputs.
#include "hull.hpp"
#include "gen.hpp"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <algorithm>
#include <iostream>
using K  = CGAL::Exact_predicates_inexact_constructions_kernel;
using P2 = K::Point_2;

std::vector<Pt> cgal_hull(const std::vector<Pt>& P) {
    std::vector<P2> in, out;
    for (auto& p : P) in.emplace_back((double)p.x, (double)p.y);   // exact: |coords| <= 1e9 < 2^53
    CGAL::convex_hull_2(in.begin(), in.end(), std::back_inserter(out));
    std::vector<Pt> H;
    for (auto& q : out) H.push_back({(long long)q.x(), (long long)q.y()});
    // CGAL returns the hull in counter-clockwise order but may start at any vertex.
    // Rotate it so it starts at the lowest point (smallest y, ties smallest x),
    // using the same operator< as our convention. Safe for empty H.
    std::rotate(H.begin(), std::min_element(H.begin(), H.end()), H.end());
    return H;
}

int main() {
    int failures = 0;
    for (unsigned seed = 0; seed < 1000; seed++)
        for (std::string d : {"square", "disk", "parabola"}) {
            int n = 1 + seed % 300;
            auto P = gen(d, n, seed);
            // Degenerate cases, chosen by seed % 4:
            //   0 -> plain random input
            //   1 -> with duplicated points
            //   2 -> with 5 collinear points on the bottom edge
            //   3 -> both duplicates and collinear points
            int kind = seed % 4;
            if (kind == 1 || kind == 3) {
                // Duplicate every third point (and repeat the first one once more).
                size_t m = P.size();
                for (size_t k = 0; k < m; k += 3) P.push_back(P[k]);
                P.push_back(P[0]);
            }
            if (kind == 2 || kind == 3) {
                // y = -1e9 is the smallest possible coordinate, so these 5 points lie on the
                // bottom hull edge. Only (-1000,-1e9) and (1000,-1e9) are extreme; the 3 in the
                // middle must NOT be reported. The leftmost one must also be the start point.
                for (long long k = 0; k <= 4; k++) P.push_back({-1000 + 500 * k, -1000000000LL});
            }
            // Shuffle so the extra points are not always at the end of the input.
            std::mt19937 rng(seed);
            std::shuffle(P.begin(), P.end(), rng);
            auto C = cgal_hull(P);
            if (graham(P) != C || jarvis(P) != C) {
                if (++failures <= 5) std::cout << "mismatch: dist=" << d << " n=" << n << " seed=" << seed << "\n";
            }
        }
    std::cout << (failures ? "FAILED: " : "OK: ") << failures << " mismatches\n";
}
